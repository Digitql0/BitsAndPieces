#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <cstdint>
#include "utilities.hpp"
#include "MiniGL.h"

void ecs_update();
void ecs_render();
void ecs_update_scripts();
void ecs_update_physics();
void ecs_check_collisions();
void ecs_collision(uint32_t first, uint32_t second);

#endif
