#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <numbers>
#define PIC "π"
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
	if (isSide) { cout << "Input side " << char('a'+part) << "\n> "; }
	else { cout << "Input angle " << char('A'+part-3) << "\n> "; }
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
		if ((!radMode) and (!isSide)) { rNum *= (piB/180); }
		cout << rNum << endl;
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
	cout << "What type of anaylisis would you like to preform?\n";
	while(doRun) {
		cout << "> ";
		cin >> inStr;
		if (inStr == "1") { sLenD = new bool[]{true,true,true}; aMesD = new bool[]{false,false,false}; sLenN = 3; aMesN = 0; doRun = false; }
		else if (inStr == "2") { sLenD = new bool[]{true,true,false}; aMesD = new bool[]{false,false,true}; sLenN = 2; aMesN = 1; doRun = false; }
		else if (inStr == "3") { sLenD = new bool[]{true,true,false}; aMesD = new bool[]{true,false,false}; sLenN = 2; aMesN = 1; doRun = false; }
		else if (inStr == "4") { sLenD = new bool[]{true,false,false}; aMesD = new bool[]{false,true,true}; sLenN = 1; aMesN = 2; doRun = false; }
		else if (inStr == "5") { sLenD = new bool[]{true,false,false}; aMesD = new bool[]{true,true,false}; sLenN = 1; aMesN = 2; doRun = false; }
		else if (inStr == "h") { pHelp(1); }
		else if (inStr == "e") { return false; }
		else { cout << "Please enter a valid input\n"; }
		
	}
	for (int i = 0; i < 3; i++) {
		if (sLenD[i]) {
			sLen[i] = getInput(i);
		}
	}
	for (int i = 0; i < 3; i++) {
		if (aMesD[i]) {
			aMes[i] = getInput(i+3);
		}
	}
	while ((aMesN < 3) and (sLenN < 3)) {
		//Law of cosines
		if (aMesN == 0) {
			aMes[2] = acosl((powl(sLen[0],2)+powl(sLen[1],2)-powl(sLen[2],2))/(2*sLen[0]*sLen[1]));
			aMesD[2] = true;
			aMesN++;
		}
		//Law of cosines
		if (sLenN == 2) {
			if (aMesD[0]) {
				bFloat rTerm = (sLen[1] * cosl(aMes[0]));
				bFloat sTerm = ((powl(sLen[1],2)*(powl(cosl(aMes[0]),2) - 1)) + powl(sLen[0],2));
				if (sTerm < 0) { cout << "NaN\n"; return true; }
				if ((rTerm-sqrtl(sTerm)) > 0) { sLen[2] = (rTerm+sqrtl(sTerm)); sLenD[2] = true; sLenN++; }
				else { sLen[2] = (rTerm+sqrtl(sTerm)); sLenD[2] = true; sLenN++; }
			} else {
				bFloat nTerm = sqrtl(pow(sLen[0],2)+pow(sLen[1],2)-(2*sLen[0]*sLen[1]*cosl(aMes[2])));
				sLen[2] = nTerm;
				sLenD[2] = true;
				sLenN++;
			}
		}

		//Tri angles add to 180
		if (aMesN == 2) {
			int valIn = 0;
			bFloat curSum = piB;
			for (int i = 0; i < 3; i++) {
				if (aMesD[i] == false) { valIn = i; }
				else { curSum -= aMes[i]; }
			}
			aMes[valIn] = curSum;
			aMesD[valIn] = true;
			aMesN++;
		}
		if ((aMesN == 1) and (sLenN == 3)) {
			int fIn = 0;
			int nfIn[2] = {0,0};
			int nfInIn = 0;
			for (int i = 0; i < 3; i++) {
				if (aMesD[i]) { fIn = i; }
				else { nfIn[nfInIn] = i; nfInIn++; }
			}
			for (int i = 0; i <= 1; i++) {
				aMes[nfIn[i]] = asinl((sLen[nfIn[i]]*sinl(aMes[fIn]))/sLen[fIn]);
				aMesD[nfIn[i]] = true;
			}
			aMesN = 3;
		}
	}
	cout << "A is: " << (aMes[0]/piB) << PIC << endl;
	cout << "B is: " << (aMes[1]/piB) << PIC << endl;
	cout << "C is: " << (aMes[2]/piB) << PIC << endl;
	cout << "a is: " << sLen[0] << endl;
	cout << "b is: " << sLen[1] << endl;
	cout << "c is: " << sLen[2] << endl;
	return true;
	
	

	

}
