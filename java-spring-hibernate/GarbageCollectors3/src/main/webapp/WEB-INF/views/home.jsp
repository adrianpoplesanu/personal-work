<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@ taglib prefix="spring" uri="http://www.springframework.org/tags" %>
<%@ taglib prefix="sec" uri="http://www.springframework.org/security/tags" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<sec:authentication var="principal" property="principal" />
<title>GarbageCollectors3</title>
    <link href="<c:url value="/resources/bootstrap-3.3.7/dist/css/bootstrap.min.css" />" rel="stylesheet">
    <link href="<c:url value="/resources/DataTables/datatables.min.css" />" rel="stylesheet">
	<link href="<c:url value="/resources/css/home.css" />" rel="stylesheet">
	
	<script src="<c:url value="/resources/jquery-3.2.1/jquery-3.2.1.min.js" />"></script>
	<script src="<c:url value="/resources/bootstrap-3.3.7/dist/js/bootstrap.min.js" />"></script>
	<script src="<c:url value="/resources/DataTables/datatables.min.js" />"></script>	
	<script src="<c:url value="/resources/js/home.js" />"></script>

</head>
<body>
    <div style="display:none;">
        Logged-in as: <sec:authentication property="name"/>
        Role: <sec:authentication property="authorities"/>
    </div>
	<!-- <div id="test">${message}</div> -->
	
    <div class="container">
        <div align="right">
            <div class="top-nav-buttons">
                <font color="green">GarbageCollectors2.0.1</font> User conectat: ${principal.username}
            </div>
		    <div class="top-nav-buttons">
			    <form action="myaccount" method="POST">
			    	<input type="hidden" name="username" value="${principal.username} }">
				    <!-- <input type="hidden" name="${_csrf.parameterName}" value="${_csrf.token}"/> -->
				    <input type="submit" class="link-button" value="Contul meu" />
			    </form>
		    </div>
		    <div class="top-nav-buttons">|</div>
            <div class="top-nav-buttons">
	            <form action="logout" method="POST">
				    <!-- <input type="hidden" name="${_csrf.parameterName}" value="${_csrf.token}"/> -->
				    <input type="submit" class="link-button" value="Deconectare" />
			    </form>
		    </div>
        </div>
        
        <div class="panel-group">
    		<div class="panel panel-default">
      			<div class="panel-heading">Admin Console</div>
      			<div class="panel-body">
      			 	<a href="admin/users">User Management</a>
      			</div>
    		</div>
    	</div>
        <!-- 
        <nav class="navbar navbar-default" role="navigation">
            <div class="container-fluid">
                <div class="navbar-header">
                    <button type="button" class="navbar-toggle" data-toggle="collapse" data-target="#bs-example-navbar-collapse-1">
                        <span class="sr-only">Toggle navigation</span>
                        <span class="icon-bar"></span>
                        <span class="icon-bar"></span>
                        <span class="icon-bar"></span>
                    </button>
                    <a class="navbar-brand" href="#">Brand</a>
                </div>

                <div class="collapse navbar-collapse" id="bs-example-navbar-collapse-1">
                    <ul class="nav navbar-nav">
                        <li class="active"><a href="#">Link</a></li>
                        <li><a href="#">Link</a></li>
                        <li class="dropdown">
                            <a href="#" id="search_term" class="dropdown-toggle" data-toggle="dropdown">Clienti <b class="caret"></b></a>
                            <ul class="dropdown-menu">
                                <li><a class="search_term_option" href="#">Adauga client</a></li>
                                <li><a class="search_term_option" href="#">Vezi toti clientii</a></li>
                                <li><a class="search_term_option" href="#">Nu mai stiu ce</a></li>
                                <li class="divider"></li>
                                <li><a class="search_term_option" href="#">Altceva</a></li>
                                <li class="divider"></li>
                                <li><a class="search_term_option" href="#">Orice</a></li>
                            </ul>
                        </li>
                    </ul>
                <form class="navbar-form navbar-left" role="search">
                    <div class="form-group">
                        <input type="text" class="form-control" placeholder="Valoare">
                    </div>
                    <button type="submit" class="btn btn-default">Cauta</button>
                </form>
                    <ul class="nav navbar-nav navbar-right">
                        <li><a href="#">Link</a></li>
                        <li class="dropdown">
                            <a href="#" class="dropdown-toggle" data-toggle="dropdown">Genereaza rapoarte <b class="caret"></b></a>
                            <ul class="dropdown-menu">
                                <li><a href="#">Raport intrari deseuri</a></li>
                                <li><a href="#">Raport iesiri deseuri</a></li>
                                <li><a href="#">Raport reciclatori</a></li>
                                <li class="divider"></li>
                                <li><a href="#">Formularul de mediu</a></li>
                            </ul>
                        </li>
                    </ul>
                </div>
            </div>
        </nav>

        <table id="example" class="display" cellspacing="0" width="100%">
            <thead>
                <tr>
                    <th>Name</th>
                    <th>Position</th>
                    <th>Office</th>
                    <th>Age</th>
                    <th>Start date</th>
                    <th>Salary</th>
                </tr>
            </thead>
            <tfoot>
                <tr>
                    <th>Name</th>
                    <th>Position</th>
                    <th>Office</th>
                    <th>Age</th>
                    <th>Start date</th>
                    <th>Salary</th>
                </tr>
            </tfoot>
            <tbody>
                <tr>
                    <td>Tiger Nixon</td>
                    <td>System Architect</td>
                    <td>Edinburgh</td>
                    <td>61</td>
                    <td>2011/04/25</td>
                    <td>$320,800</td>
                </tr>
                <tr>
                    <td>Garrett Winters</td>
                    <td>Accountant</td>
                    <td>Tokyo</td>
                    <td>63</td>
                    <td>2011/07/25</td>
                    <td>$170,750</td>
                </tr>
                <tr>
                    <td>Ashton Cox</td>
                    <td>Junior Technical Author</td>
                    <td>San Francisco</td>
                    <td>66</td>
                    <td>2009/01/12</td>
                    <td>$86,000</td>
                </tr>
            </tbody>
        </table>
		-->
    </div>	
</body>
</html>