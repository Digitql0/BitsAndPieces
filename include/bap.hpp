#ifndef BAP_HPP
#define BAP_HPP

#include "MostlyForces.hpp"
#include "MiniGL.hpp"
#include "unordered_set"
#include <cstdint>

using ScriptFunction = void (*)(uint32_t entityID, void* userData);

enum shapes {
    circle,
    rectangle,
    None
};

typedef struct {
    shapes shape;
    union {
        struct { float r; } circle;
        struct { float w; float h; } rectangle;
    };
} Shape;

typedef struct {
    ScriptFunction func = nullptr;
    void* data = nullptr;
} Script;

typedef struct {
    uint32_t id;
    Vec2 position;
    Vec2 velocity;
    Vec2 acceleration;
    Vec2 debugAcceleration;
    bool hasPhysics;
    bool hasCollision;
    Vec2 gravity;
    Vec3 color;
    Shape shape;
    Script script;
} Entity;

constexpr size_t MAX_ENTITIES = 10000;

uint32_t getNextFreeID(const std::unordered_set<uint32_t>& set);

uint32_t createEntity();
bool createEntityFrom(Entity& entity);
void destroyEntity(uint32_t id);
void activateDebug(float scalar);
void set_entity(uint32_t id, Entity entity);
void get_entity(uint32_t id, Entity& entity);
void set_script(uint32_t id, ScriptFunction f, void* data = nullptr);
void set_shape(uint32_t id, Shape shape);
void set_position(uint32_t id, Vec2 position);
void set_velocity(uint32_t id, Vec2 force);
void set_color(uint32_t id, Vec3 color);
void add_physics(uint32_t id);
void remove_physics(uint32_t id);
void add_collision(uint32_t id);
void remove_collision(uint32_t id);
void set_gravity(uint32_t id, Vec2 force);
void apply_force(uint32_t id, Vec2 force);
void get_shape(uint32_t id, Shape& s);
void ecs_update();
void ecs_render();
void ecs_update_scripts();
void ecs_update_physics();
void ecs_check_collisions();
void ecs_collision(uint32_t first, uint32_t second);

#endif // BAP_HPP
