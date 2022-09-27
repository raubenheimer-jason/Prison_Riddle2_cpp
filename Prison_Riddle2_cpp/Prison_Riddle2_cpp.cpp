#include <iostream>
#include <iomanip> // setprecision
#include <vector>
#include <algorithm>
#include <ranges>
#include <random>
#include <numeric> // iota
#include <cmath> // pow

#include "Prisoner.h"

const bool random_search{ false }; // set to true to search boxes randomly
const size_t num_sims{ 100000 };

const size_t num_prisoners{ 100 };
const size_t num_boxes{ num_prisoners };
const size_t max_search_boxes{ num_boxes / 2 };

void initialise_boxes(std::vector<size_t>& vec);
void initialise_prisoners(std::vector<Prisoner*>& vec);
void display_boxes(const std::vector<size_t>& vec);
void display_prisoners(const std::vector<Prisoner*>& vec);
bool search_boxes(const std::vector<size_t>& boxes, Prisoner* prisoner);

bool run_sim(const bool random_search);
double sim_master(const bool random_search);

double random_probability();
double loop_probability();

int main()
{
	std::cout << std::boolalpha;

	//double sim_random_probability{ sim_master(true) };
	double sim_loop_probability{ sim_master(false) };

	std::cout << "\nCalculated probabilities:" << std::endl;
	std::cout << "Random search: " << random_probability() << std::endl;
	std::cout << "Loop strategy: " << loop_probability() << std::endl;

	std::cout << "\nAverage success for " << num_sims << " simulations:" << std::endl;
	//std::cout << "Random search: " << sim_random_probability << std::endl;
	std::cout << "Loop strategy: " << sim_loop_probability << std::endl;

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
	{
		//std::cout << i << std::endl;
		p_fail += 1.0 / i;
	}
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

double sim_master(const bool random_search)
{
	std::cout << "====== Starting sim, random_search = " << random_search << " ======" << std::endl;
	double total{}; // total successful runs (where all prisoners found their number)

	for (size_t i{}; i < num_sims; ++i)
	{
		if (i % 1000 == 0)
			std::cout << "Sim: " << i << std::endl;

		if (run_sim(random_search))
			total++;
	}

	std::cout << std::endl;

	double avg{ total / num_sims };
	return avg;
}

bool run_sim(const bool random_search)
{
	// vector of size_t, num_boxes in size, all initialised to 0
	std::vector<size_t> boxes(num_boxes, 0);
	initialise_boxes(boxes);
	// display shuffled boxes
	//display_boxes(boxes);

	// vector of prisoners
	std::vector<Prisoner*> prisoners;
	initialise_prisoners(prisoners);
	// display initialised prisoners
	// display_prisoners(prisoners);

	size_t num_found{};

	if (random_search)
	{
		//// search randomly
		//// loop over each prisoner and search for their number
		//for (auto p : prisoners)
		//{
		//	// if even one prisoner doesnt find their number, there is no point in continuing
		//	if (!search_boxes_random(boxes, p))
		//		break;

		//	num_found++;
		//}
	}
	else
	{
		// search using proposed technique
		// loop over each prisoner and search for their number
		for (auto p : prisoners)
		{
			// if even one prisoner doesnt find their number, there is no point in continuing
			if (!search_boxes(boxes, p))
				break;

			num_found++;
		}
	}

	// Deallocate heap memory
	for (auto p : prisoners)
		delete p;
	prisoners.clear();

	// display prisoners
	//display_prisoners(prisoners);

	return (num_found == num_prisoners);

	//double perc_found{ (static_cast<double>(num_found) / num_prisoners) * 100 };

	//return perc_found;
}

void initialise_boxes(std::vector<size_t>& vec)
{
	// set each value of the vector, starting at 0, and incrementing by 1
	std::iota(vec.begin(), vec.end(), 0);

	// shufle box numbers in boxes vector
	// https://www.youtube.com/watch?v=oW6iuFbwPDg&ab_channel=TopShelfTechnology

	std::random_device rd;
	std::ranges::shuffle(vec, rd);
}

void initialise_prisoners(std::vector<Prisoner*>& vec)
{
	for (size_t i{}; i < num_prisoners; ++i)
	{
		Prisoner* p = new Prisoner{ i, num_prisoners, max_search_boxes };
		vec.push_back(p);
		// need to deallocate this onece the sim is done
	}
}

void display_boxes(const std::vector<size_t>& vec)
{
	size_t i{};
	std::cout << "\n=== Boxes ===" << std::endl;
	for (auto box : vec)
		std::cout << "Box " << i++ << ":\t" << box << std::endl;
}

void display_prisoners(const std::vector<Prisoner*>& vec)
{
	std::cout << "\n=== Prisoners ===" << std::endl;
	std::cout << std::boolalpha;
	for (const auto prisoner : vec)
		prisoner->display();
}

bool search_boxes(const std::vector<size_t>& boxes, Prisoner* prisoner)
{
	bool found{ false };
	while (!found && prisoner->still_boxes_left())
	{
		size_t num_in_box = boxes.at(prisoner->get_box_to_search());
		found = prisoner->search_box(num_in_box);
	}

	return found;
}

//bool search_boxes_random(const std::vector<size_t>& boxes, Prisoner* prisoner)
//{
//	bool found{ false };
//	while (!found && prisoner->still_boxes_left())
//	{
//		size_t num_in_box = boxes.at(prisoner->get_box_to_search());
//		found = prisoner->search_box(num_in_box);
//	}
//
//	return found;
//}