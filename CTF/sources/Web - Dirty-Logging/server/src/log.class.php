<?php
  class Log {
    private $type_log;

    function __costruct($hnd) {
      $this->$type_log = $hnd;
    }

    public function handler($val) {
      include($this->type_log);
      echo "LOG: " . $val;
    }
  }
?>
