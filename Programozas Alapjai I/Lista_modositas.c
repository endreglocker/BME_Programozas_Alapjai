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

/// Felszabaditja a lista alltal lefoglalt memoriateruletet
void *felszabadit(Adatok *lista)
{
    while (lista!=NULL) {

        Adatok *next=lista->next;

        free(lista->book_title);
        free(lista->author);
        free(lista->theme);
        free(lista->borrower);

        free(lista);

        lista=next;
    }
    return lista;
}

/// Hozzafuz 1 tagot a lista vegehez
Adatok *lista_hozzafuz(Adatok *lista, Adatok *hozzafuzendo)
{
    if(lista == NULL){
        return hozzafuzendo;
    }
    else{
        Adatok *cserelo = lista;
        while(cserelo->next != NULL){
            cserelo = cserelo->next;
        }
        cserelo->next = hozzafuzendo;

    }
    return lista;
}

/// Kiiratja a lista elemeit
void lista_kiir(Adatok *lista)
{
    while(lista != NULL)
    {
        printf("Cim: %s\nSzerzo: %s\nTema: %s\nKiadasi ev: %d\nKolcsonzo: %s\n\n",lista->book_title,lista->author,lista->theme,lista->release_year,lista->borrower);

        lista = lista->next;
    }
}

/// Megadja a lista hosszat
int lista_hossz(Adatok *lista)
{
    int db=0;
    if(lista == NULL){
        return 0;
    }
    else{
        while(lista != NULL){
            db++;
            lista = lista->next;
        }
    }
    return db;
}

/// Megadja a keresett szoveg indexet a listaban , ha nem lezezik akkor -1 a visszaadott ertek
int lista_elem_keres_szoveg(Adatok *lista,char *szoveg)
{
    int index = -1;
    Adatok *kereso;
    int i=0;
    for(kereso=lista;kereso!=NULL;kereso=kereso->next){
        if(strcmp(kereso->book_title,szoveg)==0 || strcmp(kereso->author,szoveg)==0 || strcmp(kereso->theme,szoveg)==0 || strcmp(kereso->borrower,szoveg)==0){
            index=i;
        }
        i++;
    }
    return index;
}

/// Megadja a keresett evszam indexet a listaban, ha nem lezezik akkor -1 a visszaadott ertek
int lista_elem_keres_ev(Adatok *lista,int szam)
{
    int index = -1;
    Adatok *kereso;
    int i=0;
    for(kereso=lista;kereso!=NULL;kereso=kereso->next){
        if(kereso->release_year==szam){
            index=i;
        }
        i++;
    }
    return index;
}

/// Lista elemenek torlese egy megadott index helyrol:
Adatok *elem_torlese(Adatok *lista,int hanyadik)
{
    if(hanyadik!=-1){
        Adatok *lemarado = NULL;
        Adatok *mozgo = lista;
        int i=0;
        while (mozgo != NULL && i!=hanyadik) {
            lemarado = mozgo;
            mozgo = mozgo->next;
            i++;
        }


        if (mozgo == NULL) {

        } else if (lemarado == NULL) {
            Adatok *ujeleje = mozgo->next;
            free(mozgo->book_title);
            free(mozgo->author);
            free(mozgo->theme);
            free(mozgo->borrower);
            free(mozgo);
            lista = ujeleje;
        } else {
            lemarado->next = mozgo->next;
            free(mozgo->book_title);
            free(mozgo->author);
            free(mozgo->theme);
            free(mozgo->borrower);
            free(mozgo);
        }
    }
    return lista;
}

/// Kiirja egy felhasznalonal levo konyveket
void felhasznalonal_levo_konyvek(Adatok *lista,char *nev)
{
    bool eldont=true;
    if(strcmp(nev,"*")==0){
        while(lista!=NULL){
            printf("Konyv: %s\nIro: %s\nTema: %s\nMegjelenes eve: %d\n\n",lista->book_title,lista->author,lista->theme,lista->release_year);
            eldont=false;
            lista=lista->next;
        }
    }
    while(lista!=NULL){
        if(strcmp(nev,lista->borrower)==0){
            printf("Konyv: %s\nIro: %s\nTema: %s\nMegjelenes eve: %d\n\n",lista->book_title,lista->author,lista->theme,lista->release_year);
            eldont=false;
        }
        lista=lista->next;
    }
    if(eldont){
        printf("A keresett felhasznalonal nincsenek kikolcsonzott konyvek!\n");
    }
}

/// Kiirja egy felhasznalonal levo konyveket
void kikolcsonzott_konyvek(Adatok *lista,char *cim)
{
    bool ellenorzo=true;
    if(strcmp(cim,"*")==0){
        while(lista!=NULL){
            printf("Kolcsonzo: %s\n",lista->borrower);
            ellenorzo=false;
            lista=lista->next;
        }
    }

    while(lista!=NULL){
        if(strcmp(lista->book_title,cim)==0){
            printf("Kolcsonzo: %s\n",lista->borrower);
            ellenorzo=false;
        }
        lista=lista->next;
    }

    if(ellenorzo){
        printf("A keresett konyv nem talalhato az adatbazisban!\n");
    }
}

/// Egy megadott indexu elem helyere egy masikat lancol
Adatok *lista_atlancol(Adatok *lista,int hanyadik)
{
    Adatok *bejovo=elem_letrehoz();

    if(hanyadik!=-1){

        Adatok *lemarado = NULL;
        Adatok *mozgo = lista;
        int i=0;
        while (mozgo != NULL && i!=hanyadik) {
            lemarado = mozgo;
            mozgo = mozgo->next;
            i++;
        }


        if (mozgo == NULL) {

        } else if (lemarado == NULL) {
            //Adatok *ujeleje = mozgo->next;
            bejovo->next=mozgo->next;
            free(mozgo->book_title);
            free(mozgo->author);
            free(mozgo->theme);
            free(mozgo->borrower);
            free(mozgo);
            lista = bejovo;
        } else {
            lemarado->next = bejovo;
            bejovo->next = mozgo->next;
            free(mozgo->book_title);
            free(mozgo->author);
            free(mozgo->theme);
            free(mozgo->borrower);
            free(mozgo);
        }

    }
    return lista;
}

/// Letrehoz egy lista elemet
Adatok *elem_letrehoz()
{
    printf("Adja meg a konyv adatait!\nCim: ");
    char *book_title=string_in();

    printf("Szerzo: ");
    char *author=string_in();

    printf("Tema: ");
    char *theme=string_in();

    printf("Kiadasi eve: ");
    char *rls=string_in();
    int release_year=atoi(rls);

    printf("Kolcsonzo: ");
    char *borrower=string_in();

    Adatok *lista=(Adatok*)malloc(sizeof(Adatok));

    lista->book_title=(char*) malloc((strlen(book_title)+1) * sizeof(char));
    strcpy(lista->book_title, book_title);

    lista->author=(char*) malloc((strlen(author)+1) * sizeof(char));
    strcpy(lista->author, author);

    lista->theme=(char*) malloc((strlen(theme)+1) * sizeof(char));
    strcpy(lista->theme, theme);

    lista->release_year=release_year;

    lista->borrower=(char*) malloc((strlen(borrower)+1) * sizeof(char));
    strcpy(lista->borrower, borrower);

    lista->next=NULL;

    free(book_title);
    free(author);
    free(theme);
    free(rls);
    free(borrower);

    return lista;
}

/// Megkeresi a keresett szoveget a listaban, majd kiirja a hozza tartozo adatokat
void lista_konyv_kereso()
{
    fflush(stdin);

    Adatok *lista=konyvtari_adatok();

    char *str=string_in();

    bool ellenorzo=true;

    if(strcmp(str,"*")==0){
        lista_kiir(lista);
        ellenorzo=false;
    }
    else{
        Adatok *kereso_;
        for(kereso_=lista;kereso_!=NULL;kereso_=kereso_->next){
            if(strcmp(kereso_->book_title,str)==0 || strcmp(kereso_->author,str)==0 || strcmp(kereso_->theme,str)==0 || strcmp(kereso_->borrower,str)==0){
                printf("\nCim: %s\nSzerzo: %s\nTema: %s\nKiadasi ev: %d\nKolcsonzo: %s\n",kereso_->book_title,kereso_->author,kereso_->theme,kereso_->release_year,kereso_->borrower);
            }
        }
    }

    if(ellenorzo){
        printf("A keresett konyv nem talalhato az adatbazisban!\n");
    }
    felszabadit(lista);
    free(str);
    system("pause");
    system("cls");

}

/// Megkeres egy szamot a listaban majd kiirja a hozza tartozo adatokat
void lista_konyv_kereso_ev()
{
    fflush(stdin);

    Adatok *lista=konyvtari_adatok();

    char *str=string_in();

    bool ellenorzo=true;
    int szam=atoi(str);

    if(strcmp(str,"*")==0){
        lista_kiir(lista);
        ellenorzo=false;
    }
    else{
        Adatok *kereso_;
        for(kereso_=lista;kereso_!=NULL;kereso_=kereso_->next){
            if(szam==kereso_->release_year){
                printf("\nCim: %s\nSzerzo: %s\nTema: %s\nKiadasi ev: %d\nKolcsonzo: %s\n",kereso_->book_title,kereso_->author,kereso_->theme,kereso_->release_year,kereso_->borrower);
            }
        }
    }

    if(ellenorzo){
        printf("A keresett konyv nem talalhato az adatbazisban!\n");
    }
    felszabadit(lista);
    free(str);
    system("pause");
    system("cls");
}
