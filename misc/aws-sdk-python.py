# https://boto3.amazonaws.com/v1/documentation/api/latest/guide/s3-example-creating-buckets.html

import logging
import boto3
from botocore.exceptions import ClientError

s3 = boto3.client('s3')
response = s3.list_buckets()

# json serialize without errors :)
# json.dumps(response, indent=4, sort_keys=True, default=str)
