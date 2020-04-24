from chase_credentials import UCSChaseCredentials

request = {}
request['BIN'] = '111111'
request['AccountNum'] = '4444444444444448'
request['SecVal'] = '123'
request['ExpDate'] = '0224'
request['Amount'] = '2000'

UCSChaseCredentials.add_chase_credentials(request)

print request
