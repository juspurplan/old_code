<?php
	
	require_once('header.php');
	
	//echoing a search form
	echo'<h4>Search A Haiku:</h4>
	<form action="searchResults.php" method="get">
		<input type="text" name="search" /> <br/>
		<input type="submit" value="Search" />
	</form>';
	
	require_once('footer.php');
	
?>