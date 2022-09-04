#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <WinSock2.h>
#include <iostream>
#include <string>

#pragma comment (lib, "ws2_32.lib")
using namespace std;


int Multiply(int A, int B)
{
	return A * B;
}

int main()
{
	char Buffer[1024] = {};
	char SendBuffer[1024] = {};
	char ResultBuffer[1024] = {};
	int MulA = 0;
	int MulB = 0;
	int Result = 0;

	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);


	//make socket
	SOCKET ServerSocket = socket(AF_INET, SOCK_DGRAM, 0);
	SOCKADDR_IN ServerSockADDR;

	//set server info
	memset(&ServerSockADDR, 0, sizeof(SOCKADDR_IN));
	ServerSockADDR.sin_addr.s_addr = INADDR_ANY;
	ServerSockADDR.sin_port = htons(1234);
	ServerSockADDR.sin_family = PF_INET;


	//socket bind ip:port
	bind(ServerSocket, (SOCKADDR*)&ServerSockADDR, sizeof(SOCKADDR_IN));
	string ASendMessage;


	while (1)
	{




		//wait for recv
		SOCKADDR_IN ClientSockADDR;
		memset(&ClientSockADDR, 0, sizeof(SOCKADDR_IN));

		int ClientSockLength = sizeof(ClientSockADDR);


		recvfrom(ServerSocket, Buffer, sizeof(Buffer), 0, (SOCKADDR*)&ClientSockADDR, &ClientSockLength);

		//printf("recvfrom : %s %s\n", inet_ntoa(ServerSockADDR.sin_addr), Buffer);
		cout << "Recev IP : " << inet_ntoa(ClientSockADDR.sin_addr) << endl;

		
		MulA = atoi(Buffer);

		recvfrom(ServerSocket, Buffer, sizeof(Buffer), 0, (SOCKADDR*)&ClientSockADDR, &ClientSockLength);
		cout << "Recev IP : " << inet_ntoa(ClientSockADDR.sin_addr) << endl;
		MulB = atoi(Buffer);


		Result = MulA * MulB;

		memcpy(&ResultBuffer, &Result, 4);

		//getline(cin, ASendMessage);

		//send
		sendto(ServerSocket, ResultBuffer, 4, 0, (SOCKADDR*)&ClientSockADDR, sizeof(ClientSockADDR));


		//for (int i = 0; i < 4; ++i)
		//{
		//	sendto(ServerSocket, &ResultBuffer[i] , 1, 0, (SOCKADDR*)&ClientSockADDR, sizeof(ClientSockADDR));

		//	cout << i;
		//}
		//cout << ResultBuffer << endl;

		
	}


	//close socket
	closesocket(ServerSocket);

	//cleanup winsock
	WSACleanup();


	return 0;

}