# -*- coding:utf-8 -*-

import argparse
import os
import shutil


def parse_command_line_args():
    parser = argparse.ArgumentParser(description='generate MANIFEST.in')

    parser.add_argument('ccsammoku_path', help='path to ccsanmoku.cpython shared object')
    args = parser.parse_args()
    return args


def main():
    args = parse_command_line_args()
    ccsammoku_path = args.ccsammoku_path

    if not os.path.exists(ccsammoku_path):
        print("not exist file : " + ccsammoku_path)
        exit(-1)

    filename = os.path.basename(ccsammoku_path)
    dst_path = os.path.join("sammoku", filename)
    shutil.copy2(ccsammoku_path, dst_path)

    with open("MANIFEST.in", "w") as f:
        f.write("include " + dst_path)


if __name__ == '__main__':
    main()
