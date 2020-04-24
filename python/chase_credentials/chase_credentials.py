import json

class MockPan(object):
    config = {
        "ucs_chase_credentials": '''{"username": "AAA", "password": "BBB"}'''
    }

    def get(self, domain, subdomain):
        return self.config[domain + '_' + subdomain]

pan = MockPan()

class UCSChaseCredentials(object):
    @staticmethod
    def add_chase_credentials(request):
        try:
            credentials = json.loads(pan.get('ucs', 'chase_credentials'))
            request['OrbitalConnectionUsername'] = credentials['username']
            request['OrbitalConnectionPassword'] = credentials['password']
        except Exception, e:
            """do not add credentials: either python 2.6 or pan not setup"""
            print e
            pass

