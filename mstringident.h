#ifndef MSTRINGIDENT_H
#define MSTRINGIDENT_H

#include "mstring.h"

class mStringIdent : public mString
{
public:
    mStringIdent();
    mStringIdent(const mStringIdent &src);
    ~mStringIdent();
    // Перегрузка оператора присваивания
    mStringIdent& operator = (const mStringIdent &src);
    mStringIdent(char *src);

    void printType(char *out);
    virtual void printVType(char *out);
    virtual void setStrV(char *src);
};

#endif // MSTRINGIDENT_H
