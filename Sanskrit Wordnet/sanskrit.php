<!DOCTYPE html>
<html>
<head>
	<title></title>
</head>
<body>

<table border="1" cellpadding="0" >

<tr>
<td>ID</td>	
<td>HEAD</td>	
<td>SYNSET</td>	
<td>CATEGORY</td>	
</tr>
<?php

$host = '127.0.0.1';
$uname = 'root';
$pass = 'Bazinga';
$dbname = 'sanskrit';

/*	Create connection	*/
$conn = new mysqli ($host,$uname,$pass,$dbname);

$sql = $conn->query("SELECT * FROM synset_table");
	while($row = $sql->fetch_assoc()){
		echo "
		<tr>
			<td>".$row['synset_id']."</td>
			<td>".$row['head']."</td>
			<td>".$row['synset']."</td>
			<td>".$row['category']."</td>
		</tr>";
	}

?>
</table>
</body>
</html>