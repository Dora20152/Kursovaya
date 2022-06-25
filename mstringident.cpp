#include "mstringident.h"

mStringIdent::mStringIdent()
{
#ifdef _OUT_NAME_METHODS_
    std::cout<<"mStringIdent::mStringIdent()"<<std::endl;
#endif
}

mStringIdent::mStringIdent(const mStringIdent &src): mString(src)
{
#ifdef _OUT_NAME_METHODS_
    std::cout<<"mStringIdent::mStringIdent(const mStringIdent &src)"<<std::endl;
#endif
}

mStringIdent::mStringIdent(char *src): mString(src)
{
#ifdef _OUT_NAME_METHODS_
    std::cout<<"mStringIdent::mStringIdent(char *src)"<<std::endl;
#endif
}

mStringIdent::~mStringIdent()
{
#ifdef _OUT_NAME_METHODS_
    std::cout<<"mStringIdent::~mStringIdent()"<<std::endl;
#endif
}

// Перегрузка оператора присваивания
mStringIdent& mStringIdent::operator = (const mStringIdent &src)
{
#ifdef _OUT_NAME_METHODS_
    std::cout<<"mStringIdent::operator ="<<std::endl;
#endif
    mStringIdent &ptrSrc = const_cast<mStringIdent&>(src);

    this->setStr(ptrSrc.getStr());

    return *this;
}

void mStringIdent::printType(char *out)
{
#ifdef _OUT_NAME_METHODS_
    std::cout<<"mStringIdent::printType()"<<std::endl;
#endif
#ifdef _CONSOLE_OUTPUT_
    std::cout<<"mStringIdent class"<<std::endl;
#endif
    strcat(out,"mStringIdent class");
}

void mStringIdent::printVType(char *out)
{
#ifdef _OUT_NAME_METHODS_
    std::cout<<"mStringIdent::printVType()"<<std::endl;
#endif
#ifdef _CONSOLE_OUTPUT_
    std::cout<<"mStringIdent class"<<std::endl;
#endif
    strcat(out,"mStringIdent class");
}

void mStringIdent::setStrV(char *src)
{
#ifdef _OUT_NAME_METHODS_
    std::cout<<"mString::setStr()"<<std::endl;
#endif
    char *ptrC;
    bool ok=true;

    if(isalpha(src[0])==0)
        ok=false;
    else
    {
        for(ptrC=src;*ptrC!='\0';ptrC++)
        {
            if((*ptrC<'0'&&*ptrC>'9')||(*ptrC<'a'&&*ptrC>'z')||(*ptrC<'A'&&*ptrC>'Z'))
            {
                ok=false;
                break;
            }
        }
    }
    mString *ptrParent=static_cast<mString*>(this);
    if(ok==true)
        ptrParent->setStr(src);
    else
         ptrParent->setStr("");
}
