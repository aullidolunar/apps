gtk2-youtubedl 1.0

A tool for downloading videos and extracting audio to MP3. By default the audio is extracted with 128K of bitrate.
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
14.12.2014 13:34:05: Release candidate
27.11.2014 10:36:41: testing release
