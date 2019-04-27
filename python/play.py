# -*- coding:utf-8 -*-

import os

from Board import Board, CROSS, CYCLE, turn_color
from Model import Model, choice_move
from Loggers import get_io_stream_logger, Logger


def play_one_game(board: Board, model: Model, logger: Logger):
    color = CROSS
    while True:
        policy = model.infer(board.data(color == CROSS))
        pos = choice_move(policy, board, random=5)
        if pos is False:
            logger.info("*** Move Choice Error ***")
            exit()
        board.put(pos, color == CROSS)

        logger.debug("\n" + str(board.as_list.reshape(3, 3)))

        if board.is_finished:
            break

        color = turn_color(color)


def main():
    model = Model(27, 18, 9)
    board = Board()
    logger = get_io_stream_logger(__name__)

    model_path = "model.pt"
    if not os.path.exists(model_path):
        model.save(model_path)
    else:
        model.load(model_path)

    logger.info("start")
    play_one_game(board, model, logger)
    logger.info("finish")

    if board.result == CROSS:
        result = "X Win"
    elif board.result == CYCLE:
        result = "O win"
    else:
        result = "DRAW"
    logger.info("result is {}".format(result))


if __name__ == '__main__':
    main()
