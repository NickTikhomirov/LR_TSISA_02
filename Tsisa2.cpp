#include <cmath>
#include <vector>
#include <iostream>
#include <random>
#include "UniqueGenerator.h"
#include <iomanip>

#define A 7
#define B 10

using std::vector;

enum mode {
	unimodal,
	multimodal
};

vector<double> getForTable() {
	vector<double> r;
	r.resize(10);
	for (int x = 0; x < 10; x++) 
		r[x] = 0.9 + 0.01 * x;
	return r;
}


double getValueFor(double x, mode m) {
	if(m==unimodal) return cos(x) + log10(x);
	if(m==multimodal) return sin(5*x)*getValueFor(x,unimodal);
	return x;
}


int n_counter(double p, double q) {
	return 1+(log(1-p)/log(1-q));
}

vector<vector<int>> tableGetter() {
	vector<vector<int>> res;
	res.resize(20);
	vector<double> positions = getForTable();
	std::cout << "q\\P \t";
	for (int k = 0; k < 10; k++) {
		std::cout << positions[k] << '\t';
	}
	std::cout << std::endl;
	for (int i = 0; i < 20; i++) {
		res[i].resize(10);
		double q = 0.005 * (i+1);
		std::cout << q << '\t';
		for (int j = 0; j < 10; j++) {
			//double p = 0.9 + 0.01*j;
			res[i][j] = n_counter(positions[j], q);
			std::cout << "|"<<res[i][j]<<'\t';
		}
		std::cout << std::endl;
	}
	return res;
}


double count(int amount, mode m){
	double x_min = INFINITY;
	double f_min = INFINITY;
	UniqueGenerator ugen(A, B);
	for (int i = 0; i < amount; i++) {
		double x = ugen.generate();
		double f = getValueFor(x, m);
		if (f < f_min) {
			x_min = x;
			f_min = f;
		}
	}
	return f_min;
}

	

int main(){
	std::cout << "P - probability of optimum point is situated in the interval of undefinity \n";
	std::cout << "q - probability of any point is situated in the interval of undefinity \n";
	std::cout<<"Amount of attempts:\n";
	vector<vector<int>> amountTable = tableGetter();
	vector<double> q_s = getForTable();
	std::cout << std::endl << std::endl;
	for (mode a : {unimodal, multimodal}) {
		std::cout << "Result for ";
		std::cout << ((a == unimodal)?"unimodal":"multimodal");
		std::cout << ":\n";
		std::cout << " q\\P \t";
		for (int k = 0; k < 10; k++) { 
			std::cout << std::fixed << std::setprecision(4) << q_s[k] << "\t"; 
		}
		std::cout << '\n';
		for (int i = 0; i < 20; i++) {
			std::cout << 0.005 * (i + 1) << '\t';
			for (int j = 0; j < 10; j++) {
				std::cout << count(amountTable[i][j], a) << "\t";
			}
			std::cout << std::endl;
		}
		std::cout << "-------------------------" << std::endl;
	}
}