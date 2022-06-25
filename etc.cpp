#include "etc.h"

int strlenW(const char *src)
{
    int length=0;
    if(src==nullptr)
        return 0;
    for(char *ptr=const_cast<char*>(src);*ptr!='\0';ptr++)
    {
        length++;
        if(*ptr<0)
            ptr++;
    }
    return length;
}
