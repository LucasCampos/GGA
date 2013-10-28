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
#ifndef BOOL_IND_HPP
#define BOOL_IND_HPP

#include <cstdlib>
#include <cmath>
#include <array>

struct BoolIndividual {

	private: 
		std::vector<bool> genes;

		int ToInteger() const {
			int res=0;
			int locPow = 1;
			for (int i=0; i<genes.size(); i++){
				res+=genes[i]*locPow;
				locPow*=2;
			}
			return res;
		}

	public:

	double fitness;


	double FitFunc() const {
		int toIn = ToInteger();
		return sin(toIn/10.0);
	}

	BoolIndividual(){
	};

	BoolIndividual(std::vector<bool> g){
		genes = g;
		fitness = FitFunc();
	};


	std::array<BoolIndividual,4> CrossOver(const BoolIndividual& bi) const {

		BoolIndividual chlA = bi;
		BoolIndividual chlB = (*this);

		for (int i=0; i<genes.size(); i++) { 
			if(rand()%2){
				const bool c=chlA.genes[i];
				chlA.genes[i] = chlB.genes[i];
				chlB.genes[i] = c;
			}
		}
		chlA.fitness = chlA.FitFunc();
		chlB.fitness = chlB.FitFunc();

		const std::array<BoolIndividual,4> arr = {chlA,chlB,(*this),bi};

		return arr;
	}

	
	void Mutate(double p) {
		for (int i=0; i<genes.size(); i++) {
			const double uni1 = rand()/(double)RAND_MAX;
			if (uni1<p){
				genes[i] = !genes[i];
			}
		}
	}
};

#endif
