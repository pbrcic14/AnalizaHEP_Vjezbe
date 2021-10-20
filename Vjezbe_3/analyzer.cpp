#include <iostream>
#include <string>
#include <ElementaryParticle.h>

using namespace std;

int main()
{
	ElementaryParticle* Higgs;
	ElementaryParticle* Top;
	ElementaryParticle* Z;
	ElementaryParticle* particle1;
	ElementaryParticle* particle2;
	
	Higgs = new ElementaryParticle("Higgs boson", 125, 1);
	Top = new ElementaryParticle("top quark", 173, 0);
	Z = new ElementaryParticle("Z boson", 91, 1);
	particle1 = new ElementaryParticle();
	particle2 = new ElementaryParticle();
	
	Higgs -> printInfo();
	Top -> printInfo();
	Z -> printInfo();
	
	Higgs -> setMomentum(55.0, 66.0, 77.0);
	Higgs -> bosonDecay(particle1, particle2);

	delete Higgs;
	delete Top;
	delete Z;
	
	return 0;
}
