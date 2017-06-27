<?php

	if(isset($_POST['view']) && isset($_POST['class_id']) && isset($_POST['student_id']) )
	{
		if($_POST['view']==true)
		{
			$str = '<table border="1">';
			$str .='<tr> <th>Assignment</th> <th>Description</th> <th>Grade</th> </tr>';
			$con = mysql_connect('localhost','root','');
			mysql_select_db('gradebook',$con);
			$result = mysql_query("SELECT assignment_name, assignment_desc, grade FROM assignments WHERE class_id='".$_POST['class_id']."' AND student_id='".$_POST['student_id']."'");
			while($row = mysql_fetch_array($result))
			{
				 $str .= '<tr> <td>'.$row['assignment_name'].'</td> <td>'.$row['assignment_desc'].'</td> <td>'.$row['grade'].'</td> </tr>';
			}
			echo $str;
		}
	}
	else
	{
	}

?>