<?php
define('PAGE_ID', 'questions');
define('PAGE_NAME', 'Questions');

require_once('./includes/engine.php');

$id = $_GET['id'];

if(empty($_GET['id']) || !is_numeric($_GET['id'])){
	$error = "No question defined.";
}

if(!empty($_POST['answer']) && !empty($user)){
	$answer = db_escape_str($_POST['answer']);
	db_query("INSERT INTO %sanswers (uid,qid,answer,time) VALUES ('%d','%d','%s','%d')", DB_PREFIX, $user['id'], (int)$id, $answer, time());
}

$query = db_query("SELECT id,uid,question FROM %squestions WHERE id = '%d' ORDER BY time ASC LIMIT 1", DB_PREFIX, $id);
if(db_count($query) < 1){
	$error = "Cannot find question.";
}else{
	$question = db_fetch_array($query);
}

require_once('./includes/header.php');

echo '<div class="content">';
if(!empty($error)){
	echo '<div class="error">'.$error.'</div>';
}else{
	echo '<div class="question" id="question-'.$question['id'].'">
		<span>'.safe_str($question['question']).'</span>
	</div>';
	$query = db_query("SELECT %sanswers.id,uid,name,qid,answer FROM %sanswers,%susers WHERE uid = %susers.id AND qid = '%d'", DB_PREFIX, DB_PREFIX, DB_PREFIX, DB_PREFIX, $question['id']);
	while($answer = db_fetch_array($query)){
		echo '<div class="answer" id="answer-'.$answer['id'].'">
			<span><strong>'.safe_str($answer['name']).'</strong> answers: '.safe_str($answer['answer']).'</span>
		</div>';
	}
	if(!empty($user)){
		echo '<br>
		<form method="POST" action="'.SITE_PATH.'/question?id='.$id.'">
			<label for="answer">Answer:</label><br>
			<textarea id="answer" name="answer"></textarea><br>
			<input type="submit" name="post" value="Post" />
		</form>';
	}
}
echo '</div>';

require_once('./includes/footer.php');
?>