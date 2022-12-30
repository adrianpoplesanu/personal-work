class A:
    def __init__(self):
        print ("A")

class B:
    def __init__(self):
        print ("B")

class C(A, B):
    def __init__(self):
        super(C, self).__init__()

C()

print ("====")

class D(B, A):
    def __init__(self):
        super(D, self).__init__()

D()
