from socket import *
import random
import time
import datetime

port = 9999
BUFSIZE = 512

onoff = ['ON', 'OFF']

now = datetime.datetime.now()
nowDatetime = now.strftime('Client Time: '
                           + '%Y-%#m-%#d %#H:%#M:%#S')
stoptime = time.time()
elapsed_time = time.time() - stoptime


sock = socket(AF_INET, SOCK_STREAM)
sock.bind(('', port)) #자신의 주소 사용
sock.listen(1) #최대 대기 틀라이언트 수
print("Waiting for clients...")

#클라이언트의 연결 요청을 받는다
c_sock, (r_host, r_port) = sock.accept()
print('connected by', r_host, r_port)

while True:
    
    onmsg = (nowDatetime + "    Status(ON/OFF, Current:) "
             + "ON")

    offmsg = (nowDatetime + "   Status(ON/OFF, Current:) "
              + "OFF"
              + "\t" + str(random.randrange(0,500))
              + "\t" + str(random.randrange(0,500))
              + "\t" + str(random.randrange(0,500)))

    e_time = ("Elasped time: " +
              time.strftime("%S", time.gmtime(elapsed_time))+' Second')

    try:#데이터 전송
        if random.choice(onoff) == 'ON':
            c_sock.send(onmsg.encode()) #켜졌을 때 메시지
            print(onmsg)
            time.sleep(3) #대기시간(Default:600)
            
        if random.choice(onoff) == 'OFF':
            c_sock.send(offmsg.encode()) #꺼졌을 때 메시지
            print(offmsg)
            time.sleep(1)
            
            while random.choice(onoff) == 'ON':
                time.sleep(1)
                if random.choice(onoff) == 'ON':
                    c_sock.send(e_time.encode())
                    print(e_time)
                    time.sleep(1)
                    break
                
                else:
                    time.sleep(1)

    except: #연결종료
        break
    
c_sock.close()
