<?php
define('PAGE_ID', 'home');
define('PAGE_NAME', 'Home');

require_once('./includes/engine.php');

if(!empty($_POST['register'])){
	$username = @db_escape_str($_POST['username']);
	$password = @$_POST['password'];
	$confirm_password = @$_POST['confirm_password'];
	$name = @db_escape_str($_POST['name']);
	if(empty($username) || empty($password) || empty($confirm_password) || empty($name)){
		$error = "Please fill in all fields.";
	}else{
		if($password != $confirm_password){
			$error = "Passwords do not match.";
		}else{
			$query = db_query("SELECT count(id) FROM %susers WHERE username = '%s' LIMIT 1", DB_PREFIX, $username);
			$count = db_fetch_first($query);
			if($count > 0){
				$error = "Username taken.";
			}else{
				db_query("INSERT INTO `%susers` (username,password,name) VALUES ('%s','%s','%s')", DB_PREFIX, $username, db_hash_password($password), $name);
				header('Location: '.SITE_PATH.'/home');
			}
		}
	}
}

require_once('./includes/header.php');

echo '<div class="content">
	<h1>Register</h1>
	'.(isset($error) ? '<div class="error">'.$error.'</div>' : '').'
	<form class="register" method="POST" action="'.SITE_PATH.'/register">
		<label for="username">Username:</label>
		<input type="text" id="username" name="username" value="" /><br>
		<label for="password">Password:</label>
		<input type="password" id="password" name="password" value="" /><br>
		<label for="confirm_password">Confirm Password:</label>
		<input type="password" id="confirm_password" name="confirm_password" value="" /><br>
		<label for="name">Display Name:</label>
		<input type="text" id="name" name="name" value="" /><br>
		<input type="submit" name="register" value="Register" />
	</form>
</div>';

require_once('./includes/footer.php');
?>