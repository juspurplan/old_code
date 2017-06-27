<?php
require_once('./includes/config.php');

session_start();

$link = mysql_connect(DB_HOST, DB_USER, DB_PASSWORD);
mysql_select_db(DB_NAME, $link);

$user = @$_SESSION['user'];

function db_query(){
	global $link;
	$args = func_get_args();
	$query = "";
	if(count($args) == 1){
		$query = $args[0];
	}else if(count($args) > 1){
		$format = array_shift($args);
		$query = vsprintf($format, $args);
	}else{
		return null;
	}
	return mysql_query($query, $link);
}

function db_escape_str($str){
	global $link;
	return mysql_real_escape_string($str, $link);
}

function db_fetch_array($result){
	return mysql_fetch_array($result, MYSQL_BOTH);
}

function db_fetch_first($result){
	$arr = db_fetch_array($result);
	return $arr[0];
}

function db_count($result){
	return mysql_num_rows($result);
}

function db_hash_password($password){
	global $link;
	return hash("sha1", $password . DB_SALT );
}

function safe_str($str){
	return htmlspecialchars($str,ENT_COMPAT,"UTF-8");
}
?>