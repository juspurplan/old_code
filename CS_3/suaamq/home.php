<?php
define('PAGE_ID', 'home');
define('PAGE_NAME', 'Home');

require_once('./includes/engine.php');

$query = db_query("SELECT question FROM %squestions ORDER BY RAND() ASC LIMIT 1", DB_PREFIX);
$random_question = safe_str(db_fetch_first($query));

require_once('./includes/header.php');

echo '<div class="content">
	<h1>Shut up and Answer my Question!</h1>
	<div class="section">Lorem ipsum dolor sit amet, consectetur adipiscing elit. Integer gravida bibendum lacus, nec lacinia neque fermentum eget. Nulla facilisis, ante eget ullamcorper auctor, lorem erat vulputate sem, at iaculis lectus enim vel urna. Sed sed massa ut tortor luctus blandit et nec eros. Cras ut tincidunt lorem. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Integer sit amet elit ac arcu volutpat luctus non a quam. Morbi a augue ut urna condimentum cursus ut a neque. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae;</div>
	<div class="section"><strong>Random Question: </strong>'.$random_question.'</div>
</div>';

require_once('./includes/footer.php');
?>