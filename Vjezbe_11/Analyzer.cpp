#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <TMath.h>
#include <cstdlib>
#include <ctime>
#include <random>
#include <Analyzer.h>

using namespace std;

Statistics::Statistics(){}

double Statistics::Binomial(int r, double p, int N)
{	
	double B;
	B = TMath::Factorial(N) * pow(p,r) * pow(1-p,N-r) / (TMath::Factorial(r) * TMath::Factorial(N-r));
	//cout << "Binomial(" << r << "; " << p << ", " << N << ") = " << B << endl;
	return B;
}

void Statistics::upperCP(int r, int N, double C)
{	
	double p = 1.0;
	double sumB = 1.0;
	while((1.0-sumB) < ((1.0-C)/2.0))
	{
		//cout << 1.0-sumB << " < " << (1.0-C)/2.0 << endl;
		sumB = 0.0;
		for(int j=r+1; j<=N; j++)
		{
			sumB += Binomial(j, p, N);
		}
		p -= 0.001;
	}
	cout << "Upper limit " << p << endl;
}

void Statistics::lowerCP(int r, int N, double C)
{	
	double p = 1.0;
	double sumB;
	double sum = 100.0;
	while(sum > ((1.0-C)/2.0))
	{
		//cout << 1.0-sumB << " > " << (1.0-C)/2.0 << endl;
		sumB = 0.0;
		for(int j=0; j<r; j++)
		{
			sumB += Binomial(j, p, N);
		}
		p -= 0.001;
		sum = 1.0 - sumB;
	}
	cout << "Lower limit " << p << endl;
}





