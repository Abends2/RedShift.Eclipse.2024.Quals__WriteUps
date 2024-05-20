<?php
include("log.class.php");

class Welcome {
    public function handler($val) {
        return "Привет, " . $val . ", ";
    }
}

class User {
    private $name;
    private $wel;

    function __construct($name) {
        $this->name = $name;
        $this->wel = new Welcome();
    }

    function getWelcomeMessage() {
        return $this->wel->handler($this->name);
    }

    function __destruct() {
    }
}

?>
