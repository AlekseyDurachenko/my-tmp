from consts import PENGUINARIUM_IMG_PATH
from bottle import route, abort, static_file
from os import getenv

@route('/img/<n:int>')
def route_img(n):
    if n < 0:
        abort(404, "Not found")

    img_filename = "%s.jpg" % (n, )
    img_root_path = getenv(PENGUINARIUM_IMG_PATH, None)
    if img_root_path is None:
        print("environment variable %s is not set" % (PENGUINARIUM_IMG_PATH, ))
        abort(404, "Not found")

    return static_file(img_filename, root=img_root_path)
