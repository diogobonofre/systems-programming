#include <sys/socket.h>
#include <string.h>
#include <fcntl.h>
#include <sys/sendfile.h>
#include <unistd.h>
#include <netinet/in.h>

void main() {
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr = {
        AF_INET,
        0x901f,
        0
    };

    bind(socket_fd, &addr, sizeof(addr));

    listen(socket_fd, 10);

    int client_fd = accept(socket_fd, 0, 0);

    char buffer[1024] = {0};
    recv(client_fd, buffer, 1024, 0);

    char* f = buffer + 5;
    *strchr(f, ' ') = 0;
    int opened_fd = open(f, O_RDONLY);
    sendfile(client_fd, opened_fd, 0, 1024);
    close(opened_fd);
    close(client_fd);
    close(socket_fd);
}