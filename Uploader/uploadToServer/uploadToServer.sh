#!bin/bash

scp monophonie.mp3 mani@mani.kubu.at:~/Uploader/monophonie.mp3
ssh mani@mani.kubu.at 'cd Uploader; bash complete.sh monophonie.mp3' > erg.txt; java SSH;
