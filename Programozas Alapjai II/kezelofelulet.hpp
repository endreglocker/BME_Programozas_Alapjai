#ifndef KEZELOFELULET_H
#define KEZELOFELULET_H

//#include "stringek.hpp"
#include "tickets.hpp"
#include "vektorok.hpp"

#include "memtrace.h"


/// VEGES ALLAPOTGEP ALLAPOTAI:
enum Allapot{
    KEZDO = 0,
    OSSZADAT = 1,
    TORLES = 2,
    HOZZAAD = 3,
    KERES = 4,
    KESES = 5,
    EXIT = 6,
};

class Kezelofelulet
{
    /// @param w - VONATJEGYEKET TAROLO HETEROGEN KOLLEKCIO
    Vektor<Train_Tickets*> w;
public:
    /// A PARAMETER NELKULI KONSTRUKTOR VEGZI AZ ADATOK TAROLOBA VALO BEOLVASASAT
    Kezelofelulet();

    /// ELMENTI AZ ADATOKAT EGY FAJLBA
    void ment();

    /// TORLI AZ ADATOKAT A "w" VEKTORBOL
    void torles();

    /// MEGADOTT HELY ALAPJAN KILISTAZZA AZON JEGYEKET AMELYEK MEGFELELNEK A PARAMETEREKNEK
    void keres_hely();

    /// KILISTAZZA AZON ELEMEKET AMELYEK MEGEGYEZNEK A MEGADOTT IDOVEL
    void keres_ido();

    /// FELVESZ EGY JEGYET A HETEROGEN KOLLEKCIOBA
    void adatfelvetel();

    /// KIVON VAGY HOZZAAD A VONAT ERKEZESI ES INDULASI IDEJEHEZ
    /// @param pred - ELDONT, HOGY HOZZAADNI (true) VAGY KIVONNI (false)
    void keses(bool pred = true);

    /// KILISTAZZA AZ ADATBAZIS OSSZES ELEMET
    void print();

    /// A FOMENU BIZTOSITJA A FELHASZNALOVAL VALO KOMMUNIKACIOT
    void fomenu();

    /// ALLAPOTGEP ALLAPOTAIT KEZELI
    int kezeles(Allapot);

    /// ALLAPOTGEP KOVETKEZO ALLAPOTAT KEZELI
    Allapot nextstate(Allapot,int);

    /// TESZTESETEKET VALOSITJA MEG
    void test();

    /// BEKER A FELHASZNALOTOL EGY ORAT ES PERCET MAJD VISSZATER ANNAK PERCBEN MEGADOTT FORMATUMABAN
    int percben();
};

#endif // KEZELOFELULET_H

