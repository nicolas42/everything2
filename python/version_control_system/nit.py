# ipython -i ../nit.py

# Interface 

# init() => creates .nit folder
# commit() => saves unique files
# checkout(version_file) => restores files from version_file

# checkout files are located in the .nit folder
# Their filenames are the date and time in the format ".nit/YYYYMMDD_hhmmss" 
# so they sort properly e.g. .nit/20220126_142431
# would be a commit done on 26 Jan 2022 at 1424 hours and 31 seconds

import os
import sys
import shutil
import hashlib
import datetime


def sha1(filepath):
    # hash the contents of a file to get a unique identifier
    # from https://stackoverflow.com/questions/22058048/hashing-a-file-in-python
    

    # BUF_SIZE is totally arbitrary, change for your app!
    BUF_SIZE = 65536  # lets read stuff in 64kb chunks!

    sha1 = hashlib.sha1()

    with open(filepath, 'rb') as f:
        while True:
            data = f.read(BUF_SIZE)
            if not data:
                break
            sha1.update(data)

    return sha1.hexdigest()


def date_time_string():
    return datetime.datetime.now().strftime("%Y%m%d_%H%M%S")


nit_dir = ".nit"
nit_files_dir = os.sep.join([nit_dir, "files"])

def init():
    for dir in [ nit_dir, nit_files_dir ]:
        if not os.path.exists(dir): 
            print("Creating", dir)
            os.makedirs(dir)


def commit():
    if not os.path.exists(nit_dir):
        print("Repository not initialized.")
        return

    with open(os.sep.join([nit_dir, date_time_string() ]), "w") as output_file:
        for root, dirs, files in os.walk("."):

            if nit_dir in root.split(os.sep): continue

            for file in files: 
                src = os.sep.join([root, file])
                dst = os.sep.join([ nit_files_dir, sha1(src) ]) # create a unique sha1 name from the file contents
                shutil.copyfile(src, dst, follow_symlinks=False)
                output_file.write(dst+'\n')
                output_file.write(src+'\n')
                print(dst,src)



def checkout( version_file ):
    
    if not os.path.exists(version_file):
        print("Version file doesn't exist")
        return
    
    with open(version_file) as f:
        lines = f.read().split("\n")

    i=0
    while i < (len(lines)-1):
        src = lines[i]
        dst = lines[i+1]
        dir = os.path.dirname(dst)
        if not os.path.exists(dir): os.makedirs(dir)
        shutil.copyfile(src, dst, follow_symlinks=False)
        i += 2

