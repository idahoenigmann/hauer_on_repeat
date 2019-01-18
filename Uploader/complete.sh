#!bin/bashls

echo "Selected mp3: " ${1}
echo "Selected pdf: " ${2}

#create a jpg out of the pdf
convert -density 300 ${2} pic.jpg
mogrify -crop 2150x400+250+0 pic.jpg
convert pic.jpg -resize 1920x1080  pic.jpg
convert pic.jpg -extent 1920x1080 -background white pic.jpg

#create the video
ffmpeg -y -loop 1 -i pic.jpg -i ${1} -vcodec libx264 -vf 'scale=640:trunc(ow/a/2)*2' -shortest -acodec aac -strict experimental -vb 1024k -minrate 1024k -maxrate 1024k -bufsize 1024k -ar 44100 -vf format=yuv420p  output.mp4

#upload the video
java -classpath ../Uploader/ Test output.mp4

#remove
rm output.mp4
rm pic.jpg
