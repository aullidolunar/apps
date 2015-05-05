gtkmm2-alarm:

My first crossplatform gtkmm2 application alarm.

What you need:
* cmake
* gtkmm2 > 2.20
* SDL2
* SDL2_mixer
* libnotifymm (*nix only)
* Win32 users: I recommend to use mingw32 + msys to build the project

How to build:
* In the project root directory, create a directory called "build"
* run this command:
+ cmake -G "MSYS Makefiles" ..
+ make

Problems? Contact me (See ./CMakeLists.txt)

Version history:

1.0 rev0 (05.05.2015): initial release
