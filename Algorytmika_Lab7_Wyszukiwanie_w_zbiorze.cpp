#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
using namespace std;
struct Studenci{
    string imie;
    string nazwisko;
    int punkty;
};
void WyszukiwanieLinniowe(Studenci *student, int szukanawartosc);
void WyszukiwanieBinarne(Studenci *student, int szukanawartosc);
void WczytywanieDanych(Studenci *student);
void quickSortDlaStruktur(Studenci *tablica, int lewy,int prawy, int tryb);
int main() {
    int wybor=-1, wartosc;
    Studenci *tab = new Studenci[20];
    while(wybor!=0){
        cout<<"Podaj z jakej funckji chcesz skorzystac"<<endl;
        cout<<"Wcisnij 1 jesli chcesz wczystać dane z pliku"<<endl;
        cout<<"Wcisnij 2 jesli chcesz wyszukac danych za pomoca algorytmu linniowego"<<endl;
        cout<<"Wcisnij 3 jesli chcesz wyszukac danych za pomoca algorytmu binarnego"<<endl;
        cout<<"Wcisnij 0 jesli chcesz wyjsc z aplikacji"<<endl;
        cout<<"Wybor: ";
        cin>>wybor;
        switch (wybor) {
            case 1: WczytywanieDanych(tab);
                quickSortDlaStruktur(tab,0,14,1);
                cout<<tab[0].imie;break;
            case 2:
                cout<<"Podaj wartosc ktora szukasz: ";
                cin>>wartosc;
                WyszukiwanieLinniowe(tab,wartosc); break;
            case 3:
                cout<<"Podaj wartosc ktora szukasz: ";
                cin>>wartosc;
                WyszukiwanieBinarne(tab,wartosc); break;
            case 0: wybor=0; break;
            default: cout<<"Bledne dane!"; break;
        }
    }
    cout<<"Dziekujemy za skorzystanie z aplikacji!"<<endl;
    return 0;
}
void WyszukiwanieLinniowe(Studenci *student, int szukanawartosc){
    int i=0;
    bool znaleziono= false;
    while(i<14){
        if(student[i].punkty==szukanawartosc){
            cout<<student[i].imie<<" "<<student[i].nazwisko<<" "<<student[i].punkty<<endl;
            znaleziono= true;
        }
        i++;
    }
    if(!znaleziono){
        cout<<"Nie znaleziono zadnego studenta z iloscia punktow rowna: "<<szukanawartosc<<endl;
    }
}
void WyszukiwanieBinarne(Studenci *student, int szukanawartosc){
    int lewy=0;
    ofstream zapis;
    string sciezkaDoZapisu="wyniki.csv";
    zapis.open(sciezkaDoZapisu);
    int prawy=14;
    bool znaleziono= false;
    while(lewy<=prawy){
        int srodek=(int)(lewy+prawy)/2;
        if(student[srodek].punkty==szukanawartosc){
            cout<<student[srodek].imie<<" "<<student[srodek].nazwisko<<" "<<student[srodek].punkty<<endl;
            zapis << student[srodek].imie << ";" << student[srodek].nazwisko << ";"<< student[srodek].punkty<<";"<<" "<<";";
            znaleziono= true;
            student[srodek].punkty=-1;
            continue;
        }
        else{
            if(szukanawartosc<student[srodek].punkty){
                prawy=srodek;
            }
            else{
                lewy=srodek;
            }
        }
        if(prawy-lewy==1){
            break;
        }
    }
    if(!znaleziono){
        cout<<"Nie znaleziono zadnego studenta z iloscia punktow rowna: "<<szukanawartosc<<endl;
    }
    zapis.close();
}
void WczytywanieDanych(Studenci *student){
    string sciezka,linia,pomoc;
    int liczbaStudentow;
    fstream plik;
    plik.open("studenci.csv");
    char sredniki;
    plik >> liczbaStudentow;
    for(int i = 0; i < 2; i++)
        plik >> sredniki;
    for(int i=0; i<liczbaStudentow; i++){
        plik>>linia;
        stringstream ss(linia);
        getline(ss, student[i].imie, ';');
        getline(ss, student[i].nazwisko, ';');
        getline(ss, pomoc);
        student[i].punkty=atoi(pomoc.c_str());
    }
    plik.close();
}
void quickSortDlaStruktur(Studenci *tablica, int lewy,int prawy, int tryb){//Quicksort dla struktur
    int srodek=(int)(lewy+prawy)/2;
    int piwot=tablica[srodek].punkty;
    Studenci robocza1 = tablica[srodek];
    tablica[srodek]=tablica[prawy];
    tablica[prawy]=robocza1;
    int granica = lewy;
    int i=lewy;
    while(i<prawy){
        if(tryb) {
            if(tablica[i].punkty<piwot){
                Studenci robocza2=tablica[granica];
                tablica[granica]=tablica[i];
                tablica[i]=robocza2;
                granica+=1;
            }
        }
        else{
            if(tablica[i].punkty>piwot){
                Studenci robocza2=tablica[granica];
                tablica[granica]=tablica[i];
                tablica[i]=robocza2;
                granica+=1;
            }
        }
        i+=1;
    }
    Studenci robocza3 = tablica[prawy];
    tablica[prawy]=tablica[granica];
    tablica[granica]=robocza3;
    if(lewy<granica-1){
        quickSortDlaStruktur(tablica,lewy,granica-1,tryb);
    }
    if(granica+1<prawy){
        quickSortDlaStruktur(tablica,granica+1,prawy,tryb);
    }
}
