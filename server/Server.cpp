/*
 * Server.cpp
 *
 *  Created on: Nov 29, 2017
 *      Author: oriel
 */

#include "Server.h"
#include <linux/ip.h>
using namespace std;
#define MAX_CONNECTED_CLIENTS 2
Server::Server(int port) :
    port(port), serverSocket(0) {
  cout << "Server" << endl;
}
void Server::start() {
  // Create a socket point
  serverSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (serverSocket == -1) {
    throw "Error opening socket";
  }
  // Assign a local address to the socket
  struct sockaddr_in serverAddress;
  bzero((void *) &serverAddress, sizeof(serverAddress));
  serverAddress.sin_family = AF_INET;

  struct hostent *ptrh;
  ptrh = gethostbyname("127.0.0.1");
  memcpy(&serverAddress.sin_addr, ptrh->h_addr, ptrh->h_length);

//  serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1"); //inet_addr("127.0.0.1");// inet_addr("95.86.112.226"); //INADDR_ANY; "127.0.0.1"
  serverAddress.sin_port = htons(port);
  if (bind(serverSocket, (struct sockaddr *) &serverAddress,
      sizeof(serverAddress)) == -1) {
    throw "Error on binding";
  }
  // Start listening to incoming connections
  listen(serverSocket, MAX_CONNECTED_CLIENTS);

  // Define the clients socket's structures
  struct sockaddr_in clientAddress1;
  struct sockaddr_in clientAddress2;
  socklen_t clientAddressLen1;
  socklen_t clientAddressLen2;
  while (true) {
    cout << "Waiting for client1 connections..." << endl;
    // Accept a new client connection
    int clientSocket1 = accept(serverSocket,
        (struct sockaddr *) &clientAddress1, &clientAddressLen1);

    if (clientSocket1 == -1)
      throw "Error on accept clientSocket1";

    cout << "Client1 connected" << endl;

    int clientSocket2 = accept(serverSocket,
        (struct sockaddr *) &clientAddress2, &clientAddressLen2);

    if (clientSocket2 == -1)
      throw "Error on accept clientSocket2";

    cout << "Client2 connected" << endl;

    int n;
    int message = 1;
    n = write(clientSocket1, &message, sizeof(message));
    if (n == -1) {
      throw "Error writing to clientSocket1";
      cout << "Error writing to clientSocket1" << endl;
    }
    cout << "Success writing to clientSocket1" << endl;

    message = 2;
    n = write(clientSocket2, &message, sizeof(message));
    if (n == -1) {
      throw "Error writing to clientSocket2";
      cout << "Error writing to clientSocket2" << endl;
    }
    cout << "Success writing to clientSocket2" << endl;

    startTheGame(clientSocket1, clientSocket2);
    // Close communication with the clients
    close(clientSocket1);
    close(clientSocket2);
  }
}

// start The Game
void Server::startTheGame(int clientSocket1, int clientSocket2) {
  int message;

  do {
    //get two message for X and Y of point from clientSocket1
    for (int i = 0; i < 2; i++) {
      getMessage(clientSocket1, message);
      //if we get -2 it is mean End of game so we do not need
      //to continue get the other message
      if (message == -2) {
        cout << "clientSocket1 end the game \n";
        break;
      }

      sendMessege(clientSocket2, message);
      //if we get -1 it is mean NoMove so we do not need
      //to continue get the other message
      if (message == -1) {
        break;
      }
    }
    //if we get -2 it is mean End of game so we need to stop the game
    if (message == -2) {
      break;
    }

    for (int i = 0; i < 2; i++) {
      getMessage(clientSocket2, message);
      if (message == -2) {
        cout << "clientSocket2 end the game \n";
        break;
      }

      sendMessege(clientSocket1, message);
      if (message == -1) {
        break;
      }
    }
    if (message == -2) {
      break;
    }

  } while (true);
}

void Server::getMessage(int clientSocket, int& message) {
  int n = read(clientSocket, &message, sizeof(message));
  if (n == -1) {
    throw "Error reading message\n";
  }
}
void Server::sendMessege(int clientSocket, int& message) {
  int n = write(clientSocket, &message, sizeof(message));
  if (n == -1) {
    throw "Error writing to socket\n";
  }
}

void Server::stop() {
  close (serverSocket);
}