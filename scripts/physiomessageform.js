var connectionURL = "http://10.22.68.76:5000"
var patient_email;
var physio_email;

document.getElementById("email-submit").addEventListener("click", function (event) {
    event.preventDefault();

    var note = document.getElementById("note").value;
    var emailPassword = document.getElementById("emailPassword").value;

    sendEmail(note, emailPassword);

});

window.onload = function() {
    physio_email = sessionStorage.getItem("phsyio_email");
    patient_email = sessionStorage.getItem("patient_email");

    console.log(physio_email);
    console.log(patient_email);
};

function sendEmail(note, emailPassword) {
    Email.send({
    Host: "smtp.gmail.com",
    Username : physio_email,
    Password : emailPassword,
    To : patient_email, 
    From : physio_email,
    Subject : "Message from Physiotherapist-SARD",
    Body : note,
    }).then(
        // message => alert("mail sent successfully")
        alert("mail sent successfully")
    );
    console.log("hello");
    setTimeout(function(){
        window.location=("physioprofile.html");
        },1000);
}
