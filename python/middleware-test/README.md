virtualenv sandbox
. sandbox/bin/activate
pip install uwsgi

(sandbox) (192-168-0-106:middleware-test adrianpoplesanu) 13:09:35 $ pip freeze
uWSGI==2.0.19.1

uwsgi --http :9090 --wsgi-file foobar.py

