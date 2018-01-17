
void setVerbProperties(int * form, int pratyayano)
{
    switch(pratyayano)
    {
        case 1: form[0] = 1; form[1] = 1;
                break;

        case 2: form[0] = 1; form[1] = 2;
                break;

        case 3: form[0] = 1; form[1] = 3;
                break;

        case 4: form[0] = 2; form[1] = 1;
                break;

        case 5: form[0] = 2; form[1] = 2;
                break;

        case 6: form[0] = 2; form[1] = 3;
                break;

        case 7: form[0] = 3; form[1] = 1;
                break;

        case 8: form[0] = 3; form[1] = 2;
                break;

        case 9: form[0] = 3; form[1] = 3;
                break;

        default: form[0] = -1; form[1] = -1;
                 break;
    }

}


/*
This function gets the properties of the words according to the value of verbform array.
verbform[0] determines the Person i.e Prathama(Third Person), Madhyama(Second Person), Uttama(First Person).
verbform[1] determines the Number i.e Singular, Dual or Plural.
*/


void getVerbProperties(int * verbform)
{
    switch(verbform[0])
    {
        case 1: printf("Prathama Purusha\n");
                break;

        case 2: printf("Madhyama Purusha\n");
                break;

        case 3: printf("Uttama Purusha\n");
                break;

        default: break;
    }

    switch(verbform[1])
    {
        case 1: printf("1, Ekavachanam - Singular\n");
                break;

        case 2: printf("2, Dwivachanam - Dual\n");
                break;

        case 3: printf("3, Bahuvachanam - Plural\n");
                break;

        default: break;
    }
}

/*
Since each verb has 9 forms in a given tense, this function checks if there exists a verb form.
If a suffix is found then, it determines the tense and it assigns a value to pratyayano which is the form number of
the word. Based on pratyayano we assign values to form array which determines the Person and Number.
form[0] determines the Person i.e Prathama(Third Person), Madhyama(Second Person), Uttama(First Person).
form[1] determines the Number i.e Singular, Dual or Plural.
*/

void getVerbForm(char * prathyayaword)
{
    int i;
    int pratyayano = -1;
    int * form = (int *) malloc (2 * sizeof(int));
    for(i = 0; i < 9; i++)
    {
        if (checkPratyayaForm(prathyayaword, latpratyayas_p[i]) == 1)//Check for Lat
        {
            printf("Present - Lat Lakar\n");
            pratyayano = i + 1;
            setVerbProperties(form, pratyayano);
            getVerbProperties(form);
            found_v = 1;
            //break;
        }

        if(islangpossible)//Check for Lang
        {
            if (checkPratyayaForm(prathyayaword, langpratyayas_p[i]) == 1)
            {
                printf("Past - Lang Lakar\n");
                pratyayano = i + 1;
                setVerbProperties(form, pratyayano);
                getVerbProperties(form);
                found_v = 1;
                //break;
            }
        }

        if (checkPratyayaForm(prathyayaword, loutpratyayas_p[i]) == 1)//Check for Lout
        {
            printf("Imperative Mood - Lout Lakar\n");
            pratyayano = i + 1;
            setVerbProperties(form, pratyayano);
            getVerbProperties(form);
            found_v = 1;
            //break;
        }

        if (checkPratyayaForm(prathyayaword, lringpratyayas_p[i]) == 1)//Check for Lring
        {
            printf("Future - Lring Lakar\n");
            pratyayano = i + 1;
            setVerbProperties(form, pratyayano);
            getVerbProperties(form);
            found_v = 1;
            //break;
        }
        
    }
  
}

