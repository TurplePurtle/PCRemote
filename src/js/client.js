
var methods = {
  1: "google",
  2: "song",
};

function request(method, url, callback, data) {
  var xhr = new XMLHttpRequest();
  xhr.onload = callback;
  xhr.open(method, url);
  xhr.send(data);
}

function ack(e) {
  console.log("Sent data to Pebble.");
}

function nack(e) {
  console.log("Failed to send data to Pebble.");
}

function sendReady() {
  Pebble.sendAppMessage({ status: 0 });
}

function sendMessage(body) {
  request("POST", "http://192.168.1.109:8080/", function(e) {
    console.log("== Received request response: ==\n" + this.responseText);
    try {
      var response = +this.responseText;
    	Pebble.sendAppMessage({
        status: response,
      }, ack, nack);
    } catch (err) {
      console.log(err.message);
    }
  }, body);
}

// Called when JS is ready
Pebble.addEventListener("ready", function(e) {
  console.log("JS client listening.");
  sendReady();
});
												
// Called when incoming message from the Pebble is received
Pebble.addEventListener("appmessage", function(e) {
  var index = e.payload.status;
  if (index === 0) {
    return;
  }
  var method = methods[e.payload.status];
  if (method) {
    console.log("Received method: " + index + " -> " + method);
    sendMessage(JSON.stringify({ method: method }));
  } else {
    console.log("Method not found: " + index);
  }
});
