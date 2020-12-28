#include <iostream>
#include <map>
#include <vector>

using namespace std;

// andmestruktruur puu tipu andmetega
template <class Silt>
class Tipp {

public:
	Silt silt;
	Tipp<Silt>* vanem;
	vector<Tipp<Silt>*> lapsed;
};

// andmestruktruur prefikspuu tippude ahelana
template <class Silt>
class Prefikspuu {

public:
    Tipp<Silt>* juur;
};

int main(){






    return 0;
}
