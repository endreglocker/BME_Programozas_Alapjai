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

Adatok *file_beolvasas(FILE *fp);
Adatok *valogato(char *sor);
char *kolcsonzo(char *borrower);

Adatok *konyvtari_adatok()
{
    /// Adattarolo letrehozasa
    Adatok *eleje=NULL;

    /// Fajl megnyitasa
    FILE* fp;
    fp = fopen("konyvtar.txt","r");

    /// Hibakezeles
    if (fp != NULL){
        eleje=file_beolvasas(fp);

    }
    else{

        perror("A konyvtar tartalma jelenleg ures!");
    }

    return eleje;
}

Adatok *file_beolvasas(FILE *fp)
{
    Adatok *betolto=NULL;

    /// Sornkenti beolvasas
    char sor[256];
    while(fgets(sor,256,fp)!=NULL){
        /// Adatok szetvalogatasa es betoltese egy lista elembe
        Adatok *kov = valogato(sor);
        /// Bejovo adatok hozzafuzese a listahoz
        betolto=lista_hozzafuz(betolto,kov);
    }
    return betolto;
}


Adatok *valogato(char *sor)
{
    /// Az adatelvalaszto definialasa
    const char keresett[2] = ";";
    char *csere;

    /// 1 sornyi adatszerkezet reszei
    char *stringek[5];

    /// Elso adat levalasztasa
    csere = strtok(sor, keresett);

    int i=0;
    /// Adatok szetvalasztasa, amig nem NULL
    while( csere != NULL ) {
        stringek[i++] = csere;
        csere = strtok(NULL, keresett);
    }


    /// "\n" karakter levalasztasa az utolso adatrol
    char *borrower=stringek[4];
    borrower=kolcsonzo(borrower);

    /// Adatok betoltese egy lista elembe
    Adatok *kov = (Adatok*)malloc(sizeof(Adatok));

    kov->book_title = (char*) malloc((strlen(stringek[0])+1) * sizeof(char));
    strcpy(kov->book_title, stringek[0]);

    kov->author = (char*) malloc((strlen(stringek[1])+1) * sizeof(char));
    strcpy(kov->author, stringek[1]);

    kov->theme = (char*) malloc((strlen(stringek[2])+1) * sizeof(char));
    strcpy(kov->theme, stringek[2]);

    kov->release_year = atoi(stringek[3]);

    kov->borrower = borrower;

    kov->next = NULL;

    return kov;
}

char *kolcsonzo(char *borrower)
{
    int hossz= strlen(borrower);
    char *atalakito=(char*)malloc(sizeof(char)*hossz);

    for(int i=0;i<hossz;i++){
        atalakito[i]=borrower[i];
    }
    atalakito[hossz - 1]='\0';
    return atalakito;
}
