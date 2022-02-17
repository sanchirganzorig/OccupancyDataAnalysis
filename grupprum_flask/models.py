from grupprum_flask import db

class Logs(db.Model):
    id = db.Column(db.Integer, primary_key=True, unique=True)
    room = db.Column(db.String)
    time = db.Column(db.Integer)

    def __repr__(self):
        return "Rooms(%s, %s, %s)" % (self.id, self.room, self.time)
