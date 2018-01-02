/**
 *  User Management Page
 */
var users;
var editUserIndex;
var deleteUserIndex;

function addUserAjax () {
	$.ajax({
		method: "POST",
		url: "/GarbageCollectors3/admin/users/add",
		data: { 
			username: $('#add-username').val(), 
			password: $('#add-password').val(),
	        name: $('#add-name').val(),
	        contact: $('#add-contact').val(),
	        email: $('#add-email').val(),
	        telefon: $('#add-telefon').val(),
	        address: $('#add-address').val(),
	        oras: $('#add-oras').val(),
	        judet: $("#addModal select[name='judet']").val(),
	        zipCode: $('#add-zip-code').val(),
	        website: $('#add-website').val(),
	        description: $('#add-description').val(),
	        tip: $("#addModal select[name='tip']").val(),
	        cui: $('#add-cui').val(),
	        jnumber: $('#add-jnumber').val(),
	        autorizatie_mediu: $('#add-autorizatie-mediu').val()
		}
	})
	.done(function(msg) {
		users.ajax.reload();
		usersData.push(JSON.parse(msg));
	})
	.fail(function(msg) {
		alert("Eroare: fail");
	});
}

function editUserAjax () {
	$.ajax({
		method: "POST",
		url: "/GarbageCollectors3/admin/users/edit",
		data: { 
	        id: $("#edit-user-id").val(),
			name: $('#edit-name').val(),
	        contact: $('#edit-contact').val(),
	        email: $('#edit-email').val(),
	        telefon: $('#edit-telefon').val(),
	        address: $('#edit-address').val(),
	        oras: $('#edit-oras').val(),
	        judet: $("#editModal select[name='judet']").val(),
	        zipCode: $('#edit-zip-code').val(),
	        website: $('#edit-website').val(),
	        description: $('#edit-description').val(),
	        tip: $("#editModal select[name='tip']").val(),
	        cui: $('#edit-cui').val(),
	        jnumber: $('#edit-jnumber').val(),
	        autorizatie_mediu: $('#edit-autorizatie-mediu').val()
		}
	})
	.done(function(msg) {
		users.ajax.reload();
		usersData[editUserIndex].userData = JSON.parse(msg);
	})
	.fail(function(msg) {
		alert("Eroare: fail");
	});
}

function deleteUserAjax () {
	$.ajax({
		method: "POST",
		url: "/GarbageCollectors3/admin/users/delete",
		data: { 
	        id: $("#edit-user-id").val(),
		}
	})
	.done(function(msg) {
		users.ajax.reload();
		//usersData[editUserIndex].userData = JSON.parse(msg);
		// delete usersData[editUserIndex];
		usersData.splice(editUserIndex, 1);
		editUserIndex = -1;
	})
	.fail(function(msg) {
		alert("Eroare: fail");
	});
}


$(document).ready(function () {
    users = $('#users').DataTable({
    	"ajax": "/GarbageCollectors3/admin/users/json",
    	"type": "GET",
    	"columns": [
    	            { "data": "username" },
    	            { "data": "userData.address" },
    	            { "data": "userData.cui" },
    	            { "data": "userData.tip" },
    	            { "data": "userData.contact" },
    	            { "data": "userData.email" },
    	            { "data": "userData.telefon" },
    	        ],
    	"columnDefs": [
    	            {
    	              "targets": 3,
    	              "render": function ( data, type, row ) {
    	            	  if (data == 1) {
    	            		  return "Colector";
    	            	  } else if (data == 2) {
    	            		  return "Generator"
    	            	  } else if (data == 3) {
    	            		  return "Eliminator";
    	            	  }
    	               } 
    	            },
    	            {
      	              "targets": 7,
      	              "render": function ( data, type, row ) {
      	                   	return '<button class="btn btn-info btn-md" data-toggle="modal" data-target="#editModal" data-user-id=' + row.id + '>edit</button>' +
      	                   	       '<button class="btn btn-danger btn-md" data-toggle="modal" data-target="#deleteModal" data-user-id=' + row.id + '>delete</button>';
      	               } 
      	            }    	            
    	]
    });
    
    $("#users").on("click", "button", function() {
    	$('#edit-user-id').val($(this).data('user-id'));
    });
    
    $('#users tbody').on( 'click', 'tr', function () {
        var idx = users
            .row( this )
            .index(); // indexul din lista de useri din json
        var user = usersData[idx];
        editUserIndex = idx;
        
        $('#edit-name').val(user.userData.name);
        $('#edit-contact').val(user.userData.contact);
        $('#edit-email').val(user.userData.email);
        $('#edit-telefon').val(user.userData.telefon);
        $('#edit-address').val(user.userData.address);
        $('#edit-oras').val(user.userData.oras);
        $("#editModal select[name='judet']").val(user.userData.judet);
        $('#edit-zip-code').val(user.userData.zipCode);
        $('#edit-website').val(user.userData.website);
        $('#edit-description').val(user.userData.description);
        $("#editModal select[name='tip']").val(user.userData.tip);
        $('#edit-cui').val(user.userData.cui);
        $('#edit-jnumber').val(user.userData.jNumber);
        $('#edit-autorizatie-mediu').val(user.userData.autorizatieMediu);
    });
    
    $('#add-save').on('click', function () {
    	addUserAjax();
    });
    
    $('#edit-save').on('click', function () {
    	editUserAjax();
    });
    
    $('#delete-save').on('click', function () {
    	deleteUserAjax();
    });    
});