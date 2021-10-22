/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp32-firebase-realtime-database/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
  Based in the RTDB Basic Example by Firebase-ESP-Client library by mobizt
  https://github.com/mobizt/Firebase-ESP-Client/blob/main/examples/RTDB/Basic/Basic.ino
*/

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
#define WIFI_SSID "TEKNIK"
#define WIFI_PASSWORD "sanchir21"

// Insert Firebase project API Key
#define API_KEY "AIzaSyADClPAYMpIZCEPikuOC4hTwQ1Xos6TMM4"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "grupprum-218a1-default-rtdb.europe-west1.firebasedatabase.app" 

#define RUM "Ebb"
#define TIMEPATH "/" + String(RUM)

//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

int count = 0;
bool signupOK = false;

boolean PIRstate ; //variable to store PIR state
boolean lastPIRstate = HIGH;
int PIR = 2; //PIR connected to GPIO 0



void setup(){
  Serial.begin(115200);
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

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")){
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }
  
  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop(){
  if (Firebase.ready() && signupOK)
  {
    PIRstate = digitalRead(PIR);

     Serial.println("PIRstate: ");
      Serial.print(PIRstate);
    
    
    if (PIRstate != lastPIRstate){
      if (Firebase.RTDB.setTimestamp(&fbdo, String(TIMEPATH) + "/log" + String(count)))
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
