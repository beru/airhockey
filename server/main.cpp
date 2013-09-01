
#include <stdio.h>
#include <math.h>

#include "csockets/PassiveSocket.h"
#include <list>

#define M_PI 3.14159265358979
#define deg2rad(a) ( (a) / 180.0 * M_PI )

int main(int argc, char* argv[])
{
    CPassiveSocket socket;
    socket.Initialize();
	socket.SetNonblocking();
    socket.Listen((const uint8_t*)"", 5000);
	
	CActiveSocket* pClient = NULL;

	uint8_t buff[4096];

	std::list<CActiveSocket*> clientSockets;

	float deg = 0;
	while (1) {
		{
			pClient = socket.Accept();
			if (pClient) {
				clientSockets.push_back(pClient);
			}
		}
		for (std::list<CActiveSocket*>::iterator it=clientSockets.begin(); it!=clientSockets.end(); ++it) {
			CActiveSocket* pClient = *it;
			int32 receivedBytes = pClient->Receive(sizeof(buff));
			if (receivedBytes > 0) {
				uint8* pData = pClient->GetData();
				int32 sentBytes = pClient->Send((const uint8*)pData, receivedBytes);
			}
			CSimpleSocket::CSocketError err = pClient->GetSocketError();
			if (err != CSimpleSocket::SocketEwouldblock) {
				continue;
			}
			{
				float pos[2];
				pos[0] = 100 * sin(deg2rad(deg));
				pos[1] = 50;
				deg += 1;
				pClient->Send((const uint8_t*)pos, sizeof(pos));
			}
		}
		Sleep(10);
	}

	for (std::list<CActiveSocket*>::iterator it=clientSockets.begin(); it!=clientSockets.end(); ++it) {
		CActiveSocket* p = *it;
		delete p;
	}
	return 0;
}


