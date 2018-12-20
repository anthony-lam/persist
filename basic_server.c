#include "pipe_networking.h"
#include <signal.h>



static void sighandler(int n){
	if(n == SIGINT){
		remove("wkp");
		printf("[server] exiting\n");
		exit(0);
	}
}


int main() {
	signal(SIGINT, sighandler);
	int to_client;
	int from_client;
	char recieved[1000];
	int i;
	while(1){
		from_client = server_handshake( &to_client );
		while(read(from_client, recieved, 1000)){
			strtok(recieved, "\n");
			printf("[server] Recieved -%s-\n", recieved);
			for(i = 0; i < strlen(recieved); i++){
				recieved[i] += 10;
			}
			write(to_client, recieved, 1000);
			printf("[server] Sent -%s-\n", recieved);
		}
	}
}
