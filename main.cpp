//Kure Dominykas Rakunas :D
#include <bits/stdc++.h> // visos bibliotekos

using namespace std;

struct zaidejas{ //zaidejo info
    string vardas;
    int numeris;
    int s;
    int suviai = 0;
};

void rikiuoti(zaidejas * zaidejai, int index);
void spausdinti(ofstream & out, zaidejas * zaidejai, int index);
int main()
{
    ifstream in("U2.txt");
    ofstream out("U2rez.txt");
    int rows; //startavusiu kiekis
    int rows2;//finisavusiu kiekis
    int h, m, s; // valanda, minute, sekunde
    int numeris; // unikalus numeris
    int suvis; // pataikyti suviai
    int suvisTemp = 0; // nepataikyti suviai
    string vardasTemp; //laikinas vardas
    int indexVyr = 0; // identifikatorius merginu lentelei
    int indexMot = 0; // identifikatorius vaikinu lentelei

    zaidejas zaidejai[30]; // visi
    zaidejas vaikinai[30]; // jau fisisave
    zaidejas merginos[30]; // jau finisave

    vardasTemp.resize(20);
    in>>rows;
    for(int i=0; i<rows; i++){ //irasau duomenis i strukturu masyva, apibudinu zaidejus
        in.read(&vardasTemp[0], 1); //nuskaitau endl bita, kuris uzsiliko pabaigoj po in>>rows
        in.read(&vardasTemp[0], 20); // nuskaitau 20 simboliu vardo
        zaidejai[i].vardas = vardasTemp;
        in>>zaidejai[i].numeris;
        in>>h; //laikinai irasau
        in>>m;
        in>>s;
        zaidejai[i].s = h*3600 + m*60 + s; // paskui paverciu viska i sekundes, nes lengviau lyginti
    }
    in>>rows2;
    for(int i = 0; i<rows2; i++){
        in>>numeris; //irasau laikinai
        in>>h;
        in>>m;
        in>>s;
        s+=m*60; // paverciu sekundem, nes lengviau
        s+=h*3600;
        if(numeris/100==2){ // tikrinu ar vyras
            for(int j = 0; j<4; j++){ // prasuka 4 kartus
                in>>suvis;
                suvis=5-suvis;
                suvisTemp+=suvis*60; // skaiciuoja, kiek kainavo prasovimai laiko
                s+=suvis*60; // dideja sekundes prasaunant

            }
        }else{ // tikrinu ar moteris
            for(int j = 0; j<2; j++){ // prasuka 2 kartus
                in>>suvis;
                suvis=5-suvis;
                suvisTemp+=suvis*60;
                s+=suvis*60;
            }
        }
        if(s/3600-suvisTemp<17){ // trasa uzdaroma 17 valanda, suvisTemp nerealus laikas, todel atimam
            for(int j = 0; j< rows; j++){
                if(numeris == zaidejai[j].numeris){ // prasukant 2 kartus ir randant atitikmeni ziurim ar vyras ar moteris
                    if(numeris/100==2){ // vyras
                        vaikinai[indexVyr].vardas = zaidejai[j].vardas; // surasoma i vaikinu masyva, naudojamas vaikinu index
                        vaikinai[indexVyr].numeris = zaidejai[j].numeris;
                        vaikinai[indexVyr].s = s-zaidejai[j].s;
                        indexVyr++; // pridedam viena, tik kai viskas tenkina salyga
                    }else{ //moteris
                        merginos[indexMot].vardas = zaidejai[j].vardas; // surasoma i merginu masyva, naudojamas merginu index
                        merginos[indexMot].numeris = zaidejai[j].numeris;
                        merginos[indexMot].s = s-zaidejai[j].s;
                        indexMot++;
                    }
                }
            }
        }

    }

    rikiuoti(merginos, indexMot); //isrikiuojam
    rikiuoti(vaikinai, indexVyr);

    out<<"Merginos\n"; // atspauzdinam
    spausdinti(out, merginos, indexMot);
    out<<"\nVaikinai\n";
    spausdinti(out, vaikinai, indexVyr);
    return 0;
}
void rikiuoti(zaidejas * zaidejai, int index){
    for(int i = 0; i<index-1; i++){ // senas bubble sort rusiavimo budas optimizuotas
        for(int j=i+1; j<index; j++){
            if(zaidejai[i].s>zaidejai[j].s){
                swap(zaidejai[i],zaidejai[j]); //apkeicia duomenis vietom, jei randa pradzioj daugiau sekundziu turinti elementa
            }else if(zaidejai[i].s==zaidejai[j].s){
                if(zaidejai[i].vardas>zaidejai[j].vardas){
                    swap(zaidejai[i],zaidejai[j]); // apkeicia duomenis vietom, jei elementu sekundes lygios, bet vardas ne a - z tvarka
                }
            }
        }
    }
}

void spausdinti(ofstream & out, zaidejas * zaidejai, int index){ // spauzdina
    for(int i =0 ; i<index; i++){
        out<<zaidejai[i].numeris<<" ";
        out<<zaidejai[i].vardas<<" ";
        out<<zaidejai[i].s/3600<<" "; // valandos
        out<<zaidejai[i].s%3600/60<<" "; // minutes
        out<<zaidejai[i].s%3600%60<<endl; // sekundes
    }
}
