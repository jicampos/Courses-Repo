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
		incorrect = 0
		questions_asked = 0

		while incorrect < 3 and questions_asked < 10:
			self.connectionSocket.send(questions[questions_asked][0])
			response = self.connectionSocket.recv(1024)	
			# print(response, type(response))
			if response != questions[questions_asked][1]:
				incorrect = incorrect + 1

			questions_asked = questions_asked + 1

		if incorrect == 3:
			self.connectionSocket.send("Please come again after practice!")
			self.connectionSocket.close()
		else:
			self.connectionSocket.send("Congratulations, you played very well!")
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
	# print(arr)
fd.close()

while 1:
	connectionSocket, addr= serverSocket.accept()
	newThread = ClientThread(connectionSocket, addr)
	newThread.start()
