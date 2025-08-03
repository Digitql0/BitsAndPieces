#include "bap.hpp"

#include <cstdint>
#include <unordered_set>

#include "MiniGL.hpp"
#include "MostlyForces.hpp"
#include "iostream"

static bool debug = false;
static uint32_t Entities = 0;
std::unordered_set<uint32_t> usedIDs;
Vec2 Position[MAX_ENTITIES];
Vec2 Velocity[MAX_ENTITIES];
Vec2 Acceleration[MAX_ENTITIES];
bool hasPhysics[MAX_ENTITIES];
bool hasCollision[MAX_ENTITIES];
Vec2 Gravity[MAX_ENTITIES];
Vec3 Color[MAX_ENTITIES];
Shape Shapes[MAX_ENTITIES];
Script Scripts[MAX_ENTITIES];
static int debug_scalar = 1;

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
  if (Entities < MAX_ENTITIES) {
    uint32_t id = getNextFreeID(usedIDs);
    Position[id] = getZeroVec2();
    Velocity[id] = getZeroVec2();
    Acceleration[id] = getZeroVec2();
    hasPhysics[id] = false;
    Gravity[id] = getZeroVec2();
    Color[id] = getZeroVec3();
    Shapes[id] = (Shape){None};
    usedIDs.insert(id);
    Entities++;
    return id;
  }
  return MAX_ENTITIES - 1;
}

void destroyEntity(uint32_t id) {
  if (usedIDs.find(id) != usedIDs.end()) {
    usedIDs.erase(id);
    Entities--;
  }
}

void activateDebug(float scalar) {
  debug = !debug;
  debug_scalar = scalar;
}

void set_script(uint32_t id, ScriptFunction f, void* data) {
  if (id < MAX_ENTITIES) {
    Scripts[id].func = f;
    Scripts[id].data = data;
  }
}

void set_shape(uint32_t id, Shape shape) {
  if (id < MAX_ENTITIES) {
    Shapes[id] = shape;
  }
}

void set_position(uint32_t id, Vec2 position) {
  if (id < MAX_ENTITIES) {
    Position[id] = position;
  }
}

void set_velocity(uint32_t id, Vec2 force) {
  if (id < MAX_ENTITIES) {
    Velocity[id] = force;
  }
}

void set_color(uint32_t id, Vec3 color) {
  if (id < MAX_ENTITIES) {
    Color[id] = color;
  }
}

void add_physics(uint32_t id) {
  if (id < MAX_ENTITIES) {
    hasPhysics[id] = true;
  }
}

void remove_physics(uint32_t id) {
  if (id < MAX_ENTITIES) {
    hasPhysics[id] = false;
  }
}

void add_collision(uint32_t id) {
  if (id < MAX_ENTITIES) {
    hasCollision[id] = true;
  }
}

void remove_collision(uint32_t id) {
  if (id < MAX_ENTITIES) {
    hasCollision[id] = false;
  }
}

void set_gravity(uint32_t id, Vec2 force) {
  if (id < MAX_ENTITIES) {
    Gravity[id] = force;
  }
}

void apply_force(uint32_t id, Vec2 force) {
  if (id < MAX_ENTITIES) {
    Acceleration[id] =
        getAddedVec(Acceleration[id], force);  // IDEA: force * mass ?
  }
}

void get_shape(uint32_t id, Shape& s) {
  if (id < MAX_ENTITIES) {
    s = Shapes[id];
  }
}

void ecs_update() {
  ecs_update_scripts();
  ecs_update_physics();
  ecs_check_collisions();
}

void ecs_update_scripts() {
  for (int i = 0; i < MAX_ENTITIES; i++) {
    auto id = i;
    if (usedIDs.find(id) != usedIDs.end()) {
      if (Scripts[id].func) {
        Scripts[id].func(id, Scripts[id].data);
      }
    }
  }
}

void ecs_update_physics() {
  for (int i = 0; i < MAX_ENTITIES; i++) {
    auto id = i;
    if (usedIDs.find(id) != usedIDs.end()) {
      if (hasPhysics[id]) {
        Acceleration[id] = getAddedVec(Acceleration[id], Gravity[id]);
        Velocity[id] = getAddedVec(Velocity[id], Acceleration[id]);
      }
      Position[id] = getAddedVec(Velocity[id], Position[id]);
    }
  }
}

void ecs_check_collisions() {
  for (int i = 0; i < MAX_ENTITIES; i++) {
    auto first = i;
    if (usedIDs.find(first) != usedIDs.end()) {
      for (int j = i + 1; j < MAX_ENTITIES; j++) {
        auto second = j;
        if (usedIDs.find(second) != usedIDs.end()) {
          // Two Objects chosen
          if (hasCollision[first] && hasCollision[second]) {
            ecs_collision(first, second);
          }
        }
      }
    }
  }
}

void ecs_collision(uint32_t first, uint32_t second) {
  shapes first_shape = Shapes[first].shape;
  shapes second_shape = Shapes[second].shape;

  Vec2 first_position = Position[first];
  Vec2 second_position = Position[second];

  bool rvr = first_shape == rectangle && second_shape == rectangle;
  bool rvc = (first_shape == rectangle && second_shape == circle) ||
             (first_shape == circle && second_shape == rectangle);
  bool cvc = first_shape == circle && second_shape == circle;

  if (cvc) {
    Circle c1 =
        (Circle){first_position.x, first_position.y, Shapes[first].circle.r};
    Circle c2 =
        (Circle){second_position.x, second_position.y, Shapes[second].circle.r};
    Vec2 v1 = Velocity[first];
    Vec2 v2 = Velocity[second];

    if (CheckCollisionCircles(c1, c2)) {
      ResponseCollisionCircles(c1, c2, Velocity[first], Velocity[second]);
      if (!hasPhysics[first]) {
        Velocity[first] = v1;
      }
      if (!hasPhysics[second]) {
        Velocity[second] = v2;
      }
    }
  }
}

void ecs_render() {
  for (int i = 0; i < MAX_ENTITIES; i++) {
    auto id = i;
    if (usedIDs.find(id) != usedIDs.end()) {
      auto x1 = 0;
      auto y1 = 0;
      switch (Shapes[id].shape) {
        case rectangle:
          drawRectangle(Position[id].x, Position[id].y, Shapes[id].rectangle.w,
                        Shapes[id].rectangle.h, Color[id].x, Color[id].y,
                        Color[id].z);
          if (debug) {
            x1 = Position[id].x + Shapes[id].rectangle.w / 2;
            y1 = Position[id].y + Shapes[id].rectangle.h / 2;
          }
          break;
        case circle:
          drawCircle(Position[id].x, Position[id].y, Shapes[id].circle.r,
                     Color[id].x, Color[id].y, Color[id].z);
          if (debug) {
            x1 = Position[id].x;
            y1 = Position[id].y;
          }
          break;
        case None:
          break;
      }

      if (debug) {
        auto x2 = x1 + Velocity[id].x * debug_scalar;
        auto y2 = y1 + Velocity[id].y * debug_scalar;
        drawLine(x1, y1, x2, y2, Color[id].x, Color[id].y, Color[id].z);
        x2 = x1 + Acceleration[id].x * debug_scalar;
        y2 = y1 + Acceleration[id].y * debug_scalar;
        drawLine(x1, y1, x2, y2, Color[id].x, Color[id].y, Color[id].z);
        x2 = x1 + Gravity[id].x * debug_scalar;
        y2 = y1 + Gravity[id].y * debug_scalar;
        drawLine(x1, y1, x2, y2, Color[id].x, Color[id].y, Color[id].z);
        std::cout << id << std::endl;
      }
      Acceleration[id] = getZeroVec2();
    }
  }
}
