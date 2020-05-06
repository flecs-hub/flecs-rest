
Vue.config.devtools = true;

var app = new Vue({
  el: '#app',

  methods: {
    query_on_changed(e) {
      this.query = e.query;

      const Http = new XMLHttpRequest();
      host = this.host;
      url = "http://" + this.host + "/entities";
      if (this.query && this.query.length) {
        url += "?include=" + this.query;
      }

      Http.open("GET", url);

      Http.onloadend = function() {
        if(Http.status == 404) {
          this.error = true;
        };
      }.bind(this);

      Http.send();
      Http.onreadystatechange = (e)=>{
        if (Http.readyState == 4) {
          if (Http.responseText && Http.responseText.length) {
            this.data = JSON.parse(Http.responseText);
            this.error = false;
          }
        }
      }
    }
  },

  data: {
    host: window.location.host,
    query: "",
    error: false,
    data: []
  }
});

