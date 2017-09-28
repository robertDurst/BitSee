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
  var url = 'https://min-api.cryptocompare.com/data/price?fsym=USD&tsyms=USD,ETH,BTC,XMR,STEEM,DASH,ETC,LSK,ZEC,LTC,FTC';

  // Send request to CryptoCompare
  xhrRequest(url, 'GET', 
    function(responseText) {
      // responseText contains a JSON object with weather info
      var json = JSON.parse(responseText);
      
      // set the variables from the data received
      var ETH = json.USD / json.ETH;
      var BTC = json.USD / json.BTC;
      var XMR = json.USD / json.XMR;
      var STEEM = json.USD / json.STEEM;
      var DASH = json.USD / json.DASH;
      var ETC = json.USD / json.ETC;
      var LSK = json.USD / json.LSK;
      var ZEC = json.USD / json.ZEC;
      var LTC = json.USD / json.LTC;
      var FTC = json.USD / json.FTC;
      
      // create the array
      var cryptoArray = [ETH,BTC,XMR,STEEM,DASH,ETC,LSK,ZEC,LTC];
      cryptoArray = bubbleSort(cryptoArray);
      
      var cLen = cryptoArray.length;
      
      var i;
      
      var labelArray = [];
      
      for (i = 0; i < cLen; i ++){
        switch(cryptoArray[i]){
          case ETH:
            labelArray.push("ETH");
            break;
          case BTC:
            labelArray.push("BTC");
            break;
          case XMR:
            labelArray.push("XMR");
            break;
          case STEEM:
            labelArray.push("STEEM");
            break;
          case DASH:
            labelArray.push("DASH");
            break;
          case ETC:
            labelArray.push("ETC");
            break;
          case ZEC:
            labelArray.push("ZEC");
            break;
          case LTC:
            labelArray.push("LTC");
            break;
          case LSK:
            labelArray.push("LSK");
            break;
          case LSK:
            labelArray.push("FTC");
            break;
          default:  
            labelArray.push("ERROR");
        }   
      }
      
      console.log(cryptoArray[cLen - 3].toString());
      
      // Assemble dictionary using our keys
      var dictionary = {
      'Coin1_Price': cryptoArray[cLen - 1].toFixed(2).toString(),
      'Coin2_Price': cryptoArray[cLen - 2].toFixed(2).toString(),
      'Coin3_Price': cryptoArray[cLen - 3].toFixed(2).toString(),
      'Coin4_Price': cryptoArray[cLen - 4].toFixed(2).toString(),
      'Coin5_Price': cryptoArray[cLen - 5].toFixed(2).toString(),
      'Coin1_Label': labelArray[cLen - 1],
      'Coin2_Label': labelArray[cLen - 2],
      'Coin3_Label': labelArray[cLen - 3],
      'Coin4_Label': labelArray[cLen - 4],
      'Coin5_Label': labelArray[cLen - 5]
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

function bubbleSort(arr){
   var len = arr.length;
   for (var i = len-1; i>=0; i--){
     for(var j = 1; j<=i; j++){
       if(arr[j-1]>arr[j]){
           var temp = arr[j-1];
           arr[j-1] = arr[j];
           arr[j] = temp;
        }
     }
   }
   return arr;
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


