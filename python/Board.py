# -*- coding:utf-8 -*-

import numpy as np

EMPTY = 0
CYCLE = -1
CROSS = 1

CYCLE_SIGN = "o"
CROSS_SIGN = "x"
EMPTY_SIGN = "."

Color_str2int = {
    CYCLE_SIGN: CYCLE,
    CROSS_SIGN: CROSS,
}

DRAW = 1
CYCLE_WIN = 2
CROSS_WIN = 3

COLOR_RANGE = [CYCLE, CROSS]


class Board:
    def __init__(self):
        self.board = np.zeros((3, 3)).astype(np.int)
        self.bit_borad = np.zeros((3, 3)).astype(np.int)
        self.finish_flag = 0

    def is_any(self, y, x, symbol):
        return self.board[y][x] == symbol

    def is_empty(self, y, x):
        return self.is_any(y, x, EMPTY)

    def is_cycle(self, y, x):
        return self.is_any(y, x, CYCLE)

    def is_full(self):
        return self.bit_borad.sum() >= 9

    def show(self):
        board = self.board.astype(np.str)
        board[board == "{}".format(EMPTY)] = "{}".format(EMPTY_SIGN)
        board[board == "{}".format(CYCLE)] = "{}".format(CYCLE_SIGN)
        board[board == "{}".format(CROSS)] = "{}".format(CROSS_SIGN)
        print(board)

    def is_legal(self, y, x):
        return self.bit_borad[y][x] == EMPTY

    def put(self, y, x, color):
        if self.finish_flag > 0:
            print ("Game is already over.")

        if self.is_legal(y, x) and (color in COLOR_RANGE):
            self.board[y][x] = color
            self.bit_borad[y][x] = 1
            self.is_finished()
            self.show()
            return 0
        else:
            print ("Ilegal input")
            return 1

    def __in_array_check(self, sum_array):
        if CYCLE * 3 in sum_array:
            self.finish_flag = CYCLE_WIN
            return CYCLE_WIN

        if CROSS * 3 in sum_array:
            self.finish_flag = CROSS_WIN
            return CROSS_WIN

        return 0

    def __vertical_check(self):
        return self.__in_array_check(self.board.sum(0))

    def __horizontal_check(self):
        return self.__in_array_check(self.board.sum(1))

    def __aslant_check(self):
        arry = [
            self.board[0][0] + self.board[1][1] + self.board[2][2],
            self.board[0][2] + self.board[1][1] + self.board[2][0],
        ]
        return self.__in_array_check(arry)

    def is_finished(self):
        if self.is_full():
            self.finish_flag = DRAW
            return DRAW

        if self.__horizontal_check() > 0:
            return self.finish_flag

        if self.__vertical_check() > 0:
            return self.finish_flag

        if self.__aslant_check() > 0:
            return self.finish_flag

        return 0

    def print_result(self):
        if self.finish_flag == DRAW:
            print ('Draw')
        elif self.finish_flag == CYCLE_WIN:
            print ('{} Win'.format(CYCLE_SIGN))
        elif self.finish_flag == CROSS_WIN:
            print('{} Win'.format(CROSS_WIN))
        else:
            print ('error something wrong.')


if __name__ == '__main__':
    board = Board()
    print (np.arange(9).reshape(3, 3))
    while True:
        cmd = input("input = (e.g. o3)")
        try:
            color = Color_str2int[cmd[0]]
            pos = int(cmd[1])
            y = int(pos / 3)
            x = int(pos % 3)
            board.put(y, x, color)
            if board.finish_flag > 0:
                board.print_result()
                break
        except:
            print ('something wrong : {}'.format(cmd))
