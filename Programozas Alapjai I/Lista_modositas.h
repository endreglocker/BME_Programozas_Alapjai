#ifndef LISTA_MODOSITAS_H
#define LISTA_MODOSITAS_H

typedef struct Adatok
{
    char *book_title;
    char *author;
    char *theme;
    int  release_year;
    char *borrower;
    struct Adatok *next;    /// Lancolt lista letrehozasa

}Adatok;

void *felszabadit(Adatok *lista);     /// Felszabaditja a lista alltal lefoglalt memoriateruletet
Adatok *lista_hozzafuz(Adatok *lista, Adatok *hozzafuzendo);        /// Hozzafuz 1 tagot a lista vegehez
void lista_kiir(Adatok *lista);     /// Kiiratja a lista elemeit
int lista_hossz(Adatok *lista);     /// Megadja a lista hosszat (azaz: legnagyobb_index+1)
int lista_elem_keres_szoveg(Adatok *lista,char *szoveg);        /// Megadja a keresett szoveg indexet a listaban , ha nem lezezik akkor -1 a visszaadott ertek
int lista_elem_keres_ev(Adatok *lista,int szam);        /// Megadja a keresett evszam indexet a listaban, ha nem lezezik akkor -1 a visszaadott ertek
Adatok *elem_torlese(Adatok *lista,int hanyadik);       /// Lista elemenek torlese egy megadott index helyrol
void felhasznalonal_levo_konyvek(Adatok *lista, char *nev);       /// Kiirja egy felhasznalonal levo konyveket
void kikolcsonzott_konyvek(Adatok *lista,char *cim);        /// Kiirja kinel van az adott konyv
Adatok *lista_atlancol(Adatok *lista,int hanyadik);     /// Egy megadott indexu elem helyere egy masikat lancol
Adatok *elem_letrehoz();        /// Letrehoz egy lista elemet
void lista_konyv_kereso();      /// Megkeresi a keresett szoveget a listaban, majd kiirja a hozza tartozo adatokat
void lista_konyv_kereso_ev();    /// Megkeres egy szamot a listaban majd kiirja a hozza tartozo adatokat

#endif // LISTA_MODOSITAS_H
