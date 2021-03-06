// AssignmentOMP.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include <iostream>
#include<omp.h>

using namespace std;

int n = 10000000;

double deltaX = 1.0 / double(n);
double integral = 0.0;
double t1 = 0.0;
double t2 = 0.0;

double fcalc(int i)
{
	return 4.0 / (1.0 + pow((double(i)*deltaX), 2));
}

int main()
{
	t1 = omp_get_wtime();
	for (int i = 0; i < n; i++)
	{
		integral = integral + (fcalc(i) + fcalc(i + 1)) * deltaX / 2.0;
	}
	t2 = omp_get_wtime();
	cout << integral << " en : " << (t2 - t1) * 1000 << "ms" << " (Normal)" << endl;

	//We reset integral
	integral = 0.0;

	omp_set_num_threads(omp_get_max_threads());
	t1 = omp_get_wtime();
	#pragma omp parallel for reduction(+: integral)
	for (int i = 0; i < n; i++)
	{
		integral = integral + (fcalc(i) + fcalc(i + 1)) * deltaX / 2.0;
	}
	#pragma omp barrier
	t2 = omp_get_wtime();
	cout << integral << " en : " << (t2 - t1) * 1000 << "ms" << " (Multithreading)"<<endl;
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
