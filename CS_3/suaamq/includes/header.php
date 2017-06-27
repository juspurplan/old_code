<?php
echo '<html>
<body>
<title>'.SITE_NAME. (defined('PAGE_NAME') ? ' : ' . PAGE_NAME : '' ) . '</title>
<link rel="stylesheet" type="text/css" href="'.SITE_PATH.'/main.css" />
</body>
<head>
<div class="header">
	<div class="quick_login">
		'.(empty($user) ? '
		<form method="POST" action="'.SITE_PATH.'/login">
			<label class="login_label" for="username">Username:</label>
			<input type="text" id="username" name="username" value="" />
			<label class="login_label" for="password">Password:</label>
			<input type="password" id="password" name="password" value="" />
			<input type="submit" value="Login" />
			<a href="'.SITE_PATH.'/register">Register &raquo;</a>
			'.(isset($login_error) ? '<div class="error">'.$login_error.'</div>' : '').'
		</form>
		' : '<span>Welcome back, '.$user['name'].'</span><br><a href="'.SITE_PATH.'/logout">Logout &raquo;</a>').'
	</div>
	<h1></h1>
	<div class="navigation">
		<ul class="tabs">
			<li'.(PAGE_ID == 'home' ? ' class="selected"' : '').'><a href="'.SITE_PATH.'/home">Home</a></li>
			<li'.(PAGE_ID == 'questions' ? ' class="selected"' : '').'><a href="'.SITE_PATH.'/questions">Questions</a></li>
			<li'.(PAGE_ID == 'create' ? ' class="selected"' : '').'><a href="'.SITE_PATH.'/create">Create</a></li>
		</ul>
	</div>
</div>
';
?>