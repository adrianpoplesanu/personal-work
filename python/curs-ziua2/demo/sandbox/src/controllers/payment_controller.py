class JsonResponse():
    def __init__(self, response):
        self.response = response

    def __call__(self):
        return self.response

class HtmlResponse():
    def __init__(self, content):
        self.content = content

    def __call__(self):
        return self.content.upper()

from flask import render_template

class TemplateResponse():
    def __init__(self, template_path, env=None):
        self.template_path = template_path
        self.env = env

    def __call__(self):
        return render_template(self.template_path, **self.env)


class PaymentModel(object):
    def get_all_payment_methods(self):
        # connecteza la db
        # select * from ucs_bma.paymentmethod
        return ['VISA', 'MC', 'AMEX', 'DISC', 'PAYPAL']

class PaymentController(object):
    def __init__(self):
        self.model = PaymentModel()

    def index(self):
        mops = self.model.get_all_payment_methods()
        env = {
            'version': '46.0.3',
            'os': 'windws',
            'mops': mops
        }
        return TemplateResponse("payment.html", env)
        #return HtmlResponse("aaaa")
        #return JsonResponse(env)
