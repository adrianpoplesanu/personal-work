<?php
include_once($CONTROLLER_ROOT . '/base_controller.php');

class HomepageController extends BaseController {

    function __construct() {
        parent::__construct();
    }

    public function index() {
        $env = array();
        $env['username'] = $_SESSION['USERNAME'];
        $this->template_response("home", $env);
    }
}
?>