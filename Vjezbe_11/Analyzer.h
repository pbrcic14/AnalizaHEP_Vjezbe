#include <iostream>

using namespace std;

class Statistics
{
	public:
		Statistics();
		double Binomial(int r, double p, int N);
		void upperCP(int r, int N, double C);
		void lowerCP(int r, int N, double C);
};
