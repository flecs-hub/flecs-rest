#include <flecs_systems_rest.h>

static
bool endpoint_entities(
    ecs_world_t *world,
    ecs_entity_t entity,
    EcsHttpEndpoint *endpoint,
    EcsHttpRequest *request,
    EcsHttpReply *reply)
{
    char buffer[1024];
    ecs_type_t include = NULL, exclude = NULL;

    if (request->relative_url && strlen(request->relative_url)) {
        /* Request single entity */
        const char *name = request->relative_url;
        ecs_entity_t e = 0;

        /* If name starts with a number, lookup by entity id */
        if (isdigit(name[0])) {
            e = atoi(name);
        } else {
            e = ecs_lookup_fullpath(world, name);
            if (!e) {
                return false;
            }
        }

        reply->body = ecs_entity_to_json(world, e);

    } else {
        /* Request list of matching entities */
        if (ecs_http_get_query_param(
            request->params, "include", buffer, sizeof(buffer)))
        {
            include = ecs_type_from_str(world, buffer);
            if (!include) {
                return false;
            }
        }

        if (ecs_http_get_query_param(
            request->params, "exclude", buffer, sizeof(buffer)))
        {
            exclude = ecs_type_from_str(world, buffer);
            if (!exclude) {
                return false;
            }
        }

        ecs_filter_t filter = {
            .include = include,
            .exclude = exclude
        };

        reply->body = ecs_filter_to_json(world, &filter);
    }

    return true;
}

void SetRestServer(ecs_iter_t *it) {
    ECS_COLUMN(it, EcsRestServer, server_data, 1);
    ECS_COLUMN_COMPONENT(it, EcsHttpServer, 2);
    ECS_COLUMN_COMPONENT(it, EcsHttpEndpoint, 3);

    ecs_world_t *world = it->world;

    int i;
    for (i = 0; i < it->count; i ++) {
        ecs_entity_t server = it->entities[i];

        ecs_set(world, server, EcsHttpServer, {.port = server_data[i].port});
          ecs_entity_t e_entities = ecs_new_w_entity(world, ECS_CHILDOF | server);
            ecs_set(world, e_entities, EcsHttpEndpoint, {
                .url = "entities",
                .action = endpoint_entities,
                .synchronous = true,
                .ctx = NULL
            });
    }
}

void FlecsSystemsRestImport(
    ecs_world_t *world,
    int flags)
{
    ECS_MODULE(world, FlecsSystemsRest);

    ECS_IMPORT(world, FlecsMeta, 0);
    ECS_IMPORT(world, FlecsComponentsHttp, 0);

    ECS_COMPONENT(world, EcsRestServer);
    ECS_SYSTEM(world, SetRestServer, EcsOnSet, EcsRestServer, 
        :flecs.components.http.HttpServer, 
        :flecs.components.http.HttpEndpoint);

    ECS_EXPORT_COMPONENT(EcsRestServer);
}
