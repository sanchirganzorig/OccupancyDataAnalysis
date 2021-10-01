from flask import Flask
from flask_sqlalchemy import SQLAlchemy
import pyrebase

app = Flask(__name__)
app.config["SQLALCHEMY_TRACK_MODIFICATIONS"] = False

config = {
  "apiKey": "AIzaSyADClPAYMpIZCEPikuOC4hTwQ1Xos6TMM4",
  "authDomain": "grupprum-218a1.firebaseapp.com",
  "databaseURL": "https://grupprum-218a1-default-rtdb.europe-west1.firebasedatabase.app",
  "storageBucket": "grupprum-218a1.appspot.com/"
}

firebase = pyrebase.initialize_app(config)
db = firebase.database()


from grupprum import routes
