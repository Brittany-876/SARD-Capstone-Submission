var connectionURL = "http://10.22.68.76:5000"
var email;

function drawPhysioData(physiotherapist){
    var card = document.createElement("DIV");
    card.classList.add("card");

    var name = document.createElement("H1");
    name.innerHTML = physiotherapist.firstName + " " + physiotherapist.lastName;

    var DOB = document.createElement("H5");
    DOB.innerHTML = "Date of Birth: " + physiotherapist.DOB;

    var email = document.createElement("H5");
    email.innerHTML = "Email Address: " + physiotherapist.email;

    card.append(name);
    card.append(DOB);
    card.append(email);

    return card;
}

function getPhysio(){
    return fetch(connectionURL.concat("/physiotherapist/").concat(email))
    .then((res) => res.json())
    .then((json) => json);
}

function getPatients(){
    return fetch(connectionURL.concat("/patient"))
    .then((res) => res.json())
    .then((json) => json);
}

async function getSpecificPatients() {
    let patients = await getPatients();

    patients.forEach((patient) => {
        if(patient.physiotherapistemail === email){
            addTableBody(patient);
            console.log(patient);
        }
    });
}

async function displayData(){
    let physiotherapist = await getPhysio();
    var container = document.querySelector(".container");
    container.append(drawPhysioData(physiotherapist));
}

function addTableHead(){
    var table = document.getElementById("patientTable");
    var header = table.createTHead();
    var row = header.insertRow(0);

    var patientIDHead = row.insertCell(0);
    patientIDHead.classList.add("head-row");

    var firstNameHead = row.insertCell(1);
    firstNameHead.classList.add("head-row");

    var lastNameHead = row.insertCell(2);
    lastNameHead.classList.add("head-row");

    var actionsHead = row.insertCell(3);
    actionsHead.classList.add("head-row");

    var actionsHead1 = row.insertCell(4);
    actionsHead1.classList.add("head-row");


    patientIDHead.innerHTML = "Patient ID";
    firstNameHead.innerHTML = "First Name";
    lastNameHead.innerHTML = "Last Name"; 
    actionsHead.innerHTML = "Profile"; 
    actionsHead1.innerHTML = "Message"; 
}

function addTableBody(patient){
    var table = document.getElementById("patientTable");

    var row = table.insertRow(0);

    var patientIDContent = row.insertCell(0);
    var firstNameContent = row.insertCell(1);
    var lastNameContent = row.insertCell(2);

    var actionsContent = row.insertCell(3);
    var actionsContent1 = row.insertCell(4);

    patientIDContent.innerHTML = patient.PatientID;
    firstNameContent.innerHTML = patient.firstName;
    lastNameContent.innerHTML = patient.lastName; 

    // PROFILE:
    var profileButton = document.createElement("BUTTON");
    profileButton.innerHTML = "View";
    profileButton.setAttribute("onclick", "goToProfile('".concat(patient.email).concat("')"));
    actionsContent.append(profileButton);

    // MESSAGE
    var messageButton = document.createElement("BUTTON");
    messageButton.innerHTML = "Send Email";
    messageButton.setAttribute("onclick", "goToEmailPage('".concat(patient.email).concat("')"));
    actionsContent1.append(messageButton);
}

function goToProfile(patient_email){
    // sessionStorage.clear();

    sessionStorage.setItem("patient_email", patient_email);
    window.location = "patientprofile.html";
}

function goToEmailPage(patient_email){
    sessionStorage.setItem("patient_email", patient_email);
    window.location = "physiomessageform.html";
}


window.onload = function() {
    email = sessionStorage.getItem("phsyio_email");
    displayData();
    getSpecificPatients();

    setTimeout( function(){
         addTableHead();
    }, 1000);
};

