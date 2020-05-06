#ifndef FLECS_SYSTEMS_REST_H
#define FLECS_SYSTEMS_REST_H

/* This generated file contains includes for project dependencies */
#include "flecs-systems-rest/bake_config.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct EcsRestServer {
    int16_t port;
} EcsRestServer;

typedef struct FlecsSystemsRest {
    ECS_DECLARE_COMPONENT(EcsRestServer);
} FlecsSystemsRest;

void FlecsSystemsRestImport(
    ecs_world_t *world,
    int flags);

#define FlecsSystemsRestImportHandles(handles) \
    ECS_IMPORT_COMPONENT(handles, EcsRestServer); 

#ifdef __cplusplus
}
#endif

#endif
