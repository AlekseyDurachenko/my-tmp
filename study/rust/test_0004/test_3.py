#!/usr/bin/evn python
from ctypes import cdll
lib = cdll.LoadLibrary("embed/target/release/libembed.so")
lib.process()
print("done!")
