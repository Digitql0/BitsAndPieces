#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <cstddef>
#include <cstdint>
#include <unordered_set>
#include "MostlyForces.hpp"

using ScriptFunction = void (*)(uint32_t entityID, void* userData);

enum geometries {
    circle,
    rectangle,
    None
};

typedef struct {
    geometries geometry;
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
    MF_vec2 position;
    MF_vec2 velocity;
    MF_vec2 acceleration;
    MF_vec2 debugAcceleration;
    bool hasPhysics;
    bool hasCollision;
    MF_vec2 gravity;
    MF_vec3 color;
    Shape shape;
    Script script;
} Entity;

constexpr size_t MAX_ENTITIES = 10000;

extern bool debug;
extern uint32_t currentEntities;
extern std::unordered_set<uint32_t> usedIDs;
extern Entity entities[MAX_ENTITIES];
extern int debug_scalar;

#endif
