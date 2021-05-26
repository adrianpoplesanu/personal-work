from pip._internal.req import parse_requirements
#from pip.req import parse_requirements

from os import path

here = path.abspath(path.dirname(__file__))
reqs = parse_requirements(path.join(here, 'requirements.in'), session='fake')
# reqs is a generator, i need to persist it in a list
install_reqs = list(reqs)
try:
    requirements = [str(req.req) for req in install_reqs]
except AttributeError:
    requirements = [str(req.requirement) for req in install_reqs]

print (requirements)
