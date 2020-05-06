# flecs-systems-rest
**NOTE: This library currently only works with the bleeding_edge branch of Flecs!**

REST interface for Flecs applications. This module allows introspection of entities through a REST interface. Applications can enable the REST interface by importing the module and instantiating the EcsRestServer component:

```c
ECS_IMPORT(world, FlecsSystemsRest, 0);
ecs_entity_t server = ecs_set(world, 0, EcsRestServer, {port: 8080});
```

## Building
The REST module has the following dependencies:

- https://github.com/flecs-hub/flecs-components-meta
- https://github.com/flecs-hub/flecs-json
- https://github.com/SanderMertens/flecs (checkout bleeding-edge)

To build & run the code either embed the source files of these modules into your project, or use bake (https://github.com/SanderMertens/bake):

```c
git clone https://github.com/SanderMertens/bake
make -C bake/build-$(uname)
bake/bake setup
```

Then clone the repositories in the same directory:
```
git clone https://github.com/flecs-hub/flecs-components-meta
git clone https://github.com/flecs-hub/flecs-json
git clone https://github.com/SanderMertens/flecs (checkout bleeding-edge)
```

And then run bake in that directory:
```
bake
```

To run the entity browser example, do (after building):
```
cd examples/c/entity_browser
bake run
```

