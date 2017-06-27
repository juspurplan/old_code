<?php

	require_once('header.php');
	require_once('authenticate.php');
	
	$class_id = $_GET['class_id'];
	$student_id = $_GET['student_id'];
	$con = mysql_connect('localhost','root','');
	mysql_select_db('gradebook',$con);
	
	$result = mysql_query('SELECT class_name, teacher_id FROM classes WHERE class_id=\''.$class_id.'\'');
	$row = mysql_fetch_array($result);
	$teacher = mysql_query('SELECT firstname, lastname FROM teachers WHERE teacher_id=\''.$row['teacher_id'].'\'');
	$teacher_row = mysql_fetch_array($teacher);
	
	echo '<h1>'.$row['class_name'].'</h1>';
	echo '<h2>'.$teacher_row['firstname'].' '.$teacher_row['lastname'].'</h2> <br/>';
	echo '<table border="1">';
	echo '<tr> <th>Assignment</th> <th>Description</th> <th>Grade</th> </tr>';
	
	$assignment_query = mysql_query("SELECT assignment_name, assignment_desc, grade FROM assignments WHERE class_id='".$class_id."' AND student_id='".$student_id."'");
	while($assignment_row = mysql_fetch_array($assignment_query))
	{
		echo '<tr> <td>'.$assignment_row['assignment_name'].'</td> <td>'.$assignment_row['assignment_desc'].'</td> <td>'.$assignment_row['grade'].'</td> </tr>';
	}
	
	require_once('footer.php');
	
?>