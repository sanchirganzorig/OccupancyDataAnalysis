from flask import request, render_template, redirect, url_for, session
from grupprum_flask import app, db
from datetime import datetime
import math

@app.route("/")
@app.route("/home")
def home():
    unread_logs = db.child("Ebb").get()

    log0 = round(unread_logs.val()['log0']/1000)

    return "{}".format(log0)

@app.route("/receive", methods=["POST"])
def receive():
    data = request.json()
    print(data)

    return "receive"
