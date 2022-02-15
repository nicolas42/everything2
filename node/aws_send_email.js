// You have to verify your email address with amazon before sending emails
//
// SES > Email Addresses > Verify a New Email Address
//


var aws = require('aws-sdk');
aws.config.loadFromPath('/Users/nick/aws_config.json');

var ses = new aws.SES();

var params = {
    Destination: {
        ToAddresses: ["nicolas42@gmail.com"]
    },
    Message: {
        Body: { Text: { Data: "I am the man with no name.  Zapp Brannigan." } },
        Subject: { Data: "subject: hello"}
    },
    Source: "nicolas42@gmail.com"
};


 ses.sendEmail(params, function (err, data) {
    if (err) {
        console.log(err);
        context.fail(err);
    } else {
        console.log(data);
    }
});