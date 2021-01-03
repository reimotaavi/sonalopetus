#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <limits>
#include <fstream>
#include <map>

using namespace std;
#define KONSTANT (26) //inglise sonastiku pikkus
#define CHAR_TO_INDEX(c) (c-'a') //muudame tahemargi numbriliseks vaartuseks

class Tipp{
public:
    Tipp *lapsed[KONSTANT]; //laste loend
    bool sonalopp;
};

class Prefiksipuu {
public:

    static Tipp* prefikspuu () {
        Tipp *tuhi_puuoks = new Tipp; //loome oksa
        tuhi_puuoks->sonalopp = true; //maarame sonalopu

        for(auto & i : tuhi_puuoks->lapsed){ //taidame oksa tuhjade kohtadega
            i = nullptr;
        }
        return tuhi_puuoks;
    }

    void lisa(Tipp *juur, vector<string> lisatavad_sonad) {
        Tipp *taidetud_puuoks = juur;
        for(auto lisatav_sona : lisatavad_sonad) {
            for (char tase : lisatav_sona) {
                int indeks = CHAR_TO_INDEX(tase); //loome tahele vastava numbrilise vaartuse
                if (!taidetud_puuoks->lapsed[indeks]) {//kui vastavat oksa ei leidu siis loome oksa
                    taidetud_puuoks->lapsed[indeks] = prefikspuu();
                }
                taidetud_puuoks = taidetud_puuoks->lapsed[indeks]; //maarame oksale vastava tahe
            }
            taidetud_puuoks->sonalopp = false; //maarame koha mitte sonalopuks
        }
    }

    static bool viimane_solm(Tipp* juur){ //kontrollime, kas vastaval solmel on lapsi voi ei
        for(auto & i : juur->lapsed){
            if(i){
                return false; //kui on laps
            }
        }
        return true; //kui ei ole last
    }

    void sonalopetus(Tipp* juur, string otsitav){
        if(juur->sonalopp){ //kui otsitav on olemas siis valjastame
            cout << otsitav << endl;
        }
        if(viimane_solm(juur)) return; //kui on oksa lopp, siis valjume funktsioonist

        for(auto & i : juur->lapsed){ //kui solmel on veel lapsi, siis teeme sonalopetust ka lastele
            if(i){
                otsitav.push_back(97 + 1);
                sonalopetus(i, otsitav);
                otsitav.pop_back();
            }
        }
    }

    void otsi(Tipp* juur, const string& otsing){
        Tipp* taidetud_puuoks = juur;
        int tase;
        int sona_pikkus = otsing.length();
        for(tase = 0; tase < sona_pikkus; tase++){
            int indeks = CHAR_TO_INDEX(otsing[tase]);
            if(!taidetud_puuoks->lapsed[indeks]){ //kui otsingut pole puus, siis ei valjasta midagi
                return;
            }
        }
        bool on_sona = taidetud_puuoks->sonalopp;
        bool on_viimane_solm = viimane_solm(taidetud_puuoks);
        if(on_sona && on_viimane_solm){
            cout << otsing << endl;
        }
        if(!on_viimane_solm){
            string otsitav_sona = otsing;
            sonalopetus(taidetud_puuoks, otsitav_sona);
        }
    }

};



vector<string> lisa_sonastik() {

    vector<string> sonad;
    string failinimi = "sonastik.txt";
    string sona;
    ifstream sisend (failinimi);

    if (sisend.is_open()) {
        while (sisend >> sona) {
            sonad.push_back(sona);
        }
        return sonad;
    }
    else {
        cout << "Sellist faili ei leitud!" << endl;
        return sonad;
    }
}

int main(){

    vector<string> sonad = lisa_sonastik();
    string sisend;
    Prefiksipuu puu;
    Tipp *juur = puu.prefikspuu();
    puu.lisa(juur, sonad);
    cout << "Sisesta: ";
    cin >> sisend;
    puu.otsi(juur, sisend);


//    do {
//        cout << "Sisesta otsing, voi '-', et valjuda programmist: ";
//        cin >> sisend;
//    } while (sisend != "-");
//    cout << "Aitah, et kasutasid programmi!";
}