#ifndef TICKETS_HPP
#define TICKETS_HPP


#include "stringek.hpp"

#include "memtrace.h"

class Train_Tickets
{
protected:
    int type; /// @param type - megadja a vonatjegy tipusat: elsoosztaly vagy masodosztaly
    int train_number; /// @param train_number - vonat szama
    int carriage_number; /// @param carriage_number - kocsi szama
    int place; /// @param place - ules szama
    String start_place; /// @param start_place - indulas helye
    int start_time; /// @param start_time - indulas ideje
    String arrival_place; /// @param arrival_place - erkezes helye
    int arrival_time; /// @param arrival_time - erkezes ideje
public:

    Train_Tickets();

    Train_Tickets(const Train_Tickets & rhs);

    /// MENTES (A LESZARMAZOTTAK PONTOSITJAK)
    virtual void save(std::ostream&)const;

    /// KIIRATAS (A LESZARMAZOTTAK PONTOSITJAK)
    virtual void print()const;

    virtual ~Train_Tickets(){}

    /// += ; -= OPERATOROK KONSTANSSAL, A MENETREND VALTOZASANAK BEALLITASAHOZ (A LESZARMAZOTTAK PONTOSITJAK)
    virtual Train_Tickets & operator=(int a) = 0;
    virtual Train_Tickets & operator+=(int a) = 0;
    virtual Train_Tickets & operator-=(int a) = 0;

    /// GETTEREK:
    int get_type() const;
    int get_train_number() const;
    int get_carriage_number() const;
    int get_place() const;
    String get_start_place() const;
    int get_start_time() const;
    String get_arrival_place() const;
    int get_arrival_time() const;
};



class First_Class : public Train_Tickets
{
    int dining_table;
    int sleeper;
public:

    First_Class():Train_Tickets(),dining_table(-1),sleeper(-1){}
    First_Class(int,int,int,String,int,String,int,int,int);
    ~First_Class(){}

    First_Class & operator=(int a);
    First_Class & operator+=(int a);
    First_Class & operator-=(int a);

    void save(std::ostream&)const;

    void print()const;

    /// MEGADJA, HOGY VAN-E EBEDLOASZTAL FOGLALVA
    bool isD_t() const{return dining_table > 0;}
    /// MEGADJA, HOGY VAN-E HALOKOCSI FOGLALVA
    bool isSper() const{return sleeper > 0;}

    /// HALOKOCSI DIJA
    int sleeper_fee() const;

    /// GETTEREK:
    int get_dining_table()const;
    int get_sleeper()const;
};



class Second_Class : public Train_Tickets
{
    bool AC;
    bool bufe;
public:

    Second_Class():Train_Tickets(),AC(false),bufe(false){}
    Second_Class(int,int,int,String,int,String,int,bool,bool);
    ~Second_Class(){}

    Second_Class & operator=(int a);
    Second_Class & operator+=(int a);
    Second_Class & operator-=(int a);

    void save(std::ostream&)const;

    void print()const ;

    /// KLIMA DIJA
    int AC_fee()const;

    /// GETTEREK:
    bool get_AC()const;
    bool get_bufe()const;
};

#endif // TICKETS_HPP














/*
     Train_Tickets& operator = (int a);
     Train_Tickets& operator = (const Train_Tickets &);
     virtual Train_Tickets& operator = (int a);

     Train_Tickets operator + (const Train_Tickets &);
     Train_Tickets operator + (int);

     Train_Tickets operator - (const Train_Tickets &);
     Train_Tickets operator - (int);
    */
