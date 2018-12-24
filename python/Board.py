# -*- coding:utf-8 -*-

import numpy as np

BOARD_SIZE = 3

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

DRAW = 0
CYCLE_WIN = CYCLE
CROSS_WIN = CROSS

COLOR_RANGE = [CYCLE, CROSS]


class Position:
    def __init__(self, color, pos):
        self._color = color
        self._pos = pos

    @property
    def color(self):
        return self._color

    @property
    def pos(self):
        return self._pos

    @property
    def x(self):
        x = int(self.pos % 3)
        return x

    @property
    def y(self):
        y = int(self.pos / 3)
        return y


class Board:
    def __init__(self):
        self._board = np.zeros((BOARD_SIZE, BOARD_SIZE)).astype(np.int)
        self._bit_borad = np.zeros((BOARD_SIZE, BOARD_SIZE)).astype(np.int)
        self._result = None

    @property
    def board(self):
        return self._board

    @property
    def result(self):
        if self._result is None:
            self.is_finished()
        return self._result

    def _is_any(self, y, x, symbol):
        return self._board[y][x] == symbol

    def _is_empty(self, y, x):
        return self._is_any(y, x, EMPTY)

    def _is_cycle(self, y, x):
        return self._is_any(y, x, CYCLE)

    def _is_full(self):
        is_full = self._bit_borad.sum() >= 9
        if is_full:
            self._finish_flag = DRAW
        return is_full

    def show(self):
        board = self._board.astype(np.str)
        board[board == "{}".format(EMPTY)] = "{}".format(EMPTY_SIGN)
        board[board == "{}".format(CYCLE)] = "{}".format(CYCLE_SIGN)
        board[board == "{}".format(CROSS)] = "{}".format(CROSS_SIGN)
        print(board)

    def is_legal(self, position):
        return self._bit_borad[position.y][position.x] == EMPTY and position.color in COLOR_RANGE

    def _turn_on_bit_board(self, position):
        self._bit_borad[position.y][position.x] = 1

    def _put(self, position):
        self._board[position.y][position.x] = position.color
        self._turn_on_bit_board(position)
        self.is_finished()

    def put(self, position):
        if self.is_finished():
            print("Game is already over.")

        if self.is_legal(position):
            self._put(position)
            self.show()
            return 0
        else:
            print("Illegal input")
            return 1

    def __in_array_check(self, sum_array):
        if CYCLE * 3 in sum_array:
            self._finish_flag = CYCLE_WIN
            return True

        if CROSS * 3 in sum_array:
            self._finish_flag = CROSS_WIN
            return True

        return False

    def __vertical_check(self):
        return self.__in_array_check(self._board.sum(0))

    def __horizontal_check(self):
        return self.__in_array_check(self._board.sum(1))

    def __aslant_check(self):
        array = [
            self._board[0][0] + self._board[1][1] + self._board[2][2],
            self._board[0][2] + self._board[1][1] + self._board[2][0],
        ]
        return self.__in_array_check(array)

    def is_finished(self):
        if self._result is not None:
            return True

        if self.__horizontal_check() or self.__vertical_check() or self._is_full():
            return True

        return False

    def print_result(self):
        if self._finish_flag == DRAW:
            print('Draw')
        elif self._finish_flag == CYCLE_WIN:
            print('{} Win'.format(CYCLE_SIGN))
        elif self._finish_flag == CROSS_WIN:
            print('{} Win'.format(CROSS_SIGN))
        else:
            print('error something wrong.')


class CommandProcessing:
    def __init__(self):
        self.__input_printing = "input = (e.g. o3)"
        self.__numbering_board = np.arange(9).reshape(3, 3)
        self.__input_buf = None

    def show_numbering(self):
        print(self.__numbering_board)

    def get_pos_input(self):
        self.__input_buf = input(self.__input_printing)
        return self._position_processing()

    @property
    def input_buf(self):
        return self.__input_buf

    def _position_processing(self):
        """
        o3 -> [color=o, y=1, x=0]
        :return: list
        """
        try:
            color = Color_str2int[self.__input_buf[0]]
            pos = int(self.__input_buf[1])
            return Position(color, pos)
        except:
            return Position(EMPTY, -1)


def play_mode():
    board = Board()
    command_processor = CommandProcessing()
    command_processor.show_numbering()

    while True:
        position = command_processor.get_pos_input()
        try:
            board.put(position)
            if board.is_finished():
                board.print_result()
                break
        except:
            print('something wrong : {}'.format(command_processor.input_buf))


def main():
    play_mode()


if __name__ == '__main__':
    main()
