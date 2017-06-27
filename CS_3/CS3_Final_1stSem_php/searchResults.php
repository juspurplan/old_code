<?php

	require_once('header.php');
	
	//printing out links
	echo'<a href="index.php">Go To Home</a> <br/>
	<a href="search.php">Search Again</a> <br/><br/>';
	
	//connecting to server and selecting db
	$con = mysql_connect('localhost','root','');
	mysql_select_db('haikusite',$con);
	
	//getting search string, escaping it, and spliting it with " " delimiter
	$search = mysql_escape_string($_GET['search']);
	$key_words = explode(' ',$search);
	$key_letters = array();
	
	//populate key_letters
	for($index = 0; $index<sizeof($key_words) ; $index++)
	{
		array_push($key_letters, substr($key_words[$index], 0, 1));
	}
	
	//get all users
	$users = array();
	$query = mysql_query("SELECT * FROM users ");
	while($row = mysql_fetch_array($query))
	{
		array_push($users, $row);
	}
	
	//filter users first by key word then by first letter
	$users_filtered = array();
	for($index = 0; $index<sizeof($users); $index++)
	{
		$row = $users[$index];
		$name = $row['name'];
		if(in_array($name, $key_words, false) || in_array( substr($name,0,1), $key_letters, false))
		{
			array_push($users_filtered, $users[$index]);
		}
	}
	
	//create list of ids
	$ids = array();
	for($index = 0; $index<sizeof($users_filtered) ; $index++)
	{
		$row = $users_filtered[$index];
		array_push($ids, $row['id']);
	}
	
	
	//checking to see if there are ids that can be used to search
	if(sizeof($ids) > 0)
	{
		//creating query
		$query = "SELECT * FROM haiku WHERE userid='" .$ids[0]. "'";
		for($index = 1; $index<sizeof($ids) ; $index++)
		{
			$query .= " UNION ";
			$query .= "SELECT * FROM haiku WHERE userid='" .$ids[$index]. "'";
		}
		$query .=" ORDER BY title DESC";
		
		//quering db
		$result = mysql_query($query);
		
		//printing resulting haikus
		while($row = mysql_fetch_array($result))
		{
			$author = mysql_fetch_array( mysql_query("SELECT * FROM users WHERE id='" .$row['userid']. "'") ); //finding out the authors name given the userid
			echo'Author: '.$author['name'].' <br/> Title: '.$row['title'].'<br/>'.$row['haikuText'].'<br/> <br/>';
		}
	}
	else
	{
		echo 'No Results. Please refine your search.';
	}	
	
	require_once('footer.php');

?>