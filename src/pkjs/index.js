// Listen for when the watchface is opened
var xhrRequest = function (url, type, callback) {
  var xhr = new XMLHttpRequest();
  xhr.onload = function () {
    callback(this.responseText);
  };
  xhr.open(type, url);
  xhr.send();
};

function getCrypto() {
  // Construct URL
  var url = 'https://min-api.cryptocompare.com/data/price?fsym=USD&tsyms=USD,ETH,BTC,XMR';

  // Send request to CryptoCompare
  xhrRequest(url, 'GET', 
    function(responseText) {
      // responseText contains a JSON object with weather info
      var json = JSON.parse(responseText);
      
      // set the variables from the data received
      var ETH = json.USD / json.ETH;
      var BTC = json.USD / json.BTC;
      var XMR = json.USD / json.XMR;
      
      // Assemble dictionary using our keys
      var dictionary = {
      'BTC': BTC,
      'ETH': ETH,
      'XMR': XMR
      };

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



Pebble.addEventListener('ready', 
  function(e) {
    console.log('PebbleKit JS ready!');

    // Get the initial crypto value
    getCrypto();
  }
);




// Listen for when an AppMessage is received
Pebble.addEventListener('appmessage',
  function(e) {
    console.log('AppMessage received!');
    getCrypto();
  }                     
);


