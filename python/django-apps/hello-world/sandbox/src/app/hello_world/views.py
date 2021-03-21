from django.shortcuts import render
#from django.http import HttpResponse, JsonResponse
from core.http import HttpResponse, JsonResponse, TemplateResponse


def index(request):
    """Placeholder index view"""
    env = {'username': 'AdriAnus'}
    print (request.path)
    return render(request, 'index.html', env)

def dispatch(request, path=None):
    #return HttpResponse('this works')
    #return JsonResponse({'status': 'it works'})
    routes = get_routes()
    print (request.path)
    print (path)
    controller = BaseController()
    action = 'index'
    #template = controller.index()
    template = getattr(controller, 'index')()
    template.set_request(request)
    return template()
    #return render(request, template.template, template.env)

def get_routes():
    return [
        ('/home', BaseController, 'home'),
    ]


class BaseController():
    def __init__(self):
        # inject here all the needed stuff
        pass

    def index(self):
        env = {'username': 'AdriAnus'}
        return TemplateResponse(template='index.html', env=env)

    def home(self):
        env = {'username': 'Adrianus-home'}
        return TemplateResponse(template='index.html', env=env)


#class TemplateResponse(HttpResponse):
#    def __init__(self, template=None, env=None):
#        self.template = template
#        self.env = env
#
#    #def render(self):
#    #    render(self.request, self.template, self.env)