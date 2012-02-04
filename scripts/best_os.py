#!/usr/bin/python3
import random

def r(x):
        if isinstance(x, tuple):
                return r(random.choice(x))
        if isinstance(x, list):
                return ''.join(map(r, x))
        return str(x)

q = [("ГНУ", "ЖМУ", "ПНУ"), "/", \
        ("П","Л"), ("и","ы","у","я","е","ей","ю","юй","а","ай"), ("н","п"), \
        ("у","а","е","и","ай","ю","я"), ("кс","ксь","пс","псь","с","сь","ц","х"),
        " —— лучшая ОС!"]

print(r(q))

