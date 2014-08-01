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

/*
 *
 * This individual finds the routes to Recife's Circuit of Poetry.
 * It is set that the first poet to be visited is Ascenso Ferreira,
 * as it is where most people gather
 * */

#ifndef INDIVIDUAL_HPP
#define INDIVIDUAL_HPP

#include <cstdlib>
#include <cmath>
#include <array>
#include <memory>
#include <algorithm>
#include <limits>
#include <vector>
#include <string>
#include <unistd.h>

enum Poet {

	ASCENSO,
	BANDEIRA,
	CABRAL,
	CAPIBA,
	MOTA,
	PENAFILHO,
	MARIA,
	SCIENCE,
	CARDOZO,
	TRINDADE,
	LUIZGONZAGA,
	LISPECTOR

};

const std::vector<std::string> names = {"Ascenso Ferreira", "Manuel Bandeira", "Joao Cabral", "Capiba", "Mauro Mota", "Pena Filho", "Antonio Maria", "Chico Science", "Joaquim Cardozo", "Solano Trindade", "Luiz Gonzaga", "Clarice Lispector"};

const int nPoets = 12;

typedef std::array<std::array<double,nPoets>,nPoets> Matrix;
typedef std::shared_ptr<Matrix> Mptr;

template< class T> void PrintArray(const T& a) {
	for (int i=0; i<a.size(); i++) 
		std::cout << a[i] << " ";
}

struct Tour {

	private: 

		Mptr dist;

	public:
		double fitness;
		std::array<Poet,nPoets> poets;

		Tour() {
			fitness = std::numeric_limits<double>::max();
		}

		Tour(Mptr distances): dist(distances){
			std::iota(poets.begin(),poets.end(),0);
			std::random_shuffle(poets.begin()+1, poets.end()); //+1 to leave ASCENSO unchanged
			fitness = FitFunc();
		};
		
		Tour(std::array<Poet,nPoets> _poets, Mptr distances): dist(distances),poets(_poets){
			fitness = FitFunc();
		};


		FinishFill(const std::array<Poet,nPoets>& p, std::array<Poet,nPoets>& ch) const {
			for (int i=1; i<nPoets; i++) {
				if (ch[i] == 0){
					bool found = false;
					for (int j=1; !found; j++) {
						/*
#ifdef DEBUG
						std::cout << j <<" " <<  p[j] << " " << std::endl;
						PrintArray(ch);
						std::cout << " | ";
						PrintArray(p);
						std::cout << "\n";
						//sleep(1);
#endif
						*/
						//exit(0);

						//seach for element
						auto ptr = std::find(ch.begin(), ch.end(), p[j]);
						//if there is not, add it
						if (ptr == ch.end()) {
							ch[i] = p[j];
							found = true;
						}
					}
				}
			}
		}

		//Here we will use ordered crossover
		std::array<Tour,4> CrossOver(const Tour& bi) const {

			int begin = rand() % nPoets;
			int end = rand() % nPoets;
			if (begin > end) {
				const int a = begin;
				begin = end;
				end = a;
			}

			std::array<Poet,nPoets> p1,p2;
			for (int i=0; i<nPoets; i++)
				p1[i]=p2[i]=0;

			for (int i=1; i<nPoets; i++) {

				if ((i<begin) || (i>end)) 
					p1[i] = poets[i];
				else
					p2[i] = bi.poets[i];

			}
/*
#ifdef DEBUG
			std::cout << "\n\nArrays Iniciais:\n";
			PrintArray(poets); std::cout << "\n";
			PrintArray(bi.poets); std::cout << "\n\n";
			PrintArray(p1); std::cout << "\n";
			PrintArray(p2); std::cout << "\n";
#endif
*/
			FinishFill(poets, p2);
			FinishFill(bi.poets, p1);


			const Tour chlA(p1, dist);
			const Tour chlB(p2, dist);

			const std::array<Tour,4> arr = {chlA,chlB,(*this),bi};

			return arr;
		}

		double FitFunc() const {
			double distance =0;
			for (int i=0; i<nPoets-1; i++) {
				const int a = poets[i];
				const int b = poets[i+1];
				distance += (*dist)[a][b];

			}
			return 1.0/distance;
		}


		void Mutate(double p) {
			const double uni1 = rand()/(double)RAND_MAX;
			if (uni1<p){
				const int a = rand()%(nPoets-1) + 1;
				const int b = rand()%(nPoets-1) + 1;
				const Poet aux = poets[a];
				poets[a] = poets[b];
				poets[b] = aux;
			}
		}
};

#endif
