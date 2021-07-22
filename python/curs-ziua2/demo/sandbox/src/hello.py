import sys

sys.path.insert(0, '.')

from flask import Flask
from controllers.payment_controller import PaymentController

app = Flask(__name__, template_folder='views')

@app.route('/')
def hello_world():
    return 'Hello, World!'

@app.route('/payment')
def payment_enpoint_get():
    payment_controller = PaymentController()
    renderer = payment_controller.index()
    return renderer()


# app.reoute(payment_endpoint_get, '/payment')
#
#
# map_routes = {}
#
# app.route(fn, args):
#    map_routes[args] = fn
#    return fn
#
# 5000
#
# do_hadle_request(path='/payment')
#    return map_ruted[path]()
#
#
# @decortor
# def functie(niste parametri)
#
#
# decorator(functie, parametri):
#    start
#    res = functie(parametri)
#    end
#    lof(end=start)
#    return res
#
# @decaorat_flask('ruta')
# def functie(param):
#    map_[ruta] = functie
#    reutrn fucntie
#
