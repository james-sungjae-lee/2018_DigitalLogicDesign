def START():
    event = input()
    if event == 'a':
        return stateA()
    elif event == '':
        print("end")
        return 0
    else :
        return START()

def stateA():
    event = input()
    if event == 'b':
        return stateB()
    elif event == '':
        print("end")
        return 0
    else :
        return START()

def stateB():
    event = input()
    if event == 'c':
        return stateC()
    elif event == 'b':
        return stateB()
    elif event == '':
        print("end")
        return 0
    else:
        return START()

def stateC():
    print("Regular Expression Complete!")
    return 1

START()
