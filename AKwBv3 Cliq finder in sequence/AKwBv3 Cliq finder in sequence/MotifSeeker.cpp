#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;



class vector_store          //KLASA + VEKTOR KLASY DLA WCZYTANYCH SEKWENCJI
{
    public:
    string name;
    vector <char> sequence;
    vector <int> value;
    vector <int> position;

    vector_store(string a)  //konstruktor wektora z przypisaniem nazwy sekwencji
    {
        name = a;
    }
    void Vsequence(char s)  //wpisanie sekwencji
    {
        sequence.push_back(s);
    }
    void Vvalue(int v)
    {
        value.push_back(v); //wpisanie wartosci
    }
    void Vposition(int p)
    {
        position.push_back(p);
    }
};
vector <vector_store> vectorss;

class verticle          //KLASA + VEKTOR KLASY DLA WIERZCHOLKOW
{
public:
    verticle(){}
    vector <char> podciag;
    vector <int> adjlist;

    string seq_name;
    int seq_num;
    int podc_num;
    int id;

    void Vpodciag(char p)       //SPISANIE SEQ. PODCIAGU DO VEKTORA
    {
        podciag.push_back(p);
    }
    void Vseq_num(int n)    //PRZYPISANIE Z KTOREJ SEKWENCJI POCHODZI PODCIAG
    {
        seq_num = n;
    }
    void Vpodc_num(int u)   //PRZYPISANIE POZYCJI PIERWSZEGO NT W PODCIAGU
    {
        podc_num = u;
    }
    void aadjlist(int l)        //DODANIE DO LISTY NASTEPNIKOW DLA DANEGO WIERZCHOLKA
    {
        adjlist.push_back(l);
    }
    void ad_id(int d)       //NUMER WIERZCHOLKA
    {
        id = d;
    }
    void Vseq_name(string seq)
    {
        seq_name = seq;
    }

};
vector <verticle> verticless;

class cliquee
{
    public:
    cliquee(){}
    vector <char> cliq_seq; //zapamietanie sekwencji kliki
    vector <int> cliq_num; //zapamietanie elementow kliki (nr. wierzcholkow nalezacych do kliki)
    int c_id;               //zapamietanie id/numeru kliki
    vector <int> c_podc_num; //zapamietanie nr podciagu elementu z kliki
    vector <string> c_seq_name;     //nazwy sekwencji z ktorych pochodza elementy kliki

    void Cseq(char c)
    {
        cliq_seq.push_back(c);
    }
    void Cnum(int n)
    {
        cliq_num.push_back(n);
    }
    void C_id(int id)
    {
        c_id = id;
    }
    void Cp_num(int cp)        //wepchniecie nr podciagu z sekwencji oryginalnej
    {
        c_podc_num.push_back(cp);
    }
    void Cs_name(string cs)         //wepchniecie nazwy sekwencji z jakiej pochodzi podc
    {
        c_seq_name.push_back(cs);
    }
};
vector <cliquee> Cliq;

void read(string fasta,string qual)
{
   fstream file;
   string f1 = fasta + ".txt";
   string f2 = qual + ".txt";
                    //WCZYTYWANIE PIERWSZEGO PLIKU
   file.open(f1, ios::in); // otwarcie pliku

   if(file.good() == false)
   {
       cout << "Brak pliku do odczytu." << endl;
   }

    string line; //do pobrania lini i sprawdzenia czy rozpozczyna sie od " > "
    char nt; //wczytanie nukelotydow jeden po drugim do vektora


   while(file.good()== true)    //jesli plik otwarty
   {
       int p = 1; //pozycja nukleotydu

        getline(file, line);    //bierze pierwsza linie
        vector_store *temp = new vector_store(line);    //allokuje pamiec, tworzy nowy wektor,

        file >> nt;                                     //odczytuje znak po znaku plik,
        if(nt == ';'){file.close(); break; cout << "Wczytano plik fasta." << endl;}

            while(nt != '>')                              //jesli pierwszy znak w linii jest != od < to rozpoczyna sie wczytywanie sekwencji
            {   temp->Vsequence(nt);                       //wyslanie odczytanego nt. do vektora
                temp->Vposition(p);
                p++;
                file >> nt;                                 //odczytanie kolejnego nt
                 if(nt == '>' || nt == ';')                 //jesli odczytany "nt" to > lub ; wtedy break;
                {
                    break;
                }

            }

        vectorss.push_back(*temp);                          //przeslanie utworzonego wektora do magazynu vektorow

        if(nt == ';')
        {
            file.close();
        }
    }


                //WCZYTYWANIE DRUGIEGO PLIKU

    fstream file2;
    file2.open(f2,ios::in);

    int i = 0;  //do wczytania sekwencji do odpowiedniego vektora
    int val;    //do zczytania wartoœci int z pliku tekstowego

    if(file2.good() == false)
    {
        cout << "Brak pliku do odczytu" << endl;
    }


    while(file2.good() == true) //odpala sie petla
    {
        getline(file2, line);       //bierze pierwsza linie z pliku tekstowego

        file2 >> val;          //zaczyna odczytywac znak po znaku to co zapisane jest w drugiej linii pliku tekstowego

        while(val != 0)         //startuje petla wpisujaca/zczytujaca wartosci z pliku tekstowego do momentu napotkania '0'
        {

            vectorss[i].Vvalue(val);    //wpisanie odczytanej wartosci do vektora value dla odpowiedniego g³ównego vektora,
            file2 >> val;               //odczytanie kolejnej wartosci
            if(val == 0)    //jesli natrafi na '0' czyli koniec zapisu wartoscie, wtedy break i zwieksza i aby zaczac wpisywac do kolejnego wektora
            {
                i++;
                break;
            }

        }
        if( val == ';') //jesli natrafimy na znak ';' zamykamy plik, konzczymy petle odczytujaca
        {
            file2.close();
        }
        getline(file2, line); // bez tego getline program nie pobiera wartoœci dla sekwencji 0>, nie wiem czemu no ale niech bedzie

    }


    for(int i = 1; i < vectorss.size(); i++)    //DODANIE NA POCZATKU NAZWY SEKWENCJI '>'
    {
        vectorss[i].name = ">"+vectorss[i].name;

    }


   return;
}

void modyfy_sequence(int modyfy)
{


for(int i = 0; i < vectorss.size(); i++)
{
    for(int j = 0; j < vectorss[i].value.size(); j++)
    {
        if(vectorss[i].value[j] < modyfy)
        {
            vectorss[i].value.erase(vectorss[i].value.begin() + j);
            vectorss[i].sequence.erase(vectorss[i].sequence.begin() + j);
            vectorss[i].position.erase(vectorss[i].position.begin() +j);
           j = 0;           //JESLI ZNALEZIONA ZOSTALA WARTOSC MNIEJSZA NIZ TA PODANA PRZEZ UZYTKOWNIKA TO ZERUJEMY 'j' I SPRAWDZAMY OD NOWA
        }
    }
}

    return;
}

void creat_vert(int podc)
{
    int id = 0;
for(int i = 0; i < vectorss.size(); i++)
{
    for(int j = 0; j < vectorss[i].sequence.size()-podc; j++) // -podc poniewa¿ nie utworzymy odpowiedniego podciagu bedac na koncówce sekwencji
    {
        verticle *temp = new verticle;


        for(int k = 0; k < podc; k++)
        {
            temp->Vpodciag(vectorss[i].sequence[j+k]);    //SPISANIE PODCIAGU DO VEKTORA

        }
        temp->Vseq_num(i);                           //PRZYPISANIE Z KTOREJ SEKWENCJI POCHODZI PODCIAG
        temp->Vpodc_num(vectorss[i].position[j]);    //PRZYPISANIE POZYCJI PIERWSZEGO NT W PODCIAGU
        temp->ad_id(id);                            //PRZYPISANIE ID WIERZCHOLKA (TAK W RAZIE CZEGO)
        temp->Vseq_name(vectorss[i].name);         //PRZYPISANIE NAZWY SEKWENCJI Z KTOREJ POCHODZI WIERZCHOLEK

        verticless.push_back(*temp);
        id++;
    }
}

return;
}

void creat_graph()
{
    int V = verticless.size();

    for(int i = 0; i < verticless.size(); i++)  // PETLA DO WZIECIA PIERWSZEGO WIERZCHOLKA
    {

        for(int j = 0; j < verticless.size(); j++)  //PETLA DO WZIECIA DRUGIEGO WIERZCHOLKA
        {
            int N = 0;                              //ZMIENNA DO ZLICZENIA ILOSCI NIEDOPASOWAN

            if(i != j)                               //WARUNEK ABY NIE POROWNYWAC ZE SOBA TYCH SAMYCH WIERZCHOLKOW
            {
                for(int k = 0; k < verticless[i].podciag.size(); k++)   //PETLA DO POROWNYWANIA nt. W SEKWENCJI PODCIAGU
                {
                    if(verticless[i].podciag[k] == verticless[j].podciag[k])    //JESLI nt  W PODCIAGU NIE SA TAKIE SAME TO INKREMENTUJE ZMIENNA
                    {
                        N++;

                    }
                }
                if(N == verticless[i].podciag.size() )      //JESLI PO SPRAWDZENIU NIE WYSTEPUJA NIEDOPASOWANE nt.  to tworzy polaczenie miedzy wierzcholkami w grafie
                {

                   verticless[i].aadjlist(j);

                }
            }
        }
    }
/*
    for(int i = 0; i < V; i++)          //sprawdzenie listy sadziedztwa
    {

        for(int j = 0; j < verticless[i].adjlist.size(); j++)
        {
            cout << verticless[i].id << "---->" <<verticless[i].adjlist[j] << "  :: seq num:   " << verticless[verticless[i].adjlist[j]].seq_num << " " ;
        }
        cout << "" << endl;
    }

*/

    return;
}

void clique()
{
    bool sequences[5];
    bool fine = true;
    int id = 1;

    for(int i = 0; i < verticless.size(); i++)
    {
        cliquee *temp = new cliquee;

        for(int b = 0; b < 5; b++)
        {
            sequences[b] = false;
        }

        if(verticless[i].adjlist.size() >= 4)   //jesli lista nastepnikow sprawdzanego wierzcholka jest wieksza || rowna od 4 bo wtedy mamy sanse na wystapienie podciagow ze wszystkich sekwencji
        {
            for(int j = 0; j < verticless[i].adjlist.size(); j++)   //adlist.size()+1 bo chce sprawdzic wierzcholek + jego nastepniki
            {
                if(verticless[i].seq_num == 0 )             //warunki do sprawdzenia czy nastepniki pochodza z roznych sekwencji
                {
                    sequences[0] = true;
                }
                if(verticless[verticless[i].adjlist[j]].seq_num == 1)
                {
                    sequences[1] = true;
                }
                if(verticless[verticless[i].adjlist[j]].seq_num == 2)
                {
                    sequences[2] = true;
                }
                if(verticless[verticless[i].adjlist[j]].seq_num == 3)
                {
                    sequences[3] = true;
                }
                if(verticless[verticless[i].adjlist[j]].seq_num == 4)
                {
                    sequences[4] = true;
                }
            }

            for(int k = 0; k < 5; k++)          //sprawdzenie tablicy czy znaleziono podciagi ze wszystkich sekq
            {
                if(sequences[k] == false)
                {
                    fine = false;
                }

            }
            if(fine == true)
            {
                temp->cliq_seq = verticless[i].podciag;     //przekopiowanie sekwencji podciaqu do kliki
                temp->Cnum(verticless[i].id);               //wpisanie pierwszego elementu kliki

                temp->C_id(id);                             //nadanie id. klice
                id++;
                for(int g = 0; g < verticless[i].adjlist.size(); g++)   //wpisanie pozostalych elementow kliki
                {
                    temp->Cnum(verticless[i].adjlist[g]);
                }

                Cliq.push_back(*temp);              //wrzucenie kliki do vektora klik
            }


        }

    }
    //ODDZIELNE PETLE OD TEJ WYSZUKUJACEJ KLIKE
    for(int i = 0; i < Cliq.size(); i++)            //wpisanie do kliki informacji o nr. sekwencji i nr. podciagow
    {
        for(int j = 0; j < Cliq[i].cliq_num.size() ; j++)
        {
            for(int k = 0; k < verticless.size(); k++)
            {
                if(Cliq[i].cliq_num[j] == verticless[k].id) //jesli elementowi tworzocemu klike odpowiada id wierzcholka
                {
                    Cliq[i].Cs_name(verticless[k].seq_name);  //wpisanie do vektora nr. sekwencji z ktorej pochodzi podciag, ktory jest elementem kliki
                    Cliq[i].Cp_num(verticless[k].podc_num); //wpisanie do vektora nr. podciagu wierzcholka nalerzacego do kliki
                }
            }
        }
    }


    return;
}

int main()
{
    int modyfy; //wartosc wiarygodnosci do usuniecia nukleotydow
    int podc;   //jaka dlugosc ma miec tworzony podciag
    int C_lenght_Max = 0; //zmienna do zapamietania dlogosci najdluzszej kliki
    int C_lenght_Min = 0; //zapamietanie najmniejszej dlugosci
    string file1;
    string file2;


    cout << "Podaj nazwe pliku fastq do odczytu: ";
    cin >> file1;
    cout << "Podaj nazwe pliku qual do odczytu: ";
    cin >> file2;

    read(file1, file2);
    cout << "Podaj wartosc wiarygodnosci: " << endl;
    cin >> modyfy;
    modyfy_sequence(modyfy);

    cout << "Podaj dlugosc podciagow w zakresie od 4 do 9: " << endl;
    cin >> podc;
    while(podc < 4 || podc > 9)
    {
        cout << "Podana wartosc jest nieprawidlowa. Podaj wartosc podciagow w zakresie od 4 do 9." << endl;
        cin >> podc;
    }
    creat_vert(podc);
    creat_graph();
    clique();

    //WYSWIETLENIE POWSTALYCH KLIK, CHCE WYSWIETLAC TYLKO TE NAJWIEKSZE
    for(int i = 0; i < Cliq.size(); i++)
    {
        if(Cliq[i].cliq_num.size() > C_lenght_Max)
        {
            C_lenght_Max = Cliq[i].cliq_num.size();
        }
    }
    cout << "Ilosc znalezionych klik: " << Cliq.size() << endl;
     for(int i = 0; i < Cliq.size(); i++)
    {

            cout << "Klika nr: " << Cliq[i].c_id << endl;
            cout << "--------------" << endl;
            cout << "Sekwencja kliki" << endl;
            cout << "--------------" << endl;
            for(int j = 0; j < Cliq[i].cliq_seq.size(); j++)
            {
                cout << Cliq[i].cliq_seq[j] << " " ;
            }
            cout << "" << endl;
            cout << "--------------" << endl;
            cout << "Elementy kliki:" << endl ;
            for(int k = 0; k < Cliq[i].cliq_num.size(); k++)
            {
                cout << "--------------" << endl;
                cout << "Nazwa sekwencji: " << Cliq[i].c_seq_name[k] << " |Numer podciagu z sekwencji oryginalnej: " << Cliq[i].c_podc_num[k] << endl;

            }
            cout << "--------------" << endl;
            cout << ""<<endl;

    }



    return 0;
}
