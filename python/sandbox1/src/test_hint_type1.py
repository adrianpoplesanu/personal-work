from typing import Optional

class Status:
    type = 5

def generate_status(default_to_null=False) -> Optional[Status]:
    if default_to_null:
        return None
    s = Status()
    s.type = 77
    return s

result1 = generate_status()
print (result1.type)

result2 = generate_status(default_to_null=True)
print (result2)
