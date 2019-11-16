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
		request = connectionSocket.recv(4096)
		response_proto = "http/1.0"
		response_status = ""
		response_status_text = ""
		response_body = ""

		if("/index.html" in request or "/assignment1.txt" in request):
			response_status = "200"
			response_status_text = "OK"

			# determine which file to send
			read_file = ""
			if("/index.html" in request):
				read_file = "index.html"
			else:
				read_file = "assignment1.txt"

			# open file and append to reponse_body
			fd = open(read_file)
			for line in fd.readlines():
				response_body+=line
			fd.close()
			print("sending requested file...")

		else:
			response_status = "404"
			response_status_text = "Not Found"
			response_body = "<h1>404 File Not Found :(</h1>"

		# header lines
		response_headers = "Connection: close\r\n \
			Server: JICAMPOS/1.0.0 (Ubuntu)\r\n \
			Last-Modified: Friday, 15 Nov 2019 21:19:00 CMT\r\n \
            Content-Length: {}\r\n \
            Content-Type': 'text/html; encoding=utf8\r\n".format(len(response_body))

        # send response
		self.connectionSocket.send("{} {} {}\r\n".format(response_proto, response_status, response_status_text))
		self.connectionSocket.send(response_headers)
		self.connectionSocket.send("\n")
		self.connectionSocket.send(response_body)
		self.connectionSocket.close()


serverPort = 8080
serverSocket = socket(AF_INET, SOCK_STREAM)
serverSocket.bind(("", serverPort))
serverSocket.listen(1)
print("The server is ready to recieve")

while 1:
	connectionSocket, addr= serverSocket.accept()
	newThread = ClientThread(connectionSocket, addr)
	newThread.start()