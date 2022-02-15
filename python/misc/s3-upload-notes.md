boto3 https://boto3.amazonaws.com/v1/documentation/api/latest/guide/s3-uploading-files.html
pyinstaller https://pyinstaller.readthedocs.io/en/stable/usage.html
configparser error https://stackoverflow.com/questions/49616095/pyinstaller-cannot-see-configparser

# time
time python3 s3-upload.py

# make executable
pyinstaller --onefile --hidden-import=configparser s3-upload.py
