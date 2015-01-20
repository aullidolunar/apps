gtk2-youtubedl 2.0

A tool for downloading videos and extracting audio to MP3. By default the audio is extracted with 256k of bitrate.
Type for more details:

gtk2-youtubedl -h

build utility:
cmake >= 3.0

libraries:
gtk+-2.0 >= 2.24
vte >= 0.24

external:
youtube-dl
ffmpeg

How to build
* Extract contents
* create build directory
* change directory to build
* type: 
+ strings between [] are optional

cmake [-DCMAKE_INSTALL_PREFIX=/usr] ../
make
[sudo] make install

History:
19.01.2015 20:45:05: Remove default output.
14.01.2015 19:08:20: added copy the selected item
30.12.2014 11:06:40: Last release before final version
14.12.2014 13:34:05: Release candidate
27.11.2014 10:36:41: testing release
