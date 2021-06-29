var connectionURL = "http://10.22.68.76:5000"
var email;
var phsyio_email;
var patient_email;

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

async function displayData(){
    let patient = await getPatient();
    var container = document.querySelector(".container");
    container.append(drawPatientData(patient));
}

function goToEmailPage(){
    // sessionStorage.clear();
    sessionStorage.setItem("patient_email", patient_email);
    sessionStorage.setItem("physio_email", physio_email);

    window.location = "patientmessageform.html";
}

window.onload = function() {
    email = sessionStorage.getItem("patient_email");
    setTimeout(function(){
        displayData();
    },1000);
};
