# CC Sanmoku Module

Python Sanmoku Module implemented by C++

using [pybind11](https://github.com/pybind/pybind11)
```
- cc/
    |- pybind11/ (need to git clone https://github.com/pybind/pybind11.git)
    |- CMakeLists.txt
    |- PyBoard.cpp
    |- README.md

```

### How to Build CC Sanmoku Module
```
$ pwd # path/to/sannoku/cc
$ mkdir build
$ cd build

# if you use Python Version X.Y, 
# use flag -DPYBIND11_PYTHON_VERSION=X.Y
# e.g. if you use 3.6
$ cmake -DPYBIND11_PYTHON_VERSION=3.6 ..

$ make
```

### install
```
# copy so file to currentDir, XY is PythonX.Y
# cp build/ccsanmoku.cpython-XYm-darwin.so .
# e.g. if you use 3.6
cp build/ccsanmoku.cpython-36m-darwin.so .
$ python setup.py install
```
