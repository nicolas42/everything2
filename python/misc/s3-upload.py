# boto3 https://boto3.amazonaws.com/v1/documentation/api/latest/guide/s3-uploading-files.html
# pyinstaller https://pyinstaller.readthedocs.io/en/stable/usage.html
# configparser error https://stackoverflow.com/questions/49616095/pyinstaller-cannot-see-configparser


# files are copied to bucket/prefix/filepath
input_path = '/users/nick/Downloads/misc'
prefix = 'test/'
bucket = 'nschmidt'


import logging
import boto3
from botocore.exceptions import ClientError

import os
import sys
import threading

s3 = boto3.client('s3')

class ProgressPercentage(object):

    def __init__(self, filename):
        self._filename = filename
        self._size = float(os.path.getsize(filename))
        self._seen_so_far = 0
        self._lock = threading.Lock()

    def __call__(self, bytes_amount):
        # To simplify, assume this is hooked up to a single filename
        with self._lock:
            self._seen_so_far += bytes_amount
            percentage = (self._seen_so_far / self._size) * 100
            sys.stdout.write(
                "\r%s  %s / %s  (%.2f%%)" % (
                    self._filename, self._seen_so_far / 1e6 , self._size / 1e6,
                    percentage))
            sys.stdout.flush()


def upload_file(file_name, bucket, object_name=None):
    """Upload a file to an S3 bucket

    :param file_name: File to upload
    :param bucket: Bucket to upload to
    :param object_name: S3 object name. If not specified then file_name is used
    :return: True if file was uploaded, else False
    """

    # If S3 object_name was not specified, use file_name
    if object_name is None:
        object_name = prefix + file_name

    try:
        response = s3.upload_file(
            file_name, bucket, object_name, 
            Callback=ProgressPercentage(file_name)
        )
    except ClientError as e:
        logging.error(e)
        return False
    return True

if __name__ == "__main__":
    for root, dirs, files in os.walk(input_path, topdown=False):
        for name in files:
            file_path = os.path.join(root, name)
            upload_file(file_path, bucket)
            print('')
        for name in dirs:
            print(os.path.join(root, name))


# upload_file('/users/nick/Downloads/misc/a.dmg', 'bitwise-nick')

