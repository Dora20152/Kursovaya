#include <iostream>
#include <locale.h>
#include "mstring.h"
#include "mstringident.h"
#include "mstringdec.h"

#include "SDL2/SDL.h"
#include "stdio.h"
#include "SDL2/SDL_ttf.h"

using namespace std;

#define SDL_MAIN_AVAILABLE

using namespace std;

void outText(TTF_Font *font,SDL_Renderer* renderer,int pos_x,int pos_y,char *outtext)
{
    SDL_Texture* mTexture;
    SDL_Color textColor = {	138 ,43 ,226};
    int mWidth;
    int mHeight;

    SDL_Surface* textSurface=nullptr;

    textSurface = TTF_RenderUTF8_Solid( font, outtext, textColor );
    if( textSurface == nullptr )
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    else
    {
        mTexture = SDL_CreateTextureFromSurface( renderer, textSurface );
        if( mTexture == nullptr )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }
        SDL_FreeSurface( textSurface );
    }

    SDL_Rect pos;
    pos.x = pos_x*1.5;
    pos.y = pos_y*1.5;
    pos.h = FONT_SIZE*2;
    pos.w = strlenW(outtext)*FONT_SIZE;

    SDL_SetRenderTarget(renderer, mTexture);
    SDL_SetRenderDrawColor(renderer, 0,0,0,0);
    SDL_RenderFillRect(renderer,&pos);

    SDL_RenderCopy(renderer, mTexture, NULL, &pos);
    SDL_RenderPresent(renderer);
}

void clearText(SDL_Renderer* renderer,int pos_x,int pos_y,char *outtext)
{
    SDL_Rect pos;
    pos.x = pos_x;
    pos.y = pos_y;
    pos.h = FONT_SIZE;
    pos.w = strlenW(outtext)*FONT_SIZE;

    SDL_SetRenderDrawColor(renderer, 0,0,0,0);
    SDL_RenderFillRect(renderer,&pos);
    SDL_RenderPresent(renderer);
}

void waitEnter()
{
    int done = 0;
    while (!done)
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            if (event.type==SDL_KEYDOWN)
            {
                if(event.key.keysym.scancode  == SDL_SCANCODE_RETURN||event.key.keysym.scancode == SDL_SCANCODE_KP_ENTER)
                {
                    done=1;
                }
            }
        }
    }
}

void inputText(TTF_Font *gFont,SDL_Renderer* renderer,char *text)
{
    int countr=0;
    SDL_StartTextInput();
    int done = 0;
    while (!done)
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            if(event.type == SDL_TEXTINPUT )
            {
                text[countr]= event.text.text[0];
                countr++;
                if(event.text.text[0]<0)
                {
                    text[countr]= event.text.text[1];
                    countr++;
                }
                text[countr]='\0';
                outText(gFont,renderer,10,FONT_SIZE*2,text);
            }
            else if (event.type == SDL_QUIT)
            {
                done=1;
            }
            else if (event.type==SDL_KEYDOWN)
            {
                if(event.key.keysym.scancode  == SDL_SCANCODE_RETURN||event.key.keysym.scancode==SDL_SCANCODE_KP_ENTER)
                {
                    done=1;
                }
                if(event.key.keysym.scancode  == SDL_SCANCODE_BACKSPACE)
                {
                    clearText(renderer,10,FONT_SIZE*2,text);
                    if(countr>0)
                    {
                        if(text[countr-1]<0)
                        {
                            countr--;
                            text[countr]='\0';
                        }
                        countr--;
                        text[countr]='\0';
                    }
                    if(countr!=0)
                        outText(gFont,renderer,10,FONT_SIZE*2,text);
                    else
                        outText(gFont,renderer,10,FONT_SIZE*2," ");
                }
            }
        }
    }
    SDL_StopTextInput();
}

int getIndexElem(TTF_Font *gFont,SDL_Renderer* renderer,int maxElem)
{
    char tmpText[128];
    int elemIndex;
    int type;
    SDL_RenderClear(renderer);
    outText(gFont,renderer,10,FONT_SIZE,"Введите номер элемента массива");

    do
    {
        inputText(gFont,renderer,tmpText);
        elemIndex = atoi(tmpText);
    }
    while(elemIndex<1&&elemIndex>=maxElem);
    return --elemIndex;
}

int outMenu(TTF_Font *gFont,SDL_Renderer* renderer)
{
    char tmpText[128];
    SDL_RenderClear(renderer);
    outText(gFont,renderer,10,FONT_SIZE,  "1. Выбрать тип элемента массива");
    outText(gFont,renderer,10,FONT_SIZE*2,"2. Ввести значение элемента массива");
    outText(gFont,renderer,10,FONT_SIZE*3,"3. Вывести значение элемента массива");
    outText(gFont,renderer,10,FONT_SIZE*4,"4. Вывести тип элемента массива");
    outText(gFont,renderer,10,FONT_SIZE*5,"5. Операции с элементами mStringDec");
    outText(gFont,renderer,10,FONT_SIZE*8,"0. Выход");

    inputText(gFont,nullptr,tmpText);

    return atoi(tmpText);
}

void setTypeElemArray(TTF_Font *gFont,SDL_Renderer* renderer,int maxElem,mString **srcArr)
{
    char tmpText[128];
    int elemIndex;
    int type;

    elemIndex = getIndexElem(gFont,renderer,maxElem);

    SDL_RenderClear(renderer);
    outText(gFont,renderer,10,FONT_SIZE,  "1. Строка");
    outText(gFont,renderer,10,FONT_SIZE*2,"2. Строка-Идентификатор");
    outText(gFont,renderer,10,FONT_SIZE*3,"3. Десятичная строка");
    do
    {
        inputText(gFont,renderer,tmpText);
        type = atoi(tmpText);
    } while(type<0&&type>3);

    switch (type)
    {
        case 1:
            srcArr[elemIndex] = new mString ();
            break;
        case 2:
            srcArr[elemIndex] = new mStringIdent ();
            break;
        case 3:
            srcArr[elemIndex] = new mStringDec ();
            break;
    }
}

void callDecOperator(TTF_Font *gFont,SDL_Renderer* renderer,int maxElem,mString **srcArr)
{
    char tmpText[128];
    int menuIndex;
    int elemIndexLeft;
    int elemIndexRigth;
    int type;

    outText(gFont,renderer,10,FONT_SIZE, "Введите индекс первого операнда");
    elemIndexLeft = getIndexElem(gFont,renderer,maxElem);

    outText(gFont,renderer,10,FONT_SIZE, "Введите индекс второго операнда");
    elemIndexRigth = getIndexElem(gFont,renderer,maxElem);

    SDL_RenderClear(renderer);
    outText(gFont,renderer,10,FONT_SIZE,  "1. mStringDec operator+");
    outText(gFont,renderer,10,FONT_SIZE*3,"0. Выход");

    do
    {
        inputText(gFont,nullptr,tmpText);
        menuIndex = atoi(tmpText);

        if(menuIndex==1)
        {
            SDL_RenderClear(renderer);

            mStringDec *lOperand = dynamic_cast<mStringDec*>(srcArr[elemIndexLeft]);
            mStringDec *rOperand = dynamic_cast<mStringDec*>(srcArr[elemIndexRigth]);
            mStringDec *resultOperand = dynamic_cast<mStringDec*>(srcArr[elemIndexRigth]);

            *resultOperand = *lOperand +  *rOperand;
            outText(gFont,renderer,10,FONT_SIZE,  "Результат записан вместо второго операнда");
            menuIndex=0;
        }
    }
    while(menuIndex!=0);
    waitEnter();
}

void outTypeElemArray(TTF_Font *gFont,SDL_Renderer* renderer,int maxElem,mString **srcArr)
{
    char tmpText[128];
    int menuIndex;
    int elemIndex;

    do
    {
        SDL_RenderClear(renderer);
        outText(gFont,renderer,10,FONT_SIZE  ,"1. Вывести тип конкретного элемента");
        outText(gFont,renderer,10,FONT_SIZE*2,"2. Вывести тип всех элементов");
        outText(gFont,renderer,10,FONT_SIZE*3,"0. Выход");

        inputText(gFont,nullptr,tmpText);
        menuIndex = atoi(tmpText);

        if(menuIndex==1)
        {
            SDL_RenderClear(renderer);
            elemIndex = getIndexElem(gFont,renderer,maxElem);

            if(srcArr[elemIndex]!=nullptr)
            {
                strcpy(tmpText,"");
                srcArr[elemIndex]->printType(tmpText);
                outText(gFont,renderer,10,FONT_SIZE,tmpText);
                strcpy(tmpText,"");
                srcArr[elemIndex]->printVType(tmpText);

                strcpy(tmpText,"");
            }
            else
            {
#ifdef _CONSOLE_OUTPUT_
                printf("empty Elem");
#endif
                outText(gFont,renderer,10,FONT_SIZE,"Пусто");
            }
            SDL_Delay(10000);
            menuIndex=0;
        }

        if(menuIndex==2)
        {
            SDL_RenderClear(renderer);
            for(int i=0;i<maxElem;i++)
            {
                if(srcArr[i]!=nullptr)
                {
                    srcArr[i]->printType(tmpText);
                    outText(gFont,renderer,10,FONT_SIZE+FONT_SIZE*2*i,tmpText);
                    strcpy(tmpText,"");
                    srcArr[i]->printVType(tmpText);
                    outText(gFont,renderer,10,FONT_SIZE+FONT_SIZE*(2*i+1),tmpText);
                    strcpy(tmpText,"");

                }
                else
                {
#ifdef _CONSOLE_OUTPUT_
                    printf("empty Elem\n");
#endif
                    outText(gFont,renderer,10,FONT_SIZE+FONT_SIZE*2*i,"Пусто");
                }

            }
            menuIndex=0;
        }
    }
    while(menuIndex!=0);
    waitEnter();
}

void outValueElemArray(TTF_Font *gFont,SDL_Renderer* renderer,int maxElem,mString **srcArr)
{
    char tmpText[128];
    int menuIndex;
    int elemIndex;

    do
    {
        SDL_RenderClear(renderer);
        outText(gFont,renderer,10,FONT_SIZE  ,"1. Вывести значение конкретного элемента");
        outText(gFont,renderer,10,FONT_SIZE*2,"2. Вывести значение всех элементов");
        outText(gFont,renderer,10,FONT_SIZE*3,"0. Выход");

        inputText(gFont,nullptr,tmpText);
        menuIndex = atoi(tmpText);

        if(menuIndex==1)
        {
            elemIndex = getIndexElem(gFont,renderer,maxElem);

            SDL_RenderClear(renderer);

            if(srcArr[elemIndex]!=nullptr)
            {
                outText(gFont,renderer,10,FONT_SIZE,srcArr[elemIndex]->getStr());
            }
            else
            {
                outText(gFont,renderer,10,FONT_SIZE,"Пусто");
            }
            menuIndex=0;
        }

        if(menuIndex==2)
        {
            SDL_RenderClear(renderer);
            for(int i=0;i<maxElem;i++)
            {
                if(srcArr[i]!=nullptr)
                {
                    outText(gFont,renderer,10,FONT_SIZE+FONT_SIZE*i,srcArr[i]->getStr());
                }
                else
                {
                     outText(gFont,renderer,10,FONT_SIZE+FONT_SIZE*i,"Пусто");
                }
            }
            menuIndex=0;
        }
    }
    while(menuIndex!=0);
    waitEnter();
}

void inputElemArray(TTF_Font *gFont,SDL_Renderer* renderer,int maxElem,mString **srcArr)
{
    char tmpText[128];
    int menuIndex;
    int elemIndex;

    elemIndex = getIndexElem(gFont,renderer,maxElem);

    SDL_RenderClear(renderer);

    outText(gFont,renderer,10,FONT_SIZE,"Введите значение элемента");

    inputText(gFont,renderer,tmpText);

    if(srcArr[elemIndex]!=nullptr)
    {
        srcArr[elemIndex]->setStrV(tmpText);
    }
    else
    {
        printf("Пусто");
    }
    menuIndex=0;
}

int main()
{
    mString **array;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = nullptr;
    SDL_Renderer* renderer = nullptr;
    TTF_Font *gFont = nullptr;
    SDL_Renderer* gRenderer = nullptr;

    char tmpText[128];

    if(TTF_Init()<0)
    {
        printf( "Err load TTF library");
    }


    if (SDL_CreateWindowAndRenderer(640, 480, SDL_WINDOW_RESIZABLE, &window, &renderer))
    {
         printf( "Error create window %s\n", SDL_GetError());
    }

    gFont = TTF_OpenFont( "Robotomono.ttf", 12 );
    if( gFont == nullptr )
    {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
    }

    outText(gFont,renderer,10,FONT_SIZE,"Введите число элементов массива");

    inputText(gFont,renderer,tmpText);

    int countMassElem = atoi(tmpText);

    array = new mString*[countMassElem];
    for (int i=0;i<countMassElem;i++)
    {
        array[i]=nullptr;
    }

    int selectMenu;

    do
    {
        selectMenu = outMenu(gFont,renderer);

        if(selectMenu==1)
            setTypeElemArray(gFont,renderer,countMassElem,array);
        if(selectMenu==2)
            inputElemArray(gFont,renderer,countMassElem,array);
        if(selectMenu==3)
            outValueElemArray(gFont,renderer,countMassElem,array);
        if(selectMenu==4)
            outTypeElemArray(gFont,renderer,countMassElem,array);
        if(selectMenu==5)
            callDecOperator(gFont,renderer,countMassElem,array);
    }
    while(selectMenu!=0);

    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
}
