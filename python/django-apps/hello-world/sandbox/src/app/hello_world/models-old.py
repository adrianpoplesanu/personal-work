# not using this
from django.db import models

class User45(models.Model):
    first_name = models.CharField(max_length=30)
    last_name = models.CharField(max_length=30)