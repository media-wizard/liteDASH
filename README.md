# liteDASH

Motivation is to develop a DASH manifest parser optimized for low resource devices.
It is a single pass MPD parser. Using libexpat to parse mpd buffer - no DOM tree created.

### Build on Ubuntu
1. sudo apt-get install -y expat libexpat-dev
3. cd liteDASH
4. mkdir build
5. cd build
6. cmake ../
7. make

#### Run Sample
./test ../test/live1.mpd

## License

liteDASH is open source available and licensed under MIT license.
