# -*- coding:utf-8 -*-

import sys
from distutils.core import setup

python_version = sys.version[:3].replace(".", "")

setup(
    name='ccsanmoku',
    version='0.1.0',
    description='Python Sanmoku Module C++ Implement',
    author='khmlpy',
    author_email='',
    url='https://github.com/khml/sanmoku',
    install_requires=['numpy'],
    packages=[''],
    py_modules=[''],
    package_data={'': ['ccsanmoku.cpython-{}m-darwin.so'.format(python_version)]},
)
