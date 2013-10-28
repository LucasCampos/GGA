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
#ifndef INDIVIDUAL_HPP
#define INDIVIDUAL_HPP

#include <cstdlib>
#include <cmath>
#include <array>

struct BasicIndividual {

	private: 

		double genes;

	public:
		double fitness;


		BasicIndividual(){
		};

		BasicIndividual(double g){
			genes = g;
			fitness = FitFunc();
		};


		std::array<BasicIndividual,4> CrossOver(const BasicIndividual& bi) const {
			const double uni = rand()/(double)RAND_MAX;
			const double mn = std::min(bi.fitness, fitness);
			const double mx = std::max(bi.fitness, fitness);

			const BasicIndividual chlA = BasicIndividual(mx+uni*mn);
			const BasicIndividual chlB = BasicIndividual(mn-uni*mx);

			const std::array<BasicIndividual,4> arr = {chlA,chlB,(*this),bi};

			return arr;
		}

		double FitFunc() const {
			return sin(genes);
		}


		void Mutate(double p) {
			const double uni1 = rand()/(double)RAND_MAX;
			if (uni1<p){
				const double uni2 = rand()/(double)RAND_MAX;
				genes += uni2;
			}
		}
};

#endif
