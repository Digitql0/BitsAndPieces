#include "ecs.hpp"

uint32_t getNextFreeID(const std::unordered_set<uint32_t>& set) {
  static uint32_t nextID = 0;
  for (uint32_t i = nextID; i < MAX_ENTITIES; ++i) {
    if (set.find(i) == set.end()) {
      nextID = i + 1;
      return i;
    }
  }
  // fallback to 0 if wraparound needed
  for (uint32_t i = 0; i < nextID; ++i) {
    if (set.find(i) == set.end()) {
      nextID = i + 1;
      return i;
    }
  }
  return MAX_ENTITIES - 1;  // fallback if none available
}

uint32_t createEntity() {
  if (currentEntities < MAX_ENTITIES) {
    uint32_t id = getNextFreeID(usedIDs);

    Entity new_entity;
    new_entity.position = MF_getZeroVec2();
    new_entity.velocity = MF_getZeroVec2();
    new_entity.acceleration = MF_getZeroVec2();
    new_entity.hasPhysics = false;
    new_entity.gravity = MF_getZeroVec2();
    new_entity.color = MF_getZeroVec3();
    new_entity.shape = (Shape){None};
    entities[id] = new_entity;

    usedIDs.insert(id);
    currentEntities++;
    return id;
  }
  return MAX_ENTITIES - 1;
}

bool createEntityFrom(Entity& entity) {
  if (currentEntities < MAX_ENTITIES) {
    uint32_t id = getNextFreeID(usedIDs);

    entities[id] = entity;
    entities[id].id = id;

    usedIDs.insert(id);
    currentEntities++;
    return true;
  }
  return false;
}

void destroyEntity(uint32_t id) {
  if (usedIDs.find(id) != usedIDs.end()) {
    usedIDs.erase(id);
    currentEntities--;
  }
}

void activateDebug(float scalar) {
  debug = !debug;
  debug_scalar = scalar;
}
