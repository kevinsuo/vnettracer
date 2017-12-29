#!/bin/sh

make -j 4 
make modules  -j 4
make modules_install -j 4
make install



