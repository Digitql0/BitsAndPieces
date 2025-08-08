#include "utilities.hpp"

bool debug = false;
uint32_t currentEntities = 0;
int debug_scalar = 1;
std::unordered_set<uint32_t> usedIDs;
Entity entities[MAX_ENTITIES];
