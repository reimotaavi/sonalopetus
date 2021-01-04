#include <iostream>
#include <vector>
#include <string>
#include <fstream>

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
        tuhi_puuoks->sonalopp = false; //maarame sonalopu

        for(int i = 0; i < KONSTANT; i++){ //taidame oksa tuhjade kohtadega
            tuhi_puuoks->lapsed[i] = nullptr;
        }
        return tuhi_puuoks;
    }

    static void lisa(Tipp *juur, const vector<string>& lisatavad_sonad) {
        for (const auto& lisatav_sona : lisatavad_sonad) {
            Tipp *taidetud_puuoks = juur;
            for (char tase : lisatav_sona) {
                int indeks = CHAR_TO_INDEX(tase); //loome tahele vastava numbrilise vaartuse
                if (!taidetud_puuoks->lapsed[indeks]) {//kui vastavat oksa ei leidu siis loome oksa
                    taidetud_puuoks->lapsed[indeks] = prefikspuu();
                }
                taidetud_puuoks = taidetud_puuoks->lapsed[indeks]; //maarame oksale vastava tahe
            }
            taidetud_puuoks->sonalopp = true; //maarame koha mitte sonalopuks
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

        for(int i = 0; i < KONSTANT; i++){ //kui solmel on veel lapsi, siis teeme sonalopetust ka lastele
            if(juur->lapsed[i]){
                otsitav.push_back(97 + i); //paneme sonale jargmise tahe loppu
                sonalopetus(juur->lapsed[i], otsitav); //otsime saadud uuele sonale sonalopetust
                otsitav.pop_back(); //eemaldame tahe
            }
        }
    }

    void otsi(Tipp* juur, const string& otsing){
        Tipp* taidetud_puuoks = juur;
        for(char tase : otsing){
            int indeks = CHAR_TO_INDEX(tase);
            if(!taidetud_puuoks->lapsed[indeks]){ //kui otsingut pole puus
                cout << "Otsingule ei leidunud vasteid!" << endl;
                return;
            }
            taidetud_puuoks = taidetud_puuoks->lapsed[indeks];
        }
        bool on_sona = taidetud_puuoks->sonalopp; //vaatame kas on sonalopp
        bool on_viimane_solm = viimane_solm(taidetud_puuoks); //vaatame, kas solmel on lapsi
        if(on_sona && on_viimane_solm){ //vaatame kas otsingule on ainult 1 vaste puus
            cout << otsing << endl;
        }
        if(!on_viimane_solm){ //kui ei ole viimane solm, siis otsime sonalopetusi
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
    Tipp* juur = Prefiksipuu::prefikspuu();
    Prefiksipuu::lisa(juur, sonad);

    do {
        cout << endl << "Sisesta otsing, voi '-', et valjuda programmist: ";
        cin >> sisend;
        puu.otsi(juur, sisend);
    } while (sisend != "-");
    cout << "Aitah, et kasutasid programmi!";
}