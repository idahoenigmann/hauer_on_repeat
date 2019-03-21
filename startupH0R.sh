#!/bash/bin


### This is the script to start the hauer_on_repeat program on startup
### to add to startup routine, do:
### 	1) sudo crontab -e
###	2) add line "@reboot <path-to-dir>/startupH0R.sh

cd /home/pi/hauer_on_repeat/build

### export GPIO ###
#button GPIO
gpio export 2 in
gpio export 3 in
gpio export 4 in
gpio export 17 in
gpio export 27 in
gpio export 22 in
gpio export 10 in
gpio export 9 in
gpio export 11 in
gpio export 5 in
gpio export 6 in
gpio export 13 in


#led GPIO
gpio export 19 out
gpio export 26 out
gpio export 18 out
gpio export 23 out
gpio export 24 out
gpio export 25 out
gpio export 8 out
gpio export 7 out
gpio export 12 out
gpio export 16 out
gpio export 20 out
gpio export 21 out

gpio -g write 19 1
gpio -g write 26 1
gpio -g write 18 1
gpio -g write 23 1
gpio -g write 24 1
gpio -g write 25 1
gpio -g write 8 1
gpio -g write 7 1
gpio -g write 12 1
gpio -g write 16 1
gpio -g write 20 1
gpio -g write 21 1

#while true
#do
firefox /home/pi/hauer_on_repeat/web/nr0.html &
/home/pi/hauer_on_repeat/build/hauer_on_repeat
#done
