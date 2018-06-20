import re
p = re.compile('x*ya*b')
m = p.match('xyab')
if m:
    print(1)
else:
    print(0)
