import boto3
import os
import sys
import threading


def download_file_from_s3(s3_url, progress=True):

    s3_client = boto3.client('s3')

    # s3_url = "s3://nschmidt/20201016/funk_overload.mp4"
    path = s3_url.replace("s3://","")
    s3_bucket, s3_object_key = path.split("/", 1)
    local_filename = path.split("/").pop()

    meta_data = s3_client.head_object(Bucket=s3_bucket, Key=s3_object_key)
    total_length = int(meta_data.get('ContentLength', 0))

    downloaded = 0
    def progress(chunk):
        nonlocal downloaded
        downloaded += chunk
        done = int(50 * downloaded / total_length)
        # sys.stdout.write("\r" + str(downloaded) +"/"+ str(total_length))
        sys.stdout.write("\r[%s%s]" % ('=' * done, ' ' * (50-done)) )
        # print("\rDownloading", s3_url, str(downloaded) +"/"+ str(total_length),  str(int(downloaded/total_length*100)) + "%", end="")
        sys.stdout.flush()

    with open(local_filename, 'wb') as local_file:
        s3_client.download_fileobj(s3_bucket, s3_object_key, local_file, Callback=progress)
    print("")


if __name__ == "__main__":
    download_file_from_s3("s3://nschmidt/20201016/funk_overload.mp4")
