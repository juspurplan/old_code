<?php
	session_start();
	echo "<html>";
	echo "<body>";	
	echo "<center>";
	echo "<h1>GradeBook</h1>";
	
	$homeLink ="<a href=\"http://localhost/gradebook/index.php\"> Home |</a>";
	$loginLink="<a href=\"http://localhost/gradebook/login.php\">| Login |</a>";
	$logoutLink="<a href=\"http://localhost/gradebook/logout_script.php\">| Logout |</a>";
	$teacherLink="<a href=\"http://localhost/gradebook/teacher_panel.php\"> Teacher Panel |</a>";
	$studentLink="<a href=\"http://localhost/gradebook/student_panel_withAJAX.php\"> Student Panel |</a>";
	
	
	var_dump($_SESSION);
	if(isset($_SESSION['loggedIn']))
	{	
		echo $logoutLink;
		echo $homeLink;		
		if(isset($_SESSION['teacher_id']))
		{
			echo $teacherLink;
		}
		else
		{
			echo $studentLink;
		}
	}
	else
	{
		echo $loginLink;
		echo $homeLink;
	}
	
	
	// echo $homeLink;
	// echo $homeLink;
	echo "<hr/>";
	echo "</center>";
	
?>
