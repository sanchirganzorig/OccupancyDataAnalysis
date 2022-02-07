from flask import request, render_template, redirect, url_for, session
from grupprum_flask import app
from datetime import datetime
import math

@app.route("/")
@app.route("/home")
def home():
    # ebblog = round(db.reference("Ebb").get()/1000)
    # now = round(datetime.now().timestamp())
    #
    # print("log: " + str(ebblog))
    # print("now: " + str(now))
    # print("difference in seconds: " + str(now - ebblog))
    #
    # if now - ebblog > 60:
    #     ebbstate = True
    # else:
    #     ebbstate = False

    return "home"

@app.route("/log", methods=["POST"])
def log():

    print(request)
    return "POST request got"
# @app.route("/receive", methods=["POST"])
# def receive():
    # data = request.json()
    # print(data)
    #
    # return "receive"
