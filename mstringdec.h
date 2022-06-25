#ifndef MSTRINGDEC_H
#define MSTRINGDEC_H

#include "mstring.h"

class mStringDec : public mString
{
public:
    mStringDec();

    mStringDec(const mStringDec &src);
    ~mStringDec();
    // Перегрузка оператора присваивания
    mStringDec& operator = (const mStringDec &src);
    mStringDec(char *src);

    void printType(char *out);
    virtual void printVType(char *out);
    virtual void setStrV(char *src);

    mStringDec operator + (mStringDec &rigth);
};

#endif // MSTRINGDEC_H
