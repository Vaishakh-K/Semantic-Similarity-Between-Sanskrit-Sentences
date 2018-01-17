<?php 
session_start();

if (!isset($_SESSION['id']) || !isset($_SESSION['similarity'])){
	header('Location:index.php');
}

else{
	$similarity = $_SESSION['similarity'];
	$id = $_SESSION['id'];

	if ($_SERVER["REQUEST_METHOD"] == "POST"){
		header('Location:display.php');
	}
}
?>



<!DOCTYPE html>
<html>
<head>
	<title>	</title>
	<link rel="stylesheet" type="text/css" href="css/styles.css">
	<script src="style.js"></script>
</head>
<body>

	<div align="center" style="background-color:black; opacity:0.7; color:white; margin:30px; border: solid white; font-weight: bold; ">
		<h1></h1>
		<h2>Semantic Similarity between Sentences</h2>
		<br/>
	</div>

	<br/><br/><hr/><br/>
	
	<fieldset class="field" style="	margin-left: 15%; margin-right: 15%;">
	<fieldset>
		<legend><span style="color:red; background-color: white;"> Working on ID:<b> <?php echo $id;?></b> </span></legend>
		<span class="score_print">Our algorithm gives a similarity score of <?php echo ceil($similarity); ?>%</span>
	</fieldset>
	</fieldset>

	<br/><br/>

	<form method="POST" action="<?php echo $_SERVER["PHP_SELF"]; ?>" style="text-align: center;" >
		<button style="display: inline-block; font-weight: bold; color: Black; 	font-size: 110%;" name="details">View Details</button>
	</form>
	<br/><hr/><br/>

	<div class="footer_right" >
		<p><a href="unset.php">HOME PAGE</a></p>
	</div>

</body>
</html>