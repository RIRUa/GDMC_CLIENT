# GDMC_CLIENT

## Installation

- Please install compiler for c++
MinGW

- Please install libcurl in your pc. This is C Library.<br>
[libcurl API](https://curl.se/libcurl/c/)

- Please install make in your pc.<br>
[make for windows](http://gnuwin32.sourceforge.net/packages/make.htm)

- Please install cmake in your pc.<br>
[cmake Homepage](https://cmake.org/install/)

<br>

## How to Run

`##` is comment line.<br>
x,y is position of begining.
size_x, size_z is area size.

### For Windows
```
## go to this directry in your pc
cd /GDMC_CLIENT
## prepare run
make prebuild
cd build
cmake -G "MinGW Makefiles" ..
make
## run
./GDMC_CLIENT x z size_x size_z
```

### For Mac and You have Xcode
```
## go to this directry in your pc
cd /GDMC_CLIENT
## prepare run
make prebuild
cd build
cmake .. -G Xcode
open GDMC_CLIENT.xcodeproj
```
