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



## Request to change the code before run

1. Please calculate the center coordinate of our area `(x, z)`
2. Please open file, `main.cpp`
3. Please re-write just like below code.

past
```
WN::Vec3 center = WN::Vec3(0,220,0);
```

re-writed
```
WN::Vec3 center = WN::Vec3(x,220,z);
```

4.Please save it.

*I appliciate your changing!!*

<br>

## How to Run

`##` is comment line.
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
