<?php
session_start();

$id = $_SESSION['id'];

$host = '127.0.0.1';
$uname = 'root';
$pass = 'Bazinga';
$dbname = 'sanskrit';


$conn = new mysqli ($host,$uname,$pass,$dbname);

$sql = $conn->query("DROP TABLE morph".$id."");
$sql = $conn->query("DROP TABLE vibhakthi".$id."");

$conn->close();

session_unset(); 
session_destroy();
header('Location:index.php') 

?>