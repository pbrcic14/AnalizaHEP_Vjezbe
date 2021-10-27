#include <iostream>
#include <string>
#include <fstream>
#include <ElementaryParticle.h>

using namespace std;

int main()
{
	double p1, p2, p3;	
	ofstream file ("Analysis.txt");
	
	ElementaryParticle* Higgs;
	ElementaryParticle* decayParticle_1;
	ElementaryParticle* decayParticle_2;
	
	Higgs = new ElementaryParticle("Higgs boson", 125.35, 1);
	
	decayParticle_1 = new ElementaryParticle();
	decayParticle_2 = new ElementaryParticle();
	
	for(int i = 0; i < 100; i++)
	{
		srand(time(NULL));
		p1 = ((double) rand() / RAND_MAX)*200.0 - 100.0;
		p2 = ((double) rand() / RAND_MAX)*200.0 - 100.0;
		p3 = ((double) rand() / RAND_MAX)*200.0 - 100.0;
		
		Higgs -> setMomentum(p1, p2, p3);
		Higgs -> bosonDecay(decayParticle_1, decayParticle_2);
		
		file << i+1;
		for(int j = 0; j < 4; j++)
			file << "\t" << decayParticle_1 -> momentum[j];
		for(int j = 0; j < 4; j++)
			file << "\t" << decayParticle_2 -> momentum[j];
		file << "\n";
	}

	delete Higgs;
	delete decayParticle_1;
	delete decayParticle_2;
	
	file.close();
	
	return 0;
}
