from bottle import route, abort, static_file, request

@route('/api/create')
def route_create():
    if not request.query.card_count:
        abort(400, "bad request")

    return "create game %s" % (10,)
