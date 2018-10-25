#include "server.h"
/**
 * Main server routine.
 *
 *      -       instantiates a new server structure that holds the
 *              properties of our server;
 *      -       creates a socket and makes it passive with
 *              `server_listen`;
 *      -       accepts new connections on the server socket.
 *
 */
int main(int argc, char const *argv[]){
	int err = 0;
	server_t server = { 0 };

	err = server_listen(&server);

	if (err) {
		printf("Failed to listen on address 0.0.0.0:0808");
		return err;
	}

	for (;;) {
		err = server_accept(&server);
		if (err) {
			printf("Failed accepting connection\n");
			return err;
		}
	}

	err = (server->listen_fd = socket(AF_INET, SOCK_STREAM, 0));
	if (err == -1) {
		perror("socket");
		printf("Failed to create socket endpoint\n");
		return err;
	}
	err = write(server->listen_fd, "hey", 3);
    if (err == -1) {
            perror("write");
            printf("failed to write\n");
            return err;
    }

    struct sockaddr_in server_addr = { 0 };

    server_addr.sin_family = AF_INET;

    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(PORT);

	return 0;
}