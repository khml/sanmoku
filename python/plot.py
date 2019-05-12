# -*- coding:utf-8 -*-

import sys

import numpy as np
import matplotlib.pylab as plt
import matplotlib.animation as animation

from Loggers import get_io_stream_logger, Logger
from Board import Board, CROSS, turn_color, DRAW
from Model import Model, Trainer, choice_move


class Game:
    def __init__(self, logger: Logger = None):
        self._logger = logger or get_io_stream_logger(__name__)
        self._board = Board()
        self._model = Model(27, 18, 9)
        self._color = CROSS
        self._trainer = Trainer(self.model)

    def clear(self):
        self._board = Board()
        self._color = CROSS

    @property
    def board(self):
        return self._board

    @property
    def board_as_mat(self):
        return self.board.as_list.reshape([3, 3])

    @property
    def model(self):
        return self._model

    @property
    def color(self):
        return self._color

    def turn_color(self):
        self._color = turn_color(self.color)

    def _train(self):
        if self.board.result == DRAW:
            self._logger.info("Result is DRAW, do NOT training")
            return False
        loss = self._trainer.train_from_board(self.board)
        return loss

    def one_move(self) -> np.ndarray:
        if self.board.is_finished:
            self._logger.info("Game Finished!")
            self._logger.info("Training Start")
            loss = self._train()
            self._logger.info("Training Finished")
            if loss:
                self._logger.info("Training Loss = {}".format(loss))
            self.clear()
            self._logger.info("Game Start")
            return self.board_as_mat

        policy = self.model.infer(self.board.data(self.color))
        pos = choice_move(policy, self.board, 5)
        if pos is False:
            self._logger.error("*** Inference Error ***")
            sys.exit()
        self.board.put(pos, self.color)
        self.turn_color()
        return self.board_as_mat


def main():
    game = Game()
    fig = plt.figure()

    def update(unused_arg):
        plt.cla()
        board = game.one_move()
        plt.imshow(board, cmap='bwr', vmax=1, vmin=-1)

    anime = animation.FuncAnimation(fig, update, interval=50)
    plt.show()


if __name__ == '__main__':
    main()
