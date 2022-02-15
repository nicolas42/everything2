// run in console
// typically functions require callback

const AWS = require('aws-sdk');
const s3 = new AWS.S3();

resp = s3.listBuckets().send(); null
// resp.data

var params = { 
    Bucket: 'bitwise-public',
    Key: 'key.txt',
};
resp = s3.getObject(params).send(); null;
resp.data.Body.toString()

// JSON.stringify(arg,0,4)

