#include "pipe_networking.h"


/*=========================
  server_handshake
  args: int * to_client

  Performs the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {
  mkfifo("wkp", 0644);

  printf("Created pipe\n");
  int from_client = open("wkp", O_RDONLY);
  char pid[HANDSHAKE_BUFFER_SIZE];
  read(from_client, pid, sizeof(pid));
  printf("PID Received: %s\n", pid);

  *to_client = open(pid, O_WRONLY);
  remove("wkp");
  printf("Writing to pipe\n");
  write(*to_client, ACK, sizeof(ACK));

  char msg[HANDSHAKE_BUFFER_SIZE];
  printf("Waiting\n");
  read(from_client, msg, sizeof(msg));
  printf("Message Received\n");

  return from_client;
}


/*=========================
  client_handshake
  args: int * to_server

  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  printf("Creating pipe\n");
  char pid[HANDSHAKE_BUFFER_SIZE];
  sprintf(pid, "%d", getpid());
  printf("PID is %s\n", pid);
  mkfifo(pid, 0644);

  printf("Sending PID\n");
  *to_server = open("wkp", O_WRONLY);
  write(*to_server, pid, sizeof(pid));

  int from_server = open(pid, O_RDONLY);
  char msg[HANDSHAKE_BUFFER_SIZE];
  read(from_server, msg, sizeof(msg));
  printf("Message Received\n");
  remove(pid);

  printf("Writing\n");
  write(*to_server, ACK, sizeof(ACK));

  return from_server;
}
