Vue.component('entity', {
    props: ['entity', 'query'],
    methods: {
      on_change: function(e) {
        this.$emit('changed', {query: e.target.value});
      },
      query_class() {
        if (this.error) {
          return "query-error";
        } else {
          return "query-ok";
        }
      }
    },
    template: `
        <div class="ecs-table" v-if="entity">
          <table>
            <tr>
              <th>Entity</th>
              <th v-for="component in entity.type">
                <span v-if="component.length == 1">
                  {{ component[0] }}
                </span>
                <span v-else>
                  {{ component }}
                </span>
              </th>
            </tr>
            <tr>
              <td>{{ entity.entity }}</td>
              <td v-for="component in entity.type">
              <div v-if="entity.data[component[0]]">
                  {{ entity.data[component[0]] }}
              </div>
            </td>            
            </tr>
          </table>
        </div>
      `
  });
  