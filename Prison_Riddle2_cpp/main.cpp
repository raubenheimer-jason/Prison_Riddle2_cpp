/*
Prison Riddle:
YouTube video explaining the riddle:
https://www.youtube.com/watch?v=iSNsgj1OCLA&ab_channel=Veritasium

This code compares the theoretical success rate, of both random
box selection and box selection using the "loop" strategy, with
a simulated output.

The theoretical probabilities are calculated in this main file.

The simulations are performed using a vector of boxes with
random numbers in each vector position. The index of the vector
is the "number on the box" and the value in each vector position
is the "number on the slip inside the box".

The prisoners each have a unique number.
The Prisoner_Random and Prisoner_Loop classes are derrived from
the Prisoner class.
*/

#include <iostream>

//#include "Prisoner_Loop.hpp"
//#include "Prisoner_Random.hpp"
//#include "Prisoner_utils.hpp"
//#include "Box_utils.hpp"
#include "Calc_probabilities.hpp"
#include "Sim_utils.hpp"


// Config constants
const size_t num_sims{ 1000 };
const size_t num_prisoners{ 100 };
const size_t num_boxes{ num_prisoners };
const size_t max_search_boxes{ num_boxes / 2 };


int main()
{
	std::cout << std::boolalpha;

	double sim_loop_prob{}, sim_random_prob{};
	sim_master(&sim_loop_prob, &sim_random_prob, num_sims, num_boxes, num_prisoners, max_search_boxes); // run the sims

	std::cout << "\nCalculated probabilities:" << std::endl;
	std::cout << "Random search: " << random_probability(num_boxes, max_search_boxes, num_prisoners) << std::endl;
	std::cout << "Loop strategy: " << loop_probability(num_boxes) << std::endl;

	std::cout << "\nAverage success for " << num_sims << " simulations:" << std::endl;
	std::cout << "Random search: " << sim_random_prob << std::endl;
	std::cout << "Loop strategy: " << sim_loop_prob << std::endl;

	return 0;
}



