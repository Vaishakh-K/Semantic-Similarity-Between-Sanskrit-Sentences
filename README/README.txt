Instructions:

Download and install XAMPP server from 
	https://www.apachefriends.org/download.html


Usage instructions:

	1. Start the Apache and MySQL server in your system.
		sudo /opt/lampp/lampp start

	2. Extract the downloaded contents into htdocs folder
		/opt/lampp/htdocs

	3. Start MySQL
		mysql -u'username' -p

		a. Create database named 'sanskrit'
			mysql -u'username' -p
			DROP DATABASE IF EXISTS sanskrit;
			CREATE DATABASE sanskrit;

	4. Import the sanskrit wordnet into the database
		mysql -u'username' -p'password' sanskrit < Sanskrit\ Wordnet/sanskrit.sql

	5. Alter the synset table
		mysql -u'username' -p
		USE sanskrit;
		ALTER TABLE synset_table DROP COLUMN gloss;
		DELETE FROM synset_table WHERE category='adjective';


Open the file 'index.php' in any browser.
	'server_address'/Sanskrit/

	If using on a local computer enter server_address as 'localhost' or '127.0.0.1'

Input two sanskrit sentences (in WX notation) in the provided fields.

Learn more about WX notation and it's usage at: https://en.wikipedia.org/wiki/WX_notation

The system provides the similarity score based on kaaraka relationships between the words. You can also check the output from the morphological analyzer for each word.

The morphological analyser can be independently accessed to check the properties of each word.
To use this
	1. Compile main_morph.c in the directory Morph_Analyser
		gcc main_morph.c
	2. Run the executable file by passing the morpheme as the argument.
		./a.out [morpheme]
		Example : ./a.out rAmaH
	3. The morphological properties of the morpheme is obtained as the output.