#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "MostlyForces.hpp"
#include "utilities.hpp"
#include <cstddef>
#include <cstdint>

void set_entity(uint32_t id, Entity entity);
void get_entity(uint32_t id, Entity& entity);
void set_script(uint32_t id, ScriptFunction f, void* data = nullptr);
void set_shape(uint32_t id, Shape shape);
void set_position(uint32_t id, MF_vec2 position);
void set_velocity(uint32_t id, MF_vec2 force);
void set_color(uint32_t id, MF_vec3 color);
void add_physics(uint32_t id);
void remove_physics(uint32_t id);
void add_collision(uint32_t id);
void remove_collision(uint32_t id);
void set_gravity(uint32_t id, MF_vec2 force);
void apply_force(uint32_t id, MF_vec2 force);
void get_shape(uint32_t id, Shape& s);

#endif
