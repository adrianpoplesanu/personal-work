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
<title>GarbageCollectors2</title>
    <link href="<c:url value="/resources/bootstrap-3.3.7/dist/css/bootstrap.min.css" />" rel="stylesheet">
    <link href="<c:url value="/resources/DataTables/datatables.min.css" />" rel="stylesheet">
	<link href="<c:url value="/resources/css/admin/users.css" />" rel="stylesheet">
	
	<script src="<c:url value="/resources/jquery-3.2.1/jquery-3.2.1.min.js" />"></script>
	<script src="<c:url value="/resources/bootstrap-3.3.7/dist/js/bootstrap.min.js" />"></script>
	<script src="<c:url value="/resources/DataTables/datatables.min.js" />"></script>	
	<script src="<c:url value="/resources/js/admin/users.js" />"></script>
<title>Admin spot</title>
<script>
    var usersData = ${users};
</script>
</head>
<body>
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
    
        <div class="panel-group">
    		<div class="panel panel-default">
      			<div class="panel-heading"><h4>Lista utilizatori</h4></div>
      			<div class="panel-body">
					<button class="btn btn-info btn-md" data-toggle="modal" data-target="#addModal">Adauga utilizator</button>
					<div id="users_container">
						<table id="users" class="display" cellspacing="0" width="100%">
					        <thead>
					            <tr>
					                <th>Username</th>
					                <th>Address</th>
					                <th>CUI</th>
					                <th>Tip</th>
					                <th>Contact</th>
					                <th>Email</th>
					                <th>Telefon</th>
					                <th></th>
					            </tr>
					        </thead>
					        <tfoot>
					            <tr>
					                <th>Username</th>
					                <th>Address</th>
					                <th>CUI</th>
					                <th>Tip</th>
					                <th>Contact</th>
					                <th>Email</th>
					                <th>Telefon</th>                
					                <th></th>
					            </tr>
					        </tfoot>
					    </table>
				    </div>
      			</div>
    		</div>
    	</div>

	<div id="addModal" class="modal fade" role="dialog">
	  <div class="modal-dialog">
	
	    <!-- Modal content-->
	    <div class="modal-content">
	      <div class="modal-header">
	        <button type="button" class="close" data-dismiss="modal">&times;</button>
	        <h4 class="modal-title">Adauga utilizator</h4>
	      </div>
	      <div class="modal-body">




























    	    <input type="hidden" name="id" value="${userData.id}">
    	    
    	    <h4>Informatii cont</h4>
    	    
			<div class="form-group">
			    <label class="col-md-4 control-label label-offset">Username</label>  
			    <div class="col-md-8 inputGroupContainer">
			        <div class="input-group">
			            <span class="input-group-addon"><i class="glyphicon glyphicon-pencil"></i></span>
			            <input type="text" id="add-username" name="name" placeholder="username" class="form-control" value="${userData.name}">
			        </div>
			    </div>
			</div>
			
			<div class="form-group">
			    <label class="col-md-4 control-label label-offset">Parola</label>  
			    <div class="col-md-8 inputGroupContainer">
			        <div class="input-group">
			            <span class="input-group-addon"><i class="glyphicon glyphicon-pencil"></i></span>
			            <input type="text" id="add-password" name="name" placeholder="parola" class="form-control" value="${userData.name}">
			        </div>
			    </div>
			</div>			    	    
    	    
			<h4>Detalii</h4>
	
			<div class="form-group">
			    <label class="col-md-4 control-label label-offset">Nume firma</label>  
			    <div class="col-md-8 inputGroupContainer">
			        <div class="input-group">
			            <span class="input-group-addon"><i class="glyphicon glyphicon-pencil"></i></span>
			            <input type="text" id="add-name" name="name" placeholder="Nume firma" class="form-control" value="${userData.name}">
			        </div>
			    </div>
			</div>
		
			<div class="form-group">
				<label class="col-md-4 control-label label-offset">Persoana Contact</label> 
				    <div class="col-md-8 inputGroupContainer">
				    <div class="input-group">
				        <span class="input-group-addon"><i class="glyphicon glyphicon-user"></i></span>
				        <input type="text" id="add-contact" name="contact" placeholder="Persoana Contact" class="form-control" value="${userData.contact}">
				    </div>
				</div>
			</div>
		
		    <div class="form-group">
		        <label class="col-md-4 control-label label-offset">E-Mail</label>  
		        <div class="col-md-8 inputGroupContainer">
			        <div class="input-group">
			            <span class="input-group-addon"><i class="glyphicon glyphicon-envelope"></i></span>
			            <input type="text" id="add-email" name="email" placeholder="Adresa E-Mail" class="form-control" value="${userData.email}">
			        </div>
		       </div>
		    </div>
		       
			<div class="form-group">
			    <label class="col-md-4 control-label label-offset">Telefon #</label>  
			    <div class="col-md-8 inputGroupContainer">
			        <div class="input-group">
			            <span class="input-group-addon"><i class="glyphicon glyphicon-earphone"></i></span>
			            <input type="text" id="add-telefon" name="telefon" placeholder="072x-xxx-xxx" class="form-control" value="${userData.telefon}">
			        </div>
			    </div>
			</div>
		
		    <div class="form-group">
		        <label class="col-md-4 control-label label-offset">Adresa</label>  
		        <div class="col-md-8 inputGroupContainer">
		            <div class="input-group">
		                <span class="input-group-addon"><i class="glyphicon glyphicon-home"></i></span>
		                <input type="text" id="add-address" name="address" placeholder="Adresa" class="form-control" value="${userData.address}">
		            </div>
		        </div>
		    </div>
				 
		    <div class="form-group">
		        <label class="col-md-4 control-label label-offset">Oras</label>  
		        <div class="col-md-8 inputGroupContainer">
		            <div class="input-group">
		                <span class="input-group-addon"><i class="glyphicon glyphicon-home"></i></span>
		                <input type="text" id="add-oras" name="oras" placeholder="Oras" class="form-control" value="${userData.oras}">
		            </div>
		        </div>
		    </div>
				   
		    <div class="form-group"> 
		        <label class="col-md-4 control-label label-offset">Judet</label>
		        <div class="col-md-8 selectContainer">
		            <div class="input-group">
		                <span class="input-group-addon"><i class="glyphicon glyphicon-list"></i></span>
		    			<select name="judet" id="add-judet" class="form-control selectpicker" >
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
		    <label class="col-md-4 control-label label-offset">Cod postal</label>  
		        <div class="col-md-8 inputGroupContainer">
		            <div class="input-group">
		                <span class="input-group-addon"><i class="glyphicon glyphicon-home"></i></span>
		                <input type="text" id="add-zip-code" name="zipCode" placeholder="Cod postal" class="form-control" value="${userData.zipCode}">
		            </div>
		        </div>
		</div>
		
		<div class="form-group">
		    <label class="col-md-4 control-label label-offset">Website</label>  
		        <div class="col-md-8 inputGroupContainer">
		            <div class="input-group">
		                <span class="input-group-addon"><i class="glyphicon glyphicon-globe"></i></span>
		                <input type="text" id="add-website" name="website" placeholder="Website sau domeniu" class="form-control" value="${userData.website}">
		            </div>
		        </div>
		</div>
		
	    <div class="form-group">
		  <label class="col-md-4 control-label label-offset">Descriere Client</label>
		    <div class="col-md-8 inputGroupContainer">
		    <div class="input-group">
		        <span class="input-group-addon"><i class="glyphicon glyphicon-pencil"></i></span>
		        	<textarea class="form-control" id="add-description" name="description" placeholder="Descriere">${userData.description}</textarea>
		  </div>
		  </div>
		</div>
		
		<div><h4>Date fiscale</h4></div>
		
		<div class="form-group">
		    <label class="col-md-4 control-label label-offset">Tipul contului</label>
		    	<div class="col-md-8 selectContainer">
		            <div class="input-group">
		                <span class="input-group-addon"><i class="glyphicon glyphicon-list"></i></span>
		    			<select name="tip" id="add-tip" class="form-control selectpicker" >
		      				<option value="2">Generator</option>
		      				<option value="1">Colector</option>
		      				<option value="3">Eliminator</option>
		      			</select>
		      		</div>
		      	</div>
		</div>

		    <div class="form-group">
		        <label class="col-md-4 control-label label-offset">CUI</label>  
		        <div class="col-md-8 inputGroupContainer">
			        <div class="input-group">
			            <span class="input-group-addon"><i class="glyphicon glyphicon-pencil"></i></span>
			            <input type="text" id="add-cui" name="cui" placeholder="CUI" class="form-control" value="${userData.cui}">
			        </div>
		       </div>
		    </div>
		    
		    <div class="form-group">
		        <label class="col-md-4 control-label label-offset">Registrul Comertului</label>  
		        <div class="col-md-8 inputGroupContainer">
			        <div class="input-group">
			            <span class="input-group-addon"><i class="glyphicon glyphicon-pencil"></i></span>
			            <input type="text" id="add-jnumber" name="jNumber" placeholder="J1234/22-12-2017" class="form-control" value="${userData.jNumber}">
			        </div>
		       </div>
		    </div>
		    
		    <div class="form-group">
		        <label class="col-md-4 control-label label-offset">Autorizatie mediu</label>  
		        <div class="col-md-8 inputGroupContainer">
			        <div class="input-group">
			            <span class="input-group-addon"><i class="glyphicon glyphicon-pencil"></i></span>
			            <input type="text" id="add-autorizatie-mediu" name="autorizatieMediu" placeholder="Numar/Data" class="form-control" value="${userData.autorizatieMediu}">
			        </div>
		       </div>
		    </div>
		    
		    <div class="form-group row"></div>





























	      </div>
	      <div class="modal-footer">
	        <button type="button" class="btn btn-default" data-dismiss="modal">Close</button>
	        <button id="add-save" type="button" class="btn btn-danger" data-dismiss="modal">Save</button>
	      </div>
	    </div>
	
	  </div>
	</div>
	
	<div id="editModal" class="modal fade" role="dialog">
	  <div class="modal-dialog">
	
	    <!-- Modal content-->
	    <div class="modal-content">
	      <div class="modal-header">
	        <button type="button" class="close" data-dismiss="modal">&times;</button>
	        <h4 class="modal-title">Editeaza utilizator</h4>
	      </div>
	      <div class="modal-body">
			<!-- <form action="${pageContext.request.contextPath}/admin/users/edit" method="POST">
				<input type="hidden" id="edit-user-id" name="id"/>
				<input type="hidden" name="${_csrf.parameterName}" value="${_csrf.token}"/>
					username<input type="text" name="username" /><br>	    
			    	password<input type="text" name="password" /><br>
			    	name<input type="text" name="name" /><br>    
			    	address<input type="text" name="address" /><br>
			    	jnumber<input type="text" name="jnumber" /><br>
			    	tip<input type="text" name="tip" /><br>
				<input type="submit">
			</form> -->
			
			
			
			
			
			
			
			






			
			
			
			
			
			
			
			
			
			
			
	

    	    <input type="hidden" id="edit-user-id" name="id" value="${userData.id}">
    	    
			<h4>Detalii</h4>
	
			<div class="form-group">
			    <label class="col-md-4 control-label label-offset">Nume firma</label>  
			    <div class="col-md-8 inputGroupContainer">
			        <div class="input-group">
			            <span class="input-group-addon"><i class="glyphicon glyphicon-pencil"></i></span>
			            <input type="text" id="edit-name" name="name" placeholder="Nume firma" class="form-control" value="${userData.name}">
			        </div>
			    </div>
			</div>
		
			<div class="form-group">
				<label class="col-md-4 control-label label-offset">Persoana Contact</label> 
				    <div class="col-md-8 inputGroupContainer">
				    <div class="input-group">
				        <span class="input-group-addon"><i class="glyphicon glyphicon-user"></i></span>
				        <input type="text" id="edit-contact" name="contact" placeholder="Persoana Contact" class="form-control" value="${userData.contact}">
				    </div>
				</div>
			</div>
		
		    <div class="form-group">
		        <label class="col-md-4 control-label label-offset">E-Mail</label>  
		        <div class="col-md-8 inputGroupContainer">
			        <div class="input-group">
			            <span class="input-group-addon"><i class="glyphicon glyphicon-envelope"></i></span>
			            <input type="text" id="edit-email" name="email" placeholder="Adresa E-Mail" class="form-control" value="${userData.email}">
			        </div>
		       </div>
		    </div>
		       
			<div class="form-group">
			    <label class="col-md-4 control-label label-offset">Telefon #</label>  
			    <div class="col-md-8 inputGroupContainer">
			        <div class="input-group">
			            <span class="input-group-addon"><i class="glyphicon glyphicon-earphone"></i></span>
			            <input type="text" id="edit-telefon" name="telefon" placeholder="072x-xxx-xxx" class="form-control" value="${userData.telefon}">
			        </div>
			    </div>
			</div>
		
		    <div class="form-group">
		        <label class="col-md-4 control-label label-offset">Adresa</label>  
		        <div class="col-md-8 inputGroupContainer">
		            <div class="input-group">
		                <span class="input-group-addon"><i class="glyphicon glyphicon-home"></i></span>
		                <input type="text" id="edit-address" name="address" placeholder="Adresa" class="form-control" value="${userData.address}">
		            </div>
		        </div>
		    </div>
				 
		    <div class="form-group">
		        <label class="col-md-4 control-label label-offset">Oras</label>  
		        <div class="col-md-8 inputGroupContainer">
		            <div class="input-group">
		                <span class="input-group-addon"><i class="glyphicon glyphicon-home"></i></span>
		                <input type="text" id="edit-oras" name="oras" placeholder="Oras" class="form-control" value="${userData.oras}">
		            </div>
		        </div>
		    </div>
				   
		    <div class="form-group"> 
		        <label class="col-md-4 control-label label-offset">Judet</label>
		        <div class="col-md-8 selectContainer">
		            <div class="input-group">
		                <span class="input-group-addon"><i class="glyphicon glyphicon-list"></i></span>
		    			<select name="judet" id="edit-judet" class="form-control selectpicker" >
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
		    <label class="col-md-4 control-label label-offset">Cod postal</label>  
		        <div class="col-md-8 inputGroupContainer">
		            <div class="input-group">
		                <span class="input-group-addon"><i class="glyphicon glyphicon-home"></i></span>
		                <input type="text" id="edit-zip-code" name="zipCode" placeholder="Cod postal" class="form-control" value="${userData.zipCode}">
		            </div>
		        </div>
		</div>
		
		<div class="form-group">
		    <label class="col-md-4 control-label label-offset">Website</label>  
		        <div class="col-md-8 inputGroupContainer">
		            <div class="input-group">
		                <span class="input-group-addon"><i class="glyphicon glyphicon-globe"></i></span>
		                <input type="text" id="edit-website" name="website" placeholder="Website sau domeniu" class="form-control" value="${userData.website}">
		            </div>
		        </div>
		</div>
		
	    <div class="form-group">
		  <label class="col-md-4 control-label label-offset">Descriere Client</label>
		    <div class="col-md-8 inputGroupContainer">
		    <div class="input-group">
		        <span class="input-group-addon"><i class="glyphicon glyphicon-pencil"></i></span>
		        	<textarea class="form-control" id="edit-description" name="description" placeholder="Descriere">${userData.description}</textarea>
		  </div>
		  </div>
		</div>
		
		<div><h4>Date fiscale</h4></div>
		
		<div class="form-group">
		    <label class="col-md-4 control-label label-offset">Tipul contului</label>
		    	<div class="col-md-8 selectContainer">
		            <div class="input-group">
		                <span class="input-group-addon"><i class="glyphicon glyphicon-list"></i></span>
		    			<select name="tip" id="edit-tip" class="form-control selectpicker" >
		      				<option value="2">Generator</option>
		      				<option value="1">Colector</option>
		      				<option value="3">Eliminator</option>
		      			</select>
		      		</div>
		      	</div>
		</div>

		    <div class="form-group">
		        <label class="col-md-4 control-label label-offset">CUI</label>  
		        <div class="col-md-8 inputGroupContainer">
			        <div class="input-group">
			            <span class="input-group-addon"><i class="glyphicon glyphicon-pencil"></i></span>
			            <input type="text" id="edit-cui" name="cui" placeholder="CUI" class="form-control" value="${userData.cui}">
			        </div>
		       </div>
		    </div>
		    
		    <div class="form-group">
		        <label class="col-md-4 control-label label-offset">Registrul Comertului</label>  
		        <div class="col-md-8 inputGroupContainer">
			        <div class="input-group">
			            <span class="input-group-addon"><i class="glyphicon glyphicon-pencil"></i></span>
			            <input type="text" id="edit-jnumber" name="jNumber" placeholder="J1234/22-12-2017" class="form-control" value="${userData.jNumber}">
			        </div>
		       </div>
		    </div>
		    
		    <div class="form-group">
		        <label class="col-md-4 control-label label-offset">Autorizatie mediu</label>  
		        <div class="col-md-8 inputGroupContainer">
			        <div class="input-group">
			            <span class="input-group-addon"><i class="glyphicon glyphicon-pencil"></i></span>
			            <input type="text" id="edit-autorizatie-mediu" name="autorizatieMediu" placeholder="Numar/Data" class="form-control" value="${userData.autorizatieMediu}">
			        </div>
		       </div>
		    </div>
		    
		    <div class="form-group row"></div>
		
		<!-- Success message -->
		<!-- <div class="alert alert-success" role="alert" id="success_message">Success <i class="glyphicon glyphicon-thumbs-up"></i> Thanks for contacting us, we will get back to you shortly.</div> -->


			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
	      </div>
	      <div class="modal-footer">
	        <button type="button" class="btn btn-default" data-dismiss="modal">Close</button>
	        <button id="edit-save" type="button" class="btn btn-danger" data-dismiss="modal">Save</button>
	      </div>
	    </div>
	
	  </div>
	</div>
	
	<div id="deleteModal" class="modal fade" role="dialog">
	  <div class="modal-dialog">
	
	    <!-- Modal content-->
	    <div class="modal-content">
	      <div class="modal-header">
	        <button type="button" class="close" data-dismiss="modal">&times;</button>
	        <h4 class="modal-title">Sterge utilizator</h4>
	      </div>
	      <div class="modal-body">
	        <p>Esti sigur ca vrei sa-l stergi?</p>
	      </div>
	      <div class="modal-footer">
	        <button type="button" class="btn btn-default" data-dismiss="modal">Close</button>
	        <button id="delete-save" type="button" class="btn btn-danger" data-dismiss="modal">Delete</button>
	      </div>
	    </div>
	
	  </div>
	</div>
	
</body>
</html>