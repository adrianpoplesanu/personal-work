var app = new Vue({ 
    el: '#app',
    data: {
        message: 'Hello Vue!',
        title: 'Harry Poker and the Phylosopher Deuces'
    }
});

var example1 = new Vue({
  el: '#example-1',
  data: {
    counter: 0
  },
  methods: {
    test: function (event) {
        this.counter += 5;
    }
  }
});
