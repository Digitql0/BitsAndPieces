#include "entity.hpp"

void set_entity(uint32_t id, Entity entity) {
  if (id < MAX_ENTITIES) {
    entities[id] = entity;
  }
}

void get_entity(uint32_t id, Entity& entity) {
  if (id < MAX_ENTITIES) {
    entity = entities[id];
  }
}

void set_script(uint32_t id, ScriptFunction f, void* data) {
  if (id < MAX_ENTITIES) {
    entities[id].script.func = f;
    entities[id].script.data = data;
  }
}

void set_shape(uint32_t id, Shape shape) {
  if (id < MAX_ENTITIES) {
    entities[id].shape = shape;
  }
}

void set_position(uint32_t id, MF_vec2 position) {
  if (id < MAX_ENTITIES) {
    entities[id].position = position;
  }
}

void set_velocity(uint32_t id, MF_vec2 force) {
  if (id < MAX_ENTITIES) {
    entities[id].velocity = force;
  }
}

void set_color(uint32_t id, MF_vec3 color) {
  if (id < MAX_ENTITIES) {
    entities[id].color = color;
  }
}

void add_physics(uint32_t id) {
  if (id < MAX_ENTITIES) {
    entities[id].hasPhysics = true;
  }
}

void remove_physics(uint32_t id) {
  if (id < MAX_ENTITIES) {
    entities[id].hasPhysics = false;
  }
}

void add_collision(uint32_t id) {
  if (id < MAX_ENTITIES) {
    entities[id].hasCollision = true;
  }
}

void remove_collision(uint32_t id) {
  if (id < MAX_ENTITIES) {
    entities[id].hasCollision = false;
  }
}

void set_gravity(uint32_t id, MF_vec2 force) {
  if (id < MAX_ENTITIES) {
    entities[id].gravity = force;
  }
}

void apply_force(uint32_t id, MF_vec2 force) {
  if (id < MAX_ENTITIES) {
    entities[id].acceleration = MF_getAddedVec(entities[id].acceleration,
                                               force);  // IDEA: force * mass ?
  }
}

void get_shape(uint32_t id, Shape& s) {
  if (id < MAX_ENTITIES) {
    s = entities[id].shape;
  }
}
