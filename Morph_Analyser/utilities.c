/*
subString function takes two strings as parameters. This function checks for root words in the morpheme. If a defined root
is present then the location of the root (first character) in the morpheme is returned. Else returns -1.
*/ 

int subString(char *word, char *dhatu)
{
    int wi, ds = 0, di;
    int dhatustartindexinword;
    int dhatufound;
    for (wi = 0; word[wi] != '\0'; wi++)
    {
        if (word[wi] == dhatu[0])
        {
            dhatustartindexinword = wi;
            dhatufound = 1;
            for(di = 0; dhatu[di] != '\0'; di++)
            {
                if (dhatu[di] != word[dhatustartindexinword + di])
                {
                    dhatufound = 0;
                    break;
                }
            }
            if (dhatufound == 1)
            {
                return dhatustartindexinword;
            }

        }
    }
    return -1;
}

/*
checkPratyayaForm function takes two inputs. First one is the part of the input morpheme after the root. The second input 
is the suffix. The function checks for exact match of the suffix in the word. Returns 1 if found else -1.
*/

int checkPratyayaForm(char *pratyayaword, char *pratyaya)
{
    int pwi = 0, ps = 0, pi;
    int pratyayastartindexinword;
    int pratyayafound;
    
    if (pratyayaword[pwi] == pratyaya[0])
    {
        pratyayastartindexinword = pwi;
        pratyayafound = 1;
        for(pi = 0; pratyaya[pi] != '\0'; pi++)
        {
            if (pratyaya[pi] != pratyayaword[pratyayastartindexinword + pi])
            {
                pratyayafound = 0;
                break;
            }
        }
            
        if (pratyayafound == 1)
        {
            if (pratyayaword[pratyayastartindexinword + strlen(pratyaya)] == '\0')
            {
                return 1;
            }

        }

    }
    
    return -1;
}