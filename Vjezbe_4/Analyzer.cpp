#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <random>
#include <Analyzer.h>

using namespace std;

void Analyzer::readFile()
{
	ifstream input ("Analysis.txt");
	string line;
	int tmp;
	bool skip = true;
	string name1, name2;
	double p1[4];
	double p2[4];
	
	while(getline(input, line))
	{
		if(skip)
		{
			skip = false;
			continue;
		}
		stringstream linestream(line);
		linestream >> tmp >> name1 >> p1[0] >> p1[1] >> p1[2] >> p1[3] >> name2 >> p2[0] >> p2[1] >> p2[2] >> p2[3];
	}
	
	input.close();
}
void Analyzer::ConvertTxtToRootFile()
{
	bool skip = true;
	string line;
	int tmp;
	string name1, name2;
	double p1[4];
	double p2[4];
	double pt1, pt2;
	ifstream input ("Analysis.txt");

	TFile* output = output = TFile::Open("Analysis.root", "RECREATE"); //TFile::Open(name, option);  
	TTree* tree = new TTree("tree", "Converting .txt to .root"); //TTree tree (name, title); Tree -> columnar dataset; TTree consists of a list of independent columns (branches, TBranch class)

	tree->Branch("name1", &name1, "name1/S"); //Branch(name, address, string describing the leaf list); leaf: name/type
	tree->Branch("E1", &p1[0], "E1/LF");
	tree->Branch("px1", &p1[1], "px1/LF");
	tree->Branch("py1", &p1[2], "py1/LF");
	tree->Branch("pz1", &p1[3], "pz1/LF");
	tree->Branch("pt1", &pt1, "pt1/LF");
	tree->Branch("name2", &name2, "name2/S");
	tree->Branch("E2", &p2[0], "E2/LF");
	tree->Branch("px2", &p2[1], "px2/LF");
	tree->Branch("py2", &p2[2], "py2/LF");
	tree->Branch("pz2", &p2[3], "pz2/LF");
	tree->Branch("pt2", &pt2, "pt2/LF");
	
	while(getline(input, line))
	{
		if(skip)
		{
			skip = false;
			continue;
		}
		stringstream linestream(line);
		linestream >> tmp >> name1 >> p1[0] >> p1[1] >> p1[2] >> p1[3] >> name2 >> p2[0] >> p2[1] >> p2[2] >> p2[3];
		pt1 = sqrt(p1[1]*p1[1] + p1[2]*p1[2]);
		pt2 = sqrt(p2[1]*p2[1] + p2[2]*p2[2]);
		tree->Fill();
	}

	tree->Print();
	tree->Write();
	input.close();
	delete output;
}
