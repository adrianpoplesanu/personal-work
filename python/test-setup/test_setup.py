#from pip._internal.req import parse_requirements
from pip.req import parse_requirements

from os import path

here = path.abspath(path.dirname(__file__))
reqs = parse_requirements(path.join(here, 'requirements.in'), session='fake')
requirements = [str(req.req) for req in reqs]

print (requirements)
