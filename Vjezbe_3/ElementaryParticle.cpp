#include <iostream>
#include <string>
#include <cmath>
#include <ElementaryParticle.h>

using namespace std;

ElementaryParticle::ElementaryParticle(string n, int m, bool b)
{
	name = n;
	mass = m;
	isBoson = b;
}
ElementaryParticle::ElementaryParticle()
{
	name = "";
	mass = 0.0;
	isBoson = 0;
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
void ElementaryParticle::setMomentum(double p1, double p2, double p3)
{
	momentum[1] = p1;
	momentum[2] = p2;
	momentum[3] = p3;
	momentum[0] = sqrt(p1*p1 + p2*p2 + p3*p3 + mass*mass);
	cout << "Energy = " << momentum[0] << "\n";
	cout << "Transversal momentum = " << sqrt(p1*p1 + p2*p2) << "\n";
}
void ElementaryParticle::bosonDecay(ElementaryParticle* particle1, ElementaryParticle* particle2)
{
	if(isBoson == 0)
		cout << "Decay is not possible.\n";
	else
		cout << "Decay is possible yaay!\n";
}
