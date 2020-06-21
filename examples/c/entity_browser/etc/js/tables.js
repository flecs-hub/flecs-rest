
Vue.component('tables', {
    props: ['data', 'query'],
    template: `
      <div class="query">
          <div v-if="data.length">
            <h3>Tables with [{{ query }}]</h3>
          </div>
          <div v-for="table in data" class="ecs-table">
            <table>
              <tr>
                <th>Entity</th>
                <th v-for="component in table.type">
                  <span>
                    {{ component }}
                  </span>
                </th>
              </tr>
              <tr v-for="(entity, i) in table.entities">
                <td>{{ entity }}</td>
                <td v-for="component in table.type">
                  <div v-if="table.data[component]" class="ecs-value">
                      {{ table.data[component][i] }}
                  </div>
                </td>
              </tr>
            </table>
          </div>
      </div>
      `
  });
  