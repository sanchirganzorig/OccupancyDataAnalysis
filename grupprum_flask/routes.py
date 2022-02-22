from flask import request, render_template, redirect, url_for, session
from grupprum_flask import app, db
from grupprum_flask.models import Logs
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

    log1 = Logs(room="rum", time=1)

    print(log1)

    #db.session.add(log1)
    #print("added")
    #db.session.commit()
    #print("commited")

    return "home"

@app.route('/testdb')
def testdb():
    try:
        db.session.query("1").from_statement("SELECT 1").all()
        return '<h1>It works.</h1>'
    except:
        return '<h1>Something is broken.</h1>'

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
