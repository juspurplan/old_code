<?php

	require_once('header.php');
	require_once('authenticate.php');
	if(isset($_SESSION['teacher_id']))
	{
		if($_SESSION['teacher_id'] != '')
		{
			header('Location:teacher_home.php');
		}
	}
	
	echo 'this is the student page<br/>';
	echo '<a href="logout_script.php">Log Out</a>';
	
	$con = mysql_connect('localhost','root','');
	mysql_select_db('gradebook',$con);
	
	$result = mysql_query('SELECT classes FROM students WHERE student_id=\''.$_SESSION['student_id'].'\'');
	$row = mysql_fetch_array($result);
	$classes= unserialize($row['classes']);
	if(empty($classes))
	{
		$classes[0]=1;
		$inserted_array = serialize($classes);
		mysql_query("INSERT INTO students (classes) VALUES(".$inserted_array.") WHERE student_id='".$_SESSION['student_id']."'");
	}
	var_dump($classes);
	
	echo '<table border = "1">';
	echo '<tr> <th>Class</th> <th>Class ID</th> </tr>';
	for($index = 0; $index<sizeof($classes); $index++)
	{
		echo '<tr> <td>'.$classes[$index].'</td> <td>'.$classes[$index].'</td> </tr>';
	}
	
	require_once('footer.php');

?>