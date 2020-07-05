# flecs-systems-rest
**NOTE: This library currently only works with the bleeding_edge branch of Flecs!**

REST interface for Flecs applications. This module allows introspection of entities through a REST interface. Applications can enable the REST interface by importing the module and instantiating the EcsRestServer component:

```c
ECS_IMPORT(world, FlecsRest, 0);
ecs_entity_t server = ecs_set(world, 0, EcsRestServer, {port: 8080});
```

## Building
The REST module has the following dependencies:

- https://github.com/flecs-hub/flecs-components-http
- https://github.com/flecs-hub/flecs-components-meta
- https://github.com/flecs-hub/flecs-systems-civetweb
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
git clone https://github.com/SanderMertens/flecs --branch bleeding_edge
git clone https://github.com/flecs-hub/flecs-components-http
git clone https://github.com/flecs-hub/flecs-components-meta
git clone https://github.com/flecs-hub/flecs-json
git clone https://github.com/flecs-hub/flecs-systems-civetweb
git clone https://github.com/flecs-hub/flecs-systems-rest
```

And then run bake in that directory:
```
bake
```

To run the entity browser example, do (after building):
```
cd flecs-systems-rest/examples/c/entity_browser
bake run
```

## API overview

### GET /entity
Get data for a single entity.

```
http://localhost/entity/MyEntity
```

Which will return a response something similar to:

```json
{
  "type": ["Name", "Position"],
  "entity": 330,
  "data": {
    "EcsId": {
      "value": "MyEntity"
    },
    "Position": {
      "x": 30.000000,
      "y": 40.000000
    }
  }
}
```

To only return a specific set of components, use the select parameter followed by a comma separated list of components:
```
http://localhost/entity/MyEntity?select=Position
```

Which will return a response similar to:

```json
{
  "type": ["Name", "Position"],
  "entity": 330,
  "data": {
    "Position": {
      "x": 30.000000,
      "y": 40.000000
    }
  }
}
```

If no entity with the specified name is found, a 404 status is returned.

### DELETE /entity
Delete a single entity or component.

To delete an entity, just provide an entity identifier:
```
http://localhost/entity/MyEntity
```

To remove one or more components, use the select parameter followed by a comma separated list of components:
```
http://localhost/entity/MyEntity?select=Position
```

If no entity with the specified name is found, a 404 status is returned.

### POST /entity
Create a new entity with the specified name.

```
http://localhost:8080/entity/MyEntity
```

### PUT /entity
Add one or more components to an entity.

```
http://localhost/entity/MyEntity?select=Position
```

### GET /filter
Get data for entities matching a filter.

To filter on a component, add it to the include parameter which accepts a comma-separated list of components:
```
http://localhost/filter?include=Position
```

Which will return a response similar to:

```json
[{
  "type": ["Name", "Position", "Velocity"],
  "entities": [330, 331],
  "data": {
    "Name": [{
      "value": "E1"
    }, {
      "value": "E2"
    }],
    "Position": [{
      "x": 10.000000,
      "y": 20.000000
    }, {
      "x": 30.000000,
      "y": 40.000000
    }],
    "Velocity": [{
      "x": 1.000000,
      "y": 1.000000
    }, {
      "x": 1.000000,
      "y": 1.000000
    }]
  }
}, {
  "type": ["Name", "Position", "Velocity", ["CHILDOF", "E2"]],
  "entities": [332],
  "data": {
    "Name": [{
      "value": "E3"
    }],
    "Position": [{
      "x": 30.000000,
      "y": 40.000000
    }],
    "Velocity": [{
      "x": 1.000000,
      "y": 1.000000
    }]
  }
}]
```

Note how entities in different types are split up in different sections. The exclude parameter can also be used in the same way as the include parameter.

To only return a specific set of components, use the select parameter followed by a comma separated list of components:

```json
[{
  "type": ["Name", "Position", "Velocity"],
  "entities": [330, 331],
  "data": {
    "Position": [{
      "x": 10.000000,
      "y": 20.000000
    }, {
      "x": 30.000000,
      "y": 40.000000
    }]
  }
}, {
  "type": ["Name", "Position", "Velocity", ["CHILDOF", "E2"]],
  "entities": [332],
  "data": {
    "Position": [{
      "x": 30.000000,
      "y": 40.000000
    }]
  }
}]
```

### GET /scope
Similar to `/filter`, but returns entities for a specific scope.

```
http://localhost/scope/MyScope?include=Position&select=Velocity
```

Which will return a response similar to:

```json
[{
  "type": ["Name", "Position", "Velocity", ["CHILDOF", "MyScope"]],
  "entities": [330, 331],
  "data": {
    "Velocity": [{
      "x": 1.000000,
      "y": 1.000000
    }, {
      "x": 1.000000,
      "y": 1.000000
    }]
  }
}]
```

### /browse
Get information for entities in a scope.

```
http://localhost/browse/MyScope
```

Which will return a response similar to:

```json
[{
  "id": 330,
  "type": ["Name", "Position", "Velocity", ["CHILDOF", "MyScope"]],
  "name": "E1",
  "path": "MyScope.E1",
  "child_count": 0
}, {
  "id": 331,
  "type": ["Name", "Position", "Velocity", ["CHILDOF", "MyScope"]],
  "name": "E2",
  "path": "MyScope.E2",
  "child_count": 1
}]
```

The include parameter can be used to filter entities.


### /info
Get information for a single entity

```
http://localhost/browse/MyScope/E1
```

```json
{
  "id": 330,
  "type": ["Name", "Position", "Velocity", ["CHILDOF", "MyScope"]],
  "name": "E1",
  "path": "MyScope.E1",
  "child_count": 0
}
```
