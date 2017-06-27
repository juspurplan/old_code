<?php
require_once('./includes/engine.php');

$username = @$_POST['username'];
$password = @$_POST['password'];

if(empty($username) || empty($password)){
	$login_error = "Y U NO FILL FIELDS?";
}else{
	$username = db_escape_str($username);
	$password = db_hash_password($password);
	$query = db_query("SELECT id,username,password,name FROM %susers WHERE username = '%s' AND password = '%s' LIMIT 1", DB_PREFIX, $username, $password);
	if(db_count($query) < 1){
		$login_error = "Invalid username or password.";
	}else{
		$user = db_fetch_array($query);
		$user['name'] = safe_str($user['name']);
		$_SESSION['user'] = $user;
	}
}

require_once('./home.php');
?>