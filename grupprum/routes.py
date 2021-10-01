from flask import request, render_template, redirect, url_for, session
from grupprum import app, db

@app.route("/")
@app.route("/home")
def home():

    all_users = db.child("test").get()
    data = all_users.val()
    print(data)
    return "{}".format(data)
