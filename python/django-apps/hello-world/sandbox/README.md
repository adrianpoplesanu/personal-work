# starter django app

virtualenv sandbox

optional
python3 -m venv sandbox

pip install -r requirements.txt

cd sandbox/src

django-admin startproject helloworld

python manage.py runserver

pentru crearea tabelelor:
python manage.py migrate --run-syncdb
https://stackoverflow.com/questions/25771755/django-operationalerror-no-such-table
