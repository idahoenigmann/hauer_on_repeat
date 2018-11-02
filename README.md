# Hauer On Repeat #

## Prerequisites ##

* googletest (gtest)
* lilypond
* firefox
* timidity++
* vlc

## Additional ##

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
The first path specifies where the SoundFont files (FloidR3_GM.sf2) are located.

The second line specifies the SoundFont you want to use.
