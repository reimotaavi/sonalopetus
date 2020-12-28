#include <iostream>
#include <map>
#include <vector>

using namespace std;

// andmestruktruur puu tipu andmetega
class Tipp {

public:
	char tahemark;
	map <char, Tipp*> lapsed;
	bool sona_leitud;

	Tipp () {
		sona_leitud = false;
	}
};

// andmestruktruur prefikspuu tippude ahelana
class Prefikspuu {

public:
	Tipp* juur;

};

int main(){






    return 0;
}
