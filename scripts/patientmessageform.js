var connectionURL = "http://172.16.188.47:5000"
var patient_email;
var physio_email;

document.getElementById("email-submit").addEventListener("click", function (event) {
    event.preventDefault();

    var note = document.getElementById("note").value;
    var emailPassword = document.getElementById("emailPassword").value;

    sendEmail(note, emailPassword);

});

window.onload = function() {
    physio_email = sessionStorage.getItem("physio_email");
    patient_email = sessionStorage.getItem("patient_email");

    console.log(physio_email);
    console.log(patient_email);
};

function sendEmail(note, emailPassword) {
    Email.send({
    Host: "smtp.gmail.com",
    Username : patient_email,
    Password : emailPassword,
    To : physio_email, 
    From : patient_email,
    Subject : "Message from Patient-SARD",
    Body : note,
    }).then(
        // message => alert("mail sent successfully")
        alert("mail sent successfully")
    );
    console.log("hello");
    setTimeout(function(){
        window.location=("patientprofile.html");
        },1000);
}
