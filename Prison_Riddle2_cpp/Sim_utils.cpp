#include "Sim_utils.hpp"


void sim_master(double* loop_prob, double* random_prob, const size_t num_sims, const size_t num_boxes, const size_t num_prisoners, const size_t max_search_boxes)
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
		if (run_sim(false, boxes, num_prisoners, max_search_boxes))
			total_loop++;

		// random
		if (run_sim(true, boxes, num_prisoners, max_search_boxes))
			total_random++;
	}

	std::cout << " sims done." << std::endl;

	// assign values to pointer arguments
	*loop_prob = static_cast<double>(total_loop) / num_sims;
	*random_prob = static_cast<double>(total_random) / num_sims;
}

bool run_sim(const bool random_search, const std::vector<size_t>& boxes, const size_t num_prisoners, const size_t max_search_boxes)
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
