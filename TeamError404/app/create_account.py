from flask import Flask, jsonify, request
from flask_cors import CORS
import flask_sqlalchemy as sqlalchemy

import datetime

app = Flask(__name__)
CORS(app)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///sqlalchemy-demo.db'

db = sqlalchemy.SQLAlchemy(app)

class Account(db.Model):
    fname = db.Column(db.String(128), nullable=False)
    lname = db.Column(db.String(128), nullable=False)
    wsuid = db.Column(db.String(9), nullable=False)
    wsuemail = db.Column(db.String(128), nullable=False)
    psword = db.Column(db.String(128), nullable=False)
    phnum = db.Column(db.String(10), nullable=False)
    account_type = db.Column(db.String(1), nullable=False)

base_url = '/api/'


@app.route(base_url + 'accounts', methods=['POST'])
def create_account():
    account = Account(**request.json)      
    db.session.add(account)
    db.session.commit()
    db.session.refresh(account)

    return jsonify({"account": row_to_obj(account), "status": 1}), 200

def row_to_obj(row):
    row = {
            "firstname": row.fname,
            "lname": row.lname,
            "wsuid": row.wsuid,
            "wsuemail": row.wsuemail,
            "psword": row.psword,
            "phnum": row.phnum
        }
    return row


def main():
    db.create_all()
    app.run()            


if __name__ == '__main__':
    main()