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

int ev(char *rls_yr);

void letrehoz()
{
    fflush(stdin);

    /// Adatok betoltese
    Adatok *eleje=konyvtari_adatok();

    /// Uj elem letrehozasa
    Adatok *hozzafuzendo=elem_letrehoz();

    /// Uj elem hozzaadasa a listahoz
    eleje=lista_hozzafuz(eleje,hozzafuzendo);

    fileba_mentes(eleje);

    /// Memoria felszabaditas
    felszabadit(eleje);

    printf("\n");
    system("pause");
    system("cls");

}


void torles()
{
    fflush(stdin);

    /// Adatok betoltese
    Adatok *eleje=konyvtari_adatok();

    printf("Adja meg a konyv adatait!\nCim: ");
    char *book_title=string_in();

    printf("Szerzo: ");
    char *author=string_in();

    printf("Tema: ");
    char *theme=string_in();

    printf("Kiadasi eve: ");
    char *rls_yr=string_in();
    int release_year=ev(rls_yr);

    printf("Kolcsonzo: ");
    char *borrower=string_in();

    /// Megadja a keresett elem indexet a listaban
    int bt=lista_elem_keres_szoveg(eleje,book_title);
    int au=lista_elem_keres_szoveg(eleje,author);
    int th=lista_elem_keres_szoveg(eleje,theme);
    int br=lista_elem_keres_szoveg(eleje,borrower);
    int ry=lista_elem_keres_ev(eleje,release_year);

    /// Eldonti, hogy benne van-e az listaban, es hogy nem "*"-e
    if(strcmp(book_title,"*")!=0 && bt!=-1){
        eleje=elem_torlese(eleje,bt);
        printf("\nSikeres torles!\n");
    }
    else if(strcmp(author,"*")!=0 && au!=-1){
        eleje=elem_torlese(eleje,au);
        printf("\nSikeres torles!\n");
    }
    else if(strcmp(theme,"*")!=0 && th!=-1){
        eleje=elem_torlese(eleje,th);
        printf("\nSikeres torles!\n");
    }
    else if(strcmp(rls_yr,"*")!=0 && ry!=-1){
        eleje=elem_torlese(eleje,ry);
        printf("\nSikeres torles!\n");
    }
    else if(strcmp(borrower,"*")!=0 && br!=-1){
        eleje=elem_torlese(eleje,br);
        printf("\nSikeres torles!\n");
    }
    else{
        printf("\nA megadott adatok nem egy konyvhoz tartoznak!\n");
    }

    fileba_mentes(eleje);

    /// Memoria felszabaditasa
    felszabadit(eleje);

    free(book_title);
    free(author);
    free(theme);
    free(rls_yr);
    free(borrower);

    printf("\n");
    system("pause");
    system("cls");
}

void modosit()
{
    fflush(stdin);

    /// Adatok betoltese
    Adatok *eleje=konyvtari_adatok();

    printf("Adja meg a konyv adatait!\nCim: ");
    char *book_title=string_in();

    printf("Szerzo: ");
    char *author=string_in();

    printf("Tema: ");
    char *theme=string_in();

    printf("Kiadasi eve: ");
    char *rls_yr=string_in();
    int release_year=ev(rls_yr);

    printf("Kolcsonzo: ");
    char *borrower=string_in();

    /// Megadja a keresett elem indexet a listaban
    int bt=lista_elem_keres_szoveg(eleje,book_title);
    int au=lista_elem_keres_szoveg(eleje,author);
    int th=lista_elem_keres_szoveg(eleje,theme);
    int br=lista_elem_keres_szoveg(eleje,borrower);
    int ry=lista_elem_keres_ev(eleje,release_year);

    /// Eldonti, hogy benne van-e az listaban, es hogy nem "*"-e
    if(strcmp(book_title,"*")!=0 && bt!=-1){
        eleje=lista_atlancol(eleje,bt);
        printf("\nSikeres modositas!\n");
    }
    else if(strcmp(author,"*")!=0 && au!=-1){
        eleje=lista_atlancol(eleje,au);
        printf("\nSikeres modositas!\n");
    }
    else if(strcmp(theme,"*")!=0 && th!=-1){
        eleje=lista_atlancol(eleje,th);
        printf("\nSikeres modositas!\n");
    }
    else if(strcmp(rls_yr,"*")!=0 && ry!=-1){
        eleje=lista_atlancol(eleje,ry);
        printf("\nSikeres modositas!\n");
    }
    else if(strcmp(borrower,"*")!=0 && br!=-1){
        eleje=lista_atlancol(eleje,br);
        printf("\nSikeres modositas!\n");
    }
    else{
        printf("\nA megadott adatok nem egy konyvhoz tartoznak!\n");
    }

    fileba_mentes(eleje);

    /// Memoria felszabaditasa
    felszabadit(eleje);

    free(book_title);
    free(author);
    free(theme);
    free(rls_yr);
    free(borrower);

    printf("\n");
    system("pause");
    system("cls");
}

/// Eldonti hogy az ev string "*"-e vagy sem, ha nem, akkor vissza adja az ev egesz szamot
int ev(char *rls_yr)
{
    if(strcmp(rls_yr,"*")==0){
        return -1;
    }
    else{
        return atoi(rls_yr);
    }
}
