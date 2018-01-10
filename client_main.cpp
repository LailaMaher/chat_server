


#include "Client.h"

void* handleIncomingRequests(void* client_v){
	Client* client = (Client*)client_v;
	string data = client->ReadStream();
	cout << data << endl;
}

void* StartConnection(void* client_v){
	Client* client = (Client*)client_v;

	int ID;	
	cout << "Enter the ID to connect to: " << endl;
	cin >> ID;
	client->WriteToServer(to_string(ID));

	string ip = client->ReadFromServer(); 
	cout << ip << endl;

	const char *cip = ip.c_str();

	client->SendStream(cip,"hello");

}

int main(int argc, char const *argv[])
{

	pthread_t pid1, pid2;
	Client C;

	C.CreateUDPSocket();

	C.CreateTCPSocket("localhost");

	if(C.ReadFromServer().compare("1")){

		int err;
		err = pthread_create(&pid1, NULL, &handleIncomingRequests, &C);
		err = pthread_create(&pid2, NULL, &StartConnection, &C);

		
	}else {
		cout << "not equal\n";
	}

	pthread_join(pid1, NULL);
	pthread_join(pid2, NULL);

	return 0;
}