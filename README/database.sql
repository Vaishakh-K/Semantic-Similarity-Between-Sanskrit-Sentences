\q

mysql -u'username' -p'password'
DROP DATABASE IF EXISTS sanskrit;
CREATE DATABASE sanskrit;
\q

mysql -u'username' -p'password' sanskrit < Sanskrit\ Wordnet/sanskrit.sql

mysql -u'username' -p'password'

USE sanskrit;
ALTER TABLE synset_table DROP COLUMN gloss;
DELETE FROM synset_table WHERE category='adjective';
