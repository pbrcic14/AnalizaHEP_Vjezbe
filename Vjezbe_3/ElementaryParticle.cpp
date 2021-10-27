#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <random>
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
	srand(time(NULL));
	double r, E1, E2;
	
	if(isBoson == 0)
		cout << "Decay is not possible.\n";
	else
	{
		r = (double) rand() / RAND_MAX;
		if(r < 0.214)
		{
			cout << "Decay to W bosons.\n\n";
			particle1 -> mass = 80.379;
			particle2 -> mass = 80.379;
		}
		else if(r < 0.278)
		{
			cout << "Decay to tau leptons.\n\n";
			particle1 -> mass = 1.777;
			particle2 -> mass = 1.777;
		}
		else if(r < 0.304)
		{
			cout << "Decay to Z bosons.\n\n";
			particle1 -> mass = 91.188;
			particle2 -> mass = 91.188;
		}
		else
		{
			cout << "Decay to b quarks.\n\n";
			particle1 -> mass = 4.18;
			particle2 -> mass = 4.18;
		}
		
		E1 = pow(particle1 -> mass, 2);
		E2 = pow(particle2 -> mass, 2);
		for(int i = 1; i < 4; i++)
		{
			particle1 -> momentum[i] = ((double) rand() / RAND_MAX) * momentum[i];
			particle2 -> momentum[i] = momentum[i] - particle1 -> momentum[i];
			
			E1 += pow(particle1 -> momentum[i], 2);
			E2 += pow(particle2 -> momentum[i], 2);
		}
		particle1 -> momentum[0] = sqrt(E1);
		particle2 -> momentum[0] = sqrt(E2);
	}
}
