from flask import Flask

class Application(object):
    def __init__(self, port):
        self.port = port

    def start(self):
        app = Flask(__name__)

a = Application(12000)
a.start()
