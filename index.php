<?php
session_start();

if (isset($_SESSION['id'])){
	header('Location:unset.php');
}

$statement1 = $statement2 = "";
$state1Err = $state2Err = "";
$check1 = $check2 = 0;

/************************************************************************/
/*							CREATE UNIQUE SESSION						*/
/************************************************************************/


if ($_SERVER["REQUEST_METHOD"] == "POST") {

	$statement1 = test_input($_POST["statement1"]);
	$statement2 = test_input($_POST["statement2"]);
 
	$_SESSION['statement1'] = $statement1;
	$_SESSION['statement2'] = $statement2;
	if (isset($_SESSION['statement1']) && isset($_SESSION['statement2'])){
		header('Location:set.php');
	}
}

function test_input($data) {
	$data = trim($data);
	$data = stripslashes($data);
	$data = htmlspecialchars($data);
	return $data;
}

?>

<!DOCTYPE html>
<html>
	<head>
		<title>Similarity Check</title>
		<link rel="stylesheet" type="text/css" href="css/styles.css">
	</head>

	<body>
		<div align="center" style="background-color:black; opacity:0.7; color:white; margin:30px; border: solid white; font-weight: bold; ">
			<h1></h1>
			<h2>Semantic Similarity between Sentences</h2>
			<br/>
		</div>

		<div class="body">
		<br/>
			<div style="margin: 3%; margin-left:5%; margin-right: 5%">

				<form action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>" method="POST">
					<fieldset>
						<table border="0" cellpadding="10" cellspacing="0" width="" align="center">
						<tr>
							<td><p>Statement 1:</p></td>
							<td></td>
							<td><p> <input type="text" name="statement1" id="statement1" required="required" placeholder="In WX notation" /></p></td>
							<td><p><span class="error" style="text-align:left;"><?php echo $state1Err;?></span></p></td>
						</tr>
						<tr>
							<td><p>Statement 2:</p></td>
							<td></td>
							<td><p><input type="text" name="statement2" id="statement2" required="required" placeholder="In WX notation" /></p></td>
							<td><p><span class="error" style="text-align:left;"><?php echo $state2Err;?></span></p></td>
						</tr>
						</table>
					</fieldset>
					<br/>
					<input type="submit" value="Submit" style="font-weight:bold;text-align: center;" />
				</form>

			</div>
		</div>

		<br/>
		<div class="footer_right">
			<p><a href="about_us.xhtml">ABOUT US</a></p>	
		</div>
	</body>
</html>