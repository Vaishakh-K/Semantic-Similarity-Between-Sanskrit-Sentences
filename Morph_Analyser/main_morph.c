/*
A Sanskrit Morphological Analyser. Given a morpheme this system will analyse it and tell if it is a noun, verb etc, its 
Root, Gender, Vibhakti, Number, Tense, Person details. http://sanskrit.samskrutam.com/en.grammar-tutorial-reference-sabdarupa.ashx

Authors:
Vaishakh K
Akshay C D
Sanapala Mounica

Mentor:
Sowmya Kamath S
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/*
NC_P - Number of masculine base words
NC_S - Number of feminine base words
NC_N - Number of neutral base words 
*/

#define NC_aP 15
#define NC_aS 4
#define NC_aN 28

#define NC_iP 12
#define NC_iP1 1
#define NC_iP2 2
#define NC_iS 11
#define NC_iN 1
#define NC_iN1 4

#define NC_IP 1
#define NC_IP1 3
#define NC_IS 2
#define NC_IN 0

#define NC_uP 4
#define NC_uS 4
#define NC_uN 11

#define NC_UP 0
#define NC_US 3
#define NC_UN 0

#define NC_qP 7
#define NC_qP1 6
#define NC_qS 3
#define NC_qN 0

#define NC_oP 1
#define NC_oS 0
#define NC_oN 0

#define NC_cP 8
#define NC_cS 0
#define NC_cN 0

#define NC_jP 8
#define NC_jP1 1
#define NC_jS 0
#define NC_jN 0

#define NC_wP 1
#define NC_wS 0
#define NC_wN 0

#define NC_xP 0
#define NC_xS 7
#define NC_xN 0

#define NC_nP 1
#define NC_nP1 4
#define NC_nS 0
#define NC_nN 5
#define NC_nN1 7

#define NC_sP 1
#define NC_sS 0
#define NC_sN 9

#define NC_SP 0
#define NC_SS 1
#define NC_SN 0

/*
main_morph.c - The main program to be run. Takes an input morpheme and outputs its properties.
declarations.h - Contains all the external variable declarations.
utilities.c - Commonly used functions like substring, getPratyaya are defined.
verb.c - Contains code to check for verb forms.
noun.c - Contains code to check for noun forms.
search.c - Searches for the base word and then calls the function to check for noun/verb forms accordingly.
*/

#include "declarations.h"
#include "utilities.c"
#include "verb.c"
#include "noun.c"
#include "search.c"


//Is it possible to be lang lakar
int islangpossible = 0;

//Base form of a word for nown and root of th word for verb
char base_form[20], root_form[20];

/*
Pratyayas of Verbs
latpratyayas_p - Suffixes for verbs in Present Tense and Parasmaipada form.
langpratyayas_p - Suffixes for verbs in Past Tense and Parasmaipada form.
loutpratyayas_p - Suffixes for verbs in Imperative mood and Parasmaipada form.
fewdhatus - A set of roots which can have a verb form.
*/

char latpratyayas_p[9][9] = {"awi\0", "awaH\0", "anwi\0", "asi\0", "aWaH\0", "aWa\0", "Ami\0", "AvaH\0", "AmaH\0"};
char langpratyayas_p[9][9] = {"aw\0", "awAm\0", "an\0", "aH\0", "awam\0", "awa\0", "am\0", "Ava\0", "Ama\0"};
char loutpratyayas_p[9][9] = {"awu\0", "awAm\0", "anwu\0", "a\0", "awam\0", "awa\0", "Ani\0", "Ava\0", "Ama\0"};
char lringpratyayas_p[9][9] = {"iRyawi\0", "iRyawaH\0", "iRyanwi\0", "iRyasi\0", "iRyaWaH\0", "iRyaWa\0", "iRyAmi\0", "iRyAvaH\0", "iRyAmaH\0"};
char fewdhatus[10][10] = {"paT\0", "liK\0", "has\0", "XAv\0", "pac\0", "vax\0", "nam\0", "KAx\0", "krId\0", "cal\0"};

//Pratyayas of Nouns


/*************************************************Male*****************************************************/

//Suffixes for roots ending with 'a' which form masculine nouns.
char ap_pratyayas[21][10] = {"aH\0", "O\0", "AH\0", "am\0", "O\0", "An\0", "en\0", "AByAm\0", "EH\0", "Aya\0", "AByAm\0", "eByaH\0", "Aw\0", "AByAm\0", "eByaH\0", "asya\0", "ayoH\0", "AnAm\0", "e\0", "ayoH\0", "eRu\0"};
char ap_pratyayas1[21][10] = {"aH\0", "O\0", "AH\0", "aM\0", "O\0", "An\0", "eN\0", "AByAM\0", "EH\0", "Aya\0", "AByAM\0", "eByaH\0", "Aw\0", "AByAM\0", "eByaH\0", "asya\0", "ayoH\0", "ANAm\0", "e\0", "ayoH\0", "eRu\0"};

//Suffixes for roots ending with 'i' which form masculine nouns.
char ip_pratyayas[21][10] = {"iH\0", "I\0", "ayaH\0", "im\0", "I\0", "In\0", "inA\0", "iByAm\0", "iBiH\0", "aye\0", "iByAm\0", "iByaH\0", "eH\0", "iByAm\0", "iByaH\0", "eH\0", "yoH\0", "InAm\0", "O\0", "yoH\0", "iRu\0"};
char ip_pratyayas1[21][10] = {"iH\0", "I\0", "ayaH\0", "iM\0", "I\0", "In\0", "iNA\0", "iByAM\0", "iBiH\0", "aye\0", "iByAM\0", "iByaH\0", "eH\0", "iByAM\0", "iByaH\0", "eH\0", "yoH\0", "INAm\0", "O\0", "yoH\0", "iRu\0"};

//Suffixes for roots ending with 'i' which form masculine nouns. Like pawiH
char ip_pratyayas2[21][10] = {"iH\0", "I\0", "ayaH\0", "im\0", "I\0", "In\0", "yA\0", "iByAm\0", "iBiH\0", "ye\0", "iByAm\0", "iByaH\0", "yuH\0", "iByAm\0", "iByaH\0", "yuH\0", "yoH\0", "InAm\0", "yo\0", "yoH\0", "iRu\0"};
char ip_pratyayas3[21][10] = {"iH\0", "I\0", "ayaH\0", "iM\0", "I\0", "In\0", "yA\0", "iByAM\0", "iBiH\0", "ye\0", "iByAM\0", "iByaH\0", "yuH\0", "iByAM\0", "iByaH\0", "yuH\0", "yoH\0", "INAm\0", "yo\0", "yoH\0", "iRu\0"};

char ip_pratyayas4[21][10] = {"A\0", "AyO\0", "ayaH\0", "Ayam\0", "AyO\0", "In\0", "yA\0", "iByAm\0", "iBiH\0", "ye\0", "iByAm\0", "iByaH\0", "yuH\0", "iByAm\0", "iByaH\0", "yuH\0", "yoH\0", "InAm\0", "O\0", "yoH\0", "iRu\0"};
char ip_pratyayas5[21][10] = {"A\0", "AyO\0", "ayaH\0", "AyaM\0", "AyO\0", "In\0", "yA\0", "iByAM\0", "iBiH\0", "ye\0", "iByAM\0", "iByaH\0", "yuH\0", "iByAM\0", "iByaH\0", "yuH\0", "yoH\0", "INAm\0", "O\0", "yoH\0", "iRu\0"};


//Ikaranta
char Ip_pratyayas[21][10] = {"IH\0", "iyO\0", "iyaH\0", "iyam\0", "iyO\0", "iyaH\0", "iyA\0", "IByAm\0", "IBiH\0", "iye\0", "IByAm\0", "IByaH\0", "iyaH\0", "IByAm\0", "IByaH\0", "iyaH\0", "iyoH\0", "iyAm\0", "iyi\0", "iyoH\0", "IRU\0"};
char Ip_pratyayas1[21][10] = {"IH\0", "iyO\0", "iyaH\0", "iyaM\0", "iyO\0", "iyaH\0", "iyA\0", "IByAM\0", "IBiH\0", "iye\0", "IByAM\0", "IByaH\0", "iyaH\0", "IByAM\0", "IByaH\0", "iyaH\0", "iyoH\0", "iyAM\0", "iyi\0", "iyoH\0", "IRU\0"};

char Ip_pratyayas2[21][10] = {"I\0", "yO\0", "yaH\0", "yam\0", "yO\0", "yaH\0", "yA\0", "IByAm\0", "IBiH\0", "ye\0", "IByAm\0", "IByaH\0", "yaH\0", "IByAm\0", "IByaH\0", "yaH\0", "yoH\0", "yAm\0", "yAm\0", "yoH\0", "IRu\0"};
char Ip_pratyayas3[21][10] = {"I\0", "yO\0", "yaH\0", "yaM\0", "yO\0", "yaH\0", "yA\0", "IByAM\0", "IBiH\0", "ye\0", "IByAM\0", "IByaH\0", "yaH\0", "IByAM\0", "IByaH\0", "yaH\0", "yoH\0", "yAM\0", "yAM\0", "yoH\0", "IRu\0"};

//Suffixes for roots ending with 'u' which form masculine nouns.
char up_pratyayas[21][10] = {"uH\0", "U\0", "avaH\0", "um\0", "U\0", "Un\0", "uNA\0", "uByam\0", "uBiH\0", "ave\0", "uByam\0", "uByaH\0", "oH\0", "uByam\0", "uByaH\0", "oH\0", "voH\0", "UNam\0", "O\0", "voH\0", "uRu\0"};
char up_pratyayas1[21][10] = {"uH\0", "U\0", "avaH\0", "uM\0", "U\0", "Un\0", "unA\0", "uByaM\0", "uBiH\0", "ave\0", "uByaM\0", "uByaH\0", "oH\0", "uByaM\0", "uByaH\0", "oH\0", "voH\0", "Unam\0", "O\0", "voH\0", "uRu\0"};


//q male
char qp_pratyayas[21][10] = {"A\0", "ArO\0", "AraH\0", "Aram\0", "ArO\0", "qn\0", "rA\0", "qByAm\0", "qBiH\0", "re\0", "qByAm\0", "qBaH\0", "uH\0", "qByAm\0", "qBaH\0", "uH\0", "roH\0", "qNAm\0", "ari\0", "roH\0", "qRu\0"};
char qp_pratyayas1[21][10] = {"A\0", "ArO\0", "AraH\0", "AraM\0", "ArO\0", "qn\0", "rA\0", "qByAM\0", "qBiH\0", "re\0", "qByAM\0", "qBaH\0", "uH\0", "qByAM\0", "qBaH\0", "uH\0", "roH\0", "qnAm\0", "ari\0", "roH\0", "qRu\0"};

char qp_pratyayas2[21][10] = {"A\0", "arO\0", "araH\0", "aram\0", "arO\0", "qn\0", "rA\0", "qByAm\0", "qBiH\0", "re\0", "qByAm\0", "qBaH\0", "uH\0", "qByAm\0", "qBaH\0", "uH\0", "roH\0", "qNAm\0", "ari\0", "roH\0", "qRu\0"};
char qp_pratyayas3[21][10] = {"A\0", "arO\0", "araH\0", "araM\0", "arO\0", "qn\0", "rA\0", "qByAM\0", "qBiH\0", "re\0", "qByAM\0", "qBaH\0", "uH\0", "qByAM\0", "qBaH\0", "uH\0", "roH\0", "qnAm\0", "ari\0", "roH\0", "qRu\0"};

//o kara male
char op_pratyayas[21][10] = {"OH\0", "AvO\0", "AvaH\0", "Am\0", "AvO\0", "AH\0", "avA\0", "oByAm\0", "oBiH\0", "ave\0", "oByAm\0", "oByaH\0", "oH\0", "oByAm\0", "oByaH\0", "oH\0", "avoH\0", "avAm\0", "avi\0", "avoH\0", "oRu\0"};
char op_pratyayas1[21][10] = {"OH\0", "AvO\0", "AvaH\0", "AM\0", "AvO\0", "AH\0", "avA\0", "oByAM\0", "oBiH\0", "ave\0", "oByAM\0", "oByaH\0", "oH\0", "oByAM\0", "oByaH\0", "oH\0", "avoH\0", "avAM\0", "avi\0", "avoH\0", "oRu\0"};

//c kara male
char cp_pratyayas[21][10] = {"k\0", "cO\0", "caH\0", "cam\0", "cO\0", "caH\0", "cA\0", "gByAm\0", "gBiH\0", "ce\0", "gByAm\0", "gByaH\0", "gaH\0", "gByAm\0", "gByaH\0", "caH\0", "coH\0", "cAm\0", "c\0", "cOH\0", "kRu\0"};
char cp_pratyayas1[21][10] = {"k\0", "cO\0", "caH\0", "caM\0", "cO\0", "caH\0", "cA\0", "gByAM\0", "gBiH\0", "ce\0", "gByAM\0", "gByaH\0", "gaH\0", "gByAM\0", "gByaH\0", "caH\0", "coH\0", "cAM\0", "c\0", "cOH\0", "kRu\0"};

//j kara male
char jp_pratyayas[21][10] = {"k\0", "jO\0", "jaH\0", "jam\0", "jO\0", "jaH\0", "jA\0", "gByAm\0", "gBiH\0", "je\0", "gByAm\0", "gByaH\0", "jaH\0", "gByAm\0", "gByaH\0", "jaH\0", "joH\0", "jAm\0", "ji\0", "joH\0", "kRu\0"};
char jp_pratyayas1[21][10] = {"k\0", "jO\0", "jaH\0", "jaM\0", "jO\0", "jaH\0", "jA\0", "gByAM\0", "gBiH\0", "je\0", "gByAM\0", "gByaH\0", "jaH\0", "gByAM\0", "gByaH\0", "jaH\0", "joH\0", "jAM\0", "ji\0", "joH\0", "kRu\0"};

//j kara male
char jp_pratyayas2[21][10] = {"t\0", "jO\0", "jaH\0", "jam\0", "jO\0", "jaH\0", "jA\0", "fByAm\0", "fBiH\0", "je\0", "fByAm\0", "fByaH\0", "jaH\0", "fByAm\0", "fByaH\0", "jaH\0", "joH\0", "jAm\0", "ji\0", "joH\0", "tsu\0"};
char jp_pratyayas3[21][10] = {"t\0", "jO\0", "jaH\0", "jaM\0", "jO\0", "jaH\0", "jA\0", "fByAM\0", "fBiH\0", "je\0", "fByAM\0", "fByaH\0", "jaH\0", "fByAM\0", "fByaH\0", "jaH\0", "joH\0", "jAM\0", "ji\0", "joH\0", "tsu\0"};

//w kara male
char wp_pratyayas[21][10] = {"w\0", "wO\0", "waH\0", "wam\0", "wO\0", "waH\0", "wA\0", "ByAm\0", "BiH\0", "we\0", "ByAm\0", "ByaH\0", "waH\0", "Byam\0", "ByaH\0", "waH\0", "woH\0", "wAm\0", "wi\0", "woH\0", "wsu\0"};
char wp_pratyayas1[21][10] = {"w\0", "wO\0", "waH\0", "waM\0", "wO\0", "waH\0", "wA\0", "ByAM\0", "BiH\0", "we\0", "ByAM\0", "ByaH\0", "waH\0", "ByaM\0", "ByaH\0", "waH\0", "woH\0", "wAM\0", "wi\0", "woH\0", "wsu\0"};

//n kara male - rAjA
char np_pratyayas[21][10] = {"A\0", "AnO\0", "AnaH\0", "Anam\0", "AnO\0", "FaH\0", "FA\0", "AByAm\0", "aBiH\0", "Fe\0", "AByAm\0", "aByaH\0", "FaH\0", "AByAm\0", "aByaH\0", "FaH\0", "FoH\0", "AnAm\0", "Fi\0", "FoH\0", "asu\0"};
char np_pratyayas1[21][10] = {"A\0", "AnO\0", "AnaH\0", "AnaM\0", "AnO\0", "FaH\0", "FA\0", "AByAM\0", "aBiH\0", "Fe\0", "AByAM\0", "aByaH\0", "FaH\0", "AByAM\0", "aByaH\0", "FaH\0", "FoH\0", "ANAm\0", "ani\0", "FoH\0", "asu\0"};

//n kara male panWAH
char np_pratyayas2[21][10] = {"AH\0", "AnO\0", "AnaH\0", "Anam\0", "AnO\0", "aH\0", "A\0", "iByAm\0", "iBiH\0", "e\0", "iByAm\0", "iByaH\0", "aH\0", "iByAm\0", "iByaH\0", "aH\0", "oH\0", "Am\0", "i\0", "oH\0", "iRu\0"};
char np_pratyayas3[21][10] = {"AH\0", "AnO\0", "AnaH\0", "AnaM\0", "AnO\0", "aH\0", "A\0", "iByAM\0", "iBiH\0", "e\0", "iByAM\0", "iByaH\0", "aH\0", "iByAM\0", "iByaH\0", "aH\0", "oH\0", "Am\0", "i\0", "oH\0", "iRu\0"};

/*************************************Female**********************************************/

//Suffixes for roots ending with 'a' which form femnine nouns.
char as_pratyayas[21][10] = {"A\0", "e\0", "AH\0", "Am\0", "e\0", "AH\0", "ayA\0", "AByAm\0", "ABiH\0", "AyE\0", "AByAm\0", "AByaH\0", "AyAH\0", "AByAm\0", "AByaH\0", "AyAH\0", "ayoH\0", "AnAm\0", "AyAm\0", "ayoH\0", "Asu\0"};
char as_pratyayas1[21][10] = {"A\0", "e\0", "AH\0", "AM\0", "e\0", "AH\0", "ayA\0", "AByAM\0", "ABiH\0", "AyE\0", "AByAM\0", "AByaH\0", "AyAH\0", "AByAM\0", "AByaH\0", "AyAH\0", "ayoH\0", "AnAM\0", "AyAM\0", "ayoH\0", "Asu\0"};

//Ikaranta female
char is_pratyayas[21][10] = {"iH\0", "I\0", "ayaH\0", "im\0", "I\0", "IH\0", "yA\0", "iByAm\0", "iBiH\0", "aye\0", "iByAm\0", "iByaH\0", "eH\0", "iByAm\0", "iByaH\0", "eH\0", "yoH\0", "InAm\0", "O\0", "yoH\0", "iRu\0"};
char is_pratyayas1[21][10] = {"iH\0", "I\0", "ayaH\0", "iM\0", "I\0", "IH\0", "yA\0", "iByAM\0", "iBiH\0", "E\0", "iByAM\0", "iByaH\0", "yoH\0", "iByAM\0", "iByaH\0", "yAH\0", "yoH\0", "INAm\0", "O\0", "yoH\0", "iRu\0"};

//I female
char Is_pratyayas[21][10] = {"I\0", "iyO\0", "iyaH\0", "iyam\0", "iyO\0", "iyaH\0", "iyA\0", "IByAm\0", "IBiH\0", "iyE\0", "IByAm\0", "IByaH\0", "iyAH\0", "IByAm\0", "IByaH\0", "iyAH\0", "iyoH\0", "InAm\0", "iyAm\0", "iyoH\0", "IRu\0"};
char Is_pratyayas1[21][10] = {"I\0", "yO\0", "yaH\0", "IM\0", "yO\0", "IH\0", "yA\0", "IByAM\0", "IBiH\0", "yE\0", "IByAM\0", "IByaH\0", "yAH\0", "IByAM\0", "IByaH\0", "yAH\0", "yoH\0", "iNAm\0", "yAM\0", "yoH\0", "IRu\0"};

//u female
char us_pratyayas[21][10] = {"uH\0", "U\0", "avaH\0", "um\0", "U\0", "UH\0", "vA\0", "uByAm\0", "uBiH\0", "vE\0", "uByAm\0", "uByaH\0", "vAH\0", "uByAm\0", "uByaH\0", "vAH\0", "voH\0", "UnAm\0", "vAm\0", "voH\0", "uRu\0"};
char us_pratyayas1[21][10] = {"uH\0", "U\0", "avaH\0", "uM\0", "U\0", "UH\0", "vA\0", "uByAM\0", "uBiH\0", "ave\0", "uByAM\0", "uByaH\0", "oH\0", "uByAM\0", "uByaH\0", "oH\0", "voH\0", "UNAm\0", "O\0", "voH\0", "uRu\0"};

//U female
char Us_pratyayas[21][10] = {"UH\0", "vO\0", "vaH\0", "Um\0", "vO\0", "UH\0", "vA\0", "UnAm\0", "UBiH\0", "vE\0", "UByAm\0", "UByam\0", "vAH\0", "UByAm\0", "UByaH\0", "vAH\0", "voH\0", "UnAm\0", "vAm\0", "voH\0", "URu\0"};
char Us_pratyayas1[21][10] = {"UH\0", "vO\0", "vaH\0", "UM\0", "vO\0", "UH\0", "vA\0", "UnAM\0", "UBiH\0", "vE\0", "UByAM\0", "UByaM\0", "vAH\0", "UByAM\0", "UByaH\0", "vAH\0", "voH\0", "UNAm\0", "vAM\0", "voH\0", "URu\0"};

//q female
char qs_pratyayas[21][10] = {"A\0", "arO\0", "araH\0", "aram\0", "arO\0", "Q\0", "rA\0", "qByAm\0", "qBiH\0", "re\0", "qByAm\0", "qByaH\0", "uH\0", "qByAm\0", "qByaH\0", "uH\0", "roH\0", "qNAm\0", "ari\0", "roH\0", "qRu\0"};
char qs_pratyayas1[21][10] = {"A\0", "arO\0", "araH\0", "araM\0", "arO\0", "Q\0", "rA\0", "qByAM\0", "qBiH\0", "re\0", "qByAM\0", "qByaH\0", "uH\0", "qByAM\0", "qByaH\0", "uH\0", "roH\0", "qnAm\0", "ari\0", "roH\0", "qRu\0"};

//x female
char xs_pratyayas[21][10] = {"aw\0", "axO\0", "axaH\0", "axam\0", "axO\0", "axaH\0", "axA\0", "axByAm\0", "axBiH\0", "awe\0", "axByAm\0", "axByaH\0", "axaH\0", "axByAm\0", "axByaH\0", "axaH\0", "axoH\0", "awAm\0", "axi\0", "axoH\0", "awsu\0"};
char xs_pratyayas1[21][10] = {"aw\0", "axO\0", "axaH\0", "axaM\0", "axO\0", "axaH\0", "axA\0", "axByAM\0", "axBiH\0", "awe\0", "axByAM\0", "axByaH\0", "axaH\0", "axByAM\0", "axByaH\0", "axaH\0", "axoH\0", "awAM\0", "axi\0", "axoH\0", "awsu\0"};

//S female
char Ss_pratyayas[21][10] = {"k\0", "SO\0", "SaH\0", "Sam\0", "SO\0", "SaH\0", "SA\0", "gByAm\0", "gByaH\0", "Se\0", "gByAm\0", "gByaH\0", "SaH\0", "gByAm\0", "gByaH\0", "SaH\0", "SoH\0", "SAm\0", "Si\0", "SoH\0", "kRu\0"};
char Ss_pratyayas1[21][10] = {"k\0", "SO\0", "SaH\0", "SaM\0", "SO\0", "SaH\0", "SA\0", "gByAM\0", "gByaH\0", "Se\0", "gByAM\0", "gByaH\0", "SaH\0", "gByAM\0", "gByaH\0", "SaH\0", "SoH\0", "SAM\0", "Si\0", "SoH\0", "kRu\0"};

/*********************************Neutral*******************************************/

//Suffixes for roots ending with 'a' which form neutral nouns.
char an_pratyayas[21][10] = {"am\0", "e\0", "Ani\0", "am\0", "e\0", "Ani\0", "en\0", "AByAm\0", "EH\0", "Aya\0", "AByAm\0", "eByaH\0", "Aw\0", "AByAm\0", "eByaH\0", "asya\0", "ayoH\0", "AnAm\0", "e\0", "ayoH\0", "eRu\0"};
char an_pratyayas1[21][10] = {"aM\0", "e\0", "ANi\0", "aM\0", "e\0", "ANi\0", "eN\0", "AByAM\0", "EH\0", "Aya\0", "AByAM\0", "eByaH\0", "Aw\0", "AByAM\0", "eByaH\0", "asya\0", "ayoH\0", "ANAm\0", "e\0", "ayoH\0", "eRu\0"};

//i neutral
char in_pratyayas[21][10] = {"i\0", "iNI\0", "INi\0", "i\0", "iNI\0", "INi\0", "iNA\0", "iByAm\0", "iBiH\0", "iNe\0", "iByAm\0", "iByaH\0", "iNaH\0", "iByAm\0", "iByaH\0", "iNaH\0", "iNoH\0", "INAm\0", "iNi\0", "iNoH\0", "iRu\0"};
char in_pratyayas1[21][10] = {"i\0", "inI\0", "Ini\0", "i\0", "inI\0", "Ini\0", "inA\0", "iByAM\0", "iBiH\0", "ine\0", "iByAM\0", "iByaH\0", "inaH\0", "iByAM\0", "iByaH\0", "inaH\0", "inoH\0", "InAm\0", "ini\0", "inoH\0", "iRu\0"};

char in_pratyayas2[21][10] = {"i\0", "iNI\0", "INi\0", "i\0", "iNI\0", "INi\0", "NA\0", "iByAm\0", "iBiH\0", "Ne\0", "iByAm\0", "iByaH\0", "NaH\0", "iByAm\0", "iByaH\0", "NaH\0", "NoH\0", "NAm\0", "Ni\0", "NoH\0", "iRu\0"};
char in_pratyayas3[21][10] = {"i\0", "inI\0", "Ini\0", "i\0", "inI\0", "Ini\0", "nA\0", "iByAM\0", "iBiH\0", "ne\0", "iByAM\0", "iByaH\0", "naH\0", "iByAM\0", "iByaH\0", "naH\0", "noH\0", "nAm\0", "ni\0", "noH\0", "iRu\0"};

//u neutral 
char un_pratyayas[21][10] = {"u\0", "unI\0", "Uni\0", "u\0", "unI\0", "Uni\0", "unA\0", "uByAm\0", "uBiH\0", "une\0", "uByAm\0", "uByaH\0", "unaH\0", "uByAm\0", "uByaH\0", "unaH\0", "unoH\0", "UnAm\0", "uni\0", "unoH\0", "uRu\0"};
char un_pratyayas1[21][10] = {"u\0", "unI\0", "Uni\0", "u\0", "unI\0", "Uni\0", "unA\0", "uByAM\0", "uBiH\0", "une\0", "uByAM\0", "uByaH\0", "unaH\0", "uByAM\0", "uByaH\0", "unaH\0", "unoH\0", "UnAM\0", "uni\0", "unoH\0", "uRu\0"};

//n neutral nAm
char nn_pratyayas[21][10] = {"a\0", "nI\0", "Ani\0", "a\0", "nI\0", "Ani\0", "nA\0", "aByAm\0", "aBiH\0", "ne\0", "aByAm\0", "aByaH\0", "naH\0", "aByAm\0", "aByaH\0", "naH\0", "noH\0", "nAm\0", "ni\0", "noH\0", "asu\0"};
char nn_pratyayas1[21][10] = {"a\0", "anI\0", "Ani\0", "a\0", "anI\0", "Ani\0", "nA\0", "aByAM\0", "aBiH\0", "ne\0", "aByAM\0", "aByaH\0", "naH\0", "aByAM\0", "aByaH\0", "naH\0", "noH\0", "nAM\0", "ani\0", "noH\0", "asu\0"};

//n neutral karma
char nn_pratyayas2[21][10] = {"a\0", "aNI\0", "ANi\0", "a\0", "aNI\0", "ANi\0", "aNA\0", "aByAm\0", "aBiH\0", "aNe\0", "aByAm\0", "aByaH\0", "aNaH\0", "aByAm\0", "aByaH\0", "aNaH\0", "aNoH\0", "aNAm\0", "aNi\0", "aNoH\0", "asu\0"};
char nn_pratyayas3[21][10] = {"a\0", "anI\0", "Ani\0", "a\0", "anI\0", "Ani\0", "anA\0", "aByAM\0", "aBiH\0", "ane\0", "aByAM\0", "aByaH\0", "anaH\0", "aByAM\0", "aByaH\0", "anaH\0", "anoH\0", "anAM\0", "ani\0", "anoH\0", "asu\0"};

//s neutral
char sn_pratyayas[21][10] = {"aH\0", "asI\0", "AMsi\0", "aH\0", "asI\0", "AMsi\0", "asA\0", "oByAm\0", "oBiH\0", "ase\0", "oByAm\0", "oByaH\0", "asaH\0", "oByAm\0", "oByaH\0", "asaH\0", "asoH\0", "asAm\0", "asi\0", "asoH\0", "assu\0"};
char sn_pratyayas1[21][10] = {"aH\0", "asI\0", "AMsi\0", "aH\0", "asI\0", "AMsi\0", "asA\0", "oByAM\0", "oBiH\0", "ase\0", "oByAM\0", "oByaH\0", "asaH\0", "oByAM\0", "oByaH\0", "asaH\0", "asoH\0", "asAM\0", "asi\0", "asoH\0", "assu\0"};

/*
roots_noun_p - Roots which form masculine nouns.
roots_noun_s - Roots which form feminine nouns.
roots_noun_n - Roots which form neutral nouns.
*/

char roots_noun_ap[NC_aP][20] = {"rAm\0", "kqRN\0", "akRay\0", "bAl\0", "bAlak\0", "xev\0", "nar\0", "sur\0", "siMh\0", "vqkR\0", "guN\0", "varN\0", "loB\0", "mArg\0", "pAxap\0"};
char roots_noun_as[NC_aS][20] = {"sIw\0", "wAr\0", "mOnik\0", "pravalik\0"};
char roots_noun_an[NC_aN][20] = {"van\0", "Pal\0", "kAnan\0", "vipin\0", "araNy\0", "puswak\0", "kavan\0", "ann\0", "agr\0", "anqw\0", "anX\0", "alIk\0", "Asan\0", "inxriy\0", "uxar\0", "uxyAn\0", "uwWan\0", "qN\0", "kalawr\0", "kanak\0", "kamal\0", "kAraN\0", "KAxy\0", "gagan\0", "gIw\0", "gqh\0", "gowr\0", "Gqw\0"};

char roots_noun_ip[NC_iP][20] = {"kav\0", "har\0", "mun\0", "qS\0", "rav\0", "ar\0", "vahn\0", "Xvan\0", "viX\0", "niX\0", "aWiw\0", "sAraW\0"};
char roots_noun_ip1[NC_iP1][20] = {"paw\0"};
char roots_noun_ip2[NC_iP2][20] = {"saK\0"};
char roots_noun_is[NC_iS][20] = {"maw\0", "avanaw\0", "apaciw\0", "unnaw\0", "uwpaw\0", "urm\0", "kAnw\0", "kqw\0", "kRaw\0", "gaw\0", "ciw\0"};
char roots_noun_in[NC_iN][20] = {"vAr\0"};
char roots_noun_in1[NC_iN1][20] = {"akR\0", "xaX\0", "asw\0", "sakW\0"};

char roots_noun_Ip[NC_IP][20] = {"suX\0"};
char roots_noun_Ip1[NC_IP1][20] = {"senAn\0", "agraN\0", "grAmaN\0"};
char roots_noun_Is[NC_IS][20] = {"nax\0", "swr\0"};
char roots_noun_In[NC_IN][20] = {};

char roots_noun_up[NC_uP][20] = {"gur\0", "Ban\0", "viRN\0", "sAX\0"};
char roots_noun_us[NC_uS][20] = {"Xen\0", "wan\0", "reN\0", "rajj\0"};
char roots_noun_un[NC_uN][20] = {"maX\0", "amb\0", "aSr\0", "SmaSr\0", "jaw\0", "wAl\0", "xAr\0", "mawar\0", "vas\0", "vasw\0", "sAn\0"};

char roots_noun_Up[NC_UP][20] = {};
char roots_noun_Us[NC_US][20] = {"vaX\0", "cam\0", "SvaSr\0"};
char roots_noun_Un[NC_UN][20] = {};

char roots_noun_qp[NC_qP][20] = {"xAw\0", "karw\0", "jew\0", "xraRt\0", "sraRt\0", "XAw\0", "saviw\0"};
char roots_noun_qp1[NC_qP1][20] = {"piw\0", "BrAw\0", "jAmAw\0", "xuhiw\0", "xev\0", "n\0"};
char roots_noun_qs[NC_qS][20] = {"mAw\0", "xuhiw\0", "yAw\0"};
char roots_noun_qn[NC_qN][20] = {};

char roots_noun_op[NC_oP][20] = {"g\0"};
char roots_noun_os[NC_oS][20] = {};
char roots_noun_on[NC_oN][20] = {};

char roots_noun_cp[NC_cP][20] = {"payomu\0", "prA\0", "prawya\0", "uda\0", "avA\0", "worya\0", "jalam\0", "sawyavA\0"};
char roots_noun_cs[NC_oS][20] = {};
char roots_noun_cn[NC_oN][20] = {};

char roots_noun_jp[NC_jP][20] = {"vaNi\0", "BiRa\0", "qwvi\0"};
char roots_noun_jp1[NC_jP1][20] = {"samrA\0"};
char roots_noun_js[NC_jS][20] = {};
char roots_noun_jn[NC_jN][20] = {};

char roots_noun_wp[NC_wP][20] = {"BUBq\0"};
char roots_noun_ws[NC_wS][20] = {};
char roots_noun_wn[NC_wN][20] = {};

char roots_noun_xp[NC_xP][20] = {};
char roots_noun_xs[NC_xS][20] = {"vip\0", "mu\0", "Ap\0", "samp\0", "Sar\0", "pareR\0", "upaniR\0"};
char roots_noun_xn[NC_xN][20] = {};

char roots_noun_np[NC_nP][20] = {"rAj\0"};
char roots_noun_np1[NC_nP1][20] = {"panW\0"};
char roots_noun_ns[NC_nS][20] = {};
char roots_noun_nn[NC_nN][20] = {"nAm\0", "vyom\0", "XAm\0", "prem\0", "lom\0"};
char roots_noun_nn1[NC_nN1][20] = {"karm\0", "carm\0", "Basm\0", "janm\0", "veSm\0", "Sarm\0", "varm\0"};

char roots_noun_sp[NC_sP][20] = {};
char roots_noun_ss[NC_sS][20] = {};
char roots_noun_sn[NC_sN][20] = {"pay\0", "cew\0", "man\0", "yaS\0", "srow\0", "Sir\0", "vac\0", "amB\0", "vakR\0"};

char roots_noun_Sp[NC_SP][20] = {};
char roots_noun_Ss[NC_SS][20] = {"xi\0"};
char roots_noun_Sn[NC_SN][20] = {};

int found_n = 0;
int found_v = 0;


char upasarg[10];

/*
The main function. Take a morpheme as an input. Calls function to check for noun/verb forms. Prints the base form for noun
and root for verb.
*/

int main(int argc, char *argv[])
{

	isNoun(argv[1]);

	if (!found_n)
	{
		isVerb(argv[1]);
	}
	else
	{
		printf("%s\n", base_form);
	}
	
	if (found_v)
	{
		printf("%s\n", root_form);
	}

	return 0;

}

//resolve the root checking bug