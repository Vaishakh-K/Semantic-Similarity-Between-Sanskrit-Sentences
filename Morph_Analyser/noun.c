
/*
Since each noun has 21 forms, this function checks if there exists a noun form according to the gender.
If a suffix is found then, it assigns a value to pratyayano which is the form number of the word. Based on pratyayano we 
assign values to form array which determines the Vibhakti and Number.
form[0] determines the Vibhakti and can have values from 1 to 7.
form[1] determines the Number i.e Singular, Dual or Plural.
*/

void setNounProperties(int * form, int pratyayano)
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

        case 10: form[0] = 4; form[1] = 1;
                break;

        case 11: form[0] = 4; form[1] = 2;
                break;

        case 12: form[0] = 4; form[1] = 3;
                break;

        case 13: form[0] = 5; form[1] = 1;
                break;

        case 14: form[0] = 5; form[1] = 2;
                break;

        case 15: form[0] = 5; form[1] = 3;
                break;

        case 16: form[0] = 6; form[1] = 1;
                break;

        case 17: form[0] = 6; form[1] = 2;
                break;

        case 18: form[0] = 6; form[1] = 3;
                break;

        case 19: form[0] = 7; form[1] = 1;
                break;

        case 20: form[0] = 7; form[1] = 2;
                break;

        case 21: form[0] = 7; form[1] = 3;
                break;

        default: form[0] = -1; form[1] = -1;
                 break;
    }

}


/*
This function gets the properties of the words according to the value of nounform array.
nounform[0] determines the Vibhakti and can have values from 1 to 7.
nounform[1] determines the Number i.e Singular, Dual or Plural.
*/

void getNounProperties(int * nounform)
{
    printf("%d\n", nounform[0]);
    switch(nounform[1])
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

void checkSuffix(char * prathyayaword, char pratyayas[21][10], char pratyayas1[21][10], int gen)
{
    int i;
    int pratyayano = -1;
    int * form = (int *) malloc (2 * sizeof(int));

    for(i = 0; i < 21; i++)
    {
        if (checkPratyayaForm(prathyayaword, pratyayas[i]) == 1 || checkPratyayaForm(prathyayaword, pratyayas1[i]) == 1)
        {
            switch(gen)
            {
                case 0 : printf("Male\n");break;
                case 1 : printf("Female\n");break;
                case 2 : printf("Neutral\n");break;
            }
                
            pratyayano = i + 1;
            setNounProperties(form, pratyayano);
            getNounProperties(form);
            found_n = 1;
                //break;
        }

    }

        if (found_n == 1)
        {
            strcat(base_form, pratyayas[0]);
        }
}

void getNounForm(char * prathyayaword, int category)
{

    switch (category)
    {
        case 10 : checkSuffix(prathyayaword, ap_pratyayas, ap_pratyayas1, 0);break;
        case 11 : checkSuffix(prathyayaword, ip_pratyayas, ip_pratyayas1, 0);break;
        case 12 : checkSuffix(prathyayaword, ip_pratyayas2, ip_pratyayas, 0);break;
        case 13 : checkSuffix(prathyayaword, ip_pratyayas4, ip_pratyayas5, 0);break;
        case 14 : checkSuffix(prathyayaword, Ip_pratyayas, Ip_pratyayas1, 0);break;
        case 15 : checkSuffix(prathyayaword, Ip_pratyayas2, Ip_pratyayas3, 0);break;
        case 16 : checkSuffix(prathyayaword, up_pratyayas, up_pratyayas1, 0);break;
        case 17 : checkSuffix(prathyayaword, qp_pratyayas, qp_pratyayas1, 0);break;
        case 18 : checkSuffix(prathyayaword, qp_pratyayas2, qp_pratyayas3, 0);break;
        case 19 : checkSuffix(prathyayaword, op_pratyayas, op_pratyayas1, 0);break;
        case 20 : checkSuffix(prathyayaword, cp_pratyayas, cp_pratyayas1, 0);break;
        case 21 : checkSuffix(prathyayaword, jp_pratyayas, jp_pratyayas1, 0);break;
        case 22 : checkSuffix(prathyayaword, jp_pratyayas2, jp_pratyayas3, 0);break;
        case 23 : checkSuffix(prathyayaword, wp_pratyayas, wp_pratyayas1, 0);break;
        case 24 : checkSuffix(prathyayaword, np_pratyayas, np_pratyayas1, 0);break;
        case 25 : checkSuffix(prathyayaword, np_pratyayas2, np_pratyayas3, 0);break;


        case 40 : checkSuffix(prathyayaword, as_pratyayas, as_pratyayas1, 1);break;
        case 41 : checkSuffix(prathyayaword, is_pratyayas, is_pratyayas1, 1);break;
        case 42 : checkSuffix(prathyayaword, Is_pratyayas, Is_pratyayas1, 1);break;
        case 43 : checkSuffix(prathyayaword, us_pratyayas, Us_pratyayas1, 1);break;
        case 44 : checkSuffix(prathyayaword, Us_pratyayas, Us_pratyayas1, 1);break;
        case 45 : checkSuffix(prathyayaword, qs_pratyayas, qs_pratyayas1, 1);break;
        case 46 : checkSuffix(prathyayaword, xs_pratyayas, xs_pratyayas1, 1);break;
        case 47 : checkSuffix(prathyayaword, Ss_pratyayas, Ss_pratyayas1, 1);break;


        case 60 : checkSuffix(prathyayaword, an_pratyayas, an_pratyayas1, 2);break;
        case 61 : checkSuffix(prathyayaword, in_pratyayas, in_pratyayas1, 2);break;
        case 62 : checkSuffix(prathyayaword, in_pratyayas2, in_pratyayas3, 2);break;
        case 63 : checkSuffix(prathyayaword, un_pratyayas, un_pratyayas1, 2);break;
        case 64 : checkSuffix(prathyayaword, nn_pratyayas, nn_pratyayas1, 2);break;
        case 65 : checkSuffix(prathyayaword, nn_pratyayas2, nn_pratyayas3, 2);break;
        case 66 : checkSuffix(prathyayaword, sn_pratyayas, sn_pratyayas1, 2);break;



    }
    

}

