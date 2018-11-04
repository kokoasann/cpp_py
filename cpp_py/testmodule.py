import modu
import Sim

def multiply(a,b):
    print("Will compute", a, "times", b)
    c = 0
    for i in range(0, a):
        c = c + b
    return c
def function(a,c = 1):
    b =0
    for i in range(50):
        b += a*5*i/c
    print(b)
    return b

def xint(a):
    x = 2
    return x

def thiking(a):
    return int(modu.atack())

def tess():
    print(Sim.p1v())

if __name__ == "__main__":
    function(2,7)
