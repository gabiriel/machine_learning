// superdll.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"

#include <iostream>
#include <ctime>
#include <random>
#include <Eigen>

using namespace std;
using namespace Eigen;

int main()
{
	const int size = 3;
	const int xSize = size + 1;

	const double valuePlus = 1.0;
	const double valueMoins = -1.0;

	std::vector<double*> myVector;
	std::vector<double*> errors;
	
	// expected 1.0 = x[3]
	double x1[xSize] = { 0.0, 0.0, 0.0, valuePlus };
	double x2[xSize] = { 0.0, 0.0, -2.34, valuePlus };
	double x3[xSize] = { 3.0, 0.0, -5.27, valuePlus };
	double x4[xSize] = { 1.0, 0.0, -5.0, valuePlus };
	double x5[xSize] = { 8.0, 0.0, -0.5, valuePlus };
	double x6[xSize] = { 6.0, 0.0, -2.0, valuePlus };

	// expected -1.0
	double x7[xSize] = { 6.0, 0.0, -7.28, valueMoins };
	double x8[xSize] = { 9.0, 0.0, -7.28, valueMoins };
	double x9[xSize] = { 9.0, 0.0, -4.33, valueMoins };
	double x10[xSize] = { 8.0, 0.0, -5.29, valueMoins };
	double x11[xSize] = { 5.05, 0.0, -7.28, valueMoins };
	double x12[xSize] = { 7.0, 0.0, -6.29, valueMoins };

	double w[size] = { 0.0, 0.0, 0.0 };
	// cout << "INIT W = " << w[0] << " " << w[1] << " " << w[2] << endl;
	
	double* x = x7;
	double expectedValue = x[size];

	myVector.push_back(x1);
	myVector.push_back(x2);
	myVector.push_back(x3);
	myVector.push_back(x4);
	myVector.push_back(x5);
	myVector.push_back(x6);
	myVector.push_back(x7);
	myVector.push_back(x8);
	myVector.push_back(x9);
	myVector.push_back(x10);
	myVector.push_back(x11);
	myVector.push_back(x12);
	
	errors = calcul_w(myVector, w, size);

	if (errors.size() > 0) {
		int elu = rand()%errors.size();
		double* last_x = errors.at(elu);
		errors.empty();
		errors.push_back(last_x);
		calcul_w(errors, w, size);
		cout << "ERRORS (" << errors.size() << ") with elu : " << elu << endl;
	}

	cout << "LASSSSTTTT LAST W = " << w[0] << " " << w[1] << " " << w[2] << endl;
	char a;
	cin >> a;
	return 0;
}

	vector<double*> calcul_w(vector<double*> myVector, double* w, int size) {
		int result = 0;
		std::vector<double*> errors;

		while(myVector.size() > 0)
		{
			double* x = myVector.back();
			myVector.pop_back();
			double expectedValue = x[size];

			do
			{
				cout << "W = " << w[0] << " " << w[1] << " " << w[2] << " result=" << result << endl;
				result = perceptron_lineaire_classification(x, w, size);
				if (result == expectedValue) {
					break;
				}
				else {
					fit_rosenblatt(x, w, size, expectedValue);
					errors.push_back(x);
				}
			} while (result != expectedValue);
		}
		
		cout << "LAST W = " << w[0] << " " << w[1] << " " << w[2] << " result=" << result << endl;

		return errors;
	}


extern "C"
{

	__declspec(dllexport) int perceptron_lineaire_classification(double* x, double* w, int nb) {
		double result = 0;

		for (int i = 0; i < nb; i++)
		{
			result += x[i] * w[i];
		}

		return copysign(1, result);
	}

	__declspec(dllexport) void fit_pla(double* x, double* w, int nb, double expected)
	{
		const double pas = 0.10;
		for (int i = 0; i < nb; i++)
		{
			w[i] += pas * expected * x[i];
		}
	}

	__declspec(dllexport) void fit_rosenblatt(double* x, double* w, int nb, double expected)
	{
		const double pas = 0.1;
		for (int i = 0; i < nb; i++)
		{
			w[i] += pas * (expected - perceptron_lineaire_classification(x,w,nb) ) * x[i];
		}
	}

	__declspec(dllexport) int perceptron_lineaire_regression(double* x, double* w, int nb) {
		return 0;
	}

}




