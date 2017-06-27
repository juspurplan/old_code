<?php
	require_once("header.php");
	require_once("authenticate.php");
	
	$serverCon = connect();
	
	drawMenu();	
	viewClasses($serverCon,0);
	
	if(isset($_SESSION['teacher_id'])){		
		$teacherId =$_SESSION['teacher_id'];	
		
		if(isset($_GET['action'])){
			$action = $_GET['action'];
			switch($action){
				case "viewClasses":			viewClasses($serverCon,$teacherId);	
					break;
				case 1:
					break;
				case 2:
					break;
			}
		}else{
			// do without action		
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
		echoLink("ViewClasses|","teacher_panel.php?action=viewClasses");
		echoLink("Test|","");	
		echoLink("Test|","");	
		echo "</center>";		
	}
	
	function viewClasses($con,$teacherID){		
		mysql_select_db("gradebook", $con);
		$result = mysql_query("SELECT * FROM classes WHERE teacher_id='".$teacherID ."'");		
		echo "<table border=\"1\">";
		echo "<tr>";
		echo "<th>Class Name</th>";
		echo "</tr>";
		while($row = mysql_fetch_array($result)){
			echo "<tr>";
			echo "<td>";
			echo $row['class_name'];
			echo "</td>";
			echo "</tr>";		
		}
		echo "</table>";
	}
	
	
	
	
	
	

	
	
	
	
	
	
	
	
//	header("Location: index.php");	
	require_once("footer.php");
?>