#ifndef MSTRING_H
#define MSTRING_H

#include "etc.h"

#include "string.h"

class mString
{
    char* sPtr;//указатель на строку
    unsigned int sLength;//длина строки
public:
    mString();
    mString(char *src);
    mString(const mString &src);

    virtual ~mString();

    void printType(char *out=nullptr);
    virtual void printVType(char *out=nullptr);

    // Перегрузка оператора присваивания
    mString& operator = (const mString &src);
    mString(char src);
    unsigned int getLength();
    void setStr(char *src);
    virtual void setStrV(char *src);
    char* getStr();

};

#endif // MSTRING_H
