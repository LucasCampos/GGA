/*
 *     This file is part of GGA
 *
 *     POPS is free software; you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation; either version 3 of the License, or
 *     (at your option) any later version.
 * 
 *     This program is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *     GNU General Public License for more details.
 * 
 *     You should have received a copy of the GNU General Public License
 *     along with this program; if not, write to the Free Software
 *     Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 * 
 * */
#include "../../Population.hpp"
#include "Individual.hpp"

#include <cstdlib>
#include <fstream>

double uni() {return rand()/(double) RAND_MAX;}

int main() {

	Matrix m;

	std::ifstream matrixFile("matrix.dat");

	for (int i=0; i<nPoets; i++) {
		for (int j=0; j<nPoets; j++) {
			int dist;
			matrixFile >> dist;
			m[i][j] = dist;
		}
	}

#ifdef DEBUG
	for (int i=0; i<nPoets; i++) {
		for (int j=0; j<nPoets; j++) {
			int dist;
			std::cout << m[i][j] << " ";
		}
		std::cout << "\n";
	}
#endif

	Mptr dist = std::make_shared<Matrix>(m);

	srand(time(NULL));
	const int N = 3000;
	const double mp = 0.05;
	const int nIter = 1e3;
	std::vector<Tour> ind;
	for (int i=0; i<N; i++) { 
		ind.push_back(Tour(dist));
	}
	Population<Tour> pop(ind,mp);

	for (int i=0; i<nIter; i++){
		pop.MakeNewGen();
	}

	std::vector<double> ans = pop.GetAnswers();
	std::cout << "Best answer was: " << 1/ans[0] << "m" << std::endl;
	std::cout << "In the order: ";
	for (int i=0; i<nPoets; i++) {
		std::cout << names[pop.individuals[0].poets[i]]<< ", ";
	}

	std::cout << std::endl;
}
