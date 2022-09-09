#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <chrono>
using namespace std;

class element
{
    public:
    element(int n)
    {
        number = n;
    }
    int number;         //jaka to liczba/wartosc ze zbioru
    bool used = false;  //czy element uzyty czy nie

};
vector <element> digest;
vector <int> mapa;
vector <int> check;

int maxind;

void read(string name)  //done
{
    string open = name + ".txt";
    int number;

    fstream file;
    file.open(open,ios::in);

    if(file.good() == false) {cout << "Brak pliku do odczytu" << endl;}
    else
    {
        while(file.good())
        {
            file >> number;
            element *temp = new element(number);

            digest.push_back(*temp);
        }
        file.close();

    }

}

// SPRAWDZENIE CZY ILOSC ELEMENTOW W ZBIORZE JEST POPRAWNA

int checkSeq()    //done
{

    int zbior = digest.size();    //zmienna do zapamietania ilosci elementow w zbiorze,

    //OBLICZENIA DO SPRAWDZENIA

    int temp = zbior * 2;
    int digest_numb;

    for(int i = 0; i < digest.size(); i++)
    {
        if((i+1)*i == temp)
        {
            digest_numb = i-1;

            return digest_numb;
        }
    }

    return 0;
}


void pokazuzyte()
{
    for(int i = 0; i < digest.size(); i++)
    {
        cout << digest[i].number << " :: " << digest[i].used << " | " ;
    }
    cout << endl;
}
void PartialDigest(int ind,int *jest)
{
    bool match = false;


    for(int i = 0; i < digest.size(); i++)  // wyzerowanie uzytych elementow
    {
        digest[i].used = false;
    }

    for(int i = 0; i < ind; i++)    //sprawdzenie czy sumy poszczegolnych elementow mapy sa obecne w zbiorze
    {   int sum = 0;
        for(int j = i; j < ind; j++)
        {   sum += check[j];
            for(int k = 0; k < digest.size(); k++)
            {
                if(sum == digest[k].number && digest[k].used== false)
                {
                    digest[k].used = true;
                    break;
                }
            }
        }
    }
        bool found = true;
        for(int i = 0; i < digest.size(); i++)
        {
            if(digest[i].used == false)
            {
                found = false;
                break;
            }
        }

    if(ind == maxind && found == true)
    {
            for(int i = 0; i < check.size(); i++)
            {
                mapa.push_back(check[i]);
            }
            *jest = 1;
    }
    else
    {

        for(int i = 0; i < digest.size(); i++)
        {   bool mam;
            if(digest[i].used == false)
            {
                check[ind] = digest[i].number;       //dodanie nowej wartosci
                for(int j = 0; j <= ind; j++)
                {
                    int suma = 0;
                    for(int k = j; k<=ind; k++)
                    {
                        suma+=check[k];
                        mam = false;            //sprawdzenie czy takie wartosci wystepuja w zbiorze

                        for(int p = 0; p < digest.size(); p++)
                        {
                            if(suma == digest[p].number)
                            {   mam = true;

                                break;
                            }
                        }
                        if(mam == false)            //jesli nie wystapila taka wartosc to zerujemy miejsce i przerywamy petle
                        {
                            check[ind] = 0;
                            match = false;
                            break;
                        }
                        else            //jesli znaleziono wartosci to oznaczamy match na true
                        {
                            match = true;
                        }

                    }
                    if(match == false) {break;}     //jesli raz nieznaleziono wartosic pasujacej to przerywamy petle i bierzemy nowy element

                }

                if(match == true)       //jesli po wszystkich przejsciach petli sprawdzajacej mamy pasujace wartosci to wywolujemy funckje
                {
                    PartialDigest(ind+1, jest);

                }

            }
            if(*jest == 1)
            {
                break;
            }
        }

    }


}
int main()
{
    string name;
    cout << "Podaj nazwe pliku do odczytu: ";
    cin >> name;
    read(name);
    int jest = 0;
    sort(digest.begin( ), digest.end( ), [](const auto& lhs, const auto& rhs)
         {
             return lhs.number < rhs.number;
         });

    int dig = checkSeq() + 1;
    maxind = dig;
    if(checkSeq() == 0)
    {
        cout << "Niepoprawna ilosc elementow w multiziobrze" << endl;
    }
    else{
        auto begin = std::chrono::high_resolution_clock::now(); //rozpoczecie liczenia czasu

        for(int i = 0; i < dig; i++)    //zrobienie mapy na zasadzie wrzucenia zer
        {
        check.push_back(0);
        }


        int first = digest[digest.size()-1].number - digest[digest.size()-2].number;  //okreslenie pierwsze elementu, odejmowany jest najwiekszy element od najmniejszego przy zalozeniu, ze elementy sa posortowane
        check[0] = first;

        PartialDigest(1, &jest);

        cout <<"----------------"<<endl;
        if(jest == 1)
        {cout << "Ilosc ciec: " << checkSeq() << endl;
        cout <<"----------------"<<endl;
        cout << "Wielkosc mapy: " << maxind << endl;
        cout <<"----------------"<<endl;
        cout << "Mapa restrykcyjna:" << endl;
        cout <<"----------------"<<endl;
        for(int i = 0; i < mapa.size(); i++)
        {
            cout << " | " << mapa[i];
        }
        cout << " | " << endl;
        }
        else if(jest == 0)
        {
            cout << "Mapa nie zostala skonstruowana" << endl;
        }
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    cout <<"----------------"<<endl;
    cout <<"Czas przeszukiwania: " << elapsed.count()*1e-9<< endl;
    cout <<"----------------"<<endl;
    cout <<"Elementy multizbioru"<<endl;
    cout <<"----------------"<<endl;
    for(int i = 0; i<digest.size(); i++)
    {
        cout << digest[i].number << " ";
    }
    cout << endl;
    cout <<"----------------"<<endl;
    }
    return 0;
}
