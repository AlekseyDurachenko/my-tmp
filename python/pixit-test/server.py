#!/usr/bin/env python3
from bottle import run
from route_img import route_img
from route_create import route_create

run(host='localhost', port=8080, debug=True)
