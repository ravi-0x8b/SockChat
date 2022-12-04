#include <WinSock2.h>
#include <ws2tcpip.h>
#include <iostream>

#pragma comment(lib, "Ws2_32.lib")

int main(int argc, char** argv) {

	// create an object WSADATA
	WSADATA wsaData;

	std::cout << "[INFO] Starting WS2_32.dll\n";
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		std::cerr << "Error: WSAStartup failed: " << iResult << '\n';
		return 1;
	}

	// struct addrinfo
	addrinfo *result = nullptr, *ptr = nullptr, hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
	if (argc == 0) {
		std::cerr << "Number of invalid arguments. Aborting program.\n";
		return 0;
	}
	constexpr auto DEFAULT_PORT = "27015";

	iResult = getaddrinfo(argv[1], DEFAULT_PORT, &hints, &result);
	if (iResult == 0) {
		std::cerr << "Error: \'getaddrinfo\' failed: " << iResult << '\n';
		std::cout << "Shutting down \'DLL WS2_32\'\n";
		WSACleanup();
		return 1;
	}

	// create a socket object called SOCKET (yeh lol)
	SOCKET connectSocket = INVALID_SOCKET;
	ptr = result;

	connectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

	// check if is a valid socket
	if (connectSocket == INVALID_SOCKET) {
		std::cerr << "Error at socket " << WSAGetLastError() << '\n';
		freeaddrinfo(result);
		std::cout << "Shutting down \'DLL WS2_32\'\n";
		WSACleanup();
		return 1;
	}
	return 0;
}