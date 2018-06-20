

def solution(regex):
    import re
    m = re.match('x*ya*b',regex)
    if m:
        return 1
    else:
        return 0

print(solution("yb"))
