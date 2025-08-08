#ifndef ECS_HPP
#define ECS_HPP

#include "utilities.hpp"
#include <cstdint>
#include <unordered_set>

uint32_t getNextFreeID(const std::unordered_set<uint32_t>& set);
uint32_t createEntity();
bool createEntityFrom(Entity& entity);
void destroyEntity(uint32_t id);
void activateDebug(float scalar);

#endif
