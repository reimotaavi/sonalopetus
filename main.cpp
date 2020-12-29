#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

#define KONSTANT (32)
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

struct Puu{
    struct Puu *lapsed[KONSTANT];
    bool sonalopp;
};

struct Puu *solm(void){
    struct Puu *uus_solm = new Puu;
    uus_solm->sonalopp = false;
    for(int i = 0; i < KONSTANT; i++){
        uus_solm->lapsed[i] = NULL;
    }
}

void lisa(struct Puu *juur, const string voti){
    struct Puu *Crawl = juur;

    for(int tase = 0; tase < voti.length(); tase++){
        int indeks = CHAR_TO_INDEX(voti[tase]);
        if(!Crawl->lapsed[indeks]){
            Crawl->lapsed[indeks] = solm();
        }
        Crawl = Crawl->lapsed[indeks];
    }
    Crawl->sonalopp = true;
}

bool otsi(struct Puu *juur, const string voti){
    int pikkus = voti.length();
    struct Puu *Crawl = juur;
    for (int tase = 0; tase < pikkus; tase++)
    {
        int indeks = CHAR_TO_INDEX(voti[tase]);

        if (!Crawl->lapsed[indeks])
            return false;

        Crawl = Crawl->lapsed[indeks];
    }

    return (Crawl != NULL && Crawl->sonalopp);
}

bool viimane_solm(struct Puu* juur)
{
    for (int i = 0; i < KONSTANT; i++)
        if (juur->lapsed[i])
            return 0;
    return 1;
}

void sonalopetus(struct Puu* juur, string otsitav){
    if (juur->sonalopp){
        cout << otsitav;
        cout << endl;
    }
    if (viimane_solm(juur)){
        return;
    }

    for (int i = 0; i < KONSTANT; i++){
        if (juur->lapsed[i]){
            otsitav.push_back(97 + i);
            sonalopetus(juur->lapsed[i], otsitav);
            otsitav.pop_back();
        }
    }
}

int valjasta(Puu* juur, const string query)
{
    struct Puu* Crawl = juur;

    int tase;
    int pikkus = query.length();
    for (tase = 0; tase < pikkus; tase++){
        int indeks = CHAR_TO_INDEX(query[tase]);
        if (!Crawl->lapsed[indeks]) return 0;

        Crawl = Crawl->lapsed[indeks];
    }

    bool isWord = (Crawl->sonalopp == true);
    bool isLast = viimane_solm(Crawl);
    if (isWord && isLast){
        cout << query << endl;
        return -1;
    }

    if (!isLast){
        string prefix = query;
        sonalopetus(Crawl, prefix);
        return 1;
    }
}

void kuva_menuu(){
    cout << "1. Lisamine" << endl;
    cout << "2. Otsimine" << endl;
}

int loe_valik(unsigned int &kasutaja_valik) {
    int valik;
    bool vigane_sisend;

    do {
        vigane_sisend = false;
        cout << "Sisestage valik: ";
        cin >> valik;

        if (cin.fail() || valik < 0 || valik > 2 || valik != ceil(valik)) {
            cout << "Viga! Sisestage korrektne valik!" << endl;
            vigane_sisend = true;
            cin.clear();
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

    } while (vigane_sisend);
    kasutaja_valik = valik;
    return kasutaja_valik;
}

int main(){
    struct Puu* juur = solm();
    unsigned int kasutaja_valik = 0;
    string sisend;
    do {
        kuva_menuu();
        loe_valik(kasutaja_valik);
        if (kasutaja_valik == 1) {
            cout << "Sisesta sona, mida soovid lisada: ";
            cin >> sisend;
            lisa(juur, sisend);
        } else if (kasutaja_valik == 2) {
            cout << "Sisesta sone, mida soovid otsida: ";
            cin >> sisend;
            valjasta(juur, sisend);
        }
    } while (kasutaja_valik != 0);
    cout << "Aitah, et kasutasid programmi!";
}

