<?php
session_start();

if (isset($_SESSION['statement1']) && isset($_SESSION['statement2'])){
	$id = rand(0,1000000).time();
	$_SESSION['id'] = $id;
	header('Location:action_page.php');
}
else { header('Location: index.php');}
?>