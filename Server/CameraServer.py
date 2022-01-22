#!/usr/bin/python

import cv2, imutils, socket
import numpy as np
import time
import base64

from threading import Thread

BUFF_SIZE = 65536 # UDP VIDEO PACKET SIZE
server_socket = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
server_socket.setsockopt(socket.SOL_SOCKET,socket.SO_RCVBUF,BUFF_SIZE)
host_name = socket.gethostname()
host_ip = '172.20.10.10'#  socket.gethostbyname(host_name)
port = 50000
socket_address = (host_ip,port)
server_socket.bind(socket_address)
print('(UDP-Video): Listening at:',socket_address)
   
vid = cv2.VideoCapture('LiveDetectionPi.avi') # put in 0 for webcam, or 'videoFileName.mp4' to pick

def sendCameraFeed():
	while True:
		msg,client_addr = server_socket.recvfrom(BUFF_SIZE)
		print('(UDP-Video): Got connection from: ',client_addr)
		WIDTH=400
		while (vid.isOpened()): 
			try:
				_,frame = vid.read()
				print("checking for shape")
				frame = imutils.resize(frame,width=WIDTH)
				encoded,buffer = cv2.imencode('.jpg',frame,[cv2.IMWRITE_JPEG_QUALITY,80])
				message = base64.b64encode(buffer)
				server_socket.sendto(message,client_addr)
			except AttributeError:
				print("shape not found")

sendCameraFeed()



		