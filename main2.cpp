#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <limits>
#include <fstream>
#include <queue>

using namespace std;

static const int sona_pikkus = 26;

// Andmestruktuur prefikspuu tipu jaoks
struct Tipp{
    // määrab kas puu servade järgi liikudes moodustub sõna või ei
    bool sona_leidub;
    Tipp* lapsed[sona_pikkus];
};

Tipp* uus_tipp(){
    Tipp* indeks = new Tipp;
    indeks->sona_leidub = false;

    for(auto & i : indeks->lapsed){
        i = nullptr;
    }

    return indeks;
}

void lisa(Tipp* juur, const string& voti){
    Tipp* indeks = juur;

    for(char i : voti){
        int ind = int(i)-'a';
        if(indeks->lapsed[ind] == nullptr){
            indeks->lapsed[ind] = uus_tipp();
        }
        indeks = indeks->lapsed[ind];
    }
    indeks->sona_leidub = true;
}

Tipp* helper(Tipp* juur, string voti, int ind){
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

    if(ind == voti.length()){
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
    int pos = int(voti[ind])-'a';
    juur->lapsed[pos] = helper(juur->lapsed[pos],voti,ind+1);

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

void find_all_words( Tipp* juur, const string& voti, vector<string>&koik_sonad){
    if(juur==nullptr) return ;
    Tipp* indeks = juur;

    for(char i : voti){
        int ind = int(i)-'a';
        /* if child node at ind of current root is NULL this prefix do not exist in trie  */
        if( indeks->lapsed[ind] == nullptr ) return ;

        indeks = indeks->lapsed[ind];
    }

    /* if this prefix exist in trie then do BFS from current node to find all words  */
    queue<pair<Tipp*,string> > q;
    q.push(make_pair(indeks,voti));
    string this_word;
    while(!q.empty()){
        indeks = q.front().first;
        this_word = q.front().second;
        /* if this is word ,then add it to the all_words(vector) */
        if(indeks->sona_leidub) koik_sonad.push_back( this_word );
        q.pop();
        for(int i=0;i<sona_pikkus;i++){
            if( indeks->lapsed[i] !=nullptr ){
                q.push( make_pair( indeks->lapsed[i] , this_word+char(i+int('a')) ) );
            }
        }
    }
}

void auto_complete(Tipp* juur, const string& voti){
    /* this function takes two parametes
       1.) root node of trie
       2.) key for which suggestion need to find.
       this function prints all the words for which key is prefix.
    */

    /* if key is empty , no need to print */
    if(voti.empty()) return;

    /* if key is not empty , then we will print all words in trie for which key is PREFIX. */

    vector<string> koik_sonad;

    find_all_words(juur,voti,koik_sonad);

    /* print all words */

    if(koik_sonad.empty()){
        cout << "Uhtegi vastet ei leitud" << endl;
        return;
    }

    for(const auto & i : koik_sonad){
        cout<<i<<endl;
    }

}

void kuva_menuu(){
    cout << "1. Lisamine" << endl;
    cout << "2. Otsimine" << endl << endl;
}

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

    } while (vigane_sisend);
    kasutaja_valik = valik;
    return kasutaja_valik;
}

void lisa_sonastik (string& failinimi, Tipp* juur) {

    string sona;
    ifstream sisend (failinimi);

    if (sisend.is_open()) {
        while (sisend >> sona) {
            lisa (juur, sona);
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
    Tipp* juur = uus_tipp();

    do {
        kuva_menuu();
        loe_valik(kasutaja_valik);
        if (kasutaja_valik == 1) {
            cout << "Sisesta sonastiku failinimi: ";
            getline(cin, failinimi);
            lisa_sonastik (failinimi, juur);
        }
        if (kasutaja_valik == 2) {
            cout << "Sisesta sone, mida soovid otsida: ";
            cin >> sisend;
            auto_complete(juur, sisend);
        }
    }
    while (kasutaja_valik != 0);
    cout << "Aitah, et kasutasid programmi!";
}