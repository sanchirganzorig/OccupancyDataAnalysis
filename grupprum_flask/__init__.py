from flask import Flask
from flask_sqlalchemy import SQLAlchemy

from config import secrets

app = Flask(__name__)

SQLALCHEMY_DATABASE_URI = "mysql+mysqlconnector://{username}:{password}@{hostname}/{databasename}".format(
    username=secrets["mysqlusername"],
    password=secrets["mysqlpassword"],
    hostname=secrets["mysqlhostname"],
    databasename=secrets["mysqldatabasename"]
)
app.config["SQLALCHEMY_DATABASE_URI"] = SQLALCHEMY_DATABASE_URI
app.config["SQLALCHEMY_POOL_RECYCLE"] = 299
app.config["SECRET_KEY"] = secrets["appsecretkey"]
app.config["SQLALCHEMY_TRACK_MODIFICATIONS"] = False

db = SQLAlchemy(app)
# config = {
#   "apiKey": secrets["apiKey"],
#   "authDomain": secrets["authDomain"],
#   "databaseURL": secrets["databaseURL"],
#   "storageBucket": secrets["storageBucket"]
# }



from grupprum_flask import routes
