#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <limits>
#include <fstream>
#include <queue>

using namespace std;

static const int tahestiku_pikkus = 26;
// inglise keele tähestiku pikkus

// andmestruktuur prefikspuu tipu jaoks
class Tipp{

public:
    // määrab kas puu servade järgi liikudes moodustub sõna või ei
    bool sona_leidub;
    // tipu lapsed
    Tipp* lapsed[tahestiku_pikkus];
};

// andmestruktuur prefikspuu jaoks
class Prefikspuu {

public:

    // OLEKS VAJA SELGITUST, MIS TEEB??
    Tipp* uus_tipp(){
        Tipp* tahis = new Tipp;
        tahis->sona_leidub = false;

        for(auto & i : tahis->lapsed){
            i = nullptr;
        }
        return tahis;
    }

    // MIKS??
    Tipp* juur = uus_tipp();

    // KIRJUTADA SELGITUSED!!
    void leia_sonad(const string& voti, vector<string>&koik_sonad){
        if(juur==nullptr) return;
        Tipp* tahis = juur;

        for(char i : voti){
            int indeks = i-'a';
            /* if child node at ind of current root is NULL this prefix do not exist in trie  */
            if(tahis->lapsed[indeks] == nullptr) return;
            tahis = tahis->lapsed[indeks];
        }
        /* if this prefix exist in trie then do BFS from current node to find all words  */
        queue<pair<Tipp*,string> > q;
        q.push(make_pair(tahis,voti));
        string this_word;
        while(!q.empty()){
            tahis = q.front().first;
            this_word = q.front().second;
            /* if this is word ,then add it to the all_words(vector) */
            if(tahis->sona_leidub) koik_sonad.push_back(this_word);
            q.pop();
            for(int i=0;i<tahestiku_pikkus;i++){
                if(tahis->lapsed[i] !=nullptr ){
                    q.push( make_pair(tahis->lapsed[i] , this_word+char(i+'a')));
                }
            }
        }
    }

    // KIRJUTADA SELGITUSED!!
    void lisa(const string& voti) {

        Tipp* tahis = juur;

        for(char i : voti) {
            int indeks = i-'a';
            if(tahis->lapsed[indeks] == nullptr){
                tahis->lapsed[indeks] = uus_tipp();
            }
            tahis = tahis->lapsed[indeks];
        }
        tahis->sona_leidub = true;
    }

    // KORRAS!
    void otsi(const string& voti){
        // kui midagi ei sisestata, siis ei lõpetame
        if(voti.empty()) return;
    // kui sisestatakse otsitav sõna, siis väljastame kõik sõnad selles prefikspuus
        vector<string> koik_sonad;
        leia_sonad(voti,koik_sonad);
    // kui sõnu ei leitud väljastame vastava teate
        if(koik_sonad.empty()){
            cout << "Uhtegi vastet ei leitud" << endl;
            return;
        }
    // kui mõni sõna on leitud väljastame need
        for(const auto & i : koik_sonad){
            cout<<i<<endl;
        }
    }
};

// TEHA ÜMBER JA/VÕI KIRJUTADA SELGITUSED!!
Tipp* helper(Tipp* juur, string voti, int indeks){
    // if tree is empty
    if(juur==nullptr) return nullptr;
    /*
        helper function takes 3 parameters
        1) root of subtrie (or subtree)
        2) processing key (key which is going to be deleted)
        3) ind (index) -> which character is processing or how much depth
        it returns root of this subtrie
    */
    bool isempty = true;
    for(auto & i : juur->lapsed){
        if(i != nullptr){
            isempty = false;
            break;
        }
    }

    if(indeks == voti.length()){
        /* hit the end of key
         possibilty -> 1) this key is prefix of other key,
         int this case,set is_word of current root equals to false;
         possibilty ->2) this key is not prefix of any other key
         in this case delete this node;
        */
        if(!isempty){
            // case 1
            juur->sona_leidub = false;
        }
        else{
            //case 2
            delete(juur);
            juur = nullptr;
        }
        return juur;

    }
    int pos = (voti[indeks])-'a';
    juur->lapsed[pos] = helper(juur->lapsed[pos],voti,indeks+1);

    isempty = true;
    for(auto & i : juur->lapsed){
        if(i != nullptr){
            isempty = false;
            break;
        }
    }

    /* here we have two case
     1) if all  child nodes of root is empty and this root is not marked as
        of word then delete this node
     2) if all child nodes are not empty "OR" this root os marked as end of
        word then do nothing
    */

    if(isempty && !juur->sona_leidub){
        delete(juur);
        juur = nullptr;
    }
    return juur;
}

// KORRAS
void kuva_menuu(){
    cout << "1. Lisamine" << endl;
    cout << "2. Otsimine" << endl << endl;
}
// KORRAS
unsigned int loe_valik(unsigned int &kasutaja_valik) {
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

    }
    while (vigane_sisend);
    kasutaja_valik = valik;
    return kasutaja_valik;
}
// KORRAS
void lisa_sonastik (string& failinimi, Prefikspuu puu) {

    string sona;
    ifstream sisend (failinimi);

    if (sisend.is_open()) {
        while (sisend >> sona) {
            puu.lisa (sona);
        }
    }
    else {
        cout << "Sellist faili ei leitud!" << endl;
    }
}

int main()
{
    unsigned int kasutaja_valik = 0;
    string sisend;
    string failinimi;
    Prefikspuu puu;

    do {
        kuva_menuu();
        loe_valik(kasutaja_valik);
        if (kasutaja_valik == 1) {
            cout << "Sisesta sonastiku failinimi: ";
            getline(cin, failinimi);
            lisa_sonastik (failinimi, puu);
        }
        if (kasutaja_valik == 2) {
            cout << "Sisesta sone, mida soovid otsida: ";
            cin >> sisend;
            puu.otsi(sisend);
        }
    }
    while (kasutaja_valik != 0);
    cout << "Aitah, et kasutasid programmi!";
}
