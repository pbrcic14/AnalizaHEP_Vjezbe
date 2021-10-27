#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <ElementaryParticle.h>

using namespace std;

int main()
{	
	ofstream file ("Analysis.txt");
	//file << "#no.\tparticle1\tE\tpx\tpy\tpz\tparticle2\tE\tpx\tpy\tpz" << endl;
	file << "#no." << setw(10) << "particle1" << setw(10) << "E" << setw(10) << "px" << setw(10) << "py" << setw(10) << "pz";
	file << setw(10) << "particle2" << setw(10) << "E" << setw(10) << "px" << setw(10) << "py" << setw(10) << "pz" << endl;
	
	random_device ran_dev;
	mt19937 gen(ran_dev());
	uniform_real_distribution<double> dist(-100.0, 100.0);
	
	ElementaryParticle* Higgs;
	ElementaryParticle* decayParticle_1;
	ElementaryParticle* decayParticle_2;
	
	Higgs = new ElementaryParticle("Higgs boson", 125.35, 1);
	decayParticle_1 = new ElementaryParticle();
	decayParticle_2 = new ElementaryParticle();
	
	for(int i = 0; i < 10000; i++)
	{		
		Higgs -> setMomentum(dist(gen), dist(gen), dist(gen));
		Higgs -> bosonDecay(decayParticle_1, decayParticle_2);
		
		file << i+1 << "\t" << setw(8) << decayParticle_1 -> name;
		for(int j = 0; j < 4; j++)
			file << "\t" << setw(8) << decayParticle_1 -> momentum[j];
		file << "\t" << setw(8) << decayParticle_2 -> name;
		for(int j = 0; j < 4; j++)
			file << "\t" << setw(8) << decayParticle_2 -> momentum[j];
		file << endl;
	}

	delete Higgs;
	delete decayParticle_1;
	delete decayParticle_2;
	
	file.close();
	
	return 0;
}
