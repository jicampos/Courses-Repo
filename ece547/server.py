#!/usr/bin/python

import threading
from socket import *
import random 

class ClientThread(threading.Thread):

	def __init__(self, connectionSocket, addr):
		threading.Thread.__init__(self)
		self.connectionSocket = connectionSocket
		self.addr = addr
		print("New server socket started for {}:{}".format(addr[0], addr[1]))

	def run(self):
		random.shuffle(questions) # shuffle questions for different order
		# sentence = connectionSocket.recv(1024)
		# capitalizedSentence = sentence.upper()
		# self.connectionSocket.send(capitalizedSentence)
		self.connectionSocket.send(questions[0][0])
		self.connectionSocket.close()

serverPort = 12000
serverSocket = socket(AF_INET, SOCK_STREAM)
serverSocket.bind(("", serverPort))
serverSocket.listen(1)
print("The server is ready to recieve")

questions = []
fd = open("quiz.txt")

for line in fd.readlines():
	line = line.rstrip()  # Strips EOL
	arr = line.split(',') # Splits question and answer
	questions.append(arr) 

fd.close()
print(questions[0], type(questions[0]))

while 1:
	connectionSocket, addr= serverSocket.accept()
	newThread = ClientThread(connectionSocket, addr)
	newThread.start()
