#ifndef FLECS_SYSTEMS_REST_H
#define FLECS_SYSTEMS_REST_H

/* This generated file contains includes for project dependencies */
#include "flecs-rest/bake_config.h"

ECS_STRUCT(EcsRestServer, {
    int16_t port;
});

#ifdef __cplusplus
extern "C" {
#endif

typedef struct FlecsRest {
    ECS_DECLARE_COMPONENT(EcsRestServer);
} FlecsRest;

FLECS_REST_API
void FlecsRestImport(
    ecs_world_t *world);

#define FlecsRestImportHandles(handles) \
    ECS_IMPORT_COMPONENT(handles, EcsRestServer); 

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#ifndef FLECS_NO_CPP

namespace flecs {

class rest : public FlecsRest {
public:
    using Server = EcsRestServer;

    rest(flecs::world& world) {
        FlecsRestImport(world.c_ptr());

        flecs::module<flecs::rest>(world, "flecs::rest");

        flecs::component<Server>(world, "Server");
    }
};

}

#endif // FLECS_NO_CPP
#endif // __cplusplus

#endif
