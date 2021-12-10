#-*- coding: utf-8 -*-

#임시랜덤숫자
import random
import time
import datetime
import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

onoff = ['ON', 'OFF']

now = datetime.datetime.now()
nowDatetime = now.strftime('Client Time: ' + '%Y-%#m-%#d %#H:%#M:%#S')
stoptime = time.time()
elapsed_time = time.time() - stoptime



#서버 주소 입력
svrIP = input(("Server IP(default: 127.0.0.1): "))
if svrIP == '':
    svrIP = '127.0.0.1' #기본 주소
    
#포트 번호 입력
port = input('port(default: 9999): ')
if port == '':
    port = 9999 #기본 포트
else:
    port = int(port)
    
sock.connect((svrIP, port))
print('Connected to ' + svrIP + "\nSeinding Data...")

while True:
    onmsg = ("Status(Current, ON/OFF)    " +
           str(random.randrange(0,500)) +
           "\t" + random.choice(onoff))

    offmsg = (nowDatetime + '\tOFF')

    e_time = ("Elasped time: " + time.strftime("%H:%M:%S", time.gmtime(elapsed_time)))

    try:#데이터 전송
        if random.choice(onoff) == 'ON':
            sock.send(onmsg.encode()) #켜졌을 때 메시지
            time.sleep(5)
            
        if random.choice(onoff) == 'OFF':
            sock.send(offmsg.encode()) #꺼졌을 때 메시지
            while random.choice(onoff) == 'ON':
                if random.choice(onoff) == 'ON':
                    sock.send(e_time.encode())
                    break
                else:
                    time.sleep(1)
                
    except: #연결종료
        print("연결이 종료되었습니다")
        break

sock.close()
