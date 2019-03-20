#!/bash/bin


### This is the script to start the hauer_on_repeat program on startup
### to add to startup routine, do:
### 	1) sudo crontab -e
###	2) add line "@reboot <path-to-dir>/startupH0R.sh

cd /home/pi/hauer_on_repeat/build

### export GPIO ###
#button GPIO
echo "2" > /sys/class/gpio/export
echo "3" > /sys/class/gpio/export
echo "4" > /sys/class/gpio/export
echo "17" > /sys/class/gpio/export
echo "27" > /sys/class/gpio/export
echo "22" > /sys/class/gpio/export
echo "10" > /sys/class/gpio/export
echo "9" > /sys/class/gpio/export
echo "11" > /sys/class/gpio/export
echo "5" > /sys/class/gpio/export
echo "6" > /sys/class/gpio/export
echo "13" > /sys/class/gpio/export

#led GPIO
echo "19" > /sys/class/gpio/export
echo "26" > /sys/class/gpio/export
echo "18" > /sys/class/gpio/export
echo "23" > /sys/class/gpio/export
echo "24" > /sys/class/gpio/export
echo "25" > /sys/class/gpio/export
echo "8" > /sys/class/gpio/export
echo "7" > /sys/class/gpio/export
echo "12" > /sys/class/gpio/export
echo "16" > /sys/class/gpio/export
echo "20" > /sys/class/gpio/export
echo "21" > /sys/class/gpio/export

#direction button
echo "in" > /sys/class/gpio/gpio2/direction
echo "in" > /sys/class/gpio/gpio3/direction
echo "in" > /sys/class/gpio/gpio4/direction
echo "in" > /sys/class/gpio/gpio17/direction
echo "in" > /sys/class/gpio/gpio27/direction
echo "in" > /sys/class/gpio/gpio22/direction
echo "in" > /sys/class/gpio/gpio10/direction
echo "in" > /sys/class/gpio/gpio9/direction
echo "in" > /sys/class/gpio/gpio11/direction
echo "in" > /sys/class/gpio/gpio5/direction
echo "in" > /sys/class/gpio/gpio6/direction
echo "in" > /sys/class/gpio/gpio13/direction

#direction led
echo "out" > /sys/class/gpio/gpio19/direction
echo "out" > /sys/class/gpio/gpio26/direction
echo "out" > /sys/class/gpio/gpio18/direction
echo "out" > /sys/class/gpio/gpio23/direction
echo "out" > /sys/class/gpio/gpio24/direction
echo "out" > /sys/class/gpio/gpio25/direction
echo "out" > /sys/class/gpio/gpio8/direction
echo "out" > /sys/class/gpio/gpio7/direction
echo "out" > /sys/class/gpio/gpio12/direction
echo "out" > /sys/class/gpio/gpio16/direction
echo "out" > /sys/class/gpio/gpio20/direction
echo "out" > /sys/class/gpio/gpio21/direction



while true
do
firefox ~/hauer_on_repeat/web/nr0.html &
~/hauer_on_repeat/build/hauer_on_repeat
done
