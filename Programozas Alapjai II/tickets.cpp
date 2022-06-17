#include "tickets.hpp"

#include "memtrace.h"
/// TRAIN TICKETS :

Train_Tickets::Train_Tickets() /// ALAPERTELMEZETTEN MINDENRE "ERVENYTELEN ADATOT" ALLIT BE
    :type(-1),train_number(-1),carriage_number(-1),place(-1),start_place("Start place"),start_time(-1),arrival_place("Arrival place"),arrival_time(-1){}

Train_Tickets::Train_Tickets(const Train_Tickets & rhs)
{
    /// MASOLO KONSTRUKTOR
    /// AZ RHS ADATAINAK ATADASA A *THIS-NEK
    type = rhs.type;
    train_number = rhs.train_number;
    carriage_number = rhs.carriage_number;
    place = rhs.place;
    start_place = rhs.start_place;
    start_time = rhs.start_time;
    arrival_place = rhs.arrival_place;
    arrival_time = rhs.arrival_time;
}

/// MENTESHEZ KIIRJA AZ ADATTAGOKAT AZ OSTREAMRE
void Train_Tickets::save(std::ostream& os) const
{
    /// A PARAMETERKEN KAPOTT OSTREAM PARAMETERNEK
    /// ATADJUK AZ ABSZTRAKT OSZTALY ADATTAGJAIT SZOKOZZEL TAGOLVA
    /// EZ DEFINIALJA A MENTES FORMATUMAT
    os<<type<< " "
      <<train_number<< " "
      <<carriage_number<< " "
      <<place<< " "
      <<start_place<< " "
      <<start_time<< " "
      <<arrival_place<< " "
      <<arrival_time<< " ";
}

/// KIIRJA A MEGFELELO FORMATUMBAN AZ ADATOKAT
void Train_Tickets::print() const {
        /// KIIRJUK AZ OSTREAMRE AZ OSSZES ADATTAGOT
        std::cout <<"Vonat: "<<train_number<< "; Kocsi: "
                  <<carriage_number<< "; Ules: "
                  <<place<< "; Indulas: "
                  <<start_place<< "; ";
        /// IDO FORMATUMANAK BEALLITASA
        /// HA A PERC KISEBB MINT TIZ AKKOR FORMATUMA 0X
        /// HA LEGALABB TIZ A PERC, AKKOR FORMATUMA XX
        /// INDULASI IDO FORMATUM BEALLITASA
        if(start_time%60 < 10) std::cout<<start_time/60<< ":0"<<start_time%60<<"; ";
        else std::cout<<start_time/60<< ":"<<start_time%60<<"; ";
        ///ERKEZESI IDO FORMATUM BEALLITASA
        if(arrival_time%60 < 10) std::cout<<"Erkezes: "<<arrival_place<< "; "<<arrival_time/60<< ":0"<<arrival_time%60<<"; ";
        else std::cout<<"Erkezes: "<<arrival_place<< "; "<<arrival_time/60<< ":"<<arrival_time%60<<"; ";
    }

/// GETTEREK:
int Train_Tickets::get_type()const{return type;}
int Train_Tickets::get_train_number()const{return train_number;}
int Train_Tickets::get_carriage_number()const{return carriage_number;}
int Train_Tickets::get_place()const{return place;}
String Train_Tickets::get_start_place()const{return start_place;}
int Train_Tickets::get_start_time()const{return start_time;}
String Train_Tickets::get_arrival_place()const{return arrival_place;}
int Train_Tickets::get_arrival_time()const{return arrival_time;}

/// FIRST CLASS :
First_Class::First_Class(int a_train_number, int a_carriage_number, int a_place, String a_start_place, int a_start_time, String a_arrival_place, int a_arrival_time,int a_dining_table,int a_sleeper)
{
    /// BEALLITJA AZ OSSZES ADATTAGOT A PARAMETERKENT KAPOTT ADATOKKAL
    /// MIVEL ELSOOSZTALYROL VAN SZO IGY A TIPUS AZ FIX
    type = 1;
    train_number = a_train_number;
    carriage_number = a_carriage_number;
    place = a_place;
    start_place = a_start_place;
    start_time = a_start_time;
    arrival_place = a_arrival_place;
    arrival_time = a_arrival_time;
    dining_table = a_dining_table;
    sleeper = a_sleeper;
}

/// KIMENTI A TOVABBI ADATTAGOKAT
void First_Class::save(std::ostream& os) const
{
    Train_Tickets::save(os); /// MEGHIVJA AZ OSOSZTALY MENTO FUGGVENYET
    os<<dining_table<< " "<<sleeper; /// HOZZAADJA A MARADEK ADATTAGOKAT
}

/// KIIRJA A TOVABBI ADATTAGOKAT
void First_Class::print() const{
        Train_Tickets::print(); /// MEGHIVJA AZ OSOSZTALY PRINT FUGGVENYET
        /// KIIRJA A MARADEK ADATTAGOKAT
        std::cout<<"Etkezo: "<<dining_table<< "; Halokocsi: "
                  <<sleeper<<std::endl;
}

/// HALOKOCSI DIJ MEGHATAROZASA
int First_Class::sleeper_fee()const
{
        try{ /// HA AZ ERKEZES KORABBAN VAN AZ INDULASNAL HIBAT DOB
            if(arrival_time < start_time || arrival_time<0 || start_time < 0) throw -1;
        }
        catch (int myNum) /// KIVETEL KEZELESE
        {
            std::cout<<"AZ ERKEZESI IDO KISEBB MINT AZ INDULASI VAGY NEM LETEZNEK AZ IDOPONTOK!"<<std::endl;
        }
        /// HA A FELTETELEK MEGFELELOEK, AKKOR VISSZATER A DIJJAL
        int k = (arrival_time-start_time)/1440;
        return 8000*k;
    }

First_Class & First_Class::operator=(int a) /// A PARAMETERKENT KAPOTT EGESZ VALTOZO PERCBEN VAN MEGADVA
{
    /// EGYENLOVE TESZI AZ INDULASI IDOT A KAPOTT PARAMETERREL
    start_time = a;
    /// EGYENLOVE TESZI AZ ERKEZEI IDOT A KAPOTT PARAMETERREL
    arrival_time = a;
    /// VISSZATER AZ ADATTAL
    return *this;
}

First_Class & First_Class::operator+=(int a) /// A PARAMETERKENT KAPOTT EGESZ VALTOZO PERCBEN VAN MEGADVA
{
    /// MEGNOVELI AZ INDULASI IDOT A PARAMETERREL
    start_time += a;
    /// MEGNOVELI AZ ERKEZESI IDOT A PARAMETERREL
    arrival_time += a;
    /// VISSZATER A MEGVALTOZTATOTT ADATTAL
    return *this;
}

First_Class & First_Class::operator-=(int a) /// A PARAMETERKENT KAPOTT EGESZ VALTOZO PERCBEN VAN MEGADVA
{
    /// CSOKKENTI AZ INDULASI IDOT A PARAMETERREL
    start_time -= a;
    /// CSOKKENTI AZ ERKEZESI IDOT A PARAMETERREL
    arrival_time -= a;
    /// VISSZATER A MEGVALTOZTATOTT ADATTAL
    return *this;
}

/// GETTEREK:
int First_Class::get_dining_table()const{return dining_table;}
int First_Class::get_sleeper()const{return sleeper;}

/// SECOND CLASS :

Second_Class::Second_Class(int a_train_number, int a_carriage_number, int a_place, String a_start_place, int a_start_time, String a_arrival_place, int a_arrival_time,bool a_AC,bool a_bufe)
{
    /// BEALLITJA AZ OSSZES ADATTAGOT A PARAMETERKENT KAPOTT ADATOKKAL
    /// MIVEL MASODOSZTALYROL VAN SZO IGY A TIPUS AZ FIX
    type = 2;
    train_number = a_train_number;
    carriage_number = a_carriage_number;
    place = a_place;
    start_place = a_start_place;
    start_time = a_start_time;
    arrival_place = a_arrival_place;
    arrival_time = a_arrival_time;
    AC = a_AC;
    bufe = a_bufe;
}
/// TOVABBI ADATTAGOK MENTESE
void Second_Class::save(std::ostream& os)const
{
    Train_Tickets::save(os); /// MEGHIVJA AZ OSOSZTALY MENT FUGGVENYET
    os<<AC<< " "<<bufe; /// ELMENTI A MARADEK ADATTAGOKAT
}

/// TOVABBI ADATTAGOK KIIRATASA
void Second_Class::print() const {
        Train_Tickets::print(); /// MEGHIVJA AZ OSOSZTALY PRINT FUGGVENYET
        /// KIIRJA A MARADEK ADATTAGOKAT
        std::cout<<"AC: "<< std::boolalpha<<AC<< "; Bufe: "
                  << std::boolalpha<<bufe<<std::endl;;
}

Second_Class & Second_Class::operator=(int a) /// A PARAMETERKENT KAPOTT EGESZ VALTOZO PERCBEN VAN MEGADVA
{
    /// EGYENLOVE TESZI A PARAMETERREL AZ INDULASI IDOT
    start_time = a;
    /// EGYENLOVE TESZI AZ ERKEZESI IDOT A PARAMETERREL
    arrival_time = a;
    /// VISSZATER A MEGVALTOZTATOTT ADATTAL
    return *this;
}

Second_Class & Second_Class::operator+=(int a) /// A PARAMETERKENT KAPOTT EGESZ VALTOZO PERCBEN VAN MEGADVA
{
    /// MEGNOVEL A PARAMETERREL AZ INDULASI IDOT
    start_time += a;
    /// MEGNOVELI AZ ERKEZESI IDOT A KAPOTT PARAMETERREL
    arrival_time += a;
    /// VISSZATER A MEGVALTOZTATOTT ADATTAL
    return *this;
}

Second_Class & Second_Class::operator-=(int a) /// A PARAMETERKENT KAPOTT EGESZ VALTOZO PERCBEN VAN MEGADVA
{
    /// CSOKKENTI AZ INDULASI IDOT A PARAMETERREL
    start_time -= a;
    /// CSOKKENTI AZ ERKEZESI IDOT A PARAMETERREL
    arrival_time -= a;
    /// VISSZATER A MEGVALTOZTATOTT ADATTAL
    return *this;
}

/// AC DIJANAK KISZAMITASA
int Second_Class::AC_fee()const
{
    try{ /// KORABBAN ERKEZIK A JARAT MINT INDULNA AKKOR HIBAT AD
    if(arrival_time < start_time || arrival_time<0 || start_time < 0) throw -1;
    }
    catch (int myNum) /// KIVETEL KEZELESE
    {
            std::cout<<"AZ ERKEZESI IDO KISEBB MINT AZ INDULASI VAGY NEM LETEZNEK AZ IDOPONTOK!"<<std::endl;
    }
    /// HA MEGVELELO ADATOKAT KAPOTT ES A KLIMA IS BEVAN KAPCSOLVA AKKOR VISSZATER A DIJAVAL
    /// HA A KLIMA KI VAN KAPCSOLVA AKKOR AZ ARA 0 FT
    int k = arrival_time-start_time;
    if(AC) return 1600*k;
    else return 0;
}

/// GETTEREK:
bool Second_Class::get_AC()const{return AC;}
bool Second_Class::get_bufe()const{return bufe;}
