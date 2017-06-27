<?php

	require_once('header.php');

	echo'<a href="index.php">Home</a> <br/> <br/>';
	
	//echoing a submission form for adding users.
	echo'<form action="addComplete.php" method="post">
		Name:	<input type="text" name="name" /> <br/>
		Email:	<input type="text" name="email" /> <br/>
		Country:<input type="text" name="country" /> <br/>
		<input type="submit" value="Add User" />
	</form>';
	
	require_once('footer.php');
	
?>