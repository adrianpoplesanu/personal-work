def add_mime_headers(headers):
    headers['MIME-type'] = 'json'
    headers['Content-size'] = 104
    return headers

def add_api_headers(headers):
    headers['api-token'] = '2983742983dskfjash2983742kjsdbf'

def build_headers():
    headers = {
       'username': 'aaa',
       'password': 'bbb'
    }

    add_mime_headers(headers)
    add_api_headers(headers)

    return headers


print build_headers()