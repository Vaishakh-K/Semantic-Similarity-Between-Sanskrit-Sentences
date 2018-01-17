<?php
session_start();
$statement1 = $_SESSION['statement1'];
$statement2 = $_SESSION['statement2'];

$host = '127.0.0.1';
$uname = 'root';
$pass = 'Bazinga';
$dbname = 'sanskrit';

/************************************************************************/
/*							CREATE CONNECTION							*/
/************************************************************************/

$conn = new mysqli ($host,$uname,$pass,$dbname);


/************************************************************************/
/*					REDIRECT IF NO SESSION IS SET 						*/
/************************************************************************/

if (!$_SESSION['id']){
	header('Location:index.php');
}

$id = $_SESSION['id'];

/************************************************************************/
/*							SCORING VARIABLES 							*/
/************************************************************************/

$score_array = array();
$similarity = $score_noun = $score_verb = $score_other= 0;
$max_noun_score = $max_verb_score = $max_other_score = 0;
$incr_noun = 8;
$incr_verb = 10;
$incr_other = 5;


/************************************************************************/
/*																		*/
/*		CREATE MORPH TABLE WHICH STORES PROPERTIES OF EACH WORD			*/
/*																		*/
/************************************************************************/

$sql = $conn->query("
CREATE TABLE morph".$id." (
no INT(6) UNSIGNED AUTO_INCREMENT PRIMARY KEY,
statement INT(1),
word VARCHAR(100) NULL,
form  VARCHAR(100) NULL,
gender VARCHAR(100) NULL,
tense VARCHAR(100) NULL,
vibhakthi VARCHAR(100) NULL,
person VARCHAR(100) NULL,
num_vachana VARCHAR(100) NULL,
base_form VARCHAR(100) NULL
);
");




/************************************************************************/
/*																		*/
/*			CREATE VIBHAKTHI TABLE WHICH STORES BASE FORMS 				*/
/*																		*/
/************************************************************************/

$sql = $conn->query("
CREATE TABLE vibhakthi".$id."(
no INT(6) UNSIGNED AUTO_INCREMENT PRIMARY KEY,
prathama VARCHAR(100) NULL,
dwithiya VARCHAR(100) NULL,
thrithiya VARCHAR(100) NULL,
chaturthi VARCHAR(100) NULL,
panchami VARCHAR(100) NULL,
sashti VARCHAR(100) NULL,
sapthami VARCHAR(100) NULL,
verb VARCHAR(100) NULL,
others VARCHAR(100) NULL
);
");




/************************************************************************/
/*																		*/
/*						TOKENIZING STATEMENT 1	 						*/
/*																		*/
/************************************************************************/


$st1 = strtok ($statement1, " ");
while ($st1 !== false){


/************************************************************************/
/*			CALL C EXECUTABLE TO GET PROPERTIES OF EACH WORD			*/
/************************************************************************/

	$output = exec("pwd");
	$prgfile = "Morph_Analyser/./a.out ".$st1."";
	exec($prgfile, $output);


/************************************************************************/
/*				INSERT WORD PROPERTIES INTO THE DATABASE				*/
/************************************************************************/


	if ($output[0] == "Dhatu in list not found"){

		$utf_base = exec("sudo -u www-data python indic-wx-converter-master/toutf.py ".$st1."");

		$sql = $conn->prepare("INSERT INTO morph".$id."(statement,word,form,gender,vibhakthi,num_vachana,base_form) VALUES(1,?,'','','','',?)");
		$sql->bind_param("ss", $st1, $utf_base);
		$sql->execute();
	}

	else {
		if (sizeof($output) == 6){
			$utf_base = exec("sudo -u www-data python indic-wx-converter-master/toutf.py ".$output[5]."");
			
			if ($output[3] == "Noun"){
				$sql = $conn->prepare("INSERT INTO morph".$id."(statement,word,form,gender,vibhakthi,num_vachana,base_form) VALUES(1,?,?,?,?,?,?)");
				$sql->bind_param("ssssss", $st1, $output[3], $output[0], $output[1], $output[2], $utf_base);
				$sql->execute();
			}

			if ($output[3] == "Verb"){
				$sql = $conn->prepare("INSERT INTO morph".$id."(statement,word,form,tense,person,num_vachana,base_form) VALUES(1,?,?,?,?,?,?)");
				$sql->bind_param("ssssss", $st1, $output[3], $output[0], $output[1], $output[2], $utf_base);
				$sql->execute();
			}
		}

		else if (sizeof($output) == 9){
			$utf_base = exec("sudo -u www-data python indic-wx-converter-master/toutf.py ".$output[8]."");
			
			if ($output[6] == "Noun"){
				$sql = $conn->prepare("INSERT INTO morph".$id."(statement,word,form,gender,vibhakthi,num_vachana,base_form) VALUES(1,?,?,?,?,?,?)");
				$sql->bind_param("ssssss", $st1, $output[6], $output[0], $output[1], $output[2], $utf_base);
				$sql->execute();

				$sql = $conn->prepare("INSERT INTO morph".$id."(statement,word,form,gender,vibhakthi,num_vachana,base_form) VALUES(1,?,?,?,?,?,?)");
				$sql->bind_param("ssssss", $st1, $output[6], $output[0], $output[4], $output[2], $utf_base);
				$sql->execute();
			}
		}
	}




/************************************************************************/
/*							DELIMITER 									*/
/************************************************************************/

	$st1 = strtok(" ");
}







/************************************************************************/
/*																		*/
/*						TOKENIZING STATEMENT 2	 						*/
/*																		*/
/************************************************************************/

$st2 = strtok ($statement2, " ");
while ($st2 !== false){


/************************************************************************/
/*			CALL C EXECUTABLE TO GET PROPERTIES OF EACH WORD			*/
/************************************************************************/

	$output = exec("pwd");
	$prgfile = "Morph_Analyser/./a.out ".$st2."";
	exec($prgfile, $output);




/************************************************************************/
/*				INSERT WORD PROPERTIES INTO THE DATABASE				*/
/************************************************************************/

	if ($output[0] == "Dhatu in list not found"){

		$utf_base = exec("sudo -u www-data python indic-wx-converter-master/toutf.py ".$st2."");

		$sql = $conn->prepare("INSERT INTO morph".$id."(statement,word,form,gender,vibhakthi,num_vachana,base_form) VALUES(2,?,'','','','',?)");
		$sql->bind_param("ss", $st2, $utf_base);
		$sql->execute();
	}

	else {
		if (sizeof($output) == 6){
			$utf_base = exec("sudo -u www-data python indic-wx-converter-master/toutf.py ".$output[5]."");
			
			if ($output[3] == "Noun"){
			
				$sql = $conn->prepare("INSERT INTO morph".$id."(statement,word,form,gender,vibhakthi,num_vachana,base_form) VALUES(2,?,?,?,?,?,?)");
				$sql->bind_param("ssssss", $st2, $output[3], $output[0], $output[1], $output[2], $utf_base);
				$sql->execute();
			}

			if ($output[3] == "Verb"){
				$sql = $conn->prepare("INSERT INTO morph".$id."(statement,word,form,tense,person,num_vachana,base_form) VALUES(2,?,?,?,?,?,?)");
				$sql->bind_param("ssssss", $st2, $output[3], $output[0], $output[1], $output[2], $utf_base);
				$sql->execute();
			}
		}

		else if (sizeof($output) == 9){
			$utf_base = exec("sudo -u www-data python indic-wx-converter-master/toutf.py ".$output[8]."");
			
			if ($output[6] == "Noun"){
				$sql = $conn->prepare("INSERT INTO morph".$id."(statement,word,form,gender,vibhakthi,num_vachana,base_form) VALUES(2,?,?,?,?,?,?)");
				$sql->bind_param("ssssss", $st2, $output[6], $output[0], $output[1], $output[2], $utf_base);
				$sql->execute();

				$sql = $conn->prepare("INSERT INTO morph".$id."(statement,word,form,gender,vibhakthi,num_vachana,base_form) VALUES(2,?,?,?,?,?,?)");
				$sql->bind_param("ssssss", $st2, $output[6], $output[0], $output[4], $output[2], $utf_base);
				$sql->execute();
			}

			if ($output[6] == "Verb"){
				$sql = $conn->prepare("INSERT INTO morph".$id."(statement,word,form,tense,person,num_vachana,base_form) VALUES(2,?,?,?,?,?,?)");
				$sql->bind_param("ssssss", $st2, $output[3], $output[0], $output[1], $output[2], $utf_base);
				$sql->execute();
			}
		}
	}

/************************************************************************/
/*								DELIMITER								*/
/************************************************************************/

	$st2 = strtok(" ");
}






/************************************************************************/
/*																		*/
/*	CATEGORISE THE WORDS OF STATEMENT 1 BASED ON THEIR VIBHAKTHI FORMS 	*/
/*																		*/
/************************************************************************/

$prathama=$dwithiya=$thrithiya=$chaturthi=$panchami=$sashti=$sapthami=$verb=$others="";
$stmt = $conn->query("SELECT * FROM morph".$id." WHERE statement = 1");
if ($stmt->num_rows>0){
	while($row = $stmt->fetch_assoc()){
		$root = $row['base_form'];
		switch($row['vibhakthi']){
			case 1:
				$prathama .= $root." ";
				break;
			case 2:
				$dwithiya .= $root." ";
				break;
			case 3:
				$thrithiya .= $root." ";
				break;
			case 4:
				$chaturthi .= $root." ";
				break;
			case 5:
				$panchami .= $root." ";
				break;
			case 6:
				$sashti .= $root." ";
				break;
			case 7:
				$sapthami .= $root." ";
				break;
			default:{
				if($row['form'] == "Verb"){
					$verb .= $root." ";
				}
				else if($row['form'] == ""){
					$others .= $root." ";
				}
				break;
			}
		}
	}
}






/************************************************************************/
/*					INSERTING INTO VIBHAKTHI TABLE 						*/
/************************************************************************/

$sql = $conn->query("INSERT INTO vibhakthi".$id." VALUES('','$prathama','$dwithiya','$thrithiya','$chaturthi','$panchami','$sashti','$sapthami','$verb','$others')");







/************************************************************************/
/*																		*/
/*	CATEGORISE THE WORDS OF STATEMENT 2 BASED ON THEIR VIBHAKTHI FORMS 	*/
/*																		*/
/************************************************************************/

$prathama=$dwithiya=$thrithiya=$chaturthi=$panchami=$sashti=$sapthami=$verb=$others="";
$stmt = $conn->query("SELECT * FROM morph".$id." WHERE statement = 2");
if ($stmt->num_rows>0){
	while($row = $stmt->fetch_assoc()){
		$root = $row['base_form'];
		switch($row['vibhakthi']){
			case 1:
				$prathama .= $root." ";
				break;
			case 2:
				$dwithiya .= $root." ";
				break;
			case 3:
				$thrithiya .= $root." ";
				break;
			case 4:
				$chaturthi .= $root." ";
				break;
			case 5:
				$panchami .= $root." ";
				break;
			case 6:
				$sashti .= $root." ";
				break;
			case 7:
				$sapthami .= $root." ";
				break;
			default:{
				if($row['form'] == "Verb"){
					$verb .= $root." ";
				}
				else if($row['form'] == ""){
					$others .= $root." ";
				}
				break;
			}
		}
	}
}



/************************************************************************/
/*					INSERTING INTO VIBHAKTHI TABLE 						*/
/************************************************************************/

$sql = $conn->query("INSERT INTO vibhakthi".$id." VALUES('','$prathama','$dwithiya','$thrithiya','$chaturthi','$panchami','$sashti','$sapthami','$verb','$others')");






/************************************************************************/
/*																		*/
/*																		*/
/*								 SCORING 								*/
/*																		*/
/*																		*/
/************************************************************************/



/************************************************************************/
/*							OTHER WORDS SCORING							*/
/************************************************************************/

$sql = $conn->query("SELECT others from vibhakthi".$id." WHERE no = 1");
$result = $sql->fetch_assoc();
$other1 = $result['others'];

$sql = $conn->query("SELECT others from vibhakthi".$id." WHERE no = 2");
$result = $sql->fetch_assoc();
$other2 = $result['others'];

$score_array = array_fill(0, sizeof(explode(" ",$other2))-1, " ");

$tok_other1 = strtok($other1, " ");
while($tok_other1 !== false){

	score_other($id, $tok_other1, $other2, $host, $uname, $pass, $dbname);
	$tok_other1 = strtok(" ");
}

$other1 = explode(" ", $other1);
$size1 = sizeof($other1) - 1;
$other2 = explode(" ", $other2);
$size2 = sizeof($other2) - 1;

if ($size1 > $size2){
	for ($i=0; $i<$size1; $i++){
		$max_other_score += $incr_other;
	}
}
else{
	for ($i=0; $i<$size2; $i++){
		$max_other_score += $incr_other;
	}
}

for ($i=0; $i < sizeof($score_array); $i++){
	$score_other += $score_array[$i];
}



/************************************************************************/
/*							NOUN WORDS SCORING							*/
/************************************************************************/

for ($i=1; $i<=7; $i++){

	switch ($i) {
		case 1:
			$score_noun += get_noun_score($id, 'prathama', $host, $uname, $pass, $dbname);
			$max_noun_score += maxscore_noun($id, 'prathama', $host, $uname, $pass, $dbname);
			break;
		case 2:
			$score_noun += get_noun_score($id, 'dwithiya', $host, $uname, $pass, $dbname);
			$max_noun_score += maxscore_noun($id, 'dwithiya', $host, $uname, $pass, $dbname);
			break;
		case 3:
			$score_noun += get_noun_score($id, 'thrithiya', $host, $uname, $pass, $dbname);
			$max_noun_score += maxscore_noun($id, 'thrithiya', $host, $uname, $pass, $dbname);
			break;
		case 4:
			$score_noun += get_noun_score($id, 'chaturthi', $host, $uname, $pass, $dbname);
			$max_noun_score += maxscore_noun($id, 'chaturthi', $host, $uname, $pass, $dbname);
			break;
		case 5:
			$score_noun += get_noun_score($id, 'panchami', $host, $uname, $pass, $dbname);
			$max_noun_score += maxscore_noun($id, 'panchami', $host, $uname, $pass, $dbname);
			break;
		case 6:
			$score_noun += get_noun_score($id, 'sashti', $host, $uname, $pass, $dbname);
			$max_noun_score += maxscore_noun($id, 'sashti', $host, $uname, $pass, $dbname);
			break;
		case 7:
			$score_noun += get_noun_score($id, 'sapthami', $host, $uname, $pass, $dbname);
			$max_noun_score += maxscore_noun($id, 'sapthami', $host, $uname, $pass, $dbname);
			break;
		default:
			break;
	}
}	




/************************************************************************/
/*							VERB WORDS SCORING							*/
/************************************************************************/

$sql = $conn->query("SELECT verb from vibhakthi".$id." WHERE no = 1");
$result = $sql->fetch_assoc();
$verb1 = $result['verb'];

$sql = $conn->query("SELECT verb from vibhakthi".$id." WHERE no = 2");
$result = $sql->fetch_assoc();
$verb2 = $result['verb'];

$score_array = array_fill(0, sizeof(explode(" ",$verb2))-1, " ");

$tok_verb1 = strtok($verb1, " ");
while($tok_verb1 !== false){

	score_verb($id, $tok_verb1, $verb2, $host, $uname, $pass, $dbname);
	$tok_verb1 = strtok(" ");
}


$verb1 = explode(" ", $verb1);
$size1 = sizeof($verb1) - 1;
$verb2 = explode(" ", $verb2);
$size2 = sizeof($verb2) - 1;

if ($size1 > $size2){
	for ($i=0; $i<$size1; $i++){
		$max_verb_score += $incr_verb;
	}
}
else{
	for ($i=0; $i<$size2; $i++){
		$max_verb_score += $incr_verb;
	}
}

for ($i=0; $i < sizeof($score_array); $i++){
	$score_verb += $score_array[$i];
}

$conn->close();



$similarity = ($score_noun + $score_verb + $score_other) * 100 / ($max_noun_score + $max_verb_score + $max_other_score);
$_SESSION['similarity'] = $similarity;
header('Location:score_page.php');



/************************************************************************/
/*						UPDATE MAX NOUN SCORE							*/
/************************************************************************/

function maxscore_noun($id, $vibhakthi_number, $host, $uname, $pass, $dbname){

	/*	Create Connection 	*/
	$conn = new mysqli ($host,$uname,$pass,$dbname);

	$score = 0;

	$sql = $conn->query("SELECT ".$vibhakthi_number." from vibhakthi".$id." WHERE no = 1");
	$result = $sql->fetch_assoc();
	$noun1 = $result[$vibhakthi_number];

	$sql = $conn->query("SELECT ".$vibhakthi_number." from vibhakthi".$id." WHERE no = 2");
	$result = $sql->fetch_assoc();
	$noun2 = $result[$vibhakthi_number];

	$noun1 = explode(" ", $noun1);
	$size1 = sizeof($noun1) - 1;
	$noun2 = explode(" ", $noun2);
	$size2 = sizeof($noun2) - 1;

	if ($size1 > $size2){
		for ($i=0; $i<$size1; $i++){
			$score += $GLOBALS['incr_noun'];
		}
	}
	else{
		for ($i=0; $i<$size2; $i++){
			$score += $GLOBALS['incr_noun'];
		}
	}

	$conn->close();

	return $score;
}




/************************************************************************/
/*				FUNCTION TO CALL NOUN SCORING FUNCTION					*/
/************************************************************************/

function get_noun_score($id, $vibhakthi_number, $host, $uname, $pass, $dbname){

	/*	Create connection	*/
	$conn = new mysqli ($host,$uname,$pass,$dbname);

	$noun_score = 0;

	$sql = $conn->query("SELECT ".$vibhakthi_number." from vibhakthi".$id." WHERE no = 1");
	$result = $sql->fetch_assoc();
	$noun1 = $result[$vibhakthi_number];

	$sql = $conn->query("SELECT ".$vibhakthi_number." from vibhakthi".$id." WHERE no = 2");
	$result = $sql->fetch_assoc();
	$noun2 = $result[$vibhakthi_number];

	$GLOBALS['score_array'] = array_fill(0, sizeof(explode(" ",$noun2)), 0);

	$tok_noun1 = strtok($noun1, " ");
	while($tok_noun1 !== false){

		noun_scoring($id, $tok_noun1, $noun2, $host, $uname, $pass, $dbname);
		$tok_noun1 = strtok(" ");

	}

	for ($i=0; $i < sizeof($GLOBALS['score_array']); $i++){
		$noun_score += $GLOBALS['score_array'][$i];
	}

	$conn->close();

	return $noun_score;
}







/************************************************************************/
/*																		*
*																		*
*	You have session ID, tokenized word from Statement 1 and the 		*
*	matching words of Statement 2 under that Vibhakthi.					*
*																		*
*	Synonyms of tokenized word from Statement 1 are taken.				*
*																		*
*	Each word in synonym is checked for a match in words of 			*
*	Statement 2.														*
*																		*
*	If match found:														*
*		score += 4														*
*		count ++														*
*																		*
*		Get Tense, Person and Number or vachana of matching words 		*
*		from both Statement 1 and Statement 2							*
*																		*
*		For Nouns:														*
*		If match in Number:												*
*			score ++													*
*			count ++													*
*																		*
*		For Verbs:														*
*		If match in Tense, Person and Number:							*
*			score += 2													*
*			count ++													*
*																		*
*	return score + floor(count/2);										*
*																		*
*																		*/
/************************************************************************/



/************************************************************************/
/*						NOUN SCORING FUNCTION							*/
/************************************************************************/

function noun_scoring($id, $base_form, $noun2, $host, $uname, $pass, $dbname){

	$conn = new mysqli ($host,$uname,$pass,$dbname);

	$score = $count = 0;
	$syn_tok = $noun_tok = "";
	
	$sql = $conn->query("SELECT synset FROM synset_table WHERE synset LIKE '% ".$base_form.",%' OR synset like '%, ".$base_form."' OR synset like '".$base_form.",%'");
	$result = $sql->fetch_assoc();
	$synonyms = $result['synset'];

	$syn_tok = explode(", ", $synonyms);

	for ($i=0; $i<count($syn_tok); $i++){
		$noun2_tok = explode(" ",$noun2);

		for ($j=0; $j<count($noun2_tok); $j++){

			if ($syn_tok[$i] == $noun2_tok[$j]){
				$score+=5;
				$count++;

				$sql1 = $conn->query("SELECT num_vachana FROM morph".$id." WHERE form = 'Noun' AND statement = 1 AND base_form = '".$base_form."'");
				$sql2 = $conn->query("SELECT num_vachana FROM morph".$id." WHERE form = 'Noun' AND statement = 2 AND base_form = '".$noun2_tok[$j]."'");

				$result1 = $sql1->fetch_assoc();
				$result2 = $sql2->fetch_assoc();

				$number1 = $result1['num_vachana'];
				$number2 = $result2['num_vachana'];

				if ($number1 == $number2){
					$score+=2;
					$count++;
				}

				if ($GLOBALS['score_array'][$j] < ($score + floor($count/2))){
					$GLOBALS['score_array'][$j] = $score + floor($count/2);
				}
			}


		}
	}

	$conn->close();
}





/************************************************************************/
/*						VERB SCORING FUNCTION							*/
/************************************************************************/

function score_verb($id, $base_form, $verb2, $host, $uname, $pass, $dbname){

	$conn = new mysqli ($host,$uname,$pass,$dbname);

	$score = $count = 0;
	$syn_tok = $verb2_tok = "";

	$sql = $conn->query("SELECT synset FROM synset_table WHERE synset LIKE '% ".$base_form.",%' OR synset like '%, ".$base_form."' OR synset like '".$base_form.",%'");
	$result = $sql->fetch_assoc();
	$synonyms = $result['synset'];

	$syn_tok = explode(", ", $synonyms);

	for ($i=0; $i<count($syn_tok); $i++){
		$verb2_tok = explode(" ",$verb2);

		for ($j=0; $j<count($verb2_tok); $j++){

			if ($syn_tok[$i] == $verb2_tok[$j]){
				$score+=4;
				$count++;

				$sql1 = $conn->query("SELECT tense, person, num_vachana FROM morph".$id." WHERE form = 'Verb' AND statement = 1 AND base_form = '".$base_form."'");
				$sql2 = $conn->query("SELECT tense, person, num_vachana FROM morph".$id." WHERE form = 'Verb' AND statement = 2 AND base_form = '".$verb2_tok[$j]."'");

				$result1 = $sql1->fetch_assoc();
				$result2 = $sql2->fetch_assoc();

				$tense1 = $result1['tense'];
				$tense2 = $result2['tense'];
				$person1 = $result1['person'];
				$person2 = $result2['person'];
				$number1 = $result1['num_vachana'];
				$number2 = $result2['num_vachana'];

				if ($tense1 == $tense2){
					$score+=2;
					$count++;
				}

				if ($person1 == $person2){
					$score++;
					$count++;
				}

				if ($number1 == $number2){
					$score++;
					$count++;
				}


				if ($GLOBALS['score_array'][$j] < ($score + floor($count/2))){
					$GLOBALS['score_array'][$j] = $score + floor($count/2);
				}
			}
		}
	}

	$conn->close();
}




/************************************************************************/
/*						OTHER WORDS SCORING FUNCTION					*/
/************************************************************************/

function score_other($id, $base_form, $other2, $host, $uname, $pass, $dbname){

	$conn = new mysqli ($host,$uname,$pass,$dbname);

	$score = $count = 0;
	$syn_tok = $other2_tok = "";

	$sql = $conn->query("SELECT synset FROM synset_table WHERE synset LIKE '% ".$base_form.",%' OR synset like '%, ".$base_form."' OR synset like '".$base_form.",%'");
	$result = $sql->fetch_assoc();
	$synonyms = $result['synset'];

	if ($synonyms){
		$syn_tok = explode(", ", $synonyms);

		for ($i=0; $i<count($syn_tok); $i++){
			$other2_tok = explode(" ",$other2);

			for ($j=0; $j<count($other2_tok); $j++){
				if ($syn_tok[$i] == $other2_tok[$j]){
					$GLOBALS['score_array'][$j] = $GLOBALS['incr_other'];
				}
			}
		}
	}
	else {
		$other2_tok = explode(" ",$other2);

		for ($j=0; $j<count($other2_tok); $j++){
			if ($base_form == $other2_tok[$j]){
				$GLOBALS['score_array'][$j] = $GLOBALS['incr_other'];
			}
		}
	}
	
	$conn->close();
}



/************************************************************************/
/*					GET UNIQUE WORDS FROM A STRING						*/
/************************************************************************/

function unique_word($string) {
    $string = explode(" ", $string);
    $words = array_unique($string);
    return $words;
}


?>
