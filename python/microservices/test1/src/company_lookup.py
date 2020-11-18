import requests

api_key = 'insert api password here'

cif = '13548146'

url = "https://api.openapi.ro/api/companies/{0}".format(cif)
headers = {'x-api-key': api_key}
response = requests.get(url, headers=headers)

print (response.text)
