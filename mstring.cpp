#include "mstring.h"

mString::mString()
{
#ifdef _OUT_NAME_METHODS_
    std::cout<<"mString::mString()"<<std::endl;
#endif
    this->sPtr=nullptr;
    this->sLength=0;
}

mString& mString::operator = (const mString &src)
{
#ifdef _OUT_NAME_METHODS_
    std::cout<<"mString::operator = (mString)"<<std::endl;
#endif
    if (this == &src)
            return *this;

    if(this->sPtr!=nullptr)
        delete[] this->sPtr;
    this->sPtr = new char [src.sLength];
    strcpy(this->sPtr,src.sPtr);
    this->sLength = src.sLength;

    return *this;
}

mString::mString(char *src)
{
#ifdef _OUT_NAME_METHODS_
    std::cout<<"mString::mString(char *src)"<<std::endl;
#endif
    this->sLength = strlen(src)+1;
    this->sPtr = new char[this->sLength];
    strcpy(this->sPtr,src);
}

mString::mString(const mString &src)
{
#ifdef _OUT_NAME_METHODS_
    std::cout<<"mString::mString(const mString &src)"<<std::endl;
#endif
    this->sLength = src.sLength;
    this->sPtr = new char[this->sLength];
    strcpy(this->sPtr,src.sPtr);
}

mString::~mString()
{
#ifdef _OUT_NAME_METHODS_
    std::cout<<"mString::~mString()"<<std::endl;
#endif
    if(this->sPtr!=nullptr)
        delete[] this->sPtr;
    this->sPtr=nullptr;
    this->sLength = 0;
}

void mString::printType(char *out)
{
#ifdef _OUT_NAME_METHODS_
    std::cout<<"mString::printType()"<<std::endl;
#endif
#ifdef _CONSOLE_OUTPUT_
    std::cout<<"mString class"<<std::endl;
#endif
    strcat(out,"mString class");
}

void mString::printVType(char *out)
{
#ifdef _OUT_NAME_METHODS_
    std::cout<<"mString::printVType()"<<std::endl;
#endif
#ifdef _CONSOLE_OUTPUT_
    std::cout<<"mString class"<<std::endl;
#endif
    strcat(out,"mString class");
}

mString::mString(char src)
{
#ifdef _OUT_NAME_METHODS_
    std::cout<<"mString::mString(char src)"<<std::endl;
#endif
    this->sLength = 2;
    this->sPtr = new char[this->sLength];
    this->sPtr[0] =src;
    this->sPtr[1] ='\0';
}

unsigned int mString::getLength()
{
#ifdef _OUT_NAME_METHODS_
    std::cout<<"mString::getLength()"<<std::endl;
#endif
    return this->sLength;
}

void mString::setStr(char *src)
{
#ifdef _OUT_NAME_METHODS_
    std::cout<<"mString::setStr()"<<std::endl;
#endif
    if(this->sPtr!=nullptr)
        delete[] this->sPtr;
    this->sLength = strlen(src)+1;
    this->sPtr = new char[this->sLength];
    strcpy(this->sPtr,src);
}

void mString::setStrV(char *src)
{
#ifdef _OUT_NAME_METHODS_
    std::cout<<"mString::setStr()"<<std::endl;
#endif
    if(this->sPtr!=nullptr)
        delete[] this->sPtr;
    this->sLength = strlen(src)+1;
    this->sPtr = new char[this->sLength];
    strcpy(this->sPtr,src);
}

char* mString::getStr()
{
#ifdef _OUT_NAME_METHODS_
    std::cout<<"mString::getStr()"<<std::endl;
#endif
    return this->sPtr;
}
