<?php
	require_once("header.php");
	require_once("authenticate.php");
	
	$serverCon = connect();

	
	if(isset($_SESSION['teacher_id'])){		
		$teacherId =$_SESSION['teacher_id'];	
		drawMenu();
		if(isset($_GET['action'])){
			$action = $_GET['action'];
			switch($action){
				case "viewClasses":				
					viewAllClasses($serverCon,$_SESSION['teacher_id']);
					break;
				case "classView":
					if(isset($_GET['value'])){viewClass($serverCon,$_GET['value']);}else{viewAllClasses($serverCon,$_SESSION['teacher_id']);}
					break;
				case 2:
					break;
			}
		}else{
			// do without action					
			viewAllClasses($serverCon,$_SESSION['teacher_id']);
		}		
	}else{
		header("Location: index.php");	
	}
	function connect(){
		$testCon = mysql_connect("localhost","root","");
		if ($testCon){			
			return $testCon;		
		}
	}
	
	function echoLink($name,$link){			
		echo "<a href=\"" . $link ."\">" . $name . "</a>";
	}
	
	
	function drawMenu(){
		echo"<center>";		 
		echoLink("Test|","");
		echoLink("Test|","");	
		echoLink("Test|","");	
		echo "</center>";		
	}
	
	function viewClass($con, $classID){
		mysql_select_db("gradebook", $con);
		$result = mysql_query("SELECT * FROM classes WHERE class_id='".$classID ."'");
		$row = mysql_fetch_array($result);
		$className = $row['class_name'];
		echo "<h2>".$className."</h2>";
		$students = array();
		$result = mysql_query("SELECT * FROM assignments WHERE class_id='".$classID ."'");
		while($row = mysql_fetch_array($result)){		
			$studentId =  $row['student_id'];
			if(!in_array($students,$studentId)){
				array_push($students,$studentId);		
			}			
		}
		array_unique($students);
		
		echo "<table border=\"1\">";
		foreach($students as $id){
			$result = mysql_query("SELECT * FROM students WHERE student_id='".$id."'");
			$row = mysql_fetch_array($result);
			echo "<tr>";
			echo "<td>";
			echo echoLink($row['firstname'].",".$row['lastname'],"");
			echo "</td>";
			echo "</tr>";
			
		}
		echo "</table>";	
	
	}
	
	function viewAllClasses($con,$teacherID){		
		mysql_select_db("gradebook", $con);
		$result = mysql_query("SELECT * FROM classes WHERE teacher_id='".$teacherID ."'");		
		echo "<table border=\"1\">";
		echo "<tr>";
		echo "<th>Class Name</th>";
		echo "</tr>";
		while($row = mysql_fetch_array($result)){
			echo "<tr>";
			echo "<td>";
			echo echoLink($row['class_name'],"http://localhost/teacherPanel.php?action=classView&value=".$row['class_id']);
			echo "</td>";
			echo "</tr>";		
		}
		echo "</table>";
	}

	
	
	
	
	
	
	
	
//	header("Location: index.php");	
	require_once("footer.php");
?>