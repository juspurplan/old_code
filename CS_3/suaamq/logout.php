<?php
require_once('./includes/engine.php');

unset($_SESSION);
session_destroy();

header('Location: '.SITE_PATH.'/home');
?>