#ifndef STRING_H
#define STRING_H

#include <iostream>

#include "memtrace.h"

class String {
    char *pData; /// @param pData - karakterlancot tarolo mutato (string alapja)
    size_t len; /// @param len - string hossza
public:
    /// FELSZABADITJUK A FOGLALT MEMORIATERULETET
    ~String(){delete[] pData; len = 0;}

    /// PARAMETER NELKULI KONSTRUKTOR LETREHOZ EGY NULL POINTERT ES BEALLITJA A MERETET 0-RA
    String() :pData(NULL), len(0) {}

    /// GETTEREK:
    char* get_pData(){return pData;}
    size_t size() const { return len; }
    const char* iras() const { if(pData!=NULL) return pData;else return "";}

    /// KARAKTERBOL SZTRING
    String(char c);

    /// KARAKTERTOMBBOL / LANCBOL SZTRING
    String(char const *ch);

    String(const String& rhs);

    /// OPERATOROK:
    String& operator=(const String &rhs);

    bool operator==(const String &rhs);

    bool operator!=(const String &rhs);

    String operator+(const String& rhs) const ;

    char& operator[](size_t idx);

};

/// OSSZEFUZES: KARAKTER BALERTEKKENT, STRING JOBBERTEKKENT
/// KARAKTERBOL TUDUNK STRINGET KESZITENI
/// STRINGET STRINGGEL OSSZETUDUNK ADNI
inline String operator+(char c,const String& rhs) {return String(c) + rhs;}

///KIIRAS
std::ostream& operator<<(std::ostream& out, const String& rhs);
///BEOLVASAS
std::istream& operator>>(std::istream& is, String& s0);

#endif
