<?php
include("user.class.php");

ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL);

if (!isset($_COOKIE['user'])) {
    $user = new User('loser');
    setcookie("user", base64_encode(serialize($user)));
} else {
    $user = unserialize(base64_decode($_COOKIE['user']));
}

echo $user->getWelcomeMessage();
echo "как тебе мой печенькообработчик?\n";
?>
