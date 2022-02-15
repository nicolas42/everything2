print("usage: python3 text-to-speech.py <filename>")


import boto3
import sys

polly_client = boto3.Session(profile_name="default").client('polly')

filename = sys.argv[1]


f = open(filename)
data = f.read()
f.close()

chunk_size = 3000

num_parts = int(len(data) / chunk_size)

for part in range(num_parts):
    offset = part * chunk_size
    chunk = data[offset: offset + chunk_size]

    response = polly_client.synthesize_speech(
                    Engine='neural',
                    VoiceId='Salli',
                    OutputFormat='mp3', 
                    Text = chunk)

    filename = str(part).zfill(4)+'.mp3'
    print(filename)

    f = open(filename, 'wb')
    f.write(response['AudioStream'].read())
    f.close()

