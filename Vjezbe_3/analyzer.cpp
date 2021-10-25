#include <iostream>
#include <string>
#include <ElementaryParticle.h>

using namespace std;

int main()
{
	ElementaryParticle* Higgs;
	ElementaryParticle* Top;
	ElementaryParticle* Z;
	ElementaryParticle* decayParticle_1;
	ElementaryParticle* decayParticle_2;
	
	Higgs = new ElementaryParticle("Higgs boson", 125.35, 1);
	Top = new ElementaryParticle("top quark", 172.76, 0);
	Z = new ElementaryParticle("Z boson", 91.188, 1);
	decayParticle_1 = new ElementaryParticle();
	decayParticle_2 = new ElementaryParticle();
	
	Higgs -> printInfo();
	Top -> printInfo();
	Z -> printInfo();
	
	Higgs -> setMomentum(55.0, 66.0, 77.0);
	Higgs -> bosonDecay(decayParticle_1, decayParticle_2);

	delete Higgs;
	delete Top;
	delete Z;
	delete decayParticle_1;
	delete decayParticle_2;
	
	return 0;
}
