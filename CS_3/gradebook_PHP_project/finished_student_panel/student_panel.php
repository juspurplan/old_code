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
	
	//right now putting a class into the serialized array
	if(empty($classes))
	{
		$classes[0]=1;
		$classes[1]=2;
		$inserted_array = serialize($classes);
		mysql_query("INSERT INTO students (classes) VALUES(".$inserted_array.") WHERE student_id='".$_SESSION['student_id']."'");
	}
	var_dump($classes);
	
	//send post data from js to php
	echo '<script>
	function view(bool, class_id, student_id)
	{
		window.location="student_view_assignment.php?view="+bool+"&class_id="+class_id+"&student_id="+student_id+"";
	}
	</script>';

	
	echo '<table border = "1">';
	echo '<tr> <th>Class</th> <th>Class ID</th> <th>Teacher</th></tr>';
	for($index = 0; $index<sizeof($classes); $index++)
	{
		$result_class = mysql_query('SELECT class_name, class_id, teacher_id FROM classes WHERE class_id=\''.$classes[$index].'\'');
		$row_class = mysql_fetch_array($result_class);
		$result_teacher = mysql_query('SELECT firstname, lastname FROM teachers WHERE teacher_id=\''.$row_class['teacher_id'].'\'');
		$row_teacher= mysql_fetch_array($result_teacher);
		echo '<tr> <td onclick="view('.true.','.$row_class['class_id'].','.$_SESSION['student_id'].')">'.$row_class['class_name'].'</td> <td>'.$row_class['class_id'].'</td> <td>'.$row_teacher['firstname'].' '.$row_teacher['lastname'].'</td> </tr>';
	}
	
	require_once('footer.php');

?>