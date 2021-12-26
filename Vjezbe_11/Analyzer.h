#include <iostream>
#include <TH1F.h>

using namespace std;

class Statistics
{
	public:
		Statistics();
		double Binomial(int r, double p, int N);
		double upperCP(int r, int N, double C);
		double lowerCP(int r, int N, double C);
		void Drawing(int rDraw);
		
		
};
