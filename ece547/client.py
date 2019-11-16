#!/usr/bin/python

from socket import *
serverName = "localhost"
serverPort = 12000
clientSocket = socket(AF_INET, SOCK_STREAM)
clientSocket.connect((serverName, serverPort))

end_connection = ["Congratulations, you played very well!", "Please come again after practice!"]

while 1:
	question = clientSocket.recv(1024)
	if question == end_connection[0] or question == end_connection[1]:
		print(question)
		clientSocket.close()
		break
	print(question)
	sentence = raw_input("reponse: ")
	clientSocket.send(sentence)