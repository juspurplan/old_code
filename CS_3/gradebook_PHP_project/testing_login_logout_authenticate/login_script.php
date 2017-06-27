<?php
require_once("header.php");
$con = mysql_connect('localhost','root','');
mysql_select_db('gradebook',$con);

if($_SERVER['REQUEST_METHOD'] == 'POST')
{
	//$result = mysql_query("SELECT student_id, username, password FROM students WHERE username='" . $_POST['user'] . "' AND password='" . $_POST['pass'] . "' UNION SELECT teacher_id, username, password FROM teachers WHERE username='" . $_POST['user'] . "' AND password='" . $_POST['pass'] . "'");
    $students = mysql_query("SELECT student_id, username, password FROM students WHERE username='" . $_POST['user'] . "' AND password='" . $_POST['pass'] . "'");
    $teachers = mysql_query("SELECT teacher_id, username, password FROM teachers WHERE username='" . $_POST['user'] . "' AND password='" . $_POST['pass'] . "'");
	if(mysql_num_rows($teachers) > 0) 
	{
		$row = mysql_fetch_array($teachers);
		session_start();
		$_SESSION['loggedIn']=true;
		$_SESSION['teacher_id']=$row['teacher_id'];
		$_SESSION['first_name']=$row['firstname'];
		header('Location: teacherPanel.php');
    }
	else if(mysql_num_rows($students) > 0)
	{
		$row = mysql_fetch_array($students);
		session_start();
		$_SESSION['loggedIn']=true;
		$_SESSION['student_id']=$row['student_id'];
		$_SESSION['first_name']=$row['firstname'];
		header('Location:student_home.php');
	}
	else
	{
		echo 'Wrong Username or Password';
	}
}
require_once("footer.php");
?>