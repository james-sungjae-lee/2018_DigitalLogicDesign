def solution(regex):
    answer = stateX(regex)
    return answer

def stateX(regex):
    if not regex:
        return 0
    token = regex[0]

    if token == 'x':
        regex = regex[1:]
        return stateXY(regex)
    else:
        regex = regex[1:]
        return stateX(regex)

def stateXY(regex):
    if not regex:
        return 0
    token = regex[0]

    if token == 'x':
        regex = regex[1:]
        return stateXY(regex)
    elif token == 'y':
        regex = regex[1:]
        return stateA(regex)
    else:
        regex = regex[1:]
        return stateX(regex)

def stateA(regex):
    if not regex:
        return 0
    token = regex[0]

    if token == 'a':
        regex = regex[1:]
        return stateAB(regex)
    else:
        regex = regex[1:]
        return stateX(regex)

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
        return stateX(regex)

def stateB(regex):
    return 1


print(solution("xyabxyab"))










#
