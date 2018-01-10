


#include "Server.h"
#include <pthread.h>


void* Work(void* user_v){
	User* user = (User*)user_v;
	Server::instance()->addUser(user);
	Server::instance()->startConnection(user);
	return NULL;
}


int main(int argc, char const *argv[])
{
	pthread_t pid[100];
	int cnt = 0;


	Server* tcp = Server::instance();
	tcp->createSocket();
	tcp->acceptUser();


	while(true){

		User* new_user = tcp->acceptUser();

		int err = pthread_create(&pid[cnt], NULL, &Work, new_user);
		cnt++;

	}

	
	return 0;
}