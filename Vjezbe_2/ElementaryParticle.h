#include <iostream>
#include <string>

using namespace std;

class ElementaryParticle
{
	public:
		string name;
		int mass;
		bool isBoson;
		ElementaryParticle(string n, int m, bool b);
		void printInfo();
};
