from django.http import HttpResponse, JsonResponse
from django.shortcuts import render


class TemplateResponse(HttpResponse):
    def __init__(self, template=None, env=None):
        self.template = template
        self.env = env

    def set_request(self, request=None):
        self.request = request

    def __call__(self):
        return render(self.request, self.template, self.env)