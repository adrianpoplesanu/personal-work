<?php
class BaseController {

    function __construct() {
        global $VIEW_ROOT; // taken from config.php, which is included in the route file
        global $AHOST; // taken from config.php, which is included in the route file
        $this->view_root = $VIEW_ROOT;
        $this->ahost = $AHOST;
    }

    public function template_response($template, $env=array()) {
        $env['ahost'] = $this->ahost;
        extract($env);
        include_once($this->view_root . $template . '.php');
    }
}
?>