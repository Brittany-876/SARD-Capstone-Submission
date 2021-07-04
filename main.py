#from dns import message
from flask import Flask, request, jsonify, json, render_template, flash, redirect, session, url_for
from flask_pymongo import PyMongo
from marshmallow import Schema, fields, ValidationError
from flask_cors import CORS
from flask_mail import Mail, Message
from bson.json_util import dumps
from json import loads
from datetime import datetime

#from decouple import config
#import bcrypt

app = Flask(__name__)


CORS(app)
app.config["MONGO_URI"] = "mongodb+srv://Brittany:Brittany@cluster0.epheo.mongodb.net/SARD?retryWrites=true&w=majority"
mongo = PyMongo(app)


db_operations_patients = mongo.db.patients
db_operations_physiotherapists = mongo.db.physiotherapists
db_operations_records = mongo.db.records

class PhysiotherapistSchema(Schema):
    firstName = fields.String(required=True)
    lastName = fields.String(required=True)
    email = fields.String(required=True)
    DOB = fields.String(required=True)
    password1 = fields.String(required=True)
    password2 = fields.String(required=True)


class PatientSchema(Schema):
    PatientID = fields.Number(required=True)
    firstName = fields.String(required=True)
    lastName = fields.String(required=True)
    email = fields.String(required=True)
    DOB = fields.String(required=True)
    physiotherapistemail = fields.String(required=True)
    password1 = fields.String(required=True)
    password2 = fields.String(required=True)

class RecordSchema(Schema):
    PatientID = fields.Number(required=True)
    exerciseType = fields.String(required=True)
    angleShift = fields.String(required=True)
    reps = fields.Number(required=True)
    sets = fields.Number(required=True)
    temperature = fields.String(required=True)
    timeUpdated = fields.String(required=True)
    
    
# @app.route("/register", methods=["GET", "POST"])
# def register():
#     return render_template("register.html")


# @app.route("/login", methods=["GET", "POST"])
# def login():
#     return render_template("login.html")

# Patient Route
@app.route("/patient", methods=["GET", "POST"])
def addPatient():
    if request.method == "POST":
        num1 = db_operations_patients.count()
        num2 = 100000
        num = int(num1) + int(num2) 
        try:
            PatientID = num
            firstName = request.json["firstName"]
            lastName = request.json["lastName"]
            email = request.json["email"]
            DOB = request.json["DOB"]
            physiotherapistemail = request.json["physiotherapistemail"]
            password1 = request.json["password1"]
            password2 = request.json["password2"]

            jsonBody = {
                "PatientID": PatientID,
                "firstName": firstName,
                "lastName": lastName,
                "email": email,
                "DOB": DOB,
                "physiotherapistemail": physiotherapistemail,
                "password1": password1,
                "password2": password2
            }

            newPatient = PatientSchema().load(jsonBody)
            db_operations_patients.insert_one(newPatient)

            return {
                "sucess": True,
                "message": "Patient saved to database successfully!"
            }, 200

        except ValidationError as err1:
            return{
                "sucess": False,
                "message": "An error occurred trying to post patient"
            }, 400

    else:
        patients = db_operations_patients.find()
        return jsonify(loads(dumps(patients))), 200

# Single Patient Route
@app.route("/patient/<path:email>", methods=["GET"])
def getPatient(email):
    filt = {"email": email}
    patient = db_operations_patients.find_one(filt)
    return jsonify(loads(dumps(patient))), 200 

# Physiotherapist Route
@app.route("/physiotherapist", methods=["GET", "POST"])
def addPhysiotherapist():
    if request.method == "POST":
        try:
            firstName = request.json["firstName"]
            lastName = request.json["lastName"]
            email = request.json["email"]
            DOB = request.json["DOB"]
            password1 = request.json["password1"]
            password2 = request.json["password2"]

            jsonBody = {
                "firstName": firstName,
                "lastName": lastName,
                "email": email,
                "DOB": DOB,
                "password1": password1,
                "password2": password2
            }

            newPhysiotherapist = PhysiotherapistSchema().load(jsonBody)
            db_operations_physiotherapists.insert_one(newPhysiotherapist)

            return {
                "sucess": True,
                "message": "Physiotherapist saved to database successfully!"
            }, 200

        except ValidationError as err1:
            return{
                "sucess": False,
                "message": "An error occurred trying to post physiotherapist"
            }, 400

    else:
        physiotherapists = db_operations_physiotherapists.find()
        return jsonify(loads(dumps(physiotherapists))), 200

# Single Physio Route
@app.route("/physiotherapist/<path:email>", methods=["GET"])
def getPhysiotherapist(email):
    filt = {"email": email}
    physiotherapist = db_operations_physiotherapists.find_one(filt)
    return jsonify(loads(dumps(physiotherapist))), 200 

# Patient Records Route
@app.route("/record", methods=["GET", "POST"])
def addPatientRecord():
    if request.method == "POST":
        try:
            PatientID = request.json["PatientID"]
            exerciseType = request.json["exerciseType"]
            angleShift = request.json["angleShift"]
            reps = request.json["reps"]
            sets = request.json["sets"]
            temperature = request.json["temperature"]

            now = datetime.now()
            timeUpdated = now.strftime("%d/%m/%Y %H:%M")

            jsonBody = {
                "PatientID": PatientID,
                "exerciseType": exerciseType,
                "angleShift": angleShift,
                "reps": reps,
                "sets": sets,
                "temperature": temperature,
                "timeUpdated": timeUpdated
            }

            newRecord = RecordSchema().load(jsonBody)
            db_operations_records.insert_one(newRecord)

            return {
                "sucess": True,
                "message": "Record saved to database successfully!"
            }, 200

        except ValidationError as err1:
            return{
                "sucess": False,
                "message": "An error occurred trying to post record"
            }, 400

    else:
        records = db_operations_records.find()
        return jsonify(loads(dumps(records))), 200

@app.route("/")
def home():
    return render_template("index.html")


@app.route("/logout")
def logout():
    return "<p>logout</p>"


if __name__ == '__main__':
    app.config['SECRET_KEY'] = 'hjshjhdjah kjshkjdhjs'
    app.run(debug=True, host="172.16.188.47", port=5000)
