
/*
This function checks if the input morpheme has a root which can form a noun. If so then it will find the 
gender of the resulting noun.
category = 0 -> Male
category = 1 -> Female
category = 2 -> Neutral

It will then search if the word is a noun form in the getNounForm function. If it is a noun form then print the properties.
Here we send the parameter word + found + strlen(dhatufound) because we have to search for the suffix only after the root.
*/

void checkFunction(char * word, int root_list_len, char  root_array[root_list_len][20], int category)
{
	int i, found;
	char dhatufound[9];

	for (i = 0; i < root_list_len; i++)
   {
		found = subString(word, root_array[i]);
		if (found == 0)
		{
			// printf("\n%s dhatu found at %d\n", root_array[i], found);
			strcpy(dhatufound, root_array[i]);
			strncpy(base_form, word, found + strlen(dhatufound));
			getNounForm(word + found + strlen(dhatufound), category);

			if (found_n)
			{
				printf ("Noun\n");
				printf("%s dhatu found at %d\n", root_array[i], found);
				break;
			}
				
		}
	}
	
}


void isNoun(char word[30])
{
	//int *nounform;
	int * category;

	if (found_n != 1)
	{
		checkFunction(word, NC_aP, roots_noun_ap, 10);
	}
	if (found_n != 1)
	{
		checkFunction(word, NC_iP, roots_noun_ip, 11);
	}
	if (found_n != 1)
	{
		checkFunction(word, NC_iP1, roots_noun_ip1, 12);
	}
	if (found_n != 1)
	{
		checkFunction(word, NC_iP2, roots_noun_ip2, 13);
	}
	if (found_n != 1)
	{
		checkFunction(word, NC_IP, roots_noun_Ip, 14);
	}
	if (found_n != 1)
	{
		checkFunction(word, NC_IP1, roots_noun_Ip, 15);
	}
	if (found_n != 1)
	{
		checkFunction(word, NC_uP, roots_noun_up, 16);
	}
	if (found_n != 1)
	{
		checkFunction(word, NC_qP, roots_noun_qp, 17);
	}
	if (found_n != 1)
	{
		checkFunction(word, NC_qP1, roots_noun_qp1, 18);
	}
	if (found_n != 1)
	{
		checkFunction(word, NC_oP, roots_noun_op, 19);
	}
	if (found_n != 1)
	{
		checkFunction(word, NC_cP, roots_noun_cp, 20);
	}
	if (found_n != 1)
	{
		checkFunction(word, NC_jP, roots_noun_jp, 21);
	}
	 if (found_n != 1)
	{
		checkFunction(word, NC_jP1, roots_noun_jp1, 22);
	}
	if (found_n != 1)
	{
		checkFunction(word, NC_wP, roots_noun_wp, 23);
	}
	if (found_n != 1)
	{
		checkFunction(word, NC_nP, roots_noun_np, 24);
	}
	if (found_n != 1)
	{
		checkFunction(word, NC_nP1, roots_noun_np1, 25);
	}


	if (found_n != 1)
	{
		checkFunction(word, NC_aS, roots_noun_as, 40);
	}
	if (found_n != 1)
	{
		checkFunction(word, NC_iS, roots_noun_is, 41);
	}
	if (found_n != 1)
	{
		checkFunction(word, NC_IS, roots_noun_Is, 42);
	}
	if (found_n != 1)
	{
		checkFunction(word, NC_uS, roots_noun_us, 43);
	}
	if (found_n != 1)
	{
		checkFunction(word, NC_US, roots_noun_Us, 44);
	}
	if (found_n != 1)
	{
		checkFunction(word, NC_qS, roots_noun_qs, 45);
	}
	if (found_n != 1)
	{
		checkFunction(word, NC_xS, roots_noun_xs, 46);
	}
	if (found_n != 1)
	{
		checkFunction(word, NC_SS, roots_noun_Ss, 47);
	}
	 


	if (found_n != 1)
	{
		checkFunction(word, NC_aN, roots_noun_an, 60);
	}
	if (found_n != 1)
	{
		checkFunction(word, NC_iN, roots_noun_in, 61);
	}
	if (found_n != 1)
	{
		checkFunction(word, NC_iN1, roots_noun_in1, 62);
	}
	if (found_n != 1)
	{
		checkFunction(word, NC_uN, roots_noun_un, 63);
	}
	if (found_n != 1)
	{
		checkFunction(word, NC_nN, roots_noun_nn, 64);
	}
	if (found_n != 1)
	{
		checkFunction(word, NC_nN1, roots_noun_nn1, 65);
	}
	if (found_n != 1)
	{
		checkFunction(word, NC_sN, roots_noun_sn, 66);
	}  


}


/*
This function checks if the input morpheme has a root which can form a verb. 
If the verb is in past tense then the root will be preceeded by an 'a'. So we check that also here.
It will then search if the word is a verb form in the getVerbForm function. If it is a verb form then print the properties.
Here we send the parameter word + found + strlen(dhatufound) because we have to search for the suffix only after the root.
*/

void isVerb(char word[30])
{
	int i, found;
	int *verbform;
	char dhatufound[9];

	for (i = 0; i < 10; i++)
	{
		found = subString(word, fewdhatus[i]);
		if (found != -1)
		{
			// printf("%s dhatu found at %d", fewdhatus[i], found);
			strcpy(dhatufound, fewdhatus[i]);

			if (found > 0)
			{
				strncpy(upasarg, word, found);
				if (strcmp(upasarg, "a") != 0)
					strcpy(root_form, upasarg);
			}
			break;
		}
	}

	if (found > 0)
	{
		if (word[found - 1] == 'a')
			islangpossible = 1;
	}

	if (found != -1)
	{
//      verbform = getVerbForm(word + found + strlen(dhatufound));
		getVerbForm(word + found + strlen(dhatufound));

		if (found_v == 1)
		{
			strcat(root_form, dhatufound);
			printf("Verb\n");
			//getVerbProperties(verbform);
		}
	}

	if (found_v)
	{
		printf("%s dhatu found at %d\n", fewdhatus[i], found);

	}

	else
	{
		printf("Dhatu in list not found\n");
	}

}