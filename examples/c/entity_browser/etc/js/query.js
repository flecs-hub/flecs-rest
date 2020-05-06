
Vue.component('query', {
    props: ['error'],
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
      <div class="query">
          <p><img src="images/flecs.png"></p>
          <p>
          <input :class="query_class()" v-on:keyup="on_change" size="50">
          </input>
          </p>
      </div>
      `
  });
  