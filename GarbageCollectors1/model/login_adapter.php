<?php
include_once($_SERVER['DOCUMENT_ROOT'] . "/GarbageCollectors1/config.php");
include_once($UTILS_ROOT . 'dbapi.php');

class LoginAdapter {
    private $dbapi;

    function __construct() {
        $this->dbapi = new DbApi();
    }

    function validate($username, $password) {
        $results = $this->dbapi->execute("select * from USERS where username='". $username ."' and password='". $password ."'");
        if (count($results) == 1)
            return True;
        return False;
    }
}
?>