#ifndef VektorROK_HPP
#define VektorROK_HPP

#include "tickets.hpp"

#include "memtrace.h"
/// GENERIKUS VEKTOR
template <typename T>
class Vektor{
    T *adat; /// @param adat - egy adott valtozora tipushoz tartozo mutato, ami az adatokat tarolja
    size_t meret; /// @param meret - vektor merete
    /// LETILTJUK A MASOLO KONSTRUKTORT ES AZ operator= -T
    Vektor(T const &);
    Vektor& operator=(const T& rhs);

public:

    /// LETREHOZ EGY VEKTORT, AMI HA NINCS MERET MEGADVA, ALAPERTELMEZETTEN 0
    explicit Vektor(size_t meret = 0): adat(new T[meret]), meret(meret){}

    class iterator {
        Vektor *p; /// @param - egy vektorramutato;
		size_t idx; /// @idx - es ennek az indexe
    public:

        /// DEFAULT KONSTRUKTOR
        iterator() :p(0), idx(0) {}

        /// A KONSTRUKTOR EGY KONKRET OBJEKTUM IDX ELEMERE MUTAT
        iterator(Vektor& a, size_t ixd = 0): p(&a),idx(ixd){}

        /// OSSZEHASONLIT KET ITERATORT
        /// HA A KET ITERATOR EGYENLO AKKOR IGAZ ERTEKET AD, HA NEM AKKOR HAMISAT
		bool operator==(const iterator &i) const {
            return (idx == i.idx);
        }

        /// MEGNEZI HOGY AZ ITERATOROK NEM EGYENLOEK-E
        /// HA NEM EGYENLOEK VISSZATER IGAZ ERTEKKEL, HA EGYENLOEK AKKOR HAMIS ERTEKER AD
        bool operator!=(const iterator &i) const {
            return (idx != i.idx);
        }

        /// INDIREKCIO
        T& operator*() const {
            try{ /// HIBAKEZELES
            if(idx >= p->meret) throw -1; /// TULLEPI A MERETET
            }
            catch (int myNum){
                std::runtime_error("HIBA AZ INDIREKCIONAL!");
            }
            return p->adat[idx];
        }

        /// NYIL OPERATOR
        T* operator->() const {
            return &operator*();
        }

        /// PREINKREMENS
        iterator& operator++() {
            if (idx != p->meret) ++idx; /// HA ELERI A MERETET ONNAN MAR NEM TUD NOVELNI
            return *this;
        }

        /// POSTINKREMENS
        iterator operator++(int) {
            iterator tmp = *this;       /// ERTEKADAS
            if (idx != p->meret) idx++;   /// INDEX NOVELESE, HA AZ MEG NEM ERTE EL A MERET HATART
            return tmp;
        }

    };

    iterator begin() {
        return iterator(*this); /// VISSZATER EGY AZ ELEJERE MUTATO ITERATORRAL
    }

    iterator end() {
        return iterator(*this, meret); /// VISSZATER EGY AZ ADATSOROZAT UTOLSO ELEMERE UTANRA MUTATO ITERATORRAL
    }

    /// GETTER
    size_t size() const {
        return meret; /// VISSZATER A VEKTOR MERETEVEL
    }

    /// INDEXELO OPERATOROK:
    T& operator[](size_t index) {
        try{
            if(index>=meret){ /// MEGVIZSGALJA HOGY AZ INDEX AZ BELETARTOZIK-E A MERET TARTOMANYABA
                throw -1;
            }
        }catch (int myNum){ /// HA NEM AKKOR HIBAT DOB RA
                std::cout<< "MERETNEL NAGYOBB INDEX!";
        }
        return adat[index]; /// HA LETEZIK AZ INDEX AKKOR VISSZATER AZ ADOTT INDEXEN LEVEO ELEMMEL
    }

    T const& operator[](size_t index) const {
        try{
            if(index>=meret){ /// MEGVIZSGALJA HOGY AZ INDEX AZ BELETARTOZIK-E A MERET TARTOMANYABA
                throw -1;
            }
        }catch (int myNum){  /// HA NEM AKKOR HIBAT DOB RA
                std::cout<< "MERETNEL NAGYOBB INDEX!";
        }
        return adat[index]; /// MEGVIZSGALJA HOGY AZ INDEX AZ BELETARTOZIK-E A MERET TARTOMANYABA
    }

    /// T ELEM HOZZAADASA A Vektor-HOZ
    void push_back(T uj_ertek) {
        /// LETREHOZUNK EGY ATMENETI VALTOZOT
        /// A VALTOZO MERETE EGGYEL NAGYOBB MINT AZ EREDETI TAROLOE
        /// HOZZAADJUK AZ UJ ELEMET AZ UJ TAROLOHOZ
        /// TOROLJUK A REGI TAROLOT
        /// EGYENLOVE TESSZUK AZ UJ TAROLOVAL A REGET
        /// HOZZAADJUK AZ UJ ADATOT
        /// BEALLITJUK A TAROLO MERETENEK AZ ERTEKET
        T *uj_adat = new T[meret + 1]; /// ATMENETI VALTOZO AMINEK A MERETE EGGYEL NAGYOBB AZ EREDETINEL
        for(size_t i = 0; i < meret; ++i) /// ELEMENKENT ATMASOLJUK AZ ADATOKAT
            uj_adat[i] = adat[i];
        uj_adat[meret] = uj_ertek; /// AZ UJ HELYRE BEMASOLJUK AZ ERKEZO ELEMET
        delete[] adat; /// TOROLJUK A REGE TAROLOT
        adat = uj_adat; /// ATADJUK A REGI TAROLONAK AZ UJ ADATOKAT
        ++meret; /// MEGNOVELJUK A MERETET
    }

    /// KIIRJUK A TAROLOBAN TALALHATO OSSZES ADATOT
    void print() const
    {
        for(size_t i=0; i<meret; i++) /// VEGIGMEGYUNK A TAROLO OSSZES ELEMEN
        {
            std::cout<<adat[i]<<std::endl; /// MINDEN ELEMET KIIRJUK AZ OSTREAMRE
        }
    }

    ~ Vektor() {delete[] adat; meret = 0;} /// MIVEL MEMORIATERULETET FOGLALUNK, EZERT AZT FEL IS KELL SZABADITANI
};

/// SPECIALIZACIO Train_Ticket*-RA:
template <>
class Vektor<Train_Tickets*>{
    Train_Tickets* *adat; /// @param adat - Train_Tickets* tipusu adatokat tarolo tomb
    size_t meret;   /// @param meret - a tarolo merete
    /// LETILTJUK A MASOLO KONSTRUKTORT ES AZ operator=-T
    Vektor(Train_Tickets* const &);
    Vektor& operator=(const Train_Tickets*& rhs);

public:
    /// INICIALIZALJUK A MERETET ES FOGLALUNK MEMORIAT A MERETNEK
    /// HA MERET PARAMETER NINCS MEGADVA AKKOR AZ LEGYEN 0
    explicit Vektor(size_t meret = 0) : adat(new Train_Tickets*[meret]), meret(meret){}

    /// GETTER:
    size_t size() const {
        return meret; /// VISSZATER A TAROLO MERETEVEL
    }

    /// A FOGLALT MEMORIATERULETEKET FELSZABADITJA
    void clear() {
        for (; meret > 0; meret--) { /// MERETTOL INDULVA AZT FOLYAMATOSAN CSOKKENTVE VEGIGMEGY A TAROLON
            delete adat[meret-1]; /// MIVEL KETSZERES DEREFERALAS TORTENIK, IGY MINDEN ELEMET EGYESEVEL TOROLNI KELL
        }
        delete [] adat; /// PUSH_BACK VAGY ELEM HOZZAADBOL FUGGVENYBOL HATRAMARADO ELEM FELSZABADITASA
    }

    /// INDEXELES
    Train_Tickets*& operator[](size_t index) {
        /// HIBAKEZELES
        try{
            if(index>=meret){ /// MEGVIZSGALJA HOGY AZ INDEX AZ BELETARTOZIK-E A MERET TARTOMANYABA
                throw -1;
            }
        }catch (int myNum){
                std::cout<< "MERETNEL NAGYOBB INDEX!"; /// MINDEN ELEMET KIIRJUK AZ OSTREAMRE
        }
        return adat[index]; /// MINDEN ELEMET KIIRJUK AZ OSTREAMRE
    }

    Train_Tickets* const& operator[](size_t index) const {
        /// HIBAKEZELES
        try{
            if(index>=meret){ /// MEGVIZSGALJA HOGY AZ INDEX AZ BELETARTOZIK-E A MERET TARTOMANYABA
                throw -1;
            }
        }catch (int myNum){
                std::cout<< "MERETNEL NAGYOBB INDEX!"; /// MINDEN ELEMET KIIRJUK AZ OSTREAMRE
        }
        return adat[index]; /// MINDEN ELEMET KIIRJUK AZ OSTREAMRE
    }

    /// UJ ELEM HOZZAADASA A TOMBHOZ

    void push_back(Train_Tickets* uj_ertek) {
        /// LETREHOZUNK EGY ATMENETI VALTOZOT
        /// A VALTOZO MERETE EGGYEL NAGYOBB MINT AZ EREDETI TAROLOE
        /// HOZZAADJUK AZ UJ ELEMET AZ UJ TAROLOHOZ
        /// TOROLJUK A REGI TAROLOT
        /// EGYENLOVE TESSZUK AZ UJ TAROLOVAL A REGET
        /// HOZZAADJUK AZ UJ ADATOT
        /// BEALLITJUK A TAROLO MERETENEK AZ ERTEKET
        Train_Tickets* *uj_adat = new Train_Tickets*[meret + 1]; /// LEFOGlALUNK AZ EREDETINEL EGGYEL NAGYOBB MERMORIATERULETET

        for(size_t i = 0; i < meret; i++) /// VEGIGMEGYUNK AZ EREDETI TAROLO ELEMEIN
        {
            uj_adat[i] = adat[i]; /// ATADJUK AZOKAT AZ UJ TAROLONAK
        }

        uj_adat[meret] = uj_ertek; /// AZ ERKEZO ELEMET BELETESSZUK AZ UJ TAROLOBA
        delete[] adat; /// FELSZABADITJUK A REGIT
        adat = uj_adat; /// ATADJUK AZ UJ TAROLOT A REGINEK
        ++meret; /// MEGNOVELJUK A REGI TAROLOT
    }

    /// TORLUNK EGY TETSZOLEGES ELEMET A TAROLOBOL
    void erase(String honnan, String hova) /// PARAMETERUL KAPUNK 2 STRINGET
    {
        try{ /// HIBAKEZELES
            size_t uj = 0; /// @param uj - a keresett elemek szamat jelzi

            for(size_t i = 0; i < meret ; i++){ /// VEGIGMEGYUNK A TAROLON
                if(honnan == adat[i]->get_start_place() && hova == adat[i]->get_arrival_place()){ /// MEGNEZZUK HOGY VAN-E EGGYEZES A FELTETELEKKEL
                    uj++; /// HA VAN AKKOR AKKOR A TALALATOK ERTEKET MEGNOVELJUK
                }
            }

            if(uj == 0) throw -1; /// HA A MEGADOTT ADATOK NEM EGYEZNEK EGYIK ADATBAZISBELI ADATTAL SEM

            /// HA VAN TALALAT AKKOR:
            if(uj > 0){
                /// FOGLALUNK (meret-uj)-NI MEMORIATERULETET, MIVEL AZ AZ EREDETINEL KISEBB MERETU LESZ
                Train_Tickets* *uj_adat = new Train_Tickets*[meret - uj]; /// @param uj_adat - letrehozunk egy uj tombot, amibe a megmarado adatok kerulnek
                size_t counter = 0; /// @param counter - az uj_adat indexeleset biztositja

                /// ATMASOLJUK A MEGMARADO ADATOKAT uj_adat-BA, A TOROLNI KIVANT ADATOKAT PERDIG FELSZABADITJUK
                for(size_t i = 0; i < meret; i++){ /// VEGIGMEGYUNK A TAROLO OSSZES ADATAN
                    if(honnan != adat[i]->get_start_place() || hova != adat[i]->get_arrival_place()){ /// OSSZEVETJUK A KERESESI FELTETELLEL
                        uj_adat[counter++] = adat[i]; /// HA AZ ADOTT ELEM NEM TARTALMAZZA A FELTETELT, AKKOR HOZZAADJUK AZ UJ TAROLOHOZ
                    }
                    else{
                        delete adat[i]; /// HA TARTALMAZZA A FELTETELT, AKKOR FELSZABADITJUK AZ ADATOT
                    }
                }
                /// VISSZAMASOLAS AZ EREDETIBE
                delete[] adat; /// FELSZABADITJUK A MARADEK ADATOT
                adat = uj_adat; /// ATADJUK AZ UJ TAROLOT A REGINEK
                /// MERET BEALLITASA
                meret = meret - uj; /// BEALLITJUK A MERETET
                std::cout<< "SIKERES TORLES!"<<std::endl;
            }
        }
        catch (int myNum) /// HA NINCS EGYEZES HIBAT ADUNK
        {
            std::cout<< "A torolni kivant jaratok nem talalhatok az adatbazisban!"<<std::endl;
        }

    }

    /// HELY ALAPJAN KERESES
    void seek_hely(String allomas) const /// PARAMETERKENT KAPUNK EGY HELYSZINT
    {
        try{ /// HIBAKEZELES
            int talalat = 0; /// @param talalat - megadja az egyezesek szamat
            /// VEGIGMEGYUNK A TOMBON, HA VAN EGYEZES KIIRATJUK
            for(size_t i=0; i<meret; i++){ /// VEGIGMEGYUNK A TAROLON
                if(allomas == adat[i]->get_start_place() || allomas == adat[i]->get_arrival_place()){ /// MEGNEZZUK HOGY VAN-E EGYEZES AZ INDULASI VAGY ERKEZESI HELYSZINEN
                   adat[i]->print(); /// HA VAN AKKOR KIIRATJUK AZ ADATOT
                   talalat++; /// ES MEGNOVELJUK A TALALATOK SZAMAT
                }
            }
            if(talalat == 0) throw -1; /// HA NINCS TALALAT HIBAT DOBUNK
        }
        catch (int myNum) /// KEZELJUK A HIBAT
        {
            std::cout<< "A keresett helyszin nem talalhato az adatbazisban!"<<std::endl;
        }
    }

    /// IDO ALAPJAN KERESES
    void seek_ido(int ido) const /// PARAMETERUL KAPUNK EGY IDOT PERCBEN
    {
        try{ /// HIBAKEZELES
            int talalatok = 0; /// @param talalatok - megmutatja, hogy hany elem egyezik meg a keresesi feltetellel
            for(size_t i=0; i<meret; i++){ /// BEJARJUK A TAROLOT
                if(ido == adat[i]->get_start_time() || ido == adat[i]->get_arrival_time()){ /// MEGNEZZUK HOGY AZ INDULASI VAGY ERKEZESI IDO EGYEZIK-E VELE
                    adat[i]->print(); /// HA IGEN KIIRJUK
                    talalatok++; /// ES MEGNOVELJUK A TALALATOKAT
                }
            }
            if(talalatok == 0) throw -1; /// HA NINCS TALALAT AKKOR KIVETELT DOBUNK
        }
        catch (int myNum){ /// KEZELJUK A HIBAT
                std::cout<< "A keresett idopontban nem indul jarat!"<<std::endl;
        }
    }

    /// MENETIDOBELI VALTOZAS KEZELESE
    void valtozas(String honnan,String hova,int indul,int erkez, int elteres, bool eldont) /// PARAMETERUL KAPUNK KIINDULASI ES ERKEZESI HELYSZINEKET ES IDOPONTOKAT EMELLET EGY ELDONT VALTOZOT, AMI MEGHATAROZZA, HOGY AZ IDOT NOVELNI VAGY CSOKKENTENI KELL
    {
        try{
            int talalatok = 0; /// @param talalatok - megadja a keresesi feltetelekkel valo egyezesek szamat
            for(size_t i=0; i<meret; i++){ /// BEJARJUK A TAROLOT
                if(indul == adat[i]->get_start_time() && erkez == adat[i]->get_arrival_time() && honnan == adat[i]->get_start_place() && hova == adat[i]->get_arrival_place()){ /// OSSZEHASONLITJUK A FELTETELEKKEL AZ ADATOKAT
                    /// @param eldont - ha igaz, akkor novevljuk a menetidot, ha hamis akkor csokkentjuk azt
                    if(eldont){
                        *adat[i]+=elteres; /// MEGNOVELJUK A JARAT ERKEZESI ES INDULASI IDEJET
                    }
                    else{
                        *adat[i]-=elteres; /// CSOKKENTUK A JARAT INDULASI ES ERKEZESI IDEJET
                    }
                    talalatok++;
                }
            }
            if(talalatok == 0) throw -1; /// HA NINCS TALALAT AKKOR HIBAT DOBUNK
        }
        catch (int myNum){ /// KIVETEL KEZELESE
                std::cout<< "A megadott adatok nem egyeznek meg egyik jeggyel sem!"<<std::endl;
        }
    }
    /// A TAROLOBAN LEVO OSSZES ADATOT KIIRJUK
    void print() const
    {
        for(size_t i=0; i<meret; i++) /// BEJARJUK A TAROLOT
        {
            adat[i]->print(); /// A HETEROGEN KOLLEKCIO MINDEN ELEMERE MEGHIVJUK A SAJAT KIIRATO FUGGVENYET
        }
    }

    /// ADATOK MENTESE
    void save(std::ostream & os) const
    {
        for(size_t i=0;i<meret-1;i++){ /// BEJARJUK A TAROLOT
            adat[i]->save(os); /// A HETEROGEN KOLLEKCIO MINDEN ELEMERE MEGHIVJUK A SAJAT MENTO FUGGVENYET
            os<<std::endl; /// AZ ADATTAGOKAT A MENTETT FAJLBAN SORTORESSEL VALASZTJUK EL
        }
        /// UTOLSO SOR VEGERE NEM KELL ENTER
        adat[meret-1]->save(os); /// AZ UTOLSO SOR VEGERE NEM KELL SORTORES, EZERT ANNAK AZ ELEMNEK KULON KELL MEGHIVNI A MENTES FUGGVENYET
    }

    ~ Vektor()
    {
        /// FELSZABADITJUK A LEFOGLALT MEMORIATERULETEKET A CLEAR FUGGVENNYEL A KETSZERES DEREFERALAS MIATT
        clear();
    }
};

#endif // VektorROK_HPP
