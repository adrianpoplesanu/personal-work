<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@ taglib prefix="spring" uri="http://www.springframework.org/tags" %>
<%@ taglib prefix="sec" uri="http://www.springframework.org/security/tags" %>
<%@ taglib uri="http://www.springframework.org/tags/form" prefix="form" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<sec:authentication var="principal" property="principal" />
<title>Contul meu</title>
    <link href="<c:url value="/resources/bootstrap-3.3.7/dist/css/bootstrap.min.css" />" rel="stylesheet">
    <link href="<c:url value="/resources/DataTables/datatables.min.css" />" rel="stylesheet">
    <link href="<c:url value="/resources/css/myaccount.css" />" rel="stylesheet">
    
	<script src="<c:url value="/resources/jquery-3.2.1/jquery-3.2.1.min.js" />"></script>
	<script src="<c:url value="/resources/bootstrap-3.3.7/dist/js/bootstrap.min.js" />"></script>
	<script src="<c:url value="/resources/js/myaccount.js" />"></script>
	<script>
		var homepageURL = '<c:url value="/" />';
		var tip = ${userData.tip};
		var judet = "${userData.judet}";
	</script>
</head>
<body>
    <div style="display:none;">
        Logged-in as: <sec:authentication property="name"/>
        Role: <sec:authentication property="authorities"/>
    </div>
    <!-- <div style="color:red">serverul spune: ${userData}</div> -->
	<!-- <a href="<c:url value="/" />">Inapoi la homepage</a> -->
	<div class="container">
	    <div align="right">
            <div class="top-nav-buttons">
                <font color="green">GarbageCollectors2.0.1</font> User conectat: ${principal.username}
            </div>
		    <div class="top-nav-buttons">
			    <a href="<c:url value="/" />">Homepage</a>
		    </div>
		    <div class="top-nav-buttons">|</div>
            <div class="top-nav-buttons">
	            <form class="logout-form" action="logout" method="POST">
				    <input type="hidden" name="${_csrf.parameterName}" value="${_csrf.token}"/>
				    <input type="submit" class="link-button" value="Deconectare" />
			    </form>
		    </div>
        </div>

    	<form:form class="well form-horizontal" action="update-account" method="post"  id="contact_form" modelAttribute="UserData">
    	    <input type="hidden" name="${_csrf.parameterName}" value="${_csrf.token}"/>
    	    <input type="hidden" name="id" value="${userData.id}">
			<fieldset>
			<legend>Informatii cont</legend>
	
			<div class="form-group">
			    <label class="col-md-4 control-label">Nume firma</label>  
			    <div class="col-md-4 inputGroupContainer">
			        <div class="input-group">
			            <span class="input-group-addon"><i class="glyphicon glyphicon-pencil"></i></span>
			            <input type="text" name="name" placeholder="Nume firma" class="form-control" value="${userData.name}">
			        </div>
			    </div>
			</div>
		
			<div class="form-group">
				<label class="col-md-4 control-label">Persoana Contact</label> 
				    <div class="col-md-4 inputGroupContainer">
				    <div class="input-group">
				        <span class="input-group-addon"><i class="glyphicon glyphicon-user"></i></span>
				        <input type="text" name="contact" placeholder="Persoana Contact" class="form-control" value="${userData.contact}">
				    </div>
				</div>
			</div>
		
		    <div class="form-group">
		        <label class="col-md-4 control-label">E-Mail</label>  
		        <div class="col-md-4 inputGroupContainer">
			        <div class="input-group">
			            <span class="input-group-addon"><i class="glyphicon glyphicon-envelope"></i></span>
			            <input type="text" name="email" placeholder="Adresa E-Mail" class="form-control" value="${userData.email}">
			        </div>
		       </div>
		    </div>
		       
			<div class="form-group">
			    <label class="col-md-4 control-label">Telefon #</label>  
			    <div class="col-md-4 inputGroupContainer">
			        <div class="input-group">
			            <span class="input-group-addon"><i class="glyphicon glyphicon-earphone"></i></span>
			            <input type="text" name="telefon" placeholder="072x-xxx-xxx" class="form-control" value="${userData.telefon}">
			        </div>
			    </div>
			</div>
		
		    <div class="form-group">
		        <label class="col-md-4 control-label">Adresa</label>  
		        <div class="col-md-4 inputGroupContainer">
		            <div class="input-group">
		                <span class="input-group-addon"><i class="glyphicon glyphicon-home"></i></span>
		                <input type="text" name="address" placeholder="Adresa" class="form-control" value="${userData.address}">
		            </div>
		        </div>
		    </div>
				 
		    <div class="form-group">
		        <label class="col-md-4 control-label">Oras</label>  
		        <div class="col-md-4 inputGroupContainer">
		            <div class="input-group">
		                <span class="input-group-addon"><i class="glyphicon glyphicon-home"></i></span>
		                <input type="text" name="oras" placeholder="Oras" class="form-control" value="${userData.oras}">
		            </div>
		        </div>
		    </div>
				   
		    <div class="form-group"> 
		        <label class="col-md-4 control-label">Judet</label>
		        <div class="col-md-4 selectContainer">
		            <div class="input-group">
		                <span class="input-group-addon"><i class="glyphicon glyphicon-list"></i></span>
		    			<select name="judet" class="form-control selectpicker" >
		      				<option value=""></option>
		      				<option>Alba</option>
		      				<option>Arad</option>
						    <option>Arges</option>
						    <option>Bacau</option>
						    <option>Bihor</option>
						    <option>Bistrita-Nasaud</option>
						    <option>Botosani</option>
					        <option>Braila</option>
						    <option>Brasov</option>
						    <option>Bucuresti</option>
						    <option>Buzau</option>
						    <option>Calarasi</option>
						    <option>Caras-Severin</option>
						    <option>Cluj</option>
						    <option>Constanta</option>
						    <option>Covasna</option>
						    <option>Dambovita</option>
						    <option>Dolj</option>
						    <option>Galati</option>
						    <option>Giurgiu</option>
						    <option>Gorj</option>
						    <option>Harghita</option>
						    <option>Hunedoara</option>
						    <option>Ialomita</option>
						    <option>Iasi</option>
						    <option>Ilfov</option>
						    <option>Maramures</option>
		                    <option>Mehedinti</option>
					        <option>Mures</option>
					        <option>Neamt</option>
					        <option>Olt</option>
					        <option>Prahove</option>
					        <option>Salaj</option>
					        <option>Satu Mare</option>
					        <option>Sibiu</option>
					        <option>Suceava</option>
					        <option>Teleorman</option>
					        <option>Timis</option>
					        <option>Tulcea</option>
					        <option>Valcea</option>
					        <option>Vaslui</option>
					        <option>Vrancea</option>
		    			</select>
		  			</div>
				</div>
		</div>
		
		<div class="form-group">
		    <label class="col-md-4 control-label">Cod postal</label>  
		        <div class="col-md-4 inputGroupContainer">
		            <div class="input-group">
		                <span class="input-group-addon"><i class="glyphicon glyphicon-home"></i></span>
		                <input type="text" name="zipCode" placeholder="Cod postal" class="form-control" value="${userData.zipCode}">
		            </div>
		        </div>
		</div>
		
		<div class="form-group">
		    <label class="col-md-4 control-label">Website</label>  
		        <div class="col-md-4 inputGroupContainer">
		            <div class="input-group">
		                <span class="input-group-addon"><i class="glyphicon glyphicon-globe"></i></span>
		                <input type="text" name="website" placeholder="Website sau domeniu" class="form-control" value="${userData.website}">
		            </div>
		        </div>
		</div>
		
	    <div class="form-group">
		  <label class="col-md-4 control-label">Descriere Client</label>
		    <div class="col-md-4 inputGroupContainer">
		    <div class="input-group">
		        <span class="input-group-addon"><i class="glyphicon glyphicon-pencil"></i></span>
		        	<textarea class="form-control" name="description" placeholder="Descriere">${userData.description}</textarea>
		  </div>
		  </div>
		</div>
		
		<legend>Date fiscale</legend>
		
		<div class="form-group">
		    <label class="col-md-4 control-label">Tipul contului</label>
		    	<div class="col-md-4 selectContainer">
		            <div class="input-group">
		                <span class="input-group-addon"><i class="glyphicon glyphicon-list"></i></span>
		    			<select name="tip" class="form-control selectpicker" >
		      				<option value="2">Generator</option>
		      				<option value="1">Colector</option>
		      				<option value="3">Eliminator</option>
		      			</select>
		      		</div>
		      	</div>
		</div>

		    <div class="form-group">
		        <label class="col-md-4 control-label">CUI</label>  
		        <div class="col-md-4 inputGroupContainer">
			        <div class="input-group">
			            <span class="input-group-addon"><i class="glyphicon glyphicon-pencil"></i></span>
			            <input type="text" name="cui" placeholder="CUI" class="form-control" value="${userData.cui}">
			        </div>
		       </div>
		    </div>
		    
		    <div class="form-group">
		        <label class="col-md-4 control-label">Registrul Comertului</label>  
		        <div class="col-md-4 inputGroupContainer">
			        <div class="input-group">
			            <span class="input-group-addon"><i class="glyphicon glyphicon-pencil"></i></span>
			            <input type="text" name="jNumber" placeholder="J1234/22-12-2017" class="form-control" value="${userData.jNumber}">
			        </div>
		       </div>
		    </div>
		    
		    <div class="form-group">
		        <label class="col-md-4 control-label">Autorizatie mediu</label>  
		        <div class="col-md-4 inputGroupContainer">
			        <div class="input-group">
			            <span class="input-group-addon"><i class="glyphicon glyphicon-pencil"></i></span>
			            <input type="text" name="autorizatieMediu" placeholder="Numar/Data" class="form-control" value="${userData.autorizatieMediu}">
			        </div>
		       </div>
		    </div>
		
		<!-- Success message -->
		<!-- <div class="alert alert-success" role="alert" id="success_message">Success <i class="glyphicon glyphicon-thumbs-up"></i> Thanks for contacting us, we will get back to you shortly.</div> -->
		
		<!-- Button -->
		<div class="form-group">
		  <label class="col-md-4 control-label"></label>
		  <div class="col-md-4">
		    <button type="button" class="btn btn-info edit-button">Edit <span class="glyphicon glyphicon-edit"></span></button>
		    <button type="button" class="btn btn-default cancel-button">Cancel <span class="glyphicon glyphicon-remove"></span></button>
		    <button type="submit" class="btn btn-danger save-button">Save <span class="glyphicon glyphicon-ok"></span></button>
		  </div>
		</div>
		
		</fieldset>
		</form:form>
	</div> <!-- /.container -->
</body>
</html>