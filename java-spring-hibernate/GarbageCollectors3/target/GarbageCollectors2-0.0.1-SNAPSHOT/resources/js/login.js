/**
 *  Login Page Script
 */

console.log("running login js...");
$(document).ready(function () {
    setTimeout(function () {
        $('.error, .msg').hide ();
    }, 3000);
    history.pushState(null, "GarbageCollectors2", pageUrl);
});