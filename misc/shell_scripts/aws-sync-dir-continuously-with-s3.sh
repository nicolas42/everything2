

#dir=/Users/nick2/Yafoo/
#s3dir=s3://yafoo/

dir=$0
s3dir=$1

mkdir ~/.nick/
ls -lR $dir > ~/.nick/old

while true; do

#test
#touch yay4 
ls -lR $dir > ~/.nick/new

DIFF=$(diff ~/.nick/old ~/.nick/new) 
if [ "$DIFF" != "" ] 
then
    cp ~/.nick/new ~/.nick/old
    echo "The directory was modified"
    echo $DIFF
    aws s3 sync $dir $s3dir
fi

sleep 1;
done

