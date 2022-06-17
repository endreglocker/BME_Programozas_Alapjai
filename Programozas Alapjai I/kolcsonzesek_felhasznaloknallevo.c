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

void kolcsonzesek()
{
    fflush(stdin);

    /// Adatok betoltese
    Adatok *eleje=konyvtari_adatok();

    printf("Adja meg a keresett konyv cimet: ");
    char *cim=string_in();

    /// Parameter keresese es hozzatartozo adatok kiirasa
    kikolcsonzott_konyvek(eleje,cim);

    /// Memoria felszabaditas
    felszabadit(eleje);
    free(cim);

    printf("\n");
    system("pause");
    system("cls");
}

void felhasznaloi()
{
    fflush(stdin);

    /// Adatok betoltese
    Adatok *eleje=konyvtari_adatok();

    printf("Adja meg a kolcsonzo nevet: ");
    char *nev=string_in();

    /// Parameter keresese es hozzatartozo adatok kiirasa
    felhasznalonal_levo_konyvek(eleje,nev);

    /// Memoria felszabaditas
    felszabadit(eleje);
    free(nev);

    printf("\n");
    system("pause");
    system("cls");
}
