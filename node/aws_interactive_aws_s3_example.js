// This script should be run in the console

// Typically these kinds of functions require callback 
// but here we're just examining response data (resp.data ...) 
// manually after it arrives at our computer

const AWS = require('aws-sdk');

AWS.config.loadFromPath('/Users/nick/aws_config.json');


const s3 = new AWS.S3();

resp = s3.listBuckets().send(); null
// resp.data


var params = { 
    Bucket: 'nschmidt-public',
    Key: 'funwebsite/files/owlhat.gif',
};
resp = s3.getObject(params).send(); null;
// resp.data.Body 


const fs = require('fs');
var data = resp.data.Body  
fs.writeFile('owlhat.gif', data, 'binary', function(err){console.log('omg')});





//         Misc
// ------------------------
// a.toString()
// JSON.stringify(a,0,4)

