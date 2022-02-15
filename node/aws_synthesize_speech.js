// The neural engine is more expensive but betterer from memory

const fs = require('fs');
const aws = require('aws-sdk');
aws.config.loadFromPath('/Users/nick/aws_config.json');

const polly = new aws.Polly();


var params = {
  Engine: "neural",
  VoiceId: "Salli",
  OutputFormat: "mp3", 
  SampleRate: "8000", 
  Text: "Happy birthday dickhead", 
  TextType: "text", 
};

polly.synthesizeSpeech(params, function(err, data) {
  if (err) console.log(err, err.stack); // an error occurred
  else     console.log(data);           // successful response
  /*
  data = {
  AudioStream: <Binary String>, 
  ContentType: "audio/mpeg", 
  RequestCharacters: 37
  }
  */

  // successful response
  console.log('SUCCESS\n', data);
  fs.writeFile('gaul.mp3', data.AudioStream, 'binary', function (err) { 
      if (err) console.log(err, err.stack); 
  });

});
