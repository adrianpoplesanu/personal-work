<?php
session_start();

// expirearea sesiunii dupa 30 minute
if (isset($_SESSION['LAST_ACTIVITY']) && (time() - $_SESSION['LAST_ACTIVITY'] > 1800)) {
    session_unset();
    session_destroy();
}
$_SESSION['LAST_ACTIVITY'] = time();

if (!isset($_SESSION['USERNAME'])) {
    header("Location: login.php");
    exit();
}
?>