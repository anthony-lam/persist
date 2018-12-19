#include "pipe_networking.h"


void process(char* str){

}

int main() {

  int to_client;
  int from_client;
  from_client = server_handshake( &to_client );
  while(1){
  	char recieved[1000];
  	read(from_client, recieved, 1000);
    strtok(recieved, "\n");
    printf("Recieved -%s-\n", recieved);
    process(recieved);
    write(to_client, recieved, 1000);
    printf("Sent -%s-\n", recieved);
    }
}
