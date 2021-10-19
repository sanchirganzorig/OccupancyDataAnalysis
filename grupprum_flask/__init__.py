from flask import Flask
from flask_sqlalchemy import SQLAlchemy
from config import secrets
import pyrebase

app = Flask(__name__)
app.config["SQLALCHEMY_TRACK_MODIFICATIONS"] = False

config = {
  "apiKey": secrets["apiKey"],
  "authDomain": secrets["authDomain"],
  "databaseURL": secrets["databaseURL"],
  "storageBucket": secrets["storageBucket"]
}

firebase = pyrebase.initialize_app(config)
db = firebase.database()

from grupprum_flask import routes
