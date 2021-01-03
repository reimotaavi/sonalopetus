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

class Prefikspuu {
public:

    Tipp* prefikspuu () {
    Tipp *tuhi_puuoks = new Tipp; //loome oksa
    tuhi_puuoks->sonalopp = true; //maarame sonalopu

    for(auto & i : tuhi_puuoks->lapsed){ //taidame oksa tuhjade kohtadega
        i = nullptr;
    }
    return tuhi_puuoks;
    }

    void lisa(Tipp *juur, const string& lisatav_sona){
    Tipp *taidetud_puuoks = juur;
    for(char tase : lisatav_sona){
        int indeks = CHAR_TO_INDEX(tase); //loome tahele vastava numbrilise vaartuse
        if (!taidetud_puuoks->lapsed[indeks]) {//kui vastavat oksa ei leidu siis loome oksa
            taidetud_puuoks->lapsed[indeks] = prefikspuu();
        }
        taidetud_puuoks = taidetud_puuoks->lapsed[indeks]; //maarame oksale vastava tahe
    }
    taidetud_puuoks->sonalopp = false; //maarame koha mitte sonalopuks
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

    cout << "Sisesta: ";
    cin >> sisend;


//    do {
//        cout << "Sisesta otsing, voi '-', et valjuda programmist: ";
//        cin >> sisend;
//    } while (sisend != "-");
//    cout << "Aitah, et kasutasid programmi!";
}
