const http = require('http');
const fs = require('fs');
const express = require('express')
const app = express()
const bodyParser = require('body-parser');
const csvtojson = require("csvtojson");
const XMLHttpRequest = require('xmlhttprequest').XMLHttpRequest;

app.use(express.static('public'))
app.use(bodyParser.urlencoded({ extended: true }));

app.get('/', function (req, res) {


 	fs.readFile('charts.html', function(err, data) {
	    res.writeHead(200, {'Content-Type': 'text/html'});
	    res.write(data);
	    res.end();
	});	

	
  //res.send();
});

app.get('/data', function (req, res) {

	csvtojson()
  	.fromFile("stocks-csv.txt")
  	.then(function(jsonArrayObj){ //when parse finished, result will be emitted here.
     	console.log(jsonArrayObj); 

     	res.send(jsonArrayObj);
   	})

})


app.listen(4000, function () {
	console.log("connected");
})

/*
http.createServer(function (req, res) {
  fs.readFile('charts.html', function(err, data) {
    res.writeHead(200, {'Content-Type': 'text/html'});
    res.write(data);
    res.end();
  });
}).listen(8080);*/
