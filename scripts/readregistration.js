var connectionURL = "http://10.22.68.76:5000"

document.getElementById("registration-submit").addEventListener("click", function (event) {
    event.preventDefault();

    if (document.getElementById('patient').checked) {
        let firstName = document.getElementById("firstName").value;
        let lastName = document.getElementById("lastName").value;
        let email = document.getElementById("email").value;
        let DOB = document.getElementById("DOB").value;
        let physiotherapistemail = document.getElementById("physiotherapistemail").value;
        let password1 = document.getElementById("password1").value;
        let password2 = document.getElementById("password2").value;
    
        let jsonBody = {
            "firstName": firstName,
            "lastName": lastName,
            "email": email,
            "DOB": DOB,
            "physiotherapistemail": physiotherapistemail, 
            "password1": password1,
            "password2": password2
        };

        if (password1 === password2) {
            try {
                fetch(connectionURL.concat("/patient"), {
                    method: "POST",
                    body: JSON.stringify(jsonBody),
                    headers: {
                        "Content-type": "application/json",
                    }
                })
                    .then((res) => res.json())
                    .then((json) => console.log(json));

                alert("Patient Saved!");
            }
            catch (err) {
                alert("Something went wrong!");
            }

            //redirect back to index page:
            setTimeout(function () {
                window.location = ("login.html");
            }, 550);
        }
        else {
            alert("Passwords are different");
        }

    }
    else if (document.getElementById('physiotherapist').checked){ 

        let firstName = document.getElementById("firstName").value;
        let lastName = document.getElementById("lastName").value;
        let email = document.getElementById("email").value;
        let DOB = document.getElementById("DOB").value;
        let password1 = document.getElementById("password1").value;
        let password2 = document.getElementById("password2").value;
    
        let jsonBody = {
            "firstName": firstName,
            "lastName": lastName,
            "email": email,
            "DOB": DOB,
            "password1": password1,
            "password2": password2
        };

        if (password1 === password2) {
            try {
                fetch(connectionURL.concat("/physiotherapist"), {
                    method: "POST",
                    body: JSON.stringify(jsonBody),
                    headers: {
                        "Content-type": "application/json",
                    }
                })
                    .then((res) => res.json())
                    .then((json) => console.log(json));

                alert("Physiotherapist Saved!");
            }
            catch (err) {
                alert("Something went wrong!");
            }

            //redirect back to index page:
            setTimeout(function () {
                window.location = ("login.html");
            }, 550);
        }
        else {
            alert("Passwords are different");
        }

    }

});