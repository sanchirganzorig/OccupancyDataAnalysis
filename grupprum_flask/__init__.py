from flask import Flask
from flask_sqlalchemy import SQLAlchemy
from config import secrets

app = Flask(__name__)
app.config["SQLALCHEMY_TRACK_MODIFICATIONS"] = False

# config = {
#   "apiKey": secrets["apiKey"],
#   "authDomain": secrets["authDomain"],
#   "databaseURL": secrets["databaseURL"],
#   "storageBucket": secrets["storageBucket"]
# }



from grupprum_flask import routes
