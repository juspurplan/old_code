<?php

require_once('header.php');

if(isset($_SESSION['loggedIn']))
{	
	header('Location:index.php');

}else{
	echo '<center>
	<h1>Login:</h1>
	<form action="login_script.php" method="post">
		Username: <input type="text" name="user" /><br />
		Password: <input type="password" name="pass" /><br />
		<input type="submit" value="Login" />
	</form>
	</center>';

	require_once('footer.php');
}

require_once("footer.php");
/*teacher test login
user = hello
pass = world
fname = alan
lname = tan
id = 123

student test login
user = java
pass = compsci
fname = jorian
lname = khan
id = 789*/

?>