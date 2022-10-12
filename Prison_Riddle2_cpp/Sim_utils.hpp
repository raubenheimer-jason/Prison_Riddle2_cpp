#pragma once

#include <iostream>
#include <vector>

#include "Box_utils.hpp"
#include "Prisoner_Loop.hpp"
#include "Prisoner_Random.hpp"
#include "Prisoner_utils.hpp"

void sim_master(double* loop_prob, double* random_prob, const size_t num_sims, const size_t num_boxes, const size_t num_prisoners, const size_t max_search_boxes);
bool run_sim(const bool random_search, const std::vector<size_t>& boxes, const size_t num_prisoners, const size_t max_search_boxes);
