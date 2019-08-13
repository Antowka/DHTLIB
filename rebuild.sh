#!/bin/bash
make clean && make && ldconfig -v -n . && ln -sf libdht.so.0 libdht.so && export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:. && make test
