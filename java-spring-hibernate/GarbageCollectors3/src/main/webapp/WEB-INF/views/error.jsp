<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>    
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
	<c:set var="exception" value="${requestScope['javax.servlet.error.exception']}"/>
	<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
	<title>GarbageCollectors3</title>
</head>
<body>
<div>Eroare!!!</div>
<div>${code}</div>
	<ul>
	    <li>Exception: <c:out value="${requestScope['javax.servlet.error.exception']}" /></li>
	    <li>Exception type: <c:out value="${requestScope['javax.servlet.error.exception_type']}" /></li>
	    <li>Exception message: <c:out value="${requestScope['javax.servlet.error.message']}" /></li>
	    <li>Request URI: <c:out value="${requestScope['javax.servlet.error.request_uri']}" /></li>
	    <li>Servlet name: <c:out value="${requestScope['javax.servlet.error.servlet_name']}" /></li>
	    <li>Status code: <c:out value="${requestScope['javax.servlet.error.status_code']}" /></li>
	    <li>Stack trace: <pre>${exception}</pre></li>
	</ul>
</body>
</html>