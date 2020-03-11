# Sheep and Wolves (Loups et Moutons)

## Requirements
This program requires the fltk library.

#### On Windows
```bash
vcpkg install fltk:<triplet> 
```

#### On Ubuntu
```bash
sudo apt install libfltk1.3-dev 
```

#### On Windows
```bash
sudo pacman -S fltk 
```

## How to build
```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## How to run
```bash
./sheep-and-wolves
```

***Note:** As GIF are loaded from `$PWD`, you need to run the program from its build directory.* 