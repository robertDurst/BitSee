// Listen for when the watchface is opened
// Listen for when the watchface is opened

var xhrRequest = function (url, type, callback) {
  var xhr = new XMLHttpRequest();
  xhr.onload = function () {
    callback(this.responseText);
  };
  xhr.open(type, url);
  xhr.send();
};

function locationSuccess() {
  // Construct URL
  var url = 'https://min-api.cryptocompare.com/data/price?fsym=ETH&tsyms=USD,ETH,BTC' 

  // Send request to OpenWeatherMap
  xhrRequest(url, 'GET', 
    function(responseText) {
      // responseText contains a JSON object with weather info
      var json = JSON.parse(responseText);

      var ETH = json.USD
      var BTC = json.USD / json.BTC
      
      console.log("ETH")
      console.log(ETH)
      console.log("BTC")
      console.log(BTC)
      
      // Assemble dictionary using our keys
      var dictionary = {
      'BTC': BTC,
      'ETH': ETH
      };
      
      console.log(BTC)
      console.log(ETH)

      // Send to Pebble
      Pebble.sendAppMessage(dictionary,
      function(e) {
      console.log('Info sent to Pebble successfully!');
      },
      function(e) {
        console.log('Error sending info to Pebble!');
      }
      );
    }      
    );
}

function getWeather() {
   locationSuccess()
}



Pebble.addEventListener('ready', 
  function(e) {
    console.log('PebbleKit JS ready!');

    // Get the initial weather
    getWeather();
  }
);




// Listen for when an AppMessage is received
Pebble.addEventListener('appmessage',
  function(e) {
    console.log('AppMessage received!');
    getWeather();
  }                     
);


