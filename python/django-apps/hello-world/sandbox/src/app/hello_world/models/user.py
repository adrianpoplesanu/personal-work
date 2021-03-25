from django.db import models

class User23(models.Model):
    first_name = models.CharField(max_length=30)
    last_name = models.CharField(max_length=30)