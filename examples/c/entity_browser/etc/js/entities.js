
Vue.component('entities', {
    props: ['data'],
    template: `
      <div class="query">
          <div v-for="table in data" class="ecs-table">
            <table>
              <tr>
                  <th>Entity</th>
                  <th v-for="component in table.type">
                      {{ component }}
                  </th>
              </tr>
              <tr v-for="(entity, i) in table.entities">
                  <td>{{ entity }}</td>
                  <td v-for="component in table.type">
                      <div v-if="table.data[component]">
                          {{ table.data[component][i] }}
                      </div>
                  </td>
              </tr>
            </table>
          </div>
      </div>
      `
  });
  