
#include "Client.h"



// --------------------- TCP CONNECTION -------------------------

void Client::CreateTCPSocket(const char* hostname){
	
	setTCPDescriptor( socket(AF_INET, SOCK_STREAM, 0) ); 

	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
    struct hostent* server = gethostbyname(hostname);
    bcopy((char *)server->h_addr, 
         (char *)&server_address.sin_addr.s_addr,
         server->h_length);
    server_address.sin_port = htons(TCP_PORT_NUM);

    if( connect(getTCPDescriptor(), (struct sockaddr *) &server_address, sizeof(server_address)) < 0 ) 
    	perror("CONNECT TO SERVER FAILED");
}

void Client::setTCPDescriptor(int tcp_descriptor){
	this->tcp_descriptor = tcp_descriptor;
	if(tcp_descriptor < 0) perror("FAILED TO CREATE TCP SOCKET");
}

int Client::getTCPDescriptor() const{
	return tcp_descriptor;
}

string Client::ReadFromServer(){
	char buffer[1024];
	if( read(getTCPDescriptor(), buffer, 1023) < 0 ) perror("READ FAILED");
	string data(buffer);
	return data;
}

void Client::WriteToServer(string data){
    char buffer[1024];
    strcpy(buffer, data.c_str());
	if( write(getTCPDescriptor(), buffer, 1023) < 0 ) perror("WRITE FAILED");
}

// --------------------- UDP CONNECTION -------------------------

void Client::setUDPaddress(){
	udp_addr.sin_family = AF_INET;
	udp_addr.sin_addr.s_addr = INADDR_ANY;
	udp_addr.sin_port = htons(UDP_PORT_NUM);
}

sockaddr* Client::getUDPaddress() const{
	return (struct sockaddr *)&udp_addr;
}

void Client::CreateUDPSocket(){
	setUDPDescriptor(socket(AF_INET, SOCK_DGRAM, 0)); 
	setUDPaddress();
	if( bind(getUDPDescriptor(), (struct sockaddr *)&udp_addr, sizeof(udp_addr)) < 0 ) 
		perror("UDP BIND ERROR");
}

void Client::setUDPDescriptor(int udp_descriptor){
	this->udp_descriptor = udp_descriptor;
	if(udp_descriptor < 0) perror("FAILED TO CREATE UDP SOCKET");
}

int Client::getUDPDescriptor() const{
	return udp_descriptor;
}

void Client::SendStream(const char* peer_ip, string data){

    char buffer[1024];
    strcpy(buffer, data.c_str());

    struct sockaddr_in peer_addr;

    peer_addr.sin_family = AF_INET;
	
	struct hostent* peer = gethostbyname(peer_ip);
    bcopy((char *)peer->h_addr, 
         (char *)&peer_addr.sin_addr.s_addr,
         peer->h_length);

	peer_addr.sin_port = htons(UDP_PORT_NUM);

    if( sendto(getUDPDescriptor(), buffer, 1023, 0, (struct sockaddr*)&peer_addr, sizeof(peer_addr)) )
    	perror("SEND STREAM FAILED");

}

string Client::ReadStream(){
	char buffer[1024];
    if( recvfrom(getUDPDescriptor(), buffer, 1023, 0, NULL, NULL) )
    	perror("READ STREAM FAILED");
    string data(buffer);
	return data;
}
