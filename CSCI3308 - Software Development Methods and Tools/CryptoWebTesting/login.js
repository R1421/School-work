

$(document).ready(function() {
// Start when document will be ready.
$("#LogIn").click(function() {
    
    
    console.log("clicked");

var validEntry = true;
var email = $("#email").val(); // Store E-mail input value in the variable email.
var password = $("#password").val(); // Store Password input value in the variable password.
if(!/^[A-Za-z0-9_\.\-]*@[A-Za-z]*\.[A-Za-z]*$/.test(email)) {
    console.log("Invalid Email");
    validEntry = false;

}
/* If E-mail and Password do not match then shake Div having id maindiv and show the message "***Invalid email or password***" in the div having id message.*/
if(1 === 2){
    console.log("Invalid Password");
    validEntry = false;
}
if(validEntry){
    if(email === "sample@colorado.edu" && password === "samplePassword"){
        console.log("Valid Login");
        window.location = 'index.html';
    }
    else{
        console.log("Invslid Login");
    }
}
else {
$("#passwordClone0").effect("shake", { direction: "left", times: 3, distance: 8}, 400);
//$("#passwordClone0").addClass("invalid");
// $("#message").html('***Invalid email or password***');
}
});
});

