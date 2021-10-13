#include <iostream>
#include <string>

using namespace std;

class ElementaryParticle
{
	public:
		string name;
		int mass;
		bool isBoson;
		ElementaryParticle(string n, int m, bool b)
		{
			name = n;
			mass = m;
			isBoson = b;
		}
		void printInfo()
		{
			cout << "Particle name: " << name << "\n";
			cout << "Particle mass: " << mass << " GeV\n";
			cout << "Is the particle a boson: ";
			if(isBoson == 1)
				cout << "yes\n";
			else
				cout << "no\n";
		}
};

int main()
{
	ElementaryParticle HiggsBoson("Higgs boson", 125, 1);
	ElementaryParticle topQuark("top quark", 173, 0);
	ElementaryParticle ZBoson("Z boson", 91, 1);
	ElementaryParticle* ptrZBoson;
	
	ptrZBoson = &ZBoson;
		
	HiggsBoson.printInfo();
	topQuark.printInfo();
	//ZBoson.printInfo();
	ptrZBoson -> printInfo();

	delete ptrZBoson;
	
	return 0;
}
