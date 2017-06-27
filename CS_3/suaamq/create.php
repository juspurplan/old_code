<?php
define('PAGE_ID', 'create');
define('PAGE_NAME', 'Create');

require_once('./includes/engine.php');

if(empty($user)){
	$error = "You must be logged in.";
}else if(!empty($_POST['question'])){
	$question = db_escape_str($_POST['question']);
	db_query("INSERT INTO %squestions (uid,question,time) VALUES ('%d','%s','%d')", DB_PREFIX, $user['id'], $question, time());
	header('Location: '.SITE_PATH.'/questions');
}

require_once('./includes/header.php');

echo '<div class="content">';
if(!empty($error)){
	echo '<div class="error">'.$error.'</div>';
}else{
	echo '<form method="POST" action="'.SITE_PATH.'/create">
		<label for="question">Question:</label><br>
		<textarea id="question" name="question"></textarea><br>
		<input type="submit" name="post" value="Post" />
	</form>';
}
echo '</div>';

require_once('./includes/footer.php');
?>