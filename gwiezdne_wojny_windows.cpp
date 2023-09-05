
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <vector>

#define strzalka_lewo 0x25
#define strzalka_prawo 0x27
#define strzalka_dol 0x28
#define strzalka_gora 0x26

using namespace std;
int wspolzednaX, wspolzednaY;
char pole[20][20];
int paliwoX, paliwoY;
int punkty = 0;
char waz = 219;
char zbiornik[25];
int stan_paliwa = 24;
double dystans;

void idzdoxy(int x, int y)
{
    HANDLE hcon;
    COORD dwPos;

    dwPos.X = x;
    dwPos.Y = y;

    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hcon, dwPos);
}
void uzupelnienie()
{
    for(int i=0; i<20; i++)
    {
        for(int j=0; j<20; j++)
        {
            pole[j][i]='p';
        }
    }

    pole[wspolzednaX][wspolzednaY] = 'o';
}
int co_ile = 0;
void klatka()
{
    for(int i=0; i<=20; i++)
    {
        cout<<"--";
    }
    for(int i=0; i<20; i++)
    {
        cout<<endl<<"|";

        for(int j=0; j<20; j++)
        {
            if(pole[j][i]=='p')
                cout<<"  ";
            else if(pole[j][i]=='o')
                cout<<"->";
            else if(pole[j][i]=='j')
                cout<<" $";
            else if(pole[j][i]=='*')
                cout<<" *";
            else if(pole[j][i]=='w')
                cout<<waz<<waz;

        }

        cout<<"|";
    }
    cout<<endl;
    for(int i=0; i<=20; i++)
    {
        cout<<"--";
    }
    cout << endl;

    if(co_ile%8 == 0)
    {
        zbiornik[stan_paliwa] = ' ';
        stan_paliwa--;
    }
    for(int i=0; i<25; i++)
        cout << zbiornik[i];

    cout << "   " << ": ilosc paliwa" << endl;
    cout << "dystans: " << dystans << endl;


}


struct przeciwnik
{
    int X;
    int Y;
};

int ile = 0;
przeciwnik wrogowie[10000];
int czestotliwosc = 10;
bool gra = true;
bool czy1 = false;

string komunikat_o_przegranej;

int main()
{


    while(1)
    {
        dystans = 0;
        komunikat_o_przegranej = " ";
        stan_paliwa=24;
        for(int i=0; i<25; i++)
        {
            zbiornik[i] = waz;
        }
        if(czy1)
        {
            for(int i=0; i<ile; i++)
            {
                pole[wrogowie[i].X][wrogowie[i].Y] = 'p';
                wrogowie[i].X = 0;
            }
            ile = 0;
            czestotliwosc = 10;
            punkty = 0;
        }

        srand(time(NULL));

   ifstream plik("grafika.txt");
   string line;
   while(!plik.eof())
{
	getline(!plik, line);
	cout << line << endl;
}
        system("pause");


        system("cls");


        wspolzednaX = 2;
        wspolzednaY = 5;






        //inicjalizowanie tablicy dwuwymiarowej
        uzupelnienie();

        pole[wspolzednaX][wspolzednaY] = 'o';

        do
        {
            paliwoX=rand()%20;
            paliwoY=rand()%20;
        }
        while(pole[paliwoX][paliwoY]!='p' || paliwoX<3 || paliwoX > 17 && paliwoY<3 || paliwoY>17);

        pole[paliwoX][paliwoY]='j';


        for(;;)
        {
            idzdoxy(0,0);


            //rysowanie areny
            klatka();
            Sleep(30);



            pole[wspolzednaX][wspolzednaY] = 'p';
            if ((GetKeyState(strzalka_dol) & 0x8000))
            {
                wspolzednaY++;
            }
            else if ((GetKeyState(strzalka_gora) & 0x8000))
            {
                wspolzednaY--;

            }
            else if ((GetKeyState(strzalka_prawo) & 0x8000))
            {
                dystans += 2.5;
                wspolzednaX++;

            }
            else if ((GetKeyState(strzalka_lewo) & 0x8000))
            {
                wspolzednaX--;
                dystans += 0.1;

            }

            //uniemozliwienie wyjsca poza teren planszy
            if(wspolzednaX==20)
                wspolzednaX=20-1;
            if(wspolzednaX==-1)
                wspolzednaX=0;
            if(wspolzednaY==-1)
                wspolzednaY=0;
            if(wspolzednaY==20)
                wspolzednaY=20-1;

            if(co_ile%100 == 0 && czestotliwosc > 2 && co_ile > 100)
                czestotliwosc--;

            if(co_ile%czestotliwosc == 0 && co_ile > 100)
            {
                wrogowie[ile].X = 19;
                wrogowie[ile].Y = rand()%18+2;
                pole[wrogowie[ile].X][wrogowie[ile].Y] = '*';
                ile++;
            }


            if(co_ile%2 == 0)
            {
                for(int i=0; i<ile; i++)
                {

                    pole[wrogowie[i].X][wrogowie[i].Y] = 'p';
                    wrogowie[i].X--;
                    pole[wrogowie[i].X][wrogowie[i].Y] = '*';
                    if(wrogowie[i].X == -1)
                        wrogowie[i].X = 0;

                    if(pole[wrogowie[i].X][wrogowie[i].Y] == pole[paliwoX][paliwoY])
                    {
                        do
                        {
                            paliwoX=rand()%15+3;
                            paliwoY=rand()%15+3;
                        }
                        while(pole[paliwoX][paliwoY]!='p' || paliwoX<3 || paliwoX > 17 && paliwoY<3 || paliwoY>17);
					
                        pole[paliwoX][paliwoY]='j';
                    }
                }

            }

            //zdobycie punktu
            if(pole[wspolzednaX][wspolzednaY]=='j')
            {
                do
                {
                    paliwoX=rand()%15+3;
                    paliwoY=rand()%15+3;
                }
                while(pole[paliwoX][paliwoY]!='p' || paliwoX<3 || paliwoX > 17 && paliwoY<3 || paliwoY>17);

                pole[paliwoX][paliwoY]='j';

                if(stan_paliwa<22)
                   stan_paliwa+=2;

                for(int i=0; i<stan_paliwa; i++)
                {
                    zbiornik[i] = waz;
                }
            }

            if(gra == false)
            {
                cout << "error1" << endl;
                system("pause");
                break;
            }

            if(stan_paliwa < 1)
            {
                komunikat_o_przegranej = "PRZEGRANA\nzabraklo ci paliwa w zbiorniku twojej rakiety :(";
                break;
                system("cls");
            }

            if(dystans > 350)
            {
                for(int i=0; i<20; i++)
                {
                    pole[19][i] = 'w';
                }

                idzdoxy(0,0);
                klatka();
                cout << "udalo ci sie wcissnj klawisz ENTER";
                getchar();
                komunikat_o_przegranej = "BRWAO UDALO CI SIE\ndotarles na nie palnete humunokulus espikurus \n jestesmy z ciebie dumni :)";
                break;
                system("cls");
            }
            //zdobycie punktu



            //koniec gry (skucha)

            if(pole[wspolzednaX][wspolzednaY]=='*')
            {
                komunikat_o_przegranej = "PRZEGRANA\nzderzyles sie z lecaca asterioda :(";
                break;
                system("cls");
                system("pause");
            }

            pole[wspolzednaX][wspolzednaY] = 'o';

            co_ile++;

            if(co_ile%2 == 0)
            dystans+=0.25;

        }


        system("cls");


        cout << komunikat_o_przegranej << endl;

        Sleep(2000);
        czy1 = true;


        cout << endl;

        system("pause");

        system("cls");
    }


    return 0;

}

