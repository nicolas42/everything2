
const AWS = require('aws-sdk');
const fs = require('fs');


AWS.config.loadFromPath('/Users/nick/aws_config.json');
const s3 = new AWS.S3();

var obj = { 
    Bucket: 'nschmidt-public',
    Key: 'funwebsite/files/owlhat.gif',
};

s3.getObject(obj, function(err, data) {
    // https://docs.aws.amazon.com/AWSJavaScriptSDK/latest/AWS/S3.html#getObject-property

    if (err) {
        console.log('MISERABLE FAILURE\n', err, err.stack); // an error occurred
        return;
    }

    // successful response
    console.log('SUCCESS\n', data);
    fs.writeFile('owlhat.gif', data.Body, 'binary', function (err) { 
        if (err) console.log(err, err.stack); 
    });

})


