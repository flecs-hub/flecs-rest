#ifndef FLECS_SYSTEMS_REST_H
#define FLECS_SYSTEMS_REST_H

/* This generated file contains includes for project dependencies */
#include "flecs-rest/bake_config.h"

#ifdef __cplusplus
extern "C" {
#endif

ECS_STRUCT(EcsRestServer, {
    int16_t port;
});

typedef struct FlecsRest {
    ECS_DECLARE_COMPONENT(EcsRestServer);
} FlecsRest;

void FlecsRestImport(
    ecs_world_t *world);

#define FlecsRestImportHandles(handles) \
    ECS_IMPORT_COMPONENT(handles, EcsRestServer); 

#ifdef __cplusplus
}
#endif

#endif
