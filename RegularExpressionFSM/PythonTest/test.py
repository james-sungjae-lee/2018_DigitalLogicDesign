def solution(regex):
    if not regex:
        answer = 0
    else:
        answer = stateX(regex)
    return answer

def stateX(regex):
    event = regex[0]
    regex = regex[1:]
    if event == 'x':
        return stateXY(regex)
    elif not regex:
        return 0
    else:
        return stateX(regex)

def stateXY(regex):
    event = regex[0]
    regex = regex[1:]
    if not regex:
        return 0
    if event == 'y':
        return stateA(regex)
    elif event == 'x':
        return stateXY(regex)
    else:
        return stateX(regex)

def stateA(regex):
    event = regex[0]
    regex = regex[1:]
    if not regex:
        return 0
    if event == 'a':
        return stateAB(regex)
    else:
        return stateX(regex)

def stateAB(regex):
    event = regex[0]
    regex = regex[1:]
    if event == 'a':
        return stateAB(regex)
    elif event == 'b':
        return stateB(regex)
    elif not regex:
        return 0
    else :
        return stateX(regex)

def stateB(regex):
    if regex:
        return stateX(regex)
    else:
        return 1

print(solution("xyabyab"))
