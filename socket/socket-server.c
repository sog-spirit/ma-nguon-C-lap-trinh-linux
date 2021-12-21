#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

int server(int client_socket) {
    while(1) {
        int length;
        char* text;

        // doc do dai text tu socket. Neu read() tra ve 0, client dong ket noi
        if(read(client_socket, &length, sizeof(length)) == 0)
            return 0;
        
        // cap phat vung dem cho text
        text = (char*) malloc(length);

        // doc text
        read(client_socket, text, length);
        printf("%s\n", text);

        // neu client gui message "quit", thoat
        if(!strcmp(text, "quit"))
            return 1;
            
        // giai phong vung dem
        free(text);

    }
}

int main(int argc, char* const argv[]) {
    const char* const socket_name = argv[1];
    int socket_fd;
    struct sockaddr_un name;
    int client_sent_quit_message;

    // tao socket
    socket_fd = socket(PF_LOCAL, SOCK_STREAM, 0);
    // chi ra day la server
    name.sun_family = AF_LOCAL;
    strcpy(name.sun_path, socket_name);
    bind(socket_fd, &name, SUN_LEN(&name));

    // lang nghe ket noi
    listen(socket_fd, 5);

    // lap lai chap nhan ket noi. Tiep tuc cho den khi co thong diep "quit"
    do {
        struct sockaddr_un client_name;
        socklen_t client_name_len;
        int client_socket_fd;

        //chap nhan ket noi
        client_socket_fd = accept(socket_fd, &client_name, &client_name_len);

        //dieu khien ket noi
        client_sent_quit_message = server(client_socket_fd);
        printf("%d\n", client_sent_quit_message);

        //dong va ket thuc ket noi
        close(client_socket_fd);
    } while(!client_sent_quit_message);

    //xoa file socket
    close(socket_fd);
    unlink(socket_name);

    return 0;
}
