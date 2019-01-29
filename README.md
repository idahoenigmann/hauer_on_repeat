# Hauer On Repeat #

## What is twelve tone music? ##
Twelve tone music is a concept founded by Josef Matthias Hauer, that
creates music from random numbers.

To generate twelve tone music you follow an algorithm which takes numbers
as an input and outputs the corresponding music.

For more information on twelve tone music read [this](twelve_tone_music.md).

## Exhibition Landesausstellung 2019 ##
This is the source code for the hauer_on_repeat exhibit that will be showcased at
the Niederösterreichische Landesausstellung 2019.

The exhibit is created by students from HTL Wiener Neustadt in collaboration
with Josef Matthias Hauer Musikschule and the Landesausstellung 2019 team.

## How does the hauer_on_repeat exhibit work? ##
The user can select the twelve numbers by activating twelve sensors
in any order. A raspberry pi will then create a Monophony from these numbers,
display the notes on a display, play the music and upload an mp3 of the
music to a social media platform. Each tune will also be stored in a
database.

## Prerequisites ##

* googletest (gtest)
* lilypond
* firefox
* timidity++
* vlc

## Additional ##

### References ###

#### GPIO Code from ####
http://hertaville.com/introduction-to-accessing-the-raspberry-pis-gpio-in-c.html

### Installation guides: ###

#### gtest ####
Installation guide to gtest on Ubuntu [here](https://www.eriksmistad.no/getting-started-with-google-test-on-ubuntu/)

#### lilypond ####

LilyPond Download can be found [here](http://lilypond.org/unix.html)

#### vlc ####

```shell
sudo apt-get install vlc
```

#### timidity++ ####

If you are using Ubuntu:

```shell
sudo apt-get install timidity
```

If you prefer Manjaro:

```shell
pacman -S timidity++
```

If you have a SoundFont preinstalled skip the rest.

Else:

```shell
pacman -S soundfont-fluid
```
To get the SoundFont into Timidity edit the config file /etc/timidity++/timidity.cfg and add
```shell
dir /usr/share/soundfonts/
soundfont FluidR3_GM.sf2
```
The first path specifies where the SoundFont files (FluidR3_GM.sf2) are located.

The second line specifies the SoundFont you want to use.
