<?php
define('PAGE_ID', 'questions');
define('PAGE_NAME', 'Questions');

require_once('./includes/engine.php');
require_once('./includes/header.php');

echo '<div class="content">';

$query = db_query("SELECT %squestions.id,%squestions.uid,%susers.name,%squestions.question FROM %squestions,%susers WHERE %squestions.uid = %susers.id ORDER BY time DESC", DB_PREFIX, DB_PREFIX, DB_PREFIX, DB_PREFIX, DB_PREFIX, DB_PREFIX, DB_PREFIX, DB_PREFIX);
while($question = db_fetch_array($query)){
	echo '<div class="question" id="question-'.$question['id'].'">
			<span><a href="'.SITE_PATH.'/question?id='.$question['id'].'"><strong>'.safe_str($question['name']).'</strong> asks: '.safe_str($question['question']).'</a></span>
		</div>';
}

echo '</div>';

require_once('./includes/footer.php');
?>