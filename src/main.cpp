#include "MiniGL.hpp"
#include "bap.hpp"

int main() {
  MakeWindow(800, 600, "MostlyForces ECS Demo - Circles Only");

  // Entity 1: Player circle, moves right with mild gravity
  auto Player = createEntity();
  set_position(Player, (Vec2){100, 100});
  set_color(Player, (Vec3){255, 0, 255});
  set_velocity(Player, (Vec2){1.5f, 0.0f});
  add_collision(Player);
  add_physics(Player);
  set_gravity(Player, (Vec2){0.0f, 0.3f});
  Shape playerShape;
  playerShape.shape = circle;
  playerShape.circle.r = 25;
  set_shape(Player, playerShape);

  // Entity 2: Falling green circle with stronger gravity
  auto Circle2 = createEntity();
  set_position(Circle2, (Vec2){400, 0});
  set_color(Circle2, (Vec3){0, 255, 0});
  add_collision(Circle2);
  add_physics(Circle2);
  set_gravity(Circle2, (Vec2){0.0f, 0.8f});
  Shape circle2Shape;
  circle2Shape.shape = circle;
  circle2Shape.circle.r = 30;
  set_shape(Circle2, circle2Shape);

  // Entity 3: Fast horizontal blue circle with no gravity
  auto Circle3 = createEntity();
  set_position(Circle3, (Vec2){0, 300});
  set_color(Circle3, (Vec3){0, 0, 255});
  set_velocity(Circle3, (Vec2){4.0f, 0.0f});
  add_collision(Circle3);
  remove_physics(Circle3);
  // set_gravity(Circle3, (Vec2){0.0f, 0.0f});
  Shape circle3Shape;
  circle3Shape.shape = circle;
  circle3Shape.circle.r = 20;
  set_shape(Circle3, circle3Shape);

  // Enable debug output for entity IDs
  activateDebug(20);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(20, 20, 20);

    ecs_update();
    ecs_render();

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
