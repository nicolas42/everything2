cd $(dirname $0) 
aws s3 sync . s3://yafoo/
echo 'Done'

