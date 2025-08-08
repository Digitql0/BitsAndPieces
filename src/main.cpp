#include "MiniGL.hpp"
#include "bap.hpp"

int main() {
  MGL_makeWindow(800, 600, "MostlyForces ECS Demo - Circles Only");

  // Entity 1: Player circle, moves right with mild gravity
  Entity Player;
  Player.position = {100, 100};
  Player.color = {255, 0, 255};
  Player.velocity = {1.5f, 0.0f};
  Player.hasCollision = true;
  Player.hasPhysics = true;
  Player.gravity = {0.0f, 0.3f};
  Player.shape.geometry = circle;
  Player.shape.circle.r = 25;
  createEntityFrom(Player);

  // Entity 2: Falling green circle with stronger gravity
  Entity second;
  second.position = {400, 0};
  second.color = {0, 255, 0};
  second.hasCollision = true;
  second.hasPhysics = true;
  second.gravity = {0.0f, 0.8f};
  second.shape.geometry = circle;
  second.shape.circle.r = 30;
  createEntityFrom(second);

  // Entity 3: Fast horizontal blue circle with no gravity
  Entity third;
  third.position = {0, 300};
  third.color = {0, 0, 255};
  third.velocity = {4.0f, 0.0f};
  third.hasCollision = true;
  third.hasPhysics = false;
  third.gravity = {0.0f, 0.0f};
  third.shape.geometry = circle;
  third.shape.circle.r = 20;
  createEntityFrom(third);

  // Enable debug output for entity IDs
  activateDebug(20);

  while (!MGL_windowShouldClose()) {
    MGL_beginDrawing();
    MGL_clearBackground(20, 20, 20);

    ecs_update();
    ecs_render();

    MGL_endDrawing();
  }

  MGL_closeWindow();
  return 0;
}
