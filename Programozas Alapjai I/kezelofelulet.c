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

void konyvek();
void kereso();

typedef enum Allapot
{
    /// FOMENU
    KEZELOFELULET = 0,
    KONYVEK = 1,
    KOLCSONZESEK = 2,
    FELHASZNALOJNAL = 3,
    KERESES = 4,
    EXIT = 5,

    /// KONYVEK: KODOT ELCSUSZTATJUK 10-ZEL
    UJ_LETREHOZ = 11,
    MODOSIT = 12,
    TOROL = 13,

    /// KERESES: KODOT ELCSUSZTATJUK 20-SZAL
    CIM = 21,
    SZERZO = 22,
    TEMA = 23,
    KIADAS = 24,
    KOLCSONZO = 25,
}Allapot;


/// Menupontok kivalasztasa

Allapot kovetkezo_allapot(Allapot aktualis_allapot, int utasitas) {
    switch(aktualis_allapot) {
        case KEZELOFELULET:
            return utasitas;
        case KONYVEK:
            if(utasitas == 4)
            {
                return KEZELOFELULET;
            }
            /// HOZZAADJUK A CSUSZTATOTT ERTEKET -> KONYVEK KEZELESE
            return utasitas + 10;
        case KERESES:
            if(utasitas == 6){
                return KEZELOFELULET;
            }
            /// HOZZAADUJUK A CSUSZTATOTT ERTEKET -> KERESESEK
            return utasitas +20;
        default:
            return KEZELOFELULET;
    }
}

int kezeles(Allapot aktualis_allapot) {
    system("cls");
    int utasitas = -1; /// Ha nincs belso utasitas, akkor visszateres a fomenube
    switch(aktualis_allapot)
    {
        case KEZELOFELULET:
            printf("1: Konyv kezelese\n2: Kolcsonzesek\n3: Felhaszalonal levo konyvek\n4: Kereses\n5: Kilep\nAddj meg egy szamot! ");
            scanf("%d", &utasitas);
            break;
        case KONYVEK:
            printf("1: Uj letrehozasa\n2: Meglevo modositasa\n3: Meglevo torlese\n4: Vissza\nAddj meg egy szamot! ");
            scanf("%d", &utasitas);
            break;
        case KOLCSONZESEK:
            kolcsonzesek();
            break;
        case FELHASZNALOJNAL:
            felhasznaloi();
            break;
        case KERESES:
            printf("1: Cim\n2: Szerzo\n3: Tema\n4: Kiadasi ev\n5: Kolcsonzo\n6: Vissza\nAddj meg egy szamot! ");
            scanf("%d", &utasitas);
            break;
        case UJ_LETREHOZ:
            printf("Uj letrehozasa:\n");
            letrehoz();
            break;
        case TOROL:
            printf("Meglevo torlese:\n");
            torles();
            break;
        case MODOSIT:
            printf("Meglevo modositasa:\n");
            modosit();
            break;
        case CIM:
            printf("Cim: ");
            lista_konyv_kereso();
            break;
        case SZERZO:
            printf("Szerzo: ");
            lista_konyv_kereso();
            break;
        case TEMA:
            printf("Tema: ");
            lista_konyv_kereso();
            break;
        case KIADAS:
            printf("Kiadasi ev: ");
            lista_konyv_kereso_ev();
            break;
        case KOLCSONZO:
            printf("Kolcsonzo: ");
            lista_konyv_kereso();
            break;
        default:
            printf("Helytelen input!\n");
            system("pause");
            break;
    }
    return utasitas;
}

void kezelofelulet()
{

    Adatok *elso=konyvtari_adatok();
    if(elso==NULL){
        printf("\nA program mukodese erdekeben hozzon letre legalabb 1 elemet az adatbazisban (Konyv kezelese/Uj letrehozasa)!\n\n");
    }
    felszabadit(elso);



    Allapot a=KEZELOFELULET;
    while(a != EXIT){
        int utasitas = kezeles(a);
        a = kovetkezo_allapot(a, utasitas);
    }
    system("cls");
    printf("Sikeres kilepes!\n");

}
