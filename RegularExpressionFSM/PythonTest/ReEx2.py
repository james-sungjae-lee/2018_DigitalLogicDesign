def START():
    event = input()
    if event == "a":
        return stateA()
    else:
        return stateB()

def stateA():
    print("State A")

def stateB():
    print("State B")

START()
