#include <winsock.h>
#include <stdio.h>
#include <string>
#include <iostream>

#pragma comment(lib, "wsock32.lib")  

using namespace std;
#define WSWENS MAKEWORD(2,0)
#define MAXLINE 10240

//����������Ӧ����Ϣ��ӡ
void response(SOCKET sock, char buff[])
{
	int len = recv(sock, buff, MAXLINE, 0);
	buff[len] = 0;
	cout << buff << endl;
}

int main()
{
	sockaddr_in sin;
	WSADATA wsadata;

	//��Winsock�����ʼ��
	if (WSAStartup(WSWENS, &wsadata) != 0)
		cout << "startup failed" << endl;

	//�����׽��֣�ָ���˿ں�
	SOCKET s = socket(PF_INET, SOCK_STREAM, 0);
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(25);

	//��ȡ������IP��ַ
	hostent* hptr = gethostbyname("smtp.163.com");
	memcpy(&sin.sin_addr.S_un.S_addr, hptr->h_addr_list[0], hptr->h_length);
	printf("IP of smpt.163.com is : %d:%d:%d:%d",
		sin.sin_addr.S_un.S_un_b.s_b1,
		sin.sin_addr.S_un.S_un_b.s_b2,
		sin.sin_addr.S_un.S_un_b.s_b3,
		sin.sin_addr.S_un.S_un_b.s_b4);
	cout << endl;

	//�����������������
	if (connect(s, (sockaddr*)&sin, sizeof(sin)))
	{
		cout << "connect failed!" << endl;
		exit(0);
	}
	else
	{
		cout << "connect success!" << endl;
	}

	char bufferresv[10240];
	response(s, bufferresv);

	// send "ehlo"
	char bufferHello[] = "ehlo lca\r\n";
	cout << "ehlo..." << endl;
	send(s, bufferHello, strlen(bufferHello), 0);
	response(s, bufferresv);

	// send "auth login"
	char bufferLogin[] = "auth login\r\n";
	cout << "auth login..." << endl;
	send(s, bufferLogin, strlen(bufferLogin), 0);
	response(s, bufferresv);

	// send "username", "psw"
	char bufferUserName[] = "bHVvZnVuZnVuQDE2My5jb20=\r\n";
	//����������luofunfun@163.com��BASE64����
	char bufferpsw[] = "bWFpbDIwMTdsdW9mdW4=\r\n";
	//������������mail2017luofun��BASE64����

	cout << "input username...." << endl;
	send(s, bufferUserName, strlen(bufferUserName), 0);
	response(s, bufferresv);

	cout << "input password..." << endl;
	send(s, bufferpsw, strlen(bufferpsw), 0);
	response(s, bufferresv);

	// mail from:<luofunfun@163.com>
	char bufferMailFrom[] = "mail from:<luofunfun@163.com>\r\n";
	cout << "mail from:<luofunfun@163.com>..." << endl;
	send(s, bufferMailFrom, strlen(bufferMailFrom), 0);
	response(s, bufferresv);

	// rcpt to:<627018553@qq.com>
	char bufferRcptTo[] = "rcpt to:<627018553@qq.com>\r\n";
	cout << "rcpt to:<627018553@qq.com>..." << endl;
	send(s, bufferRcptTo, strlen(bufferRcptTo), 0);
	response(s, bufferresv);

	// data
	char bufferData[] = "data\r\n";
	cout << "data..." << endl;
	send(s, bufferData, strlen(bufferData), 0);
	response(s, bufferresv);

	// from.. to.. subject..
	char bufferFrom[] = "from:luofunfun@163.com\r\n";
	char bufferTo[] = "to:627018553@qq.com\r\n";
	char bufferSubject[] = "subject:Source Code Project\r\n";

	cout << "from:luofunfun@163.com..." << endl;
	send(s, bufferFrom, strlen(bufferFrom), 0);
	cout << "to:627018553@qq.com... " << endl;
	send(s, bufferTo, strlen(bufferTo), 0);
	cout << "subject:Source Code Project" << endl;
	send(s, bufferSubject, strlen(bufferSubject), 0);

	//content
	char buffersend[] = "void main(){}\r\n";
	cout << "void main(){}" << endl;
	send(s, buffersend, strlen(buffersend), 0);

	//end
	char bufferPoint[] = ".\r\n";
	send(s, bufferPoint, strlen(bufferPoint), 0);
	response(s, bufferresv);

	//quit
	char bufferend[] = "quit\n";
	send(s, bufferend, strlen(bufferend), 0);
	response(s, bufferresv);
	return 0;
}