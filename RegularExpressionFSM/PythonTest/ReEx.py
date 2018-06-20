def START():
    event = input()
    return UNLOCKED(event)

def UNLOCKED(event):
    if event == "device locked":
        print("Device is Locked!")
        event = input()
        return LOCKED(event)

def LOCKED(event):
    if event == "pin entered":
        print("Device is Unlocked !")
        event = input()
        return UNLOCKED(event)

START()
