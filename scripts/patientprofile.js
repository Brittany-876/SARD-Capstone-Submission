var connectionURL = "http://172.16.188.47:5000"
var email;
var phsyio_email;
var patient_email;
var PatientID;

function drawPatientData(patient){
    physio_email = patient.physiotherapistemail;
    patient_email = patient.email;
    
    var card = document.createElement("DIV");
    card.classList.add("card");

    var name = document.createElement("H1");
    name.innerHTML = patient.firstName + " " + patient.lastName;

    var PatientID = document.createElement("H5");
    PatientID.innerHTML = "ID Number: " + patient.PatientID;

    var DOB = document.createElement("H5");
    DOB.innerHTML = "Date of Birth: " + patient.DOB;

    var email = document.createElement("H5");
    email.innerHTML = "Email Address: " + patient.email;

    var physiotherapistemail = document.createElement("H5");
    physiotherapistemail.innerHTML = "Physiotherapist's Email Address: " + patient.physiotherapistemail;

    var btn = document.createElement("button");
    btn.innerHTML = "Message My Physiotherapist";
    btn.setAttribute("onclick", "goToEmailPage()");

    card.append(name);
    card.append(PatientID);
    card.append(DOB);
    card.append(email);
    card.append(physiotherapistemail);
    card.append(btn);

    return card;
}

function getPatient(){
    return fetch(connectionURL.concat("/patient/").concat(email))
    .then((res) => res.json())
    .then((json) => json);
}

function getRecords(){
    return fetch(connectionURL.concat("/record"))
    .then((res) => res.json())
    .then((json) => json);
}

async function getSpecificRecords() {
    let records = await getRecords();

    records.forEach((record) => {
        if(record.PatientID === PatientID){
            console.log(record);
            addTableBody(record);
        }
    });
}

async function displayData(){
    let patient = await getPatient();
    PatientID = patient.PatientID; 
    var container = document.querySelector(".container");
    container.append(drawPatientData(patient));
}

function addTableHead(){
    var table = document.getElementById("recordTable");
    var header = table.createTHead();
    var row = header.insertRow(0);

    var exerciseTypeHead = row.insertCell(0);
    exerciseTypeHead.classList.add("head-row");

    var angleShiftHead = row.insertCell(1);
    angleShiftHead.classList.add("head-row");

    var setsHead = row.insertCell(2);
    setsHead.classList.add("head-row");

    var repsHead = row.insertCell(3);
    repsHead.classList.add("head-row");

    var timeUpdatedHead = row.insertCell(4);
    timeUpdatedHead.classList.add("head-row");

    exerciseTypeHead.innerHTML = "Exercise Type";
    angleShiftHead.innerHTML = "Angle Shift";
    setsHead.innerHTML = "Sets"; 
    repsHead.innerHTML = "Reps"; 
    timeUpdatedHead.innerHTML = "Date & Time";
}

function addTableBody(record){
    var table = document.getElementById("recordTable");

    var row = table.insertRow(0);

    var exerciseTypeContent = row.insertCell(0);
    var angleShiftContent = row.insertCell(1);
    var setsContent = row.insertCell(2);
    var repsContent = row.insertCell(3);
    var timeUpdatedContent = row.insertCell(4)

    exerciseTypeContent.innerHTML = record.exerciseType;
    angleShiftContent.innerHTML = record.angleShift;
    setsContent.innerHTML = record.sets; 
    repsContent.innerHTML = record.reps;
    timeUpdatedContent.innerHTML = record.timeUpdated;
}

function goToEmailPage(){
    // sessionStorage.clear();
    sessionStorage.setItem("patient_email", patient_email);
    sessionStorage.setItem("physio_email", physio_email);

    window.location = "patientmessageform.html";
}

window.onload = function() {
    email = sessionStorage.getItem("patient_email");
    //PatientID = sessionStorage.getItem("PatientID");
        displayData();
        getSpecificRecords();
    
        setTimeout( function(){
            addTableHead();
       }, 1000);

};
