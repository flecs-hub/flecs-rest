
Vue.config.devtools = true;

function request(url, onmsg, onloadend) {
  const Http = new XMLHttpRequest();
  Http.open("GET", url);
  if (onloadend) {
    Http.onloadend = function() { onloadend(Http); };
  }
  Http.send();
  Http.onreadystatechange = (e)=>{
    if (Http.readyState == 4) {
      if (Http.responseText && Http.responseText.length) {
        onmsg(JSON.parse(Http.responseText));
      }
    }
  }
}

var app = new Vue({
  el: '#app',

  methods: {
    query_on_changed(e) {
      this.query = e.query;

      host = this.host;
      let url = "http://" + this.host + "/filter";
      if (this.query && this.query.length) {
        url += "?include=" + this.query;
      }

      request(url, 
        // On message received
        (msg) => {
          this.data = msg;
          this.error = false;
          this.query_ok = this.query;
        }, 
        // On load end
        (Http) => {
          if(Http.status == 404) {
            this.error = true;
          };
        });

      // If the query only contains a single entity, also query for just the
      // entity.
      if (this.query.length && this.query.indexOf(",") == -1) {
        let url = "http://" + this.host + "/entity/" + this.query.trim();
        request(url, (msg) => {
          this.entity = msg;
        });
      } else {
        this.entity = undefined;
      }

      
    }
  },

  data: {
    host: window.location.host,
    query: "",
    query_ok: "",
    error: false,
    data: [],
    entity: undefined
  }
});

