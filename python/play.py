# -*- coding:utf-8 -*-

import os

import numpy as np

from Board import Board, CROSS, CYCLE, turn_color
from Model import Model


def main():
    model = Model(27, 18, 9)
    board = Board()

    model_path = "model.pt"
    if not os.path.exists(model_path):
        model.save(model_path)
    else:
        model.load(model_path)

    print("start")
    color = CROSS
    while True:
        policy = model.infer(board.data(color == CROSS))
        for pos in np.argsort(policy):
            if board.is_legal(pos):
                board.put(pos, color == CROSS)
                break

        print(board.as_list.reshape(3, 3))
        print()

        if board.is_finished:
            break

        color = turn_color(color)
    print("finish")

    if board.result == CROSS:
        result = "X Win"
    elif board.result == CYCLE:
        result = "O win"
    else:
        result = "DRAW"
    print("result is {}".format(result))


if __name__ == '__main__':
    main()
