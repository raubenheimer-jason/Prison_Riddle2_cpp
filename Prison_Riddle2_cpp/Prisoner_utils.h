#pragma once

#include "Prisoner_Loop.h"
#include "Prisoner_Random.h"

void initialise_prisoners_rand(size_t num_prisoners, size_t max_search_boxes, std::vector<Prisoner_Random*>& vec);
void initialise_prisoners_loop(size_t num_prisoners, size_t max_search_boxes, std::vector<Prisoner_Loop*>& vec);
void deallocate_prisoners_rand(std::vector<Prisoner_Random*>& vec);
void deallocate_prisoners_loop(std::vector<Prisoner_Loop*>& vec);

bool search_boxes_loop(const std::vector<size_t>& boxes, Prisoner_Loop* prisoner);
bool search_boxes_random(const std::vector<size_t>& boxes, Prisoner_Random* prisoner);

