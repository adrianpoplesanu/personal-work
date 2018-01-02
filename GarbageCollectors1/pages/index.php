<?php
include_once($_SERVER['DOCUMENT_ROOT'] . "/GarbageCollectors1/config.php");
include_once($_SERVER['DOCUMENT_ROOT'] . "/GarbageCollectors1/utils/session.php");

include_once($CONTROLLER_ROOT . 'homepage_controller.php');
$controller = new HomepageController();
$controller->index();
?>