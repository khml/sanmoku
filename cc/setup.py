# -*- coding:utf-8 -*-

from glob import glob
import sys
import setuptools

SHARE_OBJECT_NAME_FORMAT = "ccsanmoku.*.so"

so_files = glob(SHARE_OBJECT_NAME_FORMAT)
if len(so_files) <= 0:
    sys.stderr.write("Error!! NOT Exist Any ccsanmoku share object file.\n")
    sys.exit()

so_file = so_files[0]
print("found .so file : {}".format(so_file))

setuptools.setup(
    name='ccsanmoku',
    version="0.1.0",
    author="khmlpy",
    description='Python Sanmoku Module C++ Implement',
    url='https://github.com/khml/sanmoku',
    packages=[''],
    py_modules=[''],
    package_data={'': [so_file]},
    install_requires=['numpy'],
)
