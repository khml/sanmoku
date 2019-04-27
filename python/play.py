# -*- coding:utf-8 -*-

import os

from Board import Board, CROSS, CYCLE, turn_color
from Move import choice_move
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
        pos = choice_move(policy, board, random=5)
        if pos is False:
            print("*** Move Choice Error ***")
            exit()
        board.put(pos, color == CROSS)

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
