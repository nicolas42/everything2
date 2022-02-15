ffmpeg \
-i $1 \
-i $2 \
-map 0:v:0 -map 1:a:0 ${1%.*}out.mp4
