global index
global inputString
index = 0
inputString = "abbbbc"

def START():
    event = inputString.index
    global index
    index = index + 1
    if event == 'a':
        return stateA()
    elif event == '':
        print("end")
        return 0
    else :
        return START()

def stateA():
    event = inputString.index
    global index
    index = index + 1
    if event == 'b':
        return stateB()
    elif event == '':
        print("end")
        return 0
    else :
        return START()

def stateB():
    event = inputString.index
    global index
    index = index + 1
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
