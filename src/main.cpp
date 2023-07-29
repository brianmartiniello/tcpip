#include <iostream>
#include <vector>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <thread>
#include <chrono>
#include <fcntl.h>
#include <sys/select.h>

void handleClient(int clientSocket) {
    char buffer[1024];
    int bytesRead;

    std::cout << "Client connected. Client socket: " << clientSocket << std::endl;

    // Set the recv timeout for the client socket to 5 seconds
    struct timeval timeout;
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;

    if (setsockopt(clientSocket, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout)) < 0) {
        std::cerr << "Error setting socket options" << std::endl;
        close(clientSocket);
        return;
    }

    while (true) {
        bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);

        if (bytesRead < 0) {
            // Handle timeout error
            if (errno == EWOULDBLOCK || errno == EAGAIN) {
                std::cerr << "Timeout occurred. No data received within the specified time." << std::endl;
            } else {
                std::cerr << "Error reading from client" << std::endl;
            }
            break;
        } else if (bytesRead == 0) {
            std::cout << "Connection closed by client. Client socket: " << clientSocket << std::endl;
            break;
        } else {
            // Process the received data (you can replace this with your own logic)
            std::cout << "Received " << bytesRead << " bytes from client: ";
            std::cout.write(buffer, bytesRead);
            std::cout << std::endl;
        }
    }

    close(clientSocket);
}

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    int port = 12345; // Choose any available port number

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        std::cerr << "Error creating socket" << std::endl;
        return 1;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Error binding socket" << std::endl;
        close(serverSocket);
        return 1;
    }

    if (listen(serverSocket, 5) < 0) {
        std::cerr << "Error listening on socket" << std::endl;
        close(serverSocket);
        return 1;
    }

    std::cout << "Server started. Listening on port " << port << std::endl;

    std::vector<std::thread> clientThreads;

    while (true) {
        clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
        if (clientSocket < 0) {
            std::cerr << "Error accepting connection" << std::endl;
            continue;
        }

        // Create a new thread for each client connection
        clientThreads.emplace_back(handleClient, clientSocket);
    }

    // Close all client sockets before joining threads
    for (auto& thread : clientThreads) {
        if (thread.joinable()) {
            thread.join();
        }
    }

    // Close the server socket before exiting
    close(serverSocket);

    return 0;
}
