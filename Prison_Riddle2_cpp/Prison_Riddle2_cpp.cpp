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
#include <vector>
#include <cmath> // pow

#include "Prisoner_Loop.h"
#include "Prisoner_Random.h"
#include "Prisoner_utils.h"
#include "Box_utils.h"


// Config constants
const size_t num_sims{ 1000 };
const size_t num_prisoners{ 100 };
const size_t num_boxes{ num_prisoners };
const size_t max_search_boxes{ num_boxes / 2 };

// Function prototypes
bool run_sim(const bool random_search, const std::vector<size_t>& boxes);
void sim_master(double* loop_prob, double* random_prob);
double random_probability();
double loop_probability();

int main()
{
	std::cout << std::boolalpha;

	double sim_loop_prob{}, sim_random_prob{};
	sim_master(&sim_loop_prob, &sim_random_prob); // run the sims

	std::cout << "\nCalculated probabilities:" << std::endl;
	std::cout << "Random search: " << random_probability() << std::endl;
	std::cout << "Loop strategy: " << loop_probability() << std::endl;

	std::cout << "\nAverage success for " << num_sims << " simulations:" << std::endl;
	std::cout << "Random search: " << sim_random_prob << std::endl;
	std::cout << "Loop strategy: " << sim_loop_prob << std::endl;

	return 0;
}


/*
Calculate the probability of all prisoners finding their number if
they each search using the proposed technique

Longest loop:		1 -> 2 -> 3 -> .... -> 100
Random length loop: 5 -> 99 -> 51 -> ... -> 53

How many permutations could you have?
For the first box: 100 options to choose from
For the second box: 99 options to choose from
Third box: 98...
The last box: 1 option left
-> total permutations = 100*99*98*97*...*1
--> This is the factorial

Therefore we have 100! permutations
-> 100! different ways that you could create a loop of 100 boxes

BUT... some loops repeat.
E.g. 1 -> 2 -> 3 -> 4 -> ... -> 100 -> (back to 1)
		is the same as: 2 -> 3 -> 4 -> ... -> 100 -> 1 -> (back to 2)
So the loop above (100 boxes) can be written 100 different ways, but it is still the same loop

Therefore: the total number of unique loops for 100 boxes is: 100!/100
So... what is the probability that any random arrangement of 100 boxes will contain a loop of length 100:
P(L=100) = # unique loops / total permutations
		 = (100!/100)     / 100!
		 = 1/100
Therefore there is a 1% chance that any random arrangement of 100 boxes will contain a loop of length 100.

This is a general result.
P(L=99) = 1/99, P(L=98) = 1/98, etc.

Therefore the probability that there is a loop longer than 50 (i.e. fail)...
P(L>50) = 1/51 + 1/52 + 1/53 + ... + 1/100
		= 0.69

Therefore there is a 69% chance of failure... or a 31% chance of success...

*/
double loop_probability()
{
	double p_fail{};
	for (size_t i{ 51 }; i <= num_boxes; ++i)
		p_fail += 1.0 / i;
	return 1.0 - p_fail;
}

/*
Calculate the probability of all prisoners finding their number if
they each search randomly
*/
double random_probability()
{
	double single_prisoner_probability{ static_cast<double>(max_search_boxes) / num_boxes };
	double rand_probability{ pow(single_prisoner_probability, num_prisoners) };
	return rand_probability;

}

void sim_master(double* loop_prob, double* random_prob)
{
	std::cout << "Running sims...";

	// Variables that total successful runs (where all prisoners found their number)
	size_t total_loop{};   // for the loop strategy
	size_t total_random{}; // for the random

	for (size_t i{}; i < num_sims; ++i)
	{
		// boxes are initialised here so the random and loop sims have the same conditions
		// vector of size_t, num_boxes in size, all initialised to 0
		std::vector<size_t> boxes(num_boxes, 0);
		initialise_boxes(boxes);
		// display shuffled boxes
		//display_boxes(boxes);

		// loop strategy
		if (run_sim(false, boxes))
			total_loop++;

		// random
		if (run_sim(true, boxes))
			total_random++;
	}

	std::cout << " sims done." << std::endl;

	// assign values to pointer arguments
	*loop_prob = static_cast<double>(total_loop) / num_sims;
	*random_prob = static_cast<double>(total_random) / num_sims;
}

bool run_sim(const bool random_search, const std::vector<size_t>& boxes)
{
	size_t num_found{};

	if (random_search)
	{
		// vector of "random" prisoners
		std::vector<Prisoner_Random*> prisoners_rand;
		initialise_prisoners_rand(num_prisoners, max_search_boxes, prisoners_rand);
		// display initialised prisoners
		// display_prisoners(prisoners);

		// search randomly
		// loop over each prisoner and search for their number
		for (auto p : prisoners_rand)
		{
			// if even one prisoner doesnt find their number, there is no point in continuing
			if (!search_boxes_random(boxes, p))
				break;

			num_found++;
		}

		deallocate_prisoners_rand(prisoners_rand);
	}
	else
	{
		// vector of "random" prisoners
		std::vector<Prisoner_Loop*> prisoners_loop;
		initialise_prisoners_loop(num_prisoners, max_search_boxes, prisoners_loop);
		// display initialised prisoners
		// display_prisoners(prisoners);

		// search using proposed technique
		// loop over each prisoner and search for their number
		for (auto p : prisoners_loop)
		{
			// if even one prisoner doesnt find their number, there is no point in continuing
			if (!search_boxes_loop(boxes, p))
				break;

			num_found++;
		}

		deallocate_prisoners_loop(prisoners_loop);

	}

	return (num_found == num_prisoners);
}
