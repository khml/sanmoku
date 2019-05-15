# Sanmoku

This is Tic Tac Toe Program. Implemented by C++ and Python.

Using [pybind11](https://github.com/pybind/pybind11), generate Python Sanmoku Module.

# Required Library
[LibTorch](https://pytorch.org/get-started/locally/)

# build C++ src
```
# build
$ mkdir build && cd build
$ cmake -DCMAKE_PREFIX_PATH=/absolute/path/to/libtorch ..
$ make 
```

# execute args
```
./sanmoku train TrainingTimes(required) modelPath(option)
./sanmoku play modelPath(option)
```


## train mode
```
$ ./sanmoku train 1

., ., .,
x, ., .,
., ., .,

., ., o,
x, ., .,
., ., .,

., ., o,
x, ., .,
., x, .,

., ., o,
x, ., .,
o, x, .,

., x, o,
x, ., .,
o, x, .,

., x, o,
x, o, .,
o, x, .,

game finished! result : o
Loss = 2.17941
Loss = 2.4002
Loss = 2.02983

```


## play mode
```
$ ./sanmoku play

Pos index
0 1 2
3 4 5
6 7 8
color(o or x),pos (e.g. o3)

input = genx
., ., x,
., ., .,
., ., .,

input = geno
., o, x,
., ., .,
., ., .,

input = o4
., o, x,
., o, .,
., ., .,

input = genx
., o, x,
., o, .,
., x, .,

input = geno
., o, x,
., o, .,
o, x, .,

input = x8
., o, x,
., o, .,
o, x, x,

input = genx
., o, x,
., o, x,
o, x, x,

game finished! result : x

```


# Training Sanmoku Player
Using PyTorch and Sanmoku Module, training Sanmoku Neural Network Player with Python.

c.f. sanmoku/cc/README.md

training Sanmoku Neural Network Player.
```
$ cd sanmoku/python

$ python play.py
```

execute log
```
2019-05-07 11:20:46,153 - INFO - start
2019-05-07 11:20:46,153 - DEBUG - 
. | . | . 
. | X | . 
. | . | .
2019-05-07 11:20:46,154 - DEBUG - 
. | O | . 
. | X | . 
. | . | .
2019-05-07 11:20:46,155 - DEBUG - 
. | O | X 
. | X | . 
. | . | .
2019-05-07 11:20:46,156 - DEBUG - 
O | O | X 
. | X | . 
. | . | .
2019-05-07 11:20:46,157 - DEBUG - 
O | O | X 
X | X | . 
. | . | .
2019-05-07 11:20:46,157 - DEBUG - 
O | O | X 
X | X | . 
O | . | .
2019-05-07 11:20:46,158 - DEBUG - 
O | O | X 
X | X | . 
O | X | .
2019-05-07 11:20:46,159 - DEBUG - 
O | O | X 
X | X | O 
O | X | .
2019-05-07 11:20:46,163 - DEBUG - 
O | O | X 
X | X | O 
O | X | X
2019-05-07 11:20:46,163 - INFO - result is DRAW
2019-05-07 11:20:46,163 - INFO - finish
2019-05-07 11:20:46,163 - INFO - start
2019-05-07 11:20:46,164 - DEBUG - 
. | X | . 
. | . | . 
. | . | .
2019-05-07 11:20:46,164 - DEBUG - 
. | X | . 
. | O | . 
. | . | .
2019-05-07 11:20:46,164 - DEBUG - 
. | X | . 
. | O | X 
. | . | .
2019-05-07 11:20:46,165 - DEBUG - 
. | X | O 
. | O | X 
. | . | .
2019-05-07 11:20:46,165 - DEBUG - 
. | X | O 
. | O | X 
. | X | .
2019-05-07 11:20:46,166 - DEBUG - 
O | X | O 
. | O | X 
. | X | .
2019-05-07 11:20:46,166 - DEBUG - 
O | X | O 
. | O | X 
. | X | X
2019-05-07 11:20:46,167 - DEBUG - 
O | X | O 
O | O | X 
. | X | X
2019-05-07 11:20:46,167 - DEBUG - 
O | X | O 
O | O | X 
X | X | X
2019-05-07 11:20:46,167 - INFO - result is DRAW
2019-05-07 11:20:46,167 - INFO - finish
2019-05-07 11:20:46,167 - INFO - start
2019-05-07 11:20:46,168 - DEBUG - 
. | . | . 
. | X | . 
. | . | .
2019-05-07 11:20:46,168 - DEBUG - 
O | . | . 
. | X | . 
. | . | .
2019-05-07 11:20:46,168 - DEBUG - 
O | . | . 
X | X | . 
. | . | .
2019-05-07 11:20:46,169 - DEBUG - 
O | . | . 
X | X | O 
. | . | .
2019-05-07 11:20:46,170 - DEBUG - 
O | . | . 
X | X | O 
X | . | .
2019-05-07 11:20:46,170 - DEBUG - 
O | . | O 
X | X | O 
X | . | .
2019-05-07 11:20:46,171 - DEBUG - 
O | . | O 
X | X | O 
X | X | .
2019-05-07 11:20:46,171 - DEBUG - 
O | . | O 
X | X | O 
X | X | O
2019-05-07 11:20:46,172 - INFO - result is O win
2019-05-07 11:20:46,172 - INFO - finish
2019-05-07 11:20:46,172 - INFO - start train
2019-05-07 11:20:46,173 - INFO - loss = 2.0868489742279053
2019-05-07 11:20:46,174 - INFO - start
2019-05-07 11:20:46,175 - DEBUG - 
. | . | . 
X | . | . 
. | . | .
2019-05-07 11:20:46,175 - DEBUG - 
. | . | . 
X | . | O 
. | . | .
2019-05-07 11:20:46,177 - DEBUG - 
. | . | . 
X | X | O 
. | . | .
2019-05-07 11:20:46,178 - DEBUG - 
O | . | . 
X | X | O 
. | . | .
2019-05-07 11:20:46,179 - DEBUG - 
O | . | X 
X | X | O 
. | . | .
2019-05-07 11:20:46,179 - DEBUG - 
O | . | X 
X | X | O 
. | O | .
2019-05-07 11:20:46,182 - DEBUG - 
O | X | X 
X | X | O 
. | O | .
2019-05-07 11:20:46,185 - DEBUG - 
O | X | X 
X | X | O 
. | O | O
2019-05-07 11:20:46,185 - DEBUG - 
O | X | X 
X | X | O 
X | O | O
2019-05-07 11:20:46,186 - INFO - result is DRAW
2019-05-07 11:20:46,186 - INFO - finish
```



