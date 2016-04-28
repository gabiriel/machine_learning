// stdafx.h : fichier Include pour les fichiers Include système standard,
// ou les fichiers Include spécifiques aux projets qui sont utilisés fréquemment,
// et sont rarement modifiés
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <vector>


std::vector<double*> calcul_w(std::vector<double*>, double*, int);

extern "C"
{
	__declspec(dllexport) int perceptron_lineaire_classification(double*, double*, int);

	__declspec(dllexport) void fit_pla(double*,double*,int,double);

	__declspec(dllexport) void fit_rosenblatt(double*, double*, int, double);

	__declspec(dllexport) int perceptron_lineaire_regression(double*, double*, int);
}
