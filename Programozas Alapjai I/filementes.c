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

/// Fajl letrehozasa es mentese
void fileba_mentes(Adatok *lista)
{
    FILE* fp;
    fp = fopen("konyvtar.txt", "w");
    while(lista!=NULL){
        fprintf(fp, "%s;%s;%s;%d;%s\n",lista->book_title,lista->author,lista->theme,lista->release_year,lista->borrower);
        lista=lista->next;
    }
    fclose(fp);
}
