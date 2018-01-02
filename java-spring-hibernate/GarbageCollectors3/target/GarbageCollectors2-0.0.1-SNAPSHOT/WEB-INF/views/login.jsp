<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@ taglib prefix="spring" uri="http://www.springframework.org/tags" %>
<%@ taglib uri="http://www.springframework.org/security/tags" prefix="sec"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<sec:authorize access="isAuthenticated()">
    <% response.sendRedirect(request.getContextPath()); %>
</sec:authorize>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>GarbageCollectors3</title>
    <link href="<c:url value="/resources/bootstrap-3.3.7/dist/css/bootstrap.min.css" />" rel="stylesheet">
	<link href="<c:url value="/resources/css/login.css" />" rel="stylesheet">
	
	<script src="<c:url value="/resources/jquery-3.2.1/jquery-3.2.1.min.js" />"></script>
	<script src="<c:url value="/resources/bootstrap-3.3.7/dist/js/bootstrap.min.js" />"></script>	
	<script src="<c:url value="/resources/js/login.js" />"></script>
	<c:url var="pageUrl" value="/login" />
	<script>
		var pageUrl = "${pageUrl}";
	</script>
</head>
<body>
    <div class="col-md-4 col-md-offset-4 text-center">
        <div class="search-box">
            <div class="caption">
                <h3>Garbage Collectors v2.0</h3>
            </div>
            <form name='f' action='login' method="POST" class="login-form">
                    <input type="text" id="username" name="username" class="form-control" placeholder="Username" autocomplete="off">
                    <input type="password" id="password" name="password" class="form-control" placeholder="Parola">
                    <input type="submit" id="submit" class="form-control login-button" value="Conectare">
 		  		    <input type="hidden" name="${_csrf.parameterName}" value="${_csrf.token}" />
            </form>
            <c:if test="${not empty error}">
				<div class="error">${error}</div>
			</c:if>
			<c:if test="${not empty msg}">
				<div class="msg">${msg}</div>
			</c:if>	
        </div>
    </div>	
</body>
</html>
