#include <iostream>
#include <string>
#include <ElementaryParticle.h>

using namespace std;

int main()
{
	ElementaryParticle* ptrHiggs;
	ElementaryParticle* ptrTop;
	ElementaryParticle* ptrZ;
	
	ptrHiggs = new ElementaryParticle("Higgs boson", 125, 1);
	ptrTop = new ElementaryParticle("top quark", 173, 0);
	ptrZ = new ElementaryParticle("Z boson", 91, 1);
	
	ptrHiggs -> printInfo();
	ptrTop -> printInfo();
	ptrZ -> printInfo();

	delete ptrHiggs;
	delete ptrTop;
	delete ptrZ;
	
	return 0;
}
