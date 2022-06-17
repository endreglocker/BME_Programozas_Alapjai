#include <iostream>
#include <cstring>
#include "stringek.hpp"

#include "memtrace.h"

String::String(char c)
{
    /// LETREHOZUNK EGY 1 HOSSZUSAGU SZTRINGET AMIBE BELEMASOLJUK A KARAKTERT
    len=1; /// HOSSZUSAGOT BEALLITJA 1-RE
    pData= new char[len+1]; /// LEFOGLAL A KARAKTERNEK ES A LEZARO 0-NAK HELYET
    pData[0]=c; /// HOZZAADJA A KARAKTERT
    pData[len]='\0'; /// HOZZAADJA A LEZARO 0-AT
}

String::String(char const *ch)
{
    /// LETREHOZUNK EGY UGYANOLYAN HOSSZU SZTRINGET MINT A KARAKTERTOMB MAJD BELEMASOLJUK AZT A SZTRINGBE
    len=strlen(ch); /// BEALLITJA A HOSSZUSAGOT A KAPOTT PARAMETER HOSSZARA
    pData=new char[len+1]; /// LEFOGLALJA A KARAKTERLANC ES A LEZARO 0 HELYET
    strcpy(pData,ch); /// ATMASOLJA AZ ADATOT
}

String::String(const String& rhs)
{
    len=rhs.len; /// ATADJA A PARAMETER HOSSZAT
    pData= new char[len+1]; /// HOSSZ + LEZARO 0 MEMORIA FOGLALASA
    strcpy(pData,rhs.pData); /// BELEMASOLJA AZ ADATOT
}

String& String::operator=(const String& rhs)
{
    /// ELLENORIZZUK HOGY NEM VOLTAK-E EGYENLOK MAJD ATMASOLJUK UGYANUGY MINT A MASOLO KONSTRUKTORNAL
    if(this!=&rhs){
        delete[] pData; /// TOROLJUK A REGI ADATOT
        len=rhs.len; /// ATADJUK AZ UJ MERETET
        pData = new char[len+1]; /// LEFOGLALJUK A HELYET A LEZARO 0-VAL EGYUTT
        strcpy(pData,rhs.pData); /// ATMASOLJUK AZ UJ ADATOT
    }
    return *this;
}

bool String::operator==(const String &rhs)
{
    /// HA NEM EGYFORMA HOSSZUSAGUAK AKKOR TOVABB NEM KELL VELE FOGLALKOZNI
    if(len==rhs.len)
    {
        /// HA EGYENLO NAGYSAGUAK KARAKTERENKENT OSSZEVETJUK
        size_t counter=0; /// @param counter - megmutatja hany karakter azonos ket sztring kozott
        for(size_t i = 0; i < len; i++) /// BEJARJUK A STRINGET
        {
            if(pData[i]==rhs.pData[i]) counter++; /// MINDEN EGYEZES ESETEN NOVELJUK A SZAMLALOT
        }
        /// HA AZ OSSZES KARAKTER AZONOS AKKOR VISSZAKAPJUK A MERET SZAMOSSAGAT TEHAT A KET SZTRING UGYANAZ
        if(counter == len) return true;
    }
    return false;
}

bool String::operator!=(const String &rhs)
{
    /// A NEM EGYENLO OPERATORT MEGKAPHATJUK AZ EGYENLOSEG OPERATOR NEGALASAVAL
    return !(*this == rhs);
}

String String::operator+(const String& rhs) const
{
    /// SZTRINGHEZ SZTRINGET FUZUNK
    /// ATMENETI VALTOZO A KET SZTRING HOSSZ OSSZEGET KAPJA
    /// ELOSZOR BELEMASOLJUK A MUVELET BALOLDALAN LEVOT MAJD A MUVELET JOBBOLDALAN LEVO SZTRINGET
    String temp; /// LETREHOZUNK EGY ATMENETI VALTOZOT
    temp.len=rhs.len+len; /// MEGKAPJA A KET ERTEK HOSSZOSSZEGET
    temp.pData= new char[temp.len+1]; /// LEFOGLALJUK A KELLO MEMORIATERULETET A LEZARO 0-VAL EGYUTT
    strcpy(temp.pData,pData); /// ATMASOLJUK A JOBBERTEKET
    strcat(temp.pData,rhs.pData); /// HOZZAFUZZUK A BALERTEKET
    return temp;
}

char& String::operator[](size_t idx)
{
    /// HIBAS INDEX ESETEN HIBA KEZELESE
    try{ /// HIBAKEZELES
    if(idx>=len){ /// MEGNEZZUK HOGY AZ INDEX A TARTOMANYBA ESIK
        throw -1; /// HA NEM HIBAT DOBUNK
    }

    }
    catch (int myNum){ /// HIBA KEZELESE
        std::cout<< "MERETNEL NAGYOBB INDEX!";
    }
    return pData[idx]; /// HA NINCS HIBA VISSZATERUNK A KARAKTERREL
}

/// OSTREAMRE KIIRAS
std::ostream& operator<<(std::ostream& out, const String& rhs)
{
    /// ATADJUK AZ ADATOT AZ OUTNAK
    out<<rhs.iras();
    return out;
}

/// OSTREAMROL BEOLVASAS
std::istream& operator>>(std::istream& is, String& s0) {
    unsigned char ch;
    s0 = String("");
	std::ios_base::fmtflags fl = is.flags();
	is.setf(std::ios_base::skipws);
    while (is >> ch) {
	    is.unsetf(std::ios_base::skipws);
        if (isspace(ch)) {
            is.putback(ch);
            break;
        } else {
            s0 = s0 + ch;
        }
    }
	is.setf(fl);
    return is;
}
