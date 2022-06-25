#include "mstringdec.h"

mStringDec::mStringDec()
{
#ifdef _OUT_NAME_METHODS_
    std::cout<<"mStringDec::mStringDec()"<<std::endl;
#endif
}

mStringDec::mStringDec(const mStringDec &src): mString(src)
{
#ifdef _OUT_NAME_METHODS_
    std::cout<<"mStringDec::mStringDec(const mStringDec &src)"<<std::endl;
#endif
}

mStringDec::mStringDec(char *src): mString(src)
{
#ifdef _OUT_NAME_METHODS_
    std::cout<<"mStringDec::mStringDec(char *src)"<<std::endl;
#endif
}

mStringDec::~mStringDec()
{
#ifdef _OUT_NAME_METHODS_
    std::cout<<"mStringDec::~mStringDec()"<<std::endl;
#endif
}

// Перегрузка оператора присваивания
mStringDec& mStringDec::operator = (const mStringDec &src)
{
#ifdef _OUT_NAME_METHODS_
    std::cout<<"mStringDec::operator ="<<std::endl;
#endif
    mStringDec &ptrSrc = const_cast<mStringDec&>(src);

    this->setStr(ptrSrc.getStr());

    return *this;
}

void mStringDec::printType(char *out)
{
#ifdef _OUT_NAME_METHODS_
    std::cout<<"mStringDec::printType()"<<std::endl;
#endif
#ifdef _CONSOLE_OUTPUT_
    std::cout<<"mStringDec class"<<std::endl;
#endif
    strcat(out,"mStringDec class");
}

void mStringDec::printVType(char *out)
{
#ifdef _OUT_NAME_METHODS_
    std::cout<<"mStringDec::printVType()"<<std::endl;
#endif
#ifdef _CONSOLE_OUTPUT_
    std::cout<<"mStringDec class"<<std::endl;
#endif
    strcat(out,"mStringDec class");
}

void mStringDec::setStrV(char *src)
{
#ifdef _OUT_NAME_METHODS_
    std::cout<<"mString::setStr()"<<std::endl;
#endif
    int tmp_i;
    char tmpS[128];
    char *ptrC;
    bool ok=true;
    int isPositive=1;
    if(src[0]=='+')
        src++;
    if(src[0]=='-')
    {
        src++;
        isPositive=-1;
    }
    for(ptrC=src;*ptrC!='\0';ptrC++)
    {
        if(*ptrC<'0'&&*ptrC>'9')
        {
            ok=false;
            break;
        }
    }
    if(ok)
    {
        tmp_i=atoi(src);
        itoa(tmp_i*isPositive,tmpS,10);
    }
    else
    {
        strcpy(tmpS,"0");
    }
    mString *ptrParent=static_cast<mString*>(this);
    ptrParent->setStr(tmpS);
}

mStringDec mStringDec::operator + (mStringDec &rigth)
{
    int leftArg = atoi(this->getStr());
    int rigthArg = atoi(rigth.getStr());
    char buff[128];
    itoa(leftArg+rigthArg,buff,10);

    return mStringDec(buff);
}
