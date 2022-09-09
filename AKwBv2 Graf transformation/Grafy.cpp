#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>


using namespace std;


void show_graph(int Gsize, int* Gnext, int** Gvert) //done
{
   for(int i = 0; i < Gsize; i++)
   {
        for(int j = 1; j < Gnext[i]; j++)
        {
            if(Gvert[i][j] == 0)
            {
            cout << "Wierzcholek: " << Gvert[i][0] << " nie posiada nastepnika." << endl;
                break;
            }

        cout << "Wierzcholek: " << Gvert[i][0] << " --> " << Gvert[i][j] << " Nastepnik " << endl; //na pozycji [i][0] - ZAWSZE jest naszego wierzcholka
        }
   }


    return;
}

bool is_adjoin(int Gsize, int* Gnext, int** Gvert)       //done
{

    for(int i = 0; i < Gsize; i++)      //wierzcholek brany do sprawdzenia
    {
        for(int j = 0; j < Gsize; j++)     //bierzemy drugi wierzcholek
        {

            if( i!=j)
            {

                if(Gnext[i] == Gnext[j] && Gvert[i][1] == Gvert[j][1])  // jesli ta sama dlugosc i te same pierwsze nastepniki
                {
                    for(int k = 1; k < Gnext[i]; k++)
                    {
                        if(Gvert[i][k]!=Gvert[j][k])    //jesli znajdziemy jakikolwiek różny nastepnik to graf nie jest sprzezony
                        {
                            return 0;
                        }
                    }
                }
                if(Gnext[i] == Gnext[j] && Gvert[i][1] != Gvert[j][1])  // jesli ta sama dlugosc i rozne pierwsze nastepniki
                {
                    for(int k = 1; k < Gnext[i]; k++)
                    {
                        for(int n = 1; n < Gnext[j]; n++)
                        {
                            if(Gvert[i][k] == Gvert[j][n])    //jesli znajdziemy jakikolwiek taki sam nastepnik to graf nie jest sprzezony
                            {

                                return 0;
                            }
                        }
                    }
                }
                if(Gnext[i] != Gnext[j])    //jesli rozna dlugosc
                {
                    for(int l = 1; l < Gnext[i]; l++)
                    {
                        for(int m = 1; m < Gnext[j]; m++)
                        {
                            if(Gvert[i][l]==Gvert[j][m])    //jesli znajdziemy taki sam nastepnik w parze o roznej dlugosci to nie jest sprz
                            {
                                return 0;
                            }
                        }
                    }
                }


            }

        }

    }
        return 1;

}


void is_linear(int Gsize, int* Gnext, int** Gvert)  //done
{

    int** rev_graph = new int*[Gsize];    //tablica poprzednikow
    int* rev_next = new int[Gsize]; //tablica do przechowania ilosci poprzednikow danego wierzcholka,

        for(int v = 0; v < Gsize; v++)  //PRZESZUKIWANIE ILE POPRZEDNIKOW BEDZIE MIAL JAKI WIERZCHOLEK
        {
            int c_rev = 0;  // zmienna do zliczania ilosci szukanych wierzcholkow,

            for(int r = 0; r < Gsize; r++)
            {
            for(int x = 1; x < Gnext[r]; x++)   // zaczynamy od 1 aby nie zliczac wierzcholkow
            {
                if( Gvert[v][0] == Gvert[r][x])  //porownywanie czy na ktoryms miejscu jest nasz wierzcholek z Gvert[r][0]
                {

                    c_rev++; //liczenie ile razy wystapil nasz wierzcholek,
                }
            }
            }
            if(c_rev == 0)
            {
                c_rev = 1;
            }

            rev_graph[v] = new int[c_rev]; //allokacja odpowiedniej ilosci pamieci dla poprzednikow
            rev_next[v] = c_rev;
        }

        //WPISYWANIE WIERZCHOLKOW DO TABLICY PORZEDNIKOW
        int r = 1;
        for(int h = 0; h < Gsize; h++)
        {
            rev_graph[h][0] = r;
            r++;
        }
        //SZUKANIE POPRZEDNIKOW
        int see = 1;
        for(int q = 0; q < Gsize;q++)
        {
            int found = 1; //sprawdzenie czy jakis wierzcholek wystepuje jako poprzednik //zmienna do okreslenia miejsca dla kolejnego poprzednika
            for(int w = 0; w < Gsize; w++)
            {
                for(int e = 0; e < Gnext[w]; e++)
                {
                    if(see == Gvert[w][e+1])        //TWORZENIE TABLICY POPRZEDNIKOW
                    {
                        rev_graph[q][found] = Gvert[w][0];
                          found++; // inkrementacja po znalezieniu poprzednika danego wierzcholka,
                    }
                }

            }
            see++;
        }

    //SPRAWDZANIE LINIOWOSCI, JESLI JEDNA PARA POPRZEDNIKOW JEST ROWNA TZN. ZE GRAF JEST NIELINIOWY
        for(int g = 0; g < Gsize; g++)
        {
            for(int w = 1; w < Gsize; w++)
            {
                int licz1 = 0;
                for(int d = 1; d < Gnext[w]; d++)
                {
                        if((Gvert[g][d] == Gvert[w][d]) && (g!=w) && (w!=g))
                        {

                            for(int q = 1; q < Gnext[g]; q++)
                            {   if((rev_graph[g][q] == 0) && (rev_graph[g][q] == 0)){break;} //wyjscie z porownania gdy brak krawedzi w danej porownywanej parze wierzcholkow
                                if((rev_graph[g][q] == rev_graph[w][q]) && (g!=w))
                                {

                                    cout << "Graf nie jest grafem liniowym." << endl;
                                    return;
                                }
                            }
                        }

                }
            }

        }


    cout << "Graf jest grafem liniowy" << endl;
  return;
}

void save(int OrySize,int *Orynext,int **Oryver, string file)
{
    string name = file + "_oryginal.txt";
    fstream fh_out;

    fh_out.open(name, ios::out);
    fh_out << OrySize << endl;
    for(int i = 0; i < OrySize; i++)
    {
        for(int j = 0; j < Orynext[i]; j++)
        {
            fh_out << Oryver[i][j] << " ";
        }
        fh_out << ";" << endl;
    }

    cout << "Graf oryginalny zapisany do pliku: " << name << endl;
}

void transform_graph(int Gsize, int* Gnext, int** Gvert, string file)    //done
{
        string save_name = file;
        int* pomocna[Gsize]; //TABLICA DO WPISYWANIA POLACZEN W GRAFIE ORYGINALNYM
        int x = 1;
        for(int i= 0; i < Gsize; i++)
        {   pomocna[i] = new int[3];

            pomocna[i][0] = x;
            pomocna[i][1] = 0;
            pomocna[i][2] = 0;
            x++;
        }
        pomocna[0][1] = 1;      //Pierwszy wierzcholek w grafie oryginalnym jest "nieznany" wiec przypisuje mu wartosci 1----2 (luk rozlaczny)
        pomocna[0][2] = 2;



int  n =3;

for(int a = 0; a < Gsize; a++)
{
    for(int k = 0; k < Gsize; k++)
    {
        for(int w = 1; w < Gnext[a]; w++)
        {

            if(Gvert[a][w] == Gvert[k][0] && pomocna[a][2] != 0)      //znalezienie nastepnikow dla a i przypisanie konca a do poczatku k
                                                                    //PRZYPISYWANIE POCZATKOW GDZY ZNANY JEST KONIEC
            {
                pomocna[k][1] = pomocna[a][2];

            }



            for(int u = 0; u < Gsize; u++)      //szukanie nastepnikow dla znalezionego k, PRZYPISYWANIE KONCOW
            {
                if(Gvert[k][w] == Gvert[u][0] && pomocna[k][1] == 0 ) //PRZYPISYWANIE POCZATKU JESLI POCZATEK WIERZCHOLKA == 0
                    {
                    pomocna[k][1] = n;
                    n++;
                    }

                    if(Gvert[k][w] == Gvert[u][0] && pomocna[k][2] == 0)     //PRZYPISYWANIE KONCA JESLI ZNANY JEST POZCZATEK NASTEPNIKA
                    {
                        pomocna[k][2] = pomocna[u][1];

                        if(pomocna[k][2] == 0)
                        {
                            pomocna[k][2] = n;
                            pomocna[u][1] = n;
                            n++;

                        }


                    }

            }

            if(Gvert[k][w] == 0 && pomocna[k][2] == 0)  //przypisywanie nowego 'nastepnika' do wierzcholka bez nastepnikow
                    {
                        if(pomocna[k][1] == 0)
                        {
                            pomocna[k][1] = n;
                            n++;
                        }
                        pomocna[k][2] = n;
                        n++;

                    }


        }
    }
}


//TWORZENIE LISTY GRAFU ORYGINALNEGO
//ZMIENNE DLA GRAFU ORYGINALNEGO
int OrySize = 0; //ile wierzcholkow
int *Orynext;
int **Oryver;

//SORTOWANIE WWIERZCHOLKOW;

int h1[Gsize];
for(int y = 0; y < Gsize; y++)  //wypelnienie tablicy zerami
{
    h1[y] = 0;
}

for(int i = 0; i < Gsize; i ++)
{
    h1[i] = pomocna[i][1];      // przypisanie wszystkich wierzcholkow do tablicy

}

int temp;
for(int j = 0; j < Gsize; j++)
{
    for(int h = j+1; h < Gsize; h++)
    {

      if(h1[j] > h1[h])             //jesli nastepny wierzcholek jest "wyzszy" to zamienia miejscami
      {
          int temp = h1[h];
          h1[h] = h1[j];
          h1[j] = temp;
      }

    }
}

// ALLOKACJA I WPROWADZENIE WIERZCHOLKOW DO LISTY
for(int i = 0; i <Gsize; i++)       //zliczenie ilosci wierzcholkow grafu oryginalnego
{
   if(h1[i] != h1[i+1])
   {
       OrySize++;
   }
}
Orynext = new int[OrySize];
Oryver = new int*[OrySize];

//WPISANIE WIERZCHOLKOW DO LISTY DLA GRAFU ORYGINALNEGO

int vert; // do policzenia ilosci nastepnikow
int next;   // do wpisania nastepnikow na miejsce

int h2[OrySize]; //tablica pomocnicza do wpisania/zliczenia nastepnikow
for(int y = 0; y < OrySize; y++)        //ZAPISANIE POJEDYNCZO WYSTAPIEN WIERZCHOLKOW DLA GRAFU ORYGINALNEGO
{
    h2[y] = 0;
}

int p = 0;
int temp2;
int temp3;

for(int i = 0; i < Gsize; i++)  //przyrownanie czy nastepna zmienna nie jest taka sama jak ta aktualnie majaca byc wpisana
{
    temp2 = h1[i];
    temp3 = h1[i+1];
    if(temp2 != temp3)  //jesli zmienne nie sa rowne to wypisujemy do tablicy
    {
        h2[p] = temp2;
        p++;
    }
}

for(int i = 0; i < OrySize; i++)    //zliczenie ile razy wystapil wierzcholek w tablicy
{
    vert = 1;

    for(int j = 0; j < Gsize; j++)
    {
        if(h2[i] == h1[j])
        {
            vert++;
        }
    }
Orynext[i] = vert;
Oryver[i] = new int[vert];
}

for(int i = 0; i < OrySize; i ++)   //wpisanie do tablicy grafu oryginalnego pojedynczych wystapien wierzcholkow
{
    Oryver[i][0] = h2[i];
}
int temp4;
int temp5;
for(int i = 0; i < OrySize; i++)
{
    next = 1;

    for(int j = 0; j < Gsize; j++)
    {
        if(Oryver[i][0] == pomocna[j][1])
        {
            Oryver[i][next] = pomocna[j][2];        //wpisywanie nastepnikow do listy
            next++;

        }

    }
}

for(int i = 0; i <OrySize; i++)                 //PORZADKOWANIE NASTEPNIKOW W TABLICY
{
    for(int j = Orynext[i]; j > 1; j--)         //segregowanie od konca listy nastepnikow
    {
        if(Orynext[i] > 2)
        {
            temp4 = Oryver[i][j-1];
            temp5 = Oryver[i][j];

            if(temp4 > temp5 && temp4 != 0 && temp5 != 0)
            {
                Oryver[i][j] = temp4;
                Oryver[i][j-1] = temp5;
                j = Orynext[i];         //rozpoczecie segregacji od poczatku do momentu az nie zadziala warunek 27.1.21
            }


        }

    }

}

cout << "Graf ORYGINALNY" << endl;
show_graph(OrySize, Orynext, Oryver);
cout << "-----------------------"<< endl;
if(is_adjoin(OrySize, Orynext, Oryver)==true)
{
    cout << "Graf ORYGINALNY jest SPRZEZONY" << endl;
    cout << "-----------------------" << endl;
    is_linear(OrySize, Orynext, Oryver);
}
else
    cout <<"Graf ORYGINALNY jest NIESPRZERZONY" << endl;

save(OrySize, Orynext, Oryver,save_name);


return;
}


int main()
{
    int Gsize; //iloœæ wierzcho³ków grafu,
    int* Gnext; //tablica do iloœci nastêpnikow dla wierzcholkow,
    int** Gvert; //tablica do zapisania wierzcho³ków i nastêpników
    string name;

    cout << "Podaj nazwe pliku do wczytania: " << endl;
    cin >> name;
    fstream plik;

    string load = name + ".txt";    //do otwarcia pliku

    plik.open(load, ios::in);

    if(plik.good() == false)
    {
        cout << "brak pliku" << endl;

    }

        string wierz;   //pobranie liczby wierzcho³ków
        int V_numb;

        getline(plik, wierz); //pobierz dane z pliku do znaku ; !!! EDIT, nie moze byc do znaku ';' po potem jest problem przy allokacji pamieci,
         V_numb = stoi(wierz); //konwersja stringa na int stoi

        Gsize = V_numb;
        Gvert = new int*[V_numb];
        Gnext = new int[V_numb];

        for(int i = 0; i <V_numb; i++)  //pedtla do uzupelniania tablicy wartosciami z pliku + liczenie nastepnikow i allokacja pamieci
        {
        string licz;
        string check1;
        string check2;

        getline(plik,licz);
        istringstream iss(licz);    // przeksztalcanie do stringa, dzieki czemu moge przejsc i zliczyc el. oddzielone spacja
        istringstream iss2(licz);   // dzieki czemu bede wiedzial ile jest nastepnikow,


        int somsiad = -1;
        while(getline(iss, check1, ' '))    //zliczanie następników
        {
            somsiad++;
        }
        Gvert[i] = new int[somsiad];        //allokacja pamieci dla tablicy przechowujacej ilosc nastepnikow dla danych wierzcholkow

        for(int m = 0; m < somsiad; m++)
        {

            getline(iss2, check2, ' ');
            if(check2 == ";")
            {
                break;
            }
            int som;
            som = stoi(check2);
            if(som == 0)
            {
                som = NULL;
            }
            Gvert[i][m] = som;
        }

        Gnext[i] = somsiad;          // przypisanie liczby nastepnikow dla danego wierzcholka do odpowiedniego miejsca
        }
    bool is = false;


    cout << "Wczytany graf: " << name << endl;
    show_graph(Gsize, Gnext, Gvert);
   cout << "-------------------------------" << endl;
    is = is_adjoin(Gsize, Gnext, Gvert);
    if(is == true)
   {cout << "Sprawdzany graf jest: SPRZEZONY." << endl;}
   else {cout << "Sprawdzany graf jest: NIESPRZEZONY" << endl;}
    cout << "-------------------------------" << endl;
   if(is == true)
   {is_linear(Gsize, Gnext, Gvert);
    cout << "-------------------------------" << endl;
    transform_graph(Gsize, Gnext, Gvert, name);
    }
    cout << "-------------------------------" << endl;

    return 0;
}
