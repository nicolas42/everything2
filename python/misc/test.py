import boto3
from S3Transfer import *

client = boto3.client('s3', 'ap-southeast-2')
transfer = S3Transfer(client)
# Upload /tmp/myfile to s3://bucket/key
f = 'test.py'
transfer.upload_file(f, 'bitwise-nick', f)
