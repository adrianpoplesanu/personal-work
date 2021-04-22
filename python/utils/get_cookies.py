import requests

a_session = requests.Session()
a_session.get('https://google.com/')
session_cookies = a_session.cookies
cookies = session_cookies.get_dict()

print(cookies)
