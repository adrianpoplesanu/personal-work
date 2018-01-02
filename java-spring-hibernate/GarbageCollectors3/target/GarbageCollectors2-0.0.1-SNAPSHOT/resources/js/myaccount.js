/**
 *  MyAccount Page Script
 */
var initialAddress, initialTip, initialJudet, initialName, initialContact, initialEmail,
	initialTelefon, initialOras, initialZipCode, initialDescription, initialWebsite, initialJNumber,
	initialCui, initialAutorizatieMediu, initialWebsite;

function init() {
	disableInputs();
	$(".save-button, .cancel-button").hide();
	initialName = $("input[name='name']").val();
	initialAddress = $("input[name='address']").val();
	initialTip = tip;
	$("select[name='tip']").val(tip);
	initialJudet = judet;
	$("select[name='judet']").val(judet);
	initialContact = $("input[name='contact']").val();
	initialEmail = $("input[name='email']").val();
	initialTelefon = $("input[name='telefon']").val();
	initialOras = $("input[name='oras']").val();
	initialZipCode = $("input[name='zipCode']").val();
	initialDescription = $("textarea[name='description']").val();
	initialWebsite = $("input[name='website']").val();
	initialJNumber = $("input[name='jNumber']").val();
	initialCui = $("input[name='cui']").val();
	initialAutorizatieMediu = $("input[name='autorizatieMediu']").val();
	initialWebsite = $("input[name='website']").val();
}

function reset() {
	$("input[name='name']").val(initialName);
	$("input[name='address']").val(initialAddress);
	$("select[name='tip']").val(initialTip);
	$("select[name='judet']").val(initialJudet);
	$("input[name='contact']").val(initialContact);
	$("input[name='email']").val(initialEmail);
	$("input[name='telefon']").val(initialTelefon);
	$("input[name='oras']").val(initialOras);
	$("input[name='zipCode']").val(initialZipCode);
	$("textarea[name='description']").val(initialDescription);
	$("input[name='website']").val(initialWebsite);
	$("input[name='jNumber']").val(initialJNumber);
	$("input[name='cui']").val(initialCui);
	$("input[name='autorizatieMediu']").val(initialAutorizatieMediu);
	$("input[name='website']").val(initialWebsite);
}

function addEvents() {
	$('.edit-button').click( function() {
		$(this).hide();
		$(".save-button, .cancel-button").show();
		enableinputs();
	});
	$('.cancel-button').click( function() {
		$(".save-button, .cancel-button").hide();
		$(".edit-button").show();
		reset();
		disableInputs();
	});	
}

function disableInputs() {
	$("input").prop('disabled', true);
	$(".logout-form input").prop('disabled', false);
	$("textarea").prop('disabled', true);
	$("select").prop('disabled', true);	
}

function enableinputs() {
	$("input").prop('disabled', false);
	$("textarea").prop('disabled', false);
	$("select").prop('disabled', false);	
}

$(document).ready(function () {
	init();
    addEvents();
});