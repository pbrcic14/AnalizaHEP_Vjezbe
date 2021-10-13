#include <iostream>
#include <string>
#include <ElementaryParticle.h>

using namespace std;

ElementaryParticle::ElementaryParticle(string n, int m, bool b)
{
	name = n;
	mass = m;
	isBoson = b;
}
void ElementaryParticle::printInfo()
{
	cout << "Particle name: " << name << "\n";
	cout << "Particle mass: " << mass << " GeV\n";
	cout << "Is the particle a boson: ";
	if(isBoson == 1)
		cout << "yes\n";
	else
		cout << "no\n";
}
