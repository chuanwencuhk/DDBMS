#ifndef DATATRANSMISSION_H_
#define DATATRANSMISSION_H_

#include <string>
#include <iostream>
#include <rpc/client.h>
#include rpc/server.h>


using std::string;
using rpc::server;
using rpc::client;

string 


class DataTransmissionServer {
public:
	DataTransmissionServer(uint16_t port):
	port_(port), server_(server(port)) { }

private:
	server server_;
	uint16_t port_;
};

class DataTransmissionClient {
public:
	DataTransmissionClient(string const server_addr, uint16_t server_port){

	}
private:
	client client_;
	uint16_t server_port_;
	string server_addr_;
};

#endif