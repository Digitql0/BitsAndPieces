#include "system.hpp"

void ecs_update() {
  ecs_update_scripts();
  ecs_update_physics();
  ecs_check_collisions();
}

void ecs_update_scripts() {
  for (int i = 0; i < MAX_ENTITIES; i++) {
    auto id = i;
    if (usedIDs.find(id) != usedIDs.end()) {
      if (entities[id].script.func) {
        entities[id].script.func(id, entities[id].script.data);
      }
    }
  }
}

void ecs_update_physics() {
  for (int i = 0; i < MAX_ENTITIES; i++) {
    auto id = i;
    if (usedIDs.find(id) != usedIDs.end()) {
      if (entities[id].hasPhysics) {
        entities[id].acceleration =
            MF_getAddedVec(entities[id].acceleration, entities[id].gravity);
        entities[id].velocity =
            MF_getAddedVec(entities[id].velocity, entities[id].acceleration);
      }
      entities[id].position =
          MF_getAddedVec(entities[id].velocity, entities[id].position);
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
          if (entities[first].hasCollision && entities[second].hasCollision) {
            ecs_collision(first, second);
          }
        }
      }
    }
  }
}

void ecs_collision(uint32_t first, uint32_t second) {
  geometries first_shape = entities[first].shape.geometry;
  geometries second_shape = entities[second].shape.geometry;

  MF_vec2 first_position = entities[first].position;
  MF_vec2 second_position = entities[second].position;

  bool rvr = first_shape == rectangle && second_shape == rectangle;
  bool rvc = (first_shape == rectangle && second_shape == circle) ||
             (first_shape == circle && second_shape == rectangle);
  bool cvc = first_shape == circle && second_shape == circle;

  if (cvc) {
    MF_circle c1 = (MF_circle){first_position.x, first_position.y,
                               entities[first].shape.circle.r};
    MF_circle c2 = (MF_circle){second_position.x, second_position.y,
                               entities[second].shape.circle.r};
    MF_vec2 v1 = entities[first].velocity;
    MF_vec2 v2 = entities[second].velocity;

    if (MF_checkCollisionCircles(c1, c2)) {
      MF_responseCollisionCircles(c1, c2, entities[first].velocity,
                                  entities[second].velocity);
      if (!entities[first].hasPhysics) {
        entities[first].velocity = v1;
      }
      if (!entities[second].hasPhysics) {
        entities[second].velocity = v2;
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
      switch (entities[id].shape.geometry) {
        case rectangle:
          MGL_drawRectangle(
              entities[id].position.x, entities[id].position.y,
              entities[id].shape.rectangle.w, entities[id].shape.rectangle.h,
              entities[id].color.x, entities[id].color.y, entities[id].color.z);
          if (debug) {
            x1 = entities[id].position.x + entities[id].shape.rectangle.w / 2;
            y1 = entities[id].position.y + entities[id].shape.rectangle.h / 2;
          }
          break;
        case circle:
          MGL_drawCircle(entities[id].position.x, entities[id].position.y,
                         entities[id].shape.circle.r, entities[id].color.x,
                         entities[id].color.y, entities[id].color.z);
          if (debug) {
            x1 = entities[id].position.x;
            y1 = entities[id].position.y;
          }
          break;
        case None:
          break;
      }

      if (debug) {
        auto x2 = x1 + entities[id].velocity.x * debug_scalar;
        auto y2 = y1 + entities[id].velocity.y * debug_scalar;
        MGL_drawLine(x1, y1, x2, y2, entities[id].color.x, entities[id].color.y,
                     entities[id].color.z);
        x2 = x1 + entities[id].acceleration.x * debug_scalar;
        y2 = y1 + entities[id].acceleration.y * debug_scalar;
        MGL_drawLine(x1, y1, x2, y2, entities[id].color.x, entities[id].color.y,
                     entities[id].color.z);
        x2 = x1 + entities[id].gravity.x * debug_scalar;
        y2 = y1 + entities[id].gravity.y * debug_scalar;
        MGL_drawLine(x1, y1, x2, y2, entities[id].color.x, entities[id].color.y,
                     entities[id].color.z);
        std::cout << id << std::endl;
      }
      entities[id].acceleration = MF_getZeroVec2();
    }
  }
}
