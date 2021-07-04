var connectionURL = "http://172.16.188.47:5000"

document.getElementById("login-submit").addEventListener("click", function (event) {
    event.preventDefault();

    var email = document.getElementById("email").value;
    var password = document.getElementById("password").value;

    if (document.getElementById('patient').checked) {
        //verify patient
        verifyPatient(email, password);
    }
    else if (document.getElementById('physiotherapist').checked) {
        //verify physio
        verifyPhysiotherapist(email, password);
    }
});

async function getPatients() {
    return fetch(connectionURL.concat("/patient"))
        .then((res) => res.json())
        .then((json) => json);
}

async function getPhysiotherapists() {
    return fetch(connectionURL.concat("/physiotherapist"))
        .then((res) => res.json())
        .then((json) => json);
}

async function verifyPatient(email, password) {
    let patients = await getPatients();
    var found = 0;
    var email; 

    patients.forEach((patient) => {
        if (patient.email === email) {
            if (patient.password1 === password) {
                //should leave the for loop here: probably just needs a break;
                found = 1;
                email = patient.email;
            }
        }
    })

    if (found === 1) {
        alert("User Found");
        sessionStorage.setItem("patient_email", email);
        window.location = "patientprofile.html";
    }
    else {
        alert("Patient Not Found, Try Again!");
    }

}

async function verifyPhysiotherapist(email, password) {
    let physiotherapists = await getPhysiotherapists();
    var found = 0;
    var email; 

    physiotherapists.forEach((physiotherapist) => {
        if (physiotherapist.email === email) {
            if (physiotherapist.password1 === password) {
                //should leave the for loop here: probably just needs a break;
                found = 1;
                email = physiotherapist.email;
            }
        }
    })

    if (found === 1) {
        alert("User Found");
        sessionStorage.setItem("phsyio_email", email);
        window.location = "physioprofile.html";
    }
    else {
        alert("Physiotherapist Not Found, Try Again!");
    }

}

// really should be in logout wherever that goes!
window.onload = function() {
    sessionStorage.clear();  
};