#include <entity_browser.h>

ECS_STRUCT(Position, {
    float x;
    float y;
});

ECS_STRUCT(Velocity, {
    float x;
    float y;
});

ECS_STRUCT(Rotation, {
    float angle;
});

static
bool request_files(
    ecs_world_t *world,
    ecs_entity_t entity,
    EcsHttpEndpoint *endpoint,
    EcsHttpRequest *request,
    EcsHttpReply *reply)
{
    const char *file = request->relative_url;
    char path[1024];

    if (!file || !strlen(file)) {
        file = "index.html";
    }

    sprintf(path, "etc/%s", file);

    FILE *f = fopen(path, "r");
    if (!f) {
        return false;
    } else {
        fclose(f);
    }

    reply->body = strdup(path);
    reply->is_file = true;

    return true;
}

int main(int argc, char *argv[]) {
    /* Create the world, pass arguments for overriding the number of threads,fps
     * or for starting the admin dashboard (see flecs.h for details). */
    ecs_world_t *world = ecs_init_w_args(argc, argv);

    ECS_IMPORT(world, FlecsComponentsMeta, 0);
    ECS_IMPORT(world, FlecsComponentsHttp, 0);
    ECS_IMPORT(world, FlecsSystemsRest, 0);
    ECS_IMPORT(world, FlecsSystemsCivetweb, 0);

    ECS_META(world, Position);
    ECS_META(world, Velocity);
    ECS_META(world, Rotation);

    /* Start REST server */
    ecs_entity_t server = ecs_set(world, 0, EcsRestServer, {port: 8080});

    /* Add endpoint to server for serving up files */
    ecs_entity_t e_files = ecs_new_child(world, server, 0);
        ecs_set(world, e_files, EcsHttpEndpoint, {
            .url = "",
            .action = request_files
        });

    ecs_set(world, ecs_set(world, 0,
        EcsId, {"E1"}),
        Position, {30, 40});

    /* Create a dummy entities for demo data */
    ecs_set(world, ecs_set(world, ecs_set(world, 0,
        EcsId, {"E2"}),
        Position, {10, 20}),
        Velocity, {1, 2});

    ecs_set(world, ecs_set(world, ecs_set(world, 0,
        EcsId, {"E3"}),
        Position, {30, 40}),
        Velocity, {3, 4});

    ecs_set(world, ecs_set(world, ecs_set(world, ecs_set(world, 0,
        EcsId, {"E4"}),
        Position, {30, 40}),
        Rotation, {0.5}),
        Velocity, {3, 4});        

    /* Set target FPS for main loop */
    ecs_set_target_fps(world, 60);
    printf("Application simple_server is running, press CTRL-C to exit...\n");

    /* Run systems */
    while ( ecs_progress(world, 0));

    /* Cleanup */
    return ecs_fini(world);
}
