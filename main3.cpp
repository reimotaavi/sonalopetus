#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <limits>
#include <fstream>
#include <map>

using namespace std;
#define KONSTANT (26)

struct Tipp{
    char taht;
    map<char, Tipp*> lapsed;
    bool sonalopp;
};

class Prefiksipuu{
private:
    Tipp juur;
    vector<Tipp*> lapsed;

public:
    void lisa(const string& sona){
        map<char, Tipp*> *praegune_puu = &juur.lapsed;
        map<char, Tipp*>::iterator it;
        for(char taht : sona){
            if((it = praegune_puu->find(taht)) != praegune_puu->end()){
                praegune_puu = &it->second->lapsed;
                continue;
            }
            if(it == praegune_puu->end()){
                Tipp* uus_solm = new Tipp();
                uus_solm->taht = taht;
                (*praegune_puu)[taht] = uus_solm;
                praegune_puu = &uus_solm->lapsed;
                lapsed.push_back(uus_solm);
                juur.sonalopp = true;
            }
        }
    }

    void loo_puu(const vector<string>& sonad){
        for(const auto & i : sonad){
            lisa(i);
        }
    }

    void sonalopetus(){

    }

    void otsi(){

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
    Prefiksipuu puu;
    puu.loo_puu(sonad);
    string sisend;

    cout << "Sisesta: ";
    cin >> sisend;


//    do {
//        cout << "Sisesta otsing, voi '-', et valjuda programmist: ";
//        cin >> sisend;
//    } while (sisend != "-");
//    cout << "Aitah, et kasutasid programmi!";
}