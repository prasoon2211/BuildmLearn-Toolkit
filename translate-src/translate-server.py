import os
import zmq
import translate

context = zmq.Context()
socket = context.socket(zmq.REP)
socket.bind("tcp://*:5555")

while True:
    filename = socket.recv()
    # Qt always has / as the separator. Replace with os.sep
    filename = filename.replace('/', os.sep)
    # handle  the file
    tld_file = str(translate.translate(filename))
    socket.send(tld_file)