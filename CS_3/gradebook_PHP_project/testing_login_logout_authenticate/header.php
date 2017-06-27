<?php
	session_start();
	echo "<html>";
	echo "<body>";	
	echo "<center>";
	echo "<h1>GradeBook</h1>";
	
	$homeLink ="<a href=\"http://localhost/\">Home |</a>";
	$loginLink="<a href=\"http://localhost/login.php\">Login |</a>";
	$logoutLink="<a href=\"http://localhost/logout_script.php\">Logout |</a>";
	$teacherLink="<a href=\"http://localhost/teacherPanel.php\">Teacher Panel</a>";
	
	if(isset($_SESSION['loggedIn']))
	{	
		echo $logoutLink;		
	}
	else{
		echo $loginLink;
	}
	
	echo $homeLink;
	echo $teacherLink;
	// echo $homeLink;
	// echo $homeLink;
	echo "<hr/>";
	echo "</center>";
	
?>
