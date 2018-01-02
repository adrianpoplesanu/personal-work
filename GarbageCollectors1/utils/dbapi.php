<?php
/*
* dbapi class object, use with include_once
* needs to be instatiated for usage
*/
class DbApi {
    public $connection;
    public $is_associative_array;

    function __construct() {
        $this->connection = mysqli_connect('localhost:3306', 'root', 'aaa', 'garbagecollectors1');
        $this->is_associative_array = False;
    }

    public function setDict($value) {
        $old = $this->is_associative_array;
        if ($value) {
            $this->is_associative_array = True;
        } else {
            $this->is_associative_array = False;
        }
        return $old;
    }

    public function execute($query) {
        $results = mysqli_query($this->connection, $query);
        if ($this->is_associative_array) {
            $rows = mysqli_fetch_all($results, MYSQLI_ASSOC);
        } else {
            $rows = mysqli_fetch_all($results, MYSQLI_NUM);
        }
        return $rows;
    }

    public function insert($query) {
        $results = mysqli_query($this->connection, $query);
        return $results;
    }

    // TODO: maybe update and delete methods.
}
?>