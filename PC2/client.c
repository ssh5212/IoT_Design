#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS //�ֽ� VC++ ������ �� ��� ����               
#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <process.h>



#define SERVERIP   "192.168.36.165"
#define SERVERPORT 9999
#define BUFSIZE    512

int get_retrench(int val1, int val2, int val3, int second) {

    float hour = second / 3600;
    printf("h: %d\n", hour);
    printf("h: %s\n", hour);
    float watt = (val1 + val2 + val3) * 220;
    printf("va1: %f\n", val1);
    printf("va2: %f\n", val2);
    printf("w: %d\n", watt);
    printf("w: %s\n", watt);
    float result = watt * hour;
    printf("fl_result: %f", result);
    printf("in_result: %d", result);


    return (int)result;
}

//  ���� �Լ� ���� ��� �� ����
void err_quit(char* msg)
{
    LPVOID lpMsgBuf;
    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
        NULL, WSAGetLastError(),
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR)&lpMsgBuf, 0, NULL);
    MessageBox(NULL, (LPCTSTR)lpMsgBuf, msg, MB_ICONERROR);
    LocalFree(lpMsgBuf);
    exit(1);
}

//  ���� �Լ� ���� ���
void err_display(char* msg)
{
    LPVOID lpMsgBuf;
    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
        NULL, WSAGetLastError(),
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR)&lpMsgBuf, 0, NULL);
    printf("[%s] %s", msg, (char*)lpMsgBuf);
    LocalFree(lpMsgBuf);
}

// ����� ���� ������ ���� �Լ�
int recvn(SOCKET s, char* buf, int len, int flags)
{
    int received;
    char* ptr = buf;
    int left = len;

    while (left > 0) {
        received = recv(s, ptr, left, flags);
        if (received == SOCKET_ERROR)
            return SOCKET_ERROR;
        else if (received == 0)
            break;
        left -= received;
        ptr += received;
    }

    return (len - left);
}

int main(int argc, char* argv[])
{

    int retval;

    // ���� �ʱ�ȭ
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
        return 1;

    // ������ ������ ���
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) err_quit("socket()");

    // connect()
    SOCKADDR_IN serveraddr;
    ZeroMemory(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr(SERVERIP);
    serveraddr.sin_port = htons(SERVERPORT);
    retval = connect(sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
    if (retval == SOCKET_ERROR) err_quit("connect()");

    // ������ ��ſ� ����� ����
    char buf[BUFSIZE + 1];

    // ������ ������ ���
    while (1) {


        // ������ Ŭ���̾�Ʈ ���� ���
        printf("\n[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n",
            inet_ntoa(serveraddr.sin_addr), ntohs(serveraddr.sin_port));

        // Ŭ���̾�Ʈ�� ������ ���

        char elec_val1[20] = "";
        char elec_val2[20] = "";
        char elec_val3[20] = "";

        char* elec_val1_;
        char* elec_val2_;
        char* elec_val3_;


        while (1) {
            // ������ �ޱ�
            retval = recv(sock, buf, BUFSIZE, 0);
            if (retval == SOCKET_ERROR) {
                err_display("recv()");
                break;
            }
            else if (retval == 0)
                break;


            // ���� ������ ���
            buf[retval] = '\0';
            printf("[TCP/%s:%d] %s\n", inet_ntoa(serveraddr.sin_addr),
                ntohs(serveraddr.sin_port), buf);


            FILE* fp = fopen("result.txt", "a");    // result.txt ������ �߰� ��� (a)�� ����. (!�̸� �����صα�)
                                                    // ���� �����͸� ��ȯ

            fputs(buf, fp);                         // ���Ͽ� ���ڿ� ����
            fputs("\n", fp);

            fclose(fp);                             // ���� ������ �ݱ�

            char* status;
            char* value;

            strtok(buf, " ");
            status = strtok(NULL, " ");

            if (strcmp(status, "OFF") == 0) {
                elec_val1_ = strtok(NULL, " ");
                elec_val2_ = strtok(NULL, " ");
                elec_val3_ = strtok(NULL, " ");

                strcpy(elec_val1, elec_val1_);
                strcpy(elec_val2, elec_val2_);
                strcpy(elec_val3, elec_val3_);
            }
            else if (strcmp(status, "ON") == 0) {
                char* second = strtok(NULL, " ");
                //num1 = atoi(s1);
                if (second == -1) {
                    continue;
                }

                //printf("__sec: %s\n", second);


                printf("atoi_elva1: %f\n", atof(elec_val1));
                printf("atoi_elva2: %f\n", atof(elec_val2));
                printf("atoi_elva3: %f\n", atof(elec_val3));
                printf("atof_sec: %f\n", atof(second));
                float atoi_val1 = atof(elec_val1);
                float atoi_val2 = atof(elec_val2);
                float atoi_val3 = atof(elec_val3);
                float atoi_sec = atof(second);
                int atod_sec = atoi(second);
                //printf("%d\n", atod_sec);
                //printf("%d, %d, %d, %d\n", atoi_val1, atoi_val2, atoi_val3, atoi_sec);
                //int retrench = get_retrench(atoi(elec_val1), atoi(elec_val2), atoi(elec_val3), atoi(second));
                float w_hour = atoi_sec / 3600;
                float w_watt = (atoi_val1 + atoi_val2 + atoi_val3) * 220;
                float w_result = w_watt * w_hour;
                printf("hour: %f\n", w_hour);
                printf("w_result: %f\n", w_result);


                //int retrench = get_retrench(atoi_val1, atoi_val2, atoi_val3, atoi_sec);



                //printf("retrench: %d\n", retrench);
                //printf("%d\n", get_retrench);
                char retrench_[20];
                sprintf(retrench_, "%f", w_result);
                //printf("ret1: %d\n", retrench);
                //printf("ret_2: %s\n", retrench_);
                FILE* f = fopen("retrench.txt", "w");

                fputs(retrench_, f);
                fclose(f);

                system("C:/VS/.vs/server/server/send_bot.cmd");

            }


        }

        // closesocket()    
        closesocket(sock);
        printf("[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n",
            inet_ntoa(serveraddr.sin_addr), ntohs(serveraddr.sin_port));
    }

    // closesocket()
    closesocket(sock);

    //          

    WSACleanup();
    return 0;
}