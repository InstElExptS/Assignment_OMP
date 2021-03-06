// AssignmentOMPMatx.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include <iostream>
#include<omp.h>

using namespace std;
int n = 3;

float A[3][3] = { {1.0f, 2.0f, 3.0f }, {4.0f, 5.0f, 6.0f }, {7.0f, 8.0f, 9.0f } };
float x[3] = { 1.0f, 2.0f, 3.0f };
float y[3] = { 2.0f, 3.0f, 4.0f };
float temp = 0.0f;

double t1 = 0.0;
double t2 = 0.0;


int main()
{

	t1 = omp_get_wtime();

	
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			y[i] += A[i][j] * x[j];
		}
	}

	

	t2 = omp_get_wtime();
	cout << "[" << y[0] << ", " << y[1] << ", " << y[2] << "]" << " en : " << (t2 - t1) * 1000 << "ms" << " (Normal)" <<endl;

	float y[3] = { 2.0f, 3.0f, 4.0f };
	

	omp_set_num_threads(omp_get_max_threads());
	t1 = omp_get_wtime();

	
	#pragma omp parallel for schedule(static) private(temp)
	for (int i = 0; i < n; i++)
	{
		temp = 0.0f;
		for (int j = 0; j < n; j++)
		{
			temp += A[i][j] * x[j];
		}

		y[i] += temp;
		temp = 0.0f;
	}
	
	t2 = omp_get_wtime();
	cout << "[" << y[0] << ", " << y[1] << ", " << y[2] << "]" << " en : " << (t2 - t1) * 1000 << "ms" << " (Multithreading)" << endl;
}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Conseils pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
