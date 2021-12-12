import RPi.GPIO as GPIO
from socket import *
import random
import time
from datetime import datetime


button_pin = 15
led_pin = 4

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
GPIO.setup(button_pin, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
GPIO.setup(led_pin, GPIO.OUT)
GPIO.setup(26,GPIO.OUT)
GPIO.setup(20,GPIO.OUT)
GPIO.setup(16,GPIO.OUT)

light_on = False
GPIO.output(26,False)
GPIO.output(20,False)
GPIO.output(16,False)

port = 9999
BUFSIZE = 512

now = datetime.now()
nowDatetime = f"{now.year}-{now.month}-{now.day}/{now.hour}:{now.minute}:{now.day}"

on_off = ['ON', 'OFF']

sock = socket(AF_INET, SOCK_STREAM)
sock.bind(('', port)) #자신의 주소 사용
sock.listen(1) #최대 대기 틀라이언트 수
print("Waiting for clients...")

#클라이언트의 연결 요청을 받는다
c_sock, (r_host, r_port) = sock.accept()
print('connected by', r_host, r_port)

global stamp
stamp = -1

def button_callback(channel):
	global light_on
	global stamp
	
	now_ = int(time.time())
	
	if light_on == False:
		GPIO.output(led_pin, 1)
		GPIO.output(26,True)
		GPIO.output(20,True)
		GPIO.output(16,True)
		
		if stamp != -1:stamp = now_ - stamp
		on_msg = f"{nowDatetime} ON {stamp}"
		c_sock.send(on_msg.encode()) #켜졌을 때 메시지
		print(on_msg)
	else:
		GPIO.output(led_pin, 0)
		GPIO.output(26,False)
		GPIO.output(20,False)
		GPIO.output(16,False)
		
		val1 = random.randrange(80, 150)
		val2 = random.randrange(80, 150)
		val3 = random.randrange(80, 150)

		off_msg = f"{nowDatetime} OFF {val1} {val2} {val3}"
		
		c_sock.send(off_msg.encode()) #꺼졌을 때 메시지
		print(off_msg)
		time.sleep(1)
		stamp = now_
        
	light_on = not light_on
	
GPIO.add_event_detect(button_pin, GPIO.RISING, callback=button_callback, bouncetime = 300)

while 1:
	time.sleep(0.1)
