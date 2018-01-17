<?php
session_start();

if (isset($_SESSION['id'])){
	$id = $_SESSION['id'];

	$host = '127.0.0.1';
	$uname = 'root';
	$pass = 'Bazinga';
	$dbname = 'sanskrit';
}

else{
	header('Location:index.php');
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

	<br/><hr/><br/>

	<fieldset class="field">
	<fieldset>
		<legend><span style="color:red; background-color: white;"> <b>Tokenized table</b> </span></legend>
		<table cellpadding="10" cellspacing="0" align="center" border="1" style="text-align: center">
		<tr>
			<th>No.</th>
			<th>Statement</th>
			<th>Word</th>
			<th>Form</th>
			<th>Gender</th>
			<th>Tense</th>
			<th>Vibhakthi</th>
			<th>Person</th>
			<th>Num (Vachana)</th>
			<th>Base Form</th>
		</tr>
		<?php

/*	Printing the output for reference	*/
			$conn = new mysqli ($host,$uname,$pass,$dbname);

			$sql = $conn->query("SELECT * FROM morph".$id."");
			if ($sql->num_rows>0){
				while($row = $sql->fetch_assoc()){
					echo "
					<tr>
						<td>".$row['no']."</td>
						<td>".$row['statement']."</td>
						<td>".$row['word']."</td>
						<td>".$row['form']."</td>
						<td>".$row['gender']."</td>
						<td>".$row['tense']."</td>
						<td>".$row['vibhakthi']."</td>
						<td>".$row['person']."</td>
						<td>".$row['num_vachana']."</td>
						<td>".$row['base_form']."</td>
					</tr>";
				}
			}
			$conn->close();
		?>
		</table>
	</fieldset>
	</fieldset>

	<br/><hr/><br/>
	
	<fieldset class="field">
	<fieldset>
		<legend><span style="color: red; background-color: white"> <b>Base Form / Root Form table</b> </span></legend>
		<table cellpadding="10" cellspacing="0" align="center" border="1" style="text-align: center">
		<tr>
			<th>St. No.</th>
			<th>Prathama</th>
			<th>Dwithiya</th>
			<th>Thrithiya</th>
			<th>Chathurthi</th>
			<th>Panchami</th>
			<th>Sashti</th>
			<th>Sapthami</th>
			<th>Verb</th>
			<th>Other Words</th>
		</tr>

		<?php
			$conn = new mysqli ($host,$uname,$pass,$dbname);

			$sql = $conn->query("SELECT * FROM vibhakthi".$id."");
			if ($sql->num_rows > 0){
				while($row = $sql->fetch_assoc()){
					echo "
					<tr>
						<td>".$row['no']."</td>
						<td>".$row['prathama']."</td>	
						<td>".$row['dwithiya']."</td>	
						<td>".$row['thrithiya']."</td>	
						<td>".$row['chaturthi']."</td>	
						<td>".$row['panchami']."</td>	
						<td>".$row['sashti']."</td>	
						<td>".$row['sapthami']."</td>	
						<td>".$row['verb']."</td>
						<td>".$row['others']."</td>
					</tr>";
				}
			}
			$conn->close();
		?>
		</table>
	</fieldset>
	</fieldset>

	<br/><hr/><br/>

	
	<div class="footer_right" >
		<p><a href="unset.php">HOME PAGE</a></p>
	</div>

	<div class="footer_left" >
		<p><a href="score_page.php">GO BACK</a></p>
	</div>
</body>
</html>