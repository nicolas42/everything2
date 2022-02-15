aws polly start-speech-synthesis-task \
  --region ap-southeast-2 \
  --endpoint-url "https://polly.ap-southeast-2.amazonaws.com/" \
  --output-format mp3 \
  --output-s3-bucket-name nschmidt-public \
  --voice-id Salli \
  --text file://chapter-3.txt

