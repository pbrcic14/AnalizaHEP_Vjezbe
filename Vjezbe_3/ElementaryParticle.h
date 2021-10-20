#include <iostream>
#include <string>

using namespace std;

class ElementaryParticle
{
	public:
		string name;
		double mass;
		bool isBoson;
		ElementaryParticle(string n, int m, bool b);
		ElementaryParticle();
		void printInfo();
		double momentum[4];
		void setMomentum(double p1, double p2, double p3);
		void bosonDecay(ElementaryParticle* particle1, ElementaryParticle* particle2);
};
