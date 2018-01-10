

#ifndef SERVER
#define SERVER

#include "User.h"
#include <pthread.h>

class Server{
	
	int PORT_NUM = 7033;
	
	User* users[100];
	pthread_mutex_t users_mutex;
	int current_users;
	
	int descriptor;
	struct sockaddr_in address;
	
	static Server* s_instance;

	User* createUser(int, string);

	User* isExist(int);

	Server();

public:


	static Server* instance();
	
	void setDescriptor(int descriptor);
	int getDescriptor() const;
	
	void setAddress();
	void createSocket();

	User* acceptUser();
	void addUser(User*);
	void removeUser(User*);


	void startConnection(User*);
	void start();

};



#endif
