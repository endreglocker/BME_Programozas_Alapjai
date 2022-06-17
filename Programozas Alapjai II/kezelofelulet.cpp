#include "tickets.hpp"
#include "vektorok.hpp"
#include "stringek.hpp"
#include "kezelofelulet.hpp"
#include "gtest_lite.h"

#include "memtrace.h"

Kezelofelulet::Kezelofelulet()
{
    try{
        /// BEOLVASAS
        std::ifstream be;
        be.open("jegyek.txt"); /// MEGNYITJUK AZ ADATOKAT TAROLO FAJLT
        if(!be || be.peek() == EOF) throw -1; /// URES FILE VAGY A FAJLT NEM SIKERUL MEGNYITNI
        int tipus; /// @param tipus - eldonti a jegy tipusat
        int trainnumber; /// @param trainnumber - vonat szama
        int carriagenumber; /// @param carriagenumber - vagon szama
        int lplace; /// @param lplace - ulohely szama
        String startplace; /// @param startplace - indulas helyszine
        int starttime;  /// @param starttime - indulas ideje
        String arrivalplace; /// @param arrivalplace - erkezes helyszine
        int arrivaltime; /// @param arrivaltime - erkezes ideje


        while(!be.eof()){ /// FAJL VEGEIG BEOLVASUNK
            /// ADATOKAT BELETOLTJUK A VALTOZOKBA
            be >> tipus;
            be >> trainnumber;
            be >> carriagenumber;
            be >> lplace;
            be >> startplace;
            be >> starttime;
            be >> arrivalplace;
            be >> arrivaltime;

            /// TIPUS ALAPJAN ELDONTJUK MILYEN TOVABBI ADATTAGOKRA VAN SZUKSEG:
            if(tipus == 1){ /// ELSO OSZTALY ADATAINAK BEOLVASASA
                int dining; /// @param dining - etkezokocsi szama
                int sleep; /// @param sleep - halokocsi szama
                be>>dining;
                be>>sleep;
                /// HA MINDEN ADATOT BEOLVASTUNK HOZZAADJUK A TAROLOHOZ
                w.push_back(new First_Class(trainnumber,carriagenumber,lplace,startplace,starttime,arrivalplace,arrivaltime,dining,sleep));
            }

            if(tipus == 2){ /// MASODOSZTALY ADATAINAK BEOLVASASA
                bool ac; /// @param ac - klima van-e
                bool buf; /// @param buf - bufekocsi van-e
                be>>ac;
                be>>buf;
                /// HA MINDEN ADATOT BEOLVASTUNK HOZZAADJUK A TAROLOHOZ
                Second_Class a(trainnumber,carriagenumber,lplace,startplace,starttime,arrivalplace,arrivaltime,ac,buf);
                w.push_back(new Second_Class(trainnumber,carriagenumber,lplace,startplace,starttime,arrivalplace,arrivaltime,ac,buf));
            }
        }
        be.close(); /// BEZARJUK A FAJLT
        Kezelofelulet::ment(); /// BIZTONSAGI MENTES
    }
    catch (int myNum) /// HIBA KEZELESE
    {
        std::cout<< "A megadott file nem felel meg a kovetelmenyeknek!";
    }
}

void Kezelofelulet::ment()
{
    std::ofstream ki;
    ki.open("jegyek.txt"); /// MEGNYITJUK A FAJLT
    w.save(ki); /// A VEKTOR MENTES FUNKCIOJAT MEGHIVJUK, AMI KIIER MINDEN ELEMET A "ki"-RE
    ki.close(); /// BEZARJUK A FAJLT
}

int atalakit(std::string adat)
{
    /// A PARAMETERKENT KAPOTT STRING VALTOZOBOL KESZIT INTEGER TIPUST
    int szam; /// @param szam - ebbe az adatba fogjuk tolteni a stringbol integerbe konvertalt tagokat
    std::stringstream atalakito; /// stringbol keszit intet
    atalakito<<adat; /// ATADJUK AZ ATALAKITONAK A SZTRINGET
    atalakito>>szam; /// INTEGERRE KONVERTALJUK

    return szam; /// VISSZATERUNK A KONVERTALT FORMATUMMAL
}

int Kezelofelulet::percben()
{
    int ora = -1; /// @param ora - ora
    int perc = -1; /// @param perc - perc
    std::string atmeneti;
    /// ADDIG KER BE A FELHASZNALOTOL ADATOT, AMIG AZ MEG NEM FELEL A KRITERIUMOKNAK
    while(ora < 0 || ora > 24 || perc < 0 || perc > 60){ /// ADDIG NEM LEHET TOVABBLEPNI AMIG AZ ORA ES A PERC NEM FELEL MEG A NORMAL FORMATUMNAK
        std::cout<< "Adja meg az indulasi idot (ora perc formatumban):\nOra: ";
        std::cin>>atmeneti; /// BEOLVASSUK AZ ORAT
        ora = atalakit(atmeneti); /// ATALAKITJUK AZ ORAT
        std::cout<< "Perc: ";
        std::cin>>atmeneti; /// BEOLVASSUK A PERCET
        perc = atalakit(atmeneti); /// ATALAKITJUK A PERCET
        if(ora < 0 || ora > 24 || perc < 0 || perc > 60) std::cout<< "Helytelen input!"<<std::endl;
    }
    return 60*ora + perc; /// VISSZATERUNK PERC FORMATUMBAN
}

void Kezelofelulet::torles()
{
    String honnan; /// @param honnan - indulas helyszine
    String hova; /// @param hova - erkezes helyszine
    /// ADATOK BEKERESE:
    std::cout<< "ELEMEK TORLESE: "<<std::endl<< "Adja meg a jarat honnan indul: ";
    std::cin>>honnan; /// BEKERJUK AZ INDULASI HELYSZINT
    std::cout<< "Adja meg a jarat hova erkezik: ";
    std::cin>>hova; /// BEKERJUK AZ ERKEZESI HELYSZINT
    /// A TORLEST VEGZO FUGGVENY (Vektor-HOZ TARTOZO FUGGVENY)
    w.erase(honnan,hova); /// A VEKTOR TORLO FUGGVENYE ELVEGZI A TORLEST
    /// TORLES UTAN ELMENTJUK AZ ADATOKAT
    Kezelofelulet::ment(); /// MIVEL A VEKTOR ADATAI LEHET MEGVALTOZTAK EZERT MENTSUK EL AZT
}

void Kezelofelulet::keres_hely()
{
    /// EGY STRINGET OLVASUNK BE AMIT OSSZEHASONLITUNK AZ ADATBAZISSAL, HA VAN EGGYEZES AKKOR KIIRJA AZON JEGYEKET
    std::cout<< "KERESES HELY ALAPJAN: "<<std::endl<<"Adja meg a keresett indulasi vagy erkezesi helyszint!    ";
    String allomas; /// @param allomas - indulas vagy erkezes helyszine
    std::cin>>allomas; /// BEKERJUK AZ ALLOMAST
    ///OSSZEHASONLITAS ELVEGZESE
    w.seek_hely(allomas); /// A VEKTOR KERESO FUGGVENYE ELVEGZI AZ OSSZEHASONLITAST ES A KIIRATAST
}

void Kezelofelulet::keres_ido()
{
    /// MIVEL AZ IDOT PERCBEN TAROLJA A Vektor EZERT ATALAKITJUK A MEGFELELO FORMATUMURA
    int ido = percben(); /// BEKERJUK AZ IDOT
    /// ELVEGEZZUK AZ OSSZEHASONLITAST
    w.seek_ido(ido); /// A VEKTOR KERESO FUGGVENYE ELVEGZI AZ OSSZEHASONLITAST ES A KIIRATAST
}

void Kezelofelulet::adatfelvetel()
{
    /// PARAMETEREK, AMIK UGYANAZT A HATASKORT TOLTIK BE MINT A BEOLVASASNAL LEVO ADATTAGOK
    /// AZ OSSZES ELEMET OLYAN ALLAPOTBA HELYEZTEM, AMI A BEOLVASASNAL ALAPVETOEN ERVENYTELEN, IGY LEHETSEGES ADDIG BEOLVASNI, AMIG ERVENYES ADAT NEM ERKEZIK
    int tipus = -1;
    int trainnumber = -1;
    int carriagenumber = -1;
    int lplace = -1;
    String startplace;
    int starttime;
    String arrivalplace;
    int arrivaltime ;
    std::string atmeneti; /// A KONVERTALASHOZ SZUKSEGES SZTRING VALTOZO
    std::cout<< "JEGY FELVETELE AZ ADATBAZISBA: "<<std::endl;

    /// LEHETSEGES HIBAS ADATOK KIZARASA:
    /// ADDIG OLVASSUK BE AZ ADATOKAT, AMIG MEG NEM FELELNEK A KOVETELMENYEKNEK
    while(tipus < 1 || tipus > 2){
        std::cout<< "Adja meg az osztaly tipusat (1: Elsoosztaly ; 2: Masodosztaly): ";
        std::cin>>atmeneti; /// BEOLVASSUK A STRINGET
        tipus = atalakit(atmeneti); /// ATALAKITJUK INTEGERRE
        if(tipus < 1 || tipus > 2) std::cout<< "Helytelen input!"<<std::endl;
    }

    /// ADDIG OLVASSUK BE AZ ADATOKAT, AMIG MEG NEM FELELNEK A KOVETELMENYEKNEK
    while(trainnumber < 1){
        std::cout<< "Adja meg a jarmu szamat: ";
        std::cin>>atmeneti; /// BEOLVASSUK A STRINGET
        trainnumber = atalakit(atmeneti); /// ATALAKITJUK INTEGERRE
        if(trainnumber < 1) std::cout<< "Helytelen input!"<<std::endl;
    }

    /// ADDIG OLVASSUK BE AZ ADATOKAT, AMIG MEG NEM FELELNEK A KOVETELMENYEKNEK
    while(carriagenumber < 1){
        std::cout<< "Adja meg a kocsi szamat: ";
        std::cin>>atmeneti; /// BEOLVASSUK A STRINGET
        carriagenumber = atalakit(atmeneti); /// ATALAKITJUK INTEGERRE
        if(carriagenumber < 1) std::cout<< "Helytelen input!"<<std::endl;
    }

    /// ADDIG OLVASSUK BE AZ ADATOKAT, AMIG MEG NEM FELELNEK A KOVETELMENYEKNEK
    while(lplace < 1){
        std::cout<< "Adja meg a ules szamat: ";
        std::cin>>atmeneti; /// BEOLVASSUK A STRINGET
        lplace = atalakit(atmeneti); /// ATALAKITJUK INTEGERRE
        if(lplace < 1) std::cout<< "Helytelen input!"<<std::endl;
    }

    std::cout<< "Adja meg az indulasi helyszint: ";
    std::cin>> startplace; /// BEOLVASSUK AZ INDULAS HELYET

    /// MIVEL A VEKTOR PERCBEN TAROLJA AZ ADATOT EZERT ALTVALTJUK ARRA
    starttime = percben(); /// BEOLVASSUK AZ INDULAS IDEJET

    std::cout<< "Adja meg az erkezesi helyszint: ";
    std::cin>> arrivalplace; /// BEOLVASSUK AZ ERKEZES HELYET

    /// ADDIG OLVASSUK BE AZ ADATOKAT, AMIG MEG NEM FELELNEK A KOVETELMENYEKNEK
    /// ADATOK KONVERTALASA
    arrivaltime = percben(); /// BEOLVASSUK AZ ERKEZES IDEJET

    /// TIPUS ALAPJA OSZTALYOZZUK A TOVABBI BEOLVASANDO ADATOT
    if(tipus == 1){ /// HA AZ UJ ADAT ELSOOSZTALY
        int dining = -1;
        int sleep = -1;

        /// ADDIG OLVASSUK BE AZ ADATOKAT, AMIG MEG NEM FELELNEK A KOVETELMENYEKNEK
        while(dining < 1){
            std::cout<< "Adja meg az etkezo asztal szamat: ";
            std::cin>>atmeneti; /// BEOLVASSUK A STRINGET
            dining = atalakit(atmeneti); /// ATALAKITJUK INTEGERRE
            if(dining < 1) std::cout<< "Helytelen input!"<<std::endl;
        }

        /// ADDIG OLVASSUK BE AZ ADATOKAT, AMIG MEG NEM FELELNEK A KOVETELMENYEKNEK
        while(sleep < 1){
            std::cout<< "Adja meg a halokocsi szamat: ";
            std::cin>>atmeneti; /// BEOLVASSUK A STRINGET
            sleep = atalakit(atmeneti); /// ATALAKITJUK INTEGERRE
            if(sleep < 1) std::cout<< "Helytelen input!"<<std::endl;
        }

        /// MIUTAN AZ OSSZES ADATOT BEOLVASTUK HOZZAADJUK A TAROLOHOZ
        w.push_back(new First_Class(trainnumber,carriagenumber,lplace,startplace,starttime,arrivalplace,arrivaltime,dining,sleep));
    }

    if(tipus == 2){
        /// MIVEL BOOL VALTOZOK VANNAK DE A BEOLVASASNAL NEM CSAK AZ LEHET, EZERT ATMENETI INTEGEREKET KELL LETREHOZNI, EMELLETT AZ OSSZEHASONLITAS IS PROBLEMAS A CIKLUSBAN
        bool ac = false;
        bool buf = false;
        int ac_kezel = -1; /// @param ac_kezel - az adatok beolvasasat konnyito integer
        int buf_kezel = -1; /// @param buf_kezel - az adatok beolvasasat konnyito integer

        /// ADDIG OLVASSUK BE AZ ADATOKAT, AMIG MEG NEM FELELNEK A KOVETELMENYEKNEK
        while(ac_kezel<0 || ac_kezel>1){
            std::cout<< "Adja meg hog van-e klima (1: van; 0: nincs)! ";
            std::cin>>atmeneti; /// BEOLVASSUK A STRINGET
            ac_kezel= atalakit(atmeneti); /// ATALAKITJUK INTEGERRE
            if(ac_kezel<0 || ac_kezel>1) std::cout<< "Helytelen input!"<<std::endl;
        }

        /// MIVEL INTEGERT OLVASTUNK BE TIPUSKONVERZIOVAL BOOL-T KEPZUNK BELOLE
        ac  = (bool)ac_kezel;

        /// ADDIG OLVASSUK BE AZ ADATOKAT, AMIG MEG NEM FELELNEK A KOVETELMENYEKNEK
        while(buf_kezel < 0 || buf_kezel > 1){
            std::cout<< "Adja meg hog van-e bufekocsi (1: van; 0: nincs)! ";
            std::cin>>atmeneti; /// BEOLVASSUK A STRINGET
            buf_kezel = atalakit(atmeneti); /// ATALAKITJUK INTEGERRE
            if(buf_kezel < 0 ||buf_kezel > 1) std::cout<< "Helytelen input!"<<std::endl;
        }

        /// MIVEL INTEGERT OLVASTUNK BE TIPUSKONVERZIOVAL BOOL-T KEPZUNK BELOLE
        buf = (bool)buf_kezel;

        /// MIUTAN AZ OSSZES ADATOT BEOLVASTUK HOZZAADJUK A TAROLOHOZ
        w.push_back(new Second_Class(trainnumber,carriagenumber,lplace,startplace,starttime,arrivalplace,arrivaltime,ac,buf));
    }

    std::cout<<std::endl<<"SIKERES JEGYFELVETEL!"<<std::endl;
    /// ELMENTJUK A SIKERESEN FELVETT ADATOT A FAJLBA
    Kezelofelulet::ment();
}

void Kezelofelulet::print()
{
    /// KIIRJUK AZ OSSZES ADATOT
    std::cout<< "AZ ADATBAZIS OSSZES ELEME: "<<std::endl;
    w.print(); /// A VEKTOR PRINT FUGGVENYE GONDOSKODIK AZ OSSZES ELEM KIIRASAROL
}

void Kezelofelulet::keses(bool pred) /// @param pred - eldonti, hogy novelni vagy csokkenteni akarunk
{
    std::cout<< "KESESEK KEZELESE: "<<std::endl;

    String honnan; /// @param honnan - indulas helye
    String hova;    /// @param hova - erkezes helye

    /// @param indul - indulas ideje
    /// @param erkez - erkezes ideje
    /// @param valtozas - keses / hamarabb erkezes ideje percben, ez lesz a kivonando vagy az osszeadando
    /// @param ora - ora
    /// @param perc - perc
    int indul,erkez,valtozas = 0;
    std::string atmeneti;
    /// ADATOK BEOLVASASA
    std::cout<< "Adja meg honnan indul a jarat: ";
    std::cin>>honnan; /// BEOLVASSUK AZ INDULAS HELYET
    std::cout<< "Adja meg hova erkezik a jarat: ";
    std::cin>>hova; /// BEOLVASSUK AZ ERKEZES HELYET

    /// IDO PERCBE VALTASA A Vektor ADATTAGJAI MIATT
    indul = percben(); /// BEOLVASSUK AZ IDOT
    /// BEOLVASAS MIATT VISSZAALLITJUK

    /// ADATOK BEOLVASASA AMIG MEG NEM FELELNEK A FELTETELEKNEK

    /// KONVERZIO
    erkez = percben(); /// BEOLVASSUK AZ IDOT

    /// ADATOK BEOLVASASA AMIG MEG NEM FELELNEK A FELTETELEKNEK
    while(valtozas < 1 || valtozas > 60*24){
            std::cout<< "Adja meg a megvaltozas erteket (percben): ";
            std::cin>>atmeneti; /// BEOLVASSUK A STRINGET
            valtozas = atalakit(atmeneti); /// INTEGERRE KONVERTALJUK
            if(valtozas < 1) std::cout<< "Helytelen input!"<<std::endl;
    }

    /// ELVEGZI A NOVELEST / CSOKKENTEST, pred-TOL FUGGOEN
    w.valtozas(honnan,hova,indul,erkez,valtozas,pred); /// A VEKTOR VALTOZAS FUGGVENYE ELVEGZI AZ OSSZEHASONLITAST ES AZ IDO MEGVALTOZTATASAT

    /// A MEGVALTOZOTT ADATOKAT ELMENTI
    Kezelofelulet::ment(); /// MIVEL A VEKTOR MODOSULHAT, EZERT BIZTONSAGI MENTEST KESZITUNK
}

int Kezelofelulet::kezeles(Allapot aktualis_allapot)
{
    system("cls");
    int utasitas = -1; /// @param - eldonti hogy melyik folyamat menjen vegbe
    std::string atmeneti; /// CSAK A KONVERZIOHOZ KELL
    /// ALLAPOTGEP: AKTUALIS MUVELETEK ELVEGZESE
    /// AZ OSSZES LEHETSEGES ALLAPOT LEKEZELESE
    switch(aktualis_allapot)
    {
        case KEZDO:
                std::cout<<"1: OSSZES JEGY KILISTAZASA"<<std::endl
                         <<"2: JEGY TORLESE"<<std::endl
                         <<"3: JEGY FELVETELE"<<std::endl
                         <<"4: KERESES (JEGY)"<<std::endl
                         <<"5: KESESEK KEZELESE"<<std::endl
                         <<"6: KILEPES"<<std::endl
                         <<"VALASSZA KI A TEVEKENYSEGET!    ";
                std::cin>>atmeneti; /// BEOLVASSUK A STRINGET
                utasitas = atalakit(atmeneti); /// INTEGERRE KONVERTALJUK
                break;
        case OSSZADAT:
                Kezelofelulet::print();
                system("pause");
                break;
        case TORLES:
                Kezelofelulet::torles();
                system("pause");
                break;
        case KERES:
                std::cout<< "0: VISSZA"<<std::endl
                         << "1: KERESES HELY ALAPJAN"<<std::endl
                         << "2: KERESES IDO ALAPJAN"<<std::endl
                         <<"VALASSZA KI A TEVEKENYSEGET!    ";
                std::cin>>atmeneti; /// BEOLVASSUK A STRINGET
                utasitas = atalakit(atmeneti); /// INTEGERRE KONVERTALJUK
                switch(utasitas){
                        case 0:
                            aktualis_allapot = KEZDO;
                            break;
                        case 1:
                            system("cls");
                            Kezelofelulet::keres_hely();
                            system("pause");
                            aktualis_allapot = KEZDO;
                            break;
                        case 2:
                            system("cls");
                            Kezelofelulet::keres_ido();
                            system("pause");
                            aktualis_allapot = KEZDO;
                            break;
                        default:
                            aktualis_allapot = KESES;
                }
                break;
        case KESES:
                std::cout<< "0: VISSZA"<<std::endl
                         << "1: KESES MEGADASA"<<std::endl
                         << "2: KORABBAN ERKEZES BEALLITASA"<<std::endl
                         <<"VALASSZA KI A TEVEKENYSEGET!    ";
                std::cin>>atmeneti; /// BEOLVASSUK A STRINGET
                utasitas = atalakit(atmeneti); /// INTEGERRE KONVERTALJUK
                switch(utasitas){
                        case 0:
                            aktualis_allapot = KEZDO;
                            break;
                        case 1:
                            system("cls");
                            Kezelofelulet::keses(true);
                            system("pause");
                            aktualis_allapot = KEZDO;
                            break;
                        case 2:
                            system("cls");
                            Kezelofelulet::keses(false);
                            system("pause");
                            aktualis_allapot = KEZDO;
                            break;
                        default:
                            aktualis_allapot = KESES;
                }
                break;
        case HOZZAAD:
                Kezelofelulet::adatfelvetel();
                system("pause");
                break;
        default:
                std::cout<< "Helytelen input!"<<std::endl;
                system("pause");
                break;
    }
    return utasitas;
}

Allapot Kezelofelulet::nextstate(Allapot aktualis_allapot,int utasitas)
{
    /// KOVETKEZO ALLAPOT LOGIKAJA
    switch(aktualis_allapot){
        case KEZDO:
                return (Allapot)utasitas;
        default:
            return KEZDO;
    }
    return aktualis_allapot;
}

void Kezelofelulet::fomenu()
{

    Allapot lepteto = KEZDO; /// @param lepteto - az allapotokon belluli leptetest vegzi

    /// ADDIG FUT A PROGRAM, AMIG AZ EXIT ALLAPOTBA NEM ERUNK
    while(lepteto != EXIT)
    {
        int utasitas = Kezelofelulet::kezeles(lepteto); /// UTASITAS MEGHATAROZASA
        lepteto = Kezelofelulet::nextstate(lepteto, utasitas); /// ALLAPOT MEGHATAROZASA
    }
    /// BIZTONSAGI MENTES
    Kezelofelulet::ment(); /// KILEPES UTAN MEGEGYSZER MENTJUK AZ ADATOKAT
}

void Kezelofelulet::test()
{
    GTINIT(std::cin);       // Csak C(J)PORTA mûködéséhez kell

    TEST(Test1,AlltalanosVektor) /// GENERIKUS VEKTOR TESZT
    {
        Vektor<int> a; /// LETREHOZUNK EGY VEKTORT
        EXPECT_EQ((size_t)0,a.size()) << "Nem jo a default meret"<<std::endl; /// MEGNEZZUK HOGY ALAPBOL VALOBAN 0-E A MERETE
        /// ELEMEK HOZZAADASA
        a.push_back(1);
        a.push_back(2);
        a.push_back(3);
        EXPECT_EQ((size_t)3,a.size()) << "Nem jo a meret"<<std::endl; /// MERET ELLENORZESE
        /// ELEMENKENTI ELLENORZES
        EXPECT_EQ(1,a[0]) << "Nem jo ertek"<<std::endl;
        EXPECT_EQ(2,a[1]) << "Nem jo ertek"<<std::endl;
        EXPECT_EQ(3,a[2]) << "Nem jo ertek"<<std::endl;
    }ENDM

    TEST(Test2,Train_Tickets_Vektor) /// HETEROGEN KOLLEKCIO TESZTELESE
    {
        Vektor<Train_Tickets*> b; /// SPECIALIZALT VEKTOR LETREHOZASA
        EXPECT_EQ((size_t)0,b.size()) << "Nem jo a default meret"<<std::endl; /// A MERET ALAPBOL 0-E

        /// DEFAULT ADATOK HOZZAADASA
        b.push_back(new First_Class());
        b.push_back(new Second_Class());
        EXPECT_EQ((size_t)2,b.size()) << "Nem jo a  meret"<<std::endl; /// MERET UJBOLI ELLENORZESE

        /// ERTEKEK ALAP BEALLITASA -1
        /// AZ ADATOK TAGONKENTI ELLENORZESE
        EXPECT_EQ(-1,b[0]->get_type()) << "Nem jo adat"<<std::endl;
        EXPECT_EQ(-1,b[0]->get_train_number()) << "Nem jo adat"<<std::endl;
        EXPECT_EQ(-1,b[0]->get_carriage_number()) << "Nem jo adat"<<std::endl;
        EXPECT_EQ(-1,b[0]->get_place()) << "Nem jo adat"<<std::endl;
        EXPECT_EQ(-1,b[0]->get_start_time()) << "Nem jo adat"<<std::endl;
        EXPECT_EQ(-1,b[0]->get_arrival_time()) << "Nem jo adat"<<std::endl;

        /// TOROLJUK EGY ELEMET
        b.erase("Start place","Arrival place");
        EXPECT_EQ((size_t)0,b.size()) << "Nem sikerult a torles"<<std::endl; /// ELLENORIZZUK HOGY VALOBAN CSOKKENT-E A MERET

    }ENDM

    TEST(Train_Tickets,First_Class){ /// ELSOOSZTALY TESZTELESE
        First_Class a(100,10,25,"X",500,"Y",600,7,9); /// INICIALIZALAS
        ///ADATOK ELLENORZESE
         EXPECT_EQ(1,a.get_type()) << "Nem jo adat"<<std::endl;
         EXPECT_EQ(100,a.get_train_number()) << "Nem jo adat"<<std::endl;
         EXPECT_EQ(10,a.get_carriage_number()) << "Nem jo adat"<<std::endl;
         EXPECT_EQ(25,a.get_place()) << "Nem jo adat"<<std::endl;
         EXPECT_EQ(500,a.get_start_time()) << "Nem jo adat"<<std::endl;
         EXPECT_EQ(600,a.get_arrival_time()) << "Nem jo adat"<<std::endl;
         EXPECT_EQ(7,a.get_dining_table()) << "Nem jo adat"<<std::endl;
         EXPECT_EQ(9,a.get_sleeper()) << "Nem jo adat"<<std::endl;
         std::cout<<std::endl<< "     "<<a.get_start_place()<< " "<<a.get_arrival_place()<<std::endl;
         /// operator=
         a = 10;
         EXPECT_EQ(10,a.get_start_time()) << "Nem jo adat"<<std::endl;
         EXPECT_EQ(10,a.get_arrival_time()) << "Nem jo adat"<<std::endl;
         /// operator +=
         a += 500;
         EXPECT_EQ(510,a.get_start_time()) << "Nem jo adat"<<std::endl;
         EXPECT_EQ(510,a.get_arrival_time()) << "Nem jo adat"<<std::endl;
         /// operator -=
         a -= 75;
         EXPECT_EQ(435,a.get_start_time()) << "Nem jo adat"<<std::endl;
         EXPECT_EQ(435,a.get_arrival_time()) << "Nem jo adat"<<std::endl;

         /// EBEDLO FOGLALAS TESZTELESE
         /// HALOKOCSI FOGLALAS TESZTELESE
         EXPECT_EQ(true,a.isD_t()) << "Nem jo adat"<<std::endl;
         EXPECT_EQ(true,a.isSper()) << "Nem jo adat"<<std::endl;

         /// HALOKOCSI DIJANAK TESZTELESE
         EXPECT_EQ(0,a.sleeper_fee()) << "Nem jo adat"<<std::endl;
    }ENDM

    TEST(Train_Tickets,Second_Class){ /// MASODOSZTALY TESZTELESE
        Second_Class a(100,10,25,"X",500,"Y",600,true,false); /// INICIALIZACIO
        ///ADATOK ELLENORZESE
         EXPECT_EQ(2,a.get_type()) << "Nem jo adat"<<std::endl;
         EXPECT_EQ(100,a.get_train_number()) << "Nem jo adat"<<std::endl;
         EXPECT_EQ(10,a.get_carriage_number()) << "Nem jo adat"<<std::endl;
         EXPECT_EQ(25,a.get_place()) << "Nem jo adat"<<std::endl;
         EXPECT_EQ(500,a.get_start_time()) << "Nem jo adat"<<std::endl;
         EXPECT_EQ(600,a.get_arrival_time()) << "Nem jo adat"<<std::endl;
         EXPECT_EQ(true,a.get_AC()) << "Nem jo adat"<<std::endl;
         EXPECT_EQ(false,a.get_bufe()) << "Nem jo adat"<<std::endl;
         std::cout<<std::endl<< "     "<<a.get_start_place()<< " "<<a.get_arrival_place()<<std::endl;
         /// operator=
         a = 10;
         EXPECT_EQ(10,a.get_start_time()) << "Nem jo adat"<<std::endl;
         EXPECT_EQ(10,a.get_arrival_time()) << "Nem jo adat"<<std::endl;
         /// operator +=
         a += 500;
         EXPECT_EQ(510,a.get_start_time()) << "Nem jo adat"<<std::endl;
         EXPECT_EQ(510,a.get_arrival_time()) << "Nem jo adat"<<std::endl;
         /// operator -=
         a -= 75;
         EXPECT_EQ(435,a.get_start_time()) << "Nem jo adat"<<std::endl;
         EXPECT_EQ(435,a.get_arrival_time()) << "Nem jo adat"<<std::endl;

         /// KLIMA DIJANAK ELLENORZESE
         int delta = 1600*(a.get_arrival_time()-a.get_start_time());
         EXPECT_EQ(delta,a.AC_fee()) << "Nem jo adat"<<std::endl;
    }ENDM

    TEST(String,String)
    {
        /// STRINGEK INICIALIZALASA
        String a; /// PARAMETER NELKUL
        String b('c'); /// KARAKTERREL
        String c("alma"); /// STRINGGEL
        /// MERETEK ELLENORZESE
        EXPECT_EQ((size_t)0,a.size()) << "Nem jo a default meret"<<std::endl;
        EXPECT_EQ((size_t)1,b.size()) << "Nem jo a default meret"<<std::endl;
        EXPECT_EQ((size_t)4,c.size()) << "Nem jo a default meret"<<std::endl;

        /// OPERATOR = ÉS + ELLENORZESE
        /// SZTRING + SZTRING
        a = b+c;
        EXPECT_EQ((size_t)5,a.size()) << "Nem jo a default meret"<<std::endl;
        ///SZTRING + CHAR*
        a = a + "pite";
        EXPECT_EQ((size_t)9,a.size()) << "Nem jo a default meret"<<std::endl;
        ///SZTRING + KARAKTER
        a= a + 'c';
        EXPECT_EQ((size_t)10,a.size()) << "Nem jo a default meret"<<std::endl;

        String szoveg1 = "repa";
        String szoveg2 = "torta";
        a = szoveg1 + szoveg2;
        EXPECT_EQ((size_t)9,a.size()) << "Nem jo a default meret"<<std::endl;
        EXPECT_STREQ("repatorta",a.get_pData()) << "Hibas szoveg!";
    }ENDM

    GTEND(std::cerr);       // Csak C(J)PORTA mûködéséhez kell

    std::cout<<std::endl;
    /// KIIRATO FUGGVENY TESZTELESE
    Kezelofelulet::print();
}
