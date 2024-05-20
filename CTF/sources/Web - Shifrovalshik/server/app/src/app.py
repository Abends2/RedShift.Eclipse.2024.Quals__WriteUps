import flask
from flask import Flask
from flask import request
import utils

app = Flask(__name__)


@app.route('/')
def hello_world():
    resp = flask.make_response()
    resp.headers['debug'] = "".join(outcode).encode().hex()
    if request.args.get('password'):
        try:
            deobf = utils.deobf(request.args.get('password'), outcode)
            resp.data = str(eval(deobf))
        except:
            resp.data = "Invalid password!"
    else:
        resp.data = "Enter password!"
    return resp

from utils import obf
key, outcode = obf()
print("ADMIN PASSWORD: ", key)

if __name__ == '__main__':
    app.run()
