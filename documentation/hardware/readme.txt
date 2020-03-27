## The hardware components of this exhibit consist of:

* a raspberry Pi 3 B+
* a micro sd card
* micro usb cable
* a keyboard
* 12 12V buttons (with LEDs)
* 12 pieces of yellow coloured cables
* a self-soldered board (with a rainbow cable attached)
* a (touch-screen, but not touch-screen enabled) display
* an amplifier
* two headphones(?)
* a PC power adapter



## These components must be connected / are used as follows:
The micro sd card contains a raspian installation (we changed quite some settings, therefore we recommend using our backup if needed). It must be plugged into the raspberry pi. On the raspberry pi the hauer_on_repeat directory is located in home (~). The pi is powered by the micro usb cable. The / A keyboard can be plugged into one of the four usb ports and then used for changing the configuration.

The self-soldered board is mounted on the inside of the wooden construction by a 3d printed piece (pink). The yellow cables are then looped through the holes in the top starting from 0 (top most; 12 o'clock) to the right (1, 2, 3, ...).

The 12 buttons are fitted in the acrylic plate and srewed in place. Then the yellow cables can be connected to the buttons: each yellow cable has four sub-cables: red, black, green and blue. Connect the red cable to the srew marked with a plus (+) sign, the black cable to the minus (-) sign (opposite the red one). The last two cables can be connected as you wish (one to each screw). These cables are very sensible to changes and are prone to break, so check them regularily.

The display, mounted in the top hole is connected to the pi by a hdmi cable looped through the hole in the bottom of the inner chamber. The two headphones are connected to the amplifier, which in turn connects to the pi by an aux-cable.

The 12 buttons are powered by the self-soldered board. To connect them to power (measuring all connections seems a good idea, before you connect everything up) plug the four pin wide piece (black, yellow, red coloured) of the power adapter into the four pins on the board. The rainbow cable should connect the raspi to the board and is to be connected as to have the L curve face away from the raspi (I believe you can not plug it in the other way round as the plastic cover of the pi would be in the way).

After you start the raspi (and wait a short while) firefox should start and the c++ executable should start automatically.

