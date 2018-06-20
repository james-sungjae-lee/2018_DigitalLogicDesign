def solution(regex):
    answer = stateXY(regex)
    return answer

def stateXY(regex):
    if not regex:
        return 0
    token = regex[0]

    if token == 'x':
        regex = regex[1:]
        return stateXY(regex)
    elif token == 'y':
        regex = regex[1:]
        return stateAB(regex)
    else:
        return 0

def stateAB(regex):
    if not regex:
        return 0
    token = regex[0]

    if token == 'a':
        regex = regex[1:]
        return stateAB(regex)
    elif token == 'b':
        regex = regex[1:]
        return stateB(regex)
    else:
        return 0

def stateB(regex):
    if regex:
        return 0
    else:
        return 1

print(solution("xyabb"))











    #
