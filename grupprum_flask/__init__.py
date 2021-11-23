from flask import Flask
from flask_sqlalchemy import SQLAlchemy
from config import secrets
import pyrebase
import firebase_admin
from firebase_admin import credentials
from firebase_admin import db

app = Flask(__name__)
app.config["SQLALCHEMY_TRACK_MODIFICATIONS"] = False

# config = {
#   "apiKey": secrets["apiKey"],
#   "authDomain": secrets["authDomain"],
#   "databaseURL": secrets["databaseURL"],
#   "storageBucket": secrets["storageBucket"]
# }


cred = credentials.Certificate(secrets["GOOGLE_APPLICATION_CREDENTIALS"])
firebase_admin.initialize_app(cred, {'databaseURL': secrets["databaseURL"]})

from grupprum_flask import routes
