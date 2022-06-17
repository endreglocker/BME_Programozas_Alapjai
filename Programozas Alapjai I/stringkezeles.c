#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "Lista_modositas.h"
#include "filementes.h"
#include "fileolvasas.h"
#include "kezelofelulet.h"
#include "konyv_kezeles.h"
#include "kolcsonzesek_felhasznaloknallevo.h"
#include "stringkezeles.h"

#include "debugmalloc.h"

/// Dinamikusan beolvas enterig
char *string_in()
{
    int db=0;
    char *sor=(char*)malloc(db*sizeof(char));
    char betu;

    while(scanf("%c",&betu)==1 && betu!='\n')
    {
        db++;
        char *uj =(char*) malloc((db+1)*sizeof(char));

        for(int i=0; i<db-1; i++)
        {
            uj[i]=sor[i];
        }

        free(sor);

        sor=uj;
        sor[db-1]=betu;
        sor[db]='\0';


    }
    return sor;
}

