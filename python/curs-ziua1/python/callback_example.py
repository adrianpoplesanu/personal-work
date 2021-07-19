def login():
   return '<login></login>'

def price():
   return '<price></price>'

#rp = ResponseHandler()

request_map = {
   '/login.php': login,
   '/products/price': price
}

def handle_response(endpoint):
    if endpoint not in request_map:
        return '404 - not found'
    else:
        return request_map[endpoint]()

print handle_response('/login.php')
print handle_response('/products/price')
print handle_response('/iauhjadhguadfg')
