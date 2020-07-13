#include <simple_server.h>

ECS_STRUCT(Position, {
    float x;
    float y;
});

ECS_STRUCT(Velocity, {
    float x;
    float y;
});

int main(int argc, char *argv[]) {
    /* Create the world, pass arguments for overriding the number of threads,fps
     * or for starting the admin dashboard (see flecs.h for details). */
    ecs_world_t *world = ecs_init_w_args(argc, argv);

    ECS_IMPORT(world, FlecsMeta);
    ECS_IMPORT(world, FlecsRest);
    ECS_IMPORT(world, FlecsSystemsCivetweb);

    ECS_META(world, Position);
    ECS_META(world, Velocity);

    /* Start server */
    ecs_set(world, 0, EcsRestServer, {.port = 8080});

    /* Create a dummy entities for demo data */
    ecs_set(world, ecs_set(world, ecs_set(world, 0,
        EcsName, {"E1"}),
        Position, {10, 20}),
        Velocity, {1, 2});

    ecs_set(world, ecs_set(world, ecs_set(world, 0,
        EcsName, {"E2"}),
        Position, {30, 40}),
        Velocity, {3, 4});

    /* Set target FPS for main loop */
    ecs_set_target_fps(world, 60);

    printf("Application simple_server is running, press CTRL-C to exit...\n");

    /* Run systems */
    while ( ecs_progress(world, 0));

    /* Cleanup */
    return ecs_fini(world);
}
