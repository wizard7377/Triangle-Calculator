#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <numbers>

using namespace std;
using bFloat = long double;
const bFloat piB = std::numbers::pi_v<bFloat>;


bool actMain();
void pHelp(int page) {
	fstream f("help"+to_string(page)+".txt");
	if (f.is_open()) { cout << endl << f.rdbuf() << endl << endl; }
}

bFloat getInput(int part) {
	string inStr = "";
	bFloat fNum[2] = {1,1};
	bFloat rNum = 1;
	bool isSide = (part < 3);
	bool gIn = true;
	bool radMode = false;
	bool piMode = false;
	bool negMode = false;
	int sPos;
	if (isSide) { cout << "Input side " << ('a'+part) << "\n> "; }
	else { cout << "Input angle " << ('A'+part-3) << "\n> "; }
	while (gIn) {
		cin >> inStr;
		radMode = (inStr.ends_with("r"));
		if ((inStr.ends_with("d")) or radMode) { inStr.pop_back(); }
		piMode = (inStr.ends_with("pi"));
		if (piMode) { inStr.pop_back(); inStr.pop_back(); }
		negMode = (inStr.starts_with("-"));
		if (negMode) { inStr.erase(0); }
		sPos = inStr.find("/");
		if (sPos != string::npos) { fNum[1] = stold(inStr.substr(sPos+1)); inStr.erase(sPos); }
		fNum[0] = stold(inStr);
		rNum = fNum[0]/fNum[1];
		if (negMode) { rNum *= -1; }
		if (piMode) { rNum *= piB; }
		if (!radMode) { rNum *= (piB/180); }
		if (true) { return rNum; }
	}
	return 0;
}

		
		

int main() {
	string inStr = "";
	bool doRun = true;
	while (doRun) {
		cout << "Welcome to the bad triangle calc, what would you like to do? \n 1: exit\n 2: run\n 3: help\n> ";
		cin >> inStr;
		if (inStr == "1") { cout << "Goodbye!\n"; return 1; }
		else if (inStr == "2") { if (!(actMain())) { cout << "Goodbye!\n"; return 1; } }
		else if (inStr == "3") { pHelp(0); }
		else { cout << "Please enter a valid option\n"; }
	}

}

bool actMain() {
	bool doRun = true;
	int sLenN;
	int aMesN;
	bool * sLenD;
	bool * aMesD;
	bFloat sLen[3] = {0,0,0};
	bFloat aMes[3] = {0,0,0};
	string inStr = "";
	cout << "What type of anaylisis would you like to preform?\n> ";
	while(doRun) {
		cin >> inStr;
		if (inStr == "1") { sLenD = new bool[]{true,true,true}; aMesD = new bool[]{false,false,false}; sLenN = 3; aMesN = 0; }
		else if (inStr == "2") { sLenD = new bool[]{true,true,false}; aMesD = new bool[]{false,false,true}; sLenN = 2; aMesN = 1; }
		else if (inStr == "3") { sLenD = new bool[]{true,true,false}; aMesD = new bool[]{true,false,false}; sLenN = 2; aMesN = 1; }
		else if (inStr == "4") { sLenD = new bool[]{true,false,false}; aMesD = new bool[]{false,true,true}; sLenN = 1; aMesN = 2; }
		else if (inStr == "5") { sLenD = new bool[]{true,false,false}; aMesD = new bool[]{true,true,false}; sLenN = 1; aMesN = 2; }
		else if (inStr == "h") { pHelp(1); }
		else if (inStr == "e") { return false; }
		else { cout << "Please enter a valid input\n"; }
		cout << "> ";

	}
	

	

	return true;
}
