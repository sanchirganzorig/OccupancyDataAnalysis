/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp32-firebase-realtime-database/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
  Based in the RTDB Basic Example by Firebase-ESP-Client library by mobizt
  https://github.com/mobizt/Firebase-ESP-Client/blob/main/examples/RTDB/Basic/Basic.ino
*/

#include "config.h"
#include <Arduino.h>
#if defined(ESP32)
  #include <WiFi.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
  #include <ESP8266HTTPClient.h>
#endif
#include <Firebase_ESP_Client.h>

//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
//#define WIFI_SSID "comhem_EADC05"
//#define WIFI_PASSWORD "y9734z3m"
//#define WIFI_SSID "AREA51"
//#define WIFI_PASSWORD "tegcbx06"

#define RUM "Ebb"

//Define Firebase Data object
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
String uid;

int count = 0;
bool signupOK = false;

boolean PIRstate ; //variable to store PIR state
boolean lastPIRstate = HIGH;
int PIR = 2; //PIR connected to GPIO 0



void setup(){
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  pinMode(PIR, INPUT_PULLUP);
  
  lastPIRstate = 0;

  config.host = FIREBASE_HOST;
  config.api_key = API_KEY;

  //Assign the user sign in credentials
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  //Initialize the library with the Firebase authen and config.
  Firebase.begin(&config, &auth);


  /* Assign the api key (required) */
//  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
 // config.database_url = DATABASE_URL;

  /* Sign up */
  /*if (Firebase.signUp(&config, &auth, "", "")){
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }*/
  
  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  Firebase.reconnectWiFi(true);

    // Getting the user UID might take a few seconds
  Serial.println("Getting User UID");
  while ((auth.token.uid) == "") {
    Serial.print('.');
    delay(1000);
  }
  // Print user UID
  uid = auth.token.uid.c_str();
  Serial.print("User UID: ");
  Serial.print(uid);
}

void loop(){
  if (Firebase.ready())
  {
    PIRstate = digitalRead(PIR);

     Serial.print("PIRstate: ");
     Serial.println(PIRstate);
    
    if (PIRstate != lastPIRstate){
      if (Firebase.RTDB.setTimestamp(&fbdo, String(RUM)))
      {
        Serial.println("PASSED");
        Serial.println("NEW PATH: " + fbdo.dataPath());
        count++;
      }
      else{
        Serial.println("FAILED");
        Serial.println("REASON: " + fbdo.errorReason());
      }
    
      lastPIRstate = PIRstate;
    }
    delay(300);
  }
 /* if (Firebase.ready() && signupOK && digitalRead(PIR) == HIGH)
  {
    if (Firebase.RTDB.setTimestamp(&fbdo, String(TIMEPATH) + "/log" + String(count)))
    {
      Serial.println("PASSED");
      Serial.println("NEW PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else{
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
    ++count;
    delay(500);
  } */
}
