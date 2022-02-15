mkdir frames
ffmpeg -i $1 -vf fps=1 frames/thumb%04d.jpg -hide_banner
