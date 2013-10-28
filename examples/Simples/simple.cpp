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

double uni() {return rand()/(double) RAND_MAX;}

int main() {

	srand(time(NULL));
	const int N = 500;
	const double mp = 0.001;
	const int nIter = 1e3;
	std::vector<BasicIndividual> ind;
	for (int i=0; i<N; i++) { 
		ind.push_back(BasicIndividual(uni()));
	}
	Population<BasicIndividual> pop(ind,mp);

	for (int i=0; i<nIter; i++)
		pop.MakeNewGen();

	std::vector<double> ans = pop.GetAnswers();
	std::cout << "Best answer was: " << ans[0] << " of: " << std::endl;
	for (int i=0; i<N; i++)
		std::cout << ans[i] << " ";
	std::cout << std::endl;


}
