<?php

	require_once('header.php');

	//connecting to server and selecting db
	$con = mysql_connect('localhost','root','');
	mysql_select_db('haikusite',$con);
	
	//escaping all strings from $_POST
	$name = mysql_escape_string($_POST['name']);
	$email = mysql_escape_string($_POST['email']);
	$country = mysql_escape_string($_POST['country']);
	
	//inserting user int 'users' table
	mysql_query("INSERT INTO users (name, email, country) VALUES ('".$name."', '".$email."', '".$country."')");
	
	//echoing that a user has been added
	echo'User: '.$name.' added <br/>';
	echo'<a href="index.php">Back to Home</a>';
	
	
	require_once('footer.php');
	
?>

