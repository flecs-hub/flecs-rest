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

## API overview
Currently the API has one `entities` endpoint that can either return the data for a single entity or entities that match a set of components. To retrieve data for a single entity called "MyEntity", do:

```
http://localhost:8080/entities/MyEntity
```

Which will return something similar to:

```json
{
	"type": [
		["EcsId"],
		["Position"]
	],
	"entity": 86,
	"data": {
		"EcsId": "E1",
		"Position": {
			"x": 30.000000,
			"y": 40.000000
		}
	}
}
```

To return all entities for a given component, do:

```
http://localhost:8080/entities?include=Position
```

Which will return something similar to:

```json
[{
	"type": [
		["EcsId"],
		["Position"],
		["Velocity"]
	],
	"entities": [87, 88],
	"data": {
		"EcsId": ["E2", "E3"],
		"Position": [{
			"x": 10.000000,
			"y": 20.000000
		}, {
			"x": 30.000000,
			"y": 40.000000
		}],
		"Velocity": [{
			"x": 1.000000,
			"y": 2.000000
		}, {
			"x": 3.000000,
			"y": 4.000000
		}]
	}
}, {
	"type": [
		["EcsId"],
		["Position"],
		["Velocity"],
		["Rotation"]
	],
	"entities": [89],
	"data": {
		"EcsId": ["E4"],
		"Position": [{
			"x": 30.000000,
			"y": 40.000000
		}],
		"Velocity": [{
			"x": 3.000000,
			"y": 4.000000
		}],
		"Rotation": [{
			"angle": 0.500000
		}]
	}
}]
```



