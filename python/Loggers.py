# -*- coding:utf-8 -*-

from logging import Logger, getLogger, DEBUG, INFO, WARNING, ERROR, StreamHandler, Formatter


def get_io_stream_logger(name: str, log_level: object = DEBUG,
                         format_str: str = "%(asctime)s - %(levelname)s - %(message)s") -> Logger:
    """
    :param name:
    :param log_level: logging.DEBUG, logging.INFO, and etc.
    :param format_str:
    :return: Logger
    """
    logger = getLogger(name)
    logger.setLevel(log_level)
    handler = StreamHandler()
    handler.setLevel(log_level)
    formatter = Formatter(format_str)
    handler.setFormatter(formatter)
    logger.addHandler(handler)
    return logger
