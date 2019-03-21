#!bin/bash

scp monophonie_and_chords.mp3 mani@mani.kubu.at:~/Uploader/monophonie.mp3
ssh mani@mani.kubu.at 'cd Uploader; bash complete.sh monophonie.mp3' > erg.txt; java -classpath ../Uploader/uploadToServer/ SSH;
