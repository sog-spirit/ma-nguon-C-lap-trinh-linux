#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

// ghi message vao stream voi count lan
void writer(const char *message, int count, FILE *stream) {
    for(; count > 0; --count) {
        fprintf(stream, "%s\n", message);
        fflush(stream);
        sleep(1);
    }
}

// doc ngau nhien tren stream
void reader(FILE *stream) {
    char buffer[1024];
    while(!feof(stream) && !ferror(stream) && fgets(buffer, sizeof(buffer), stream) != NULL)
        fputs(buffer, stdout);
}

int main() {
    int fds[2];
    pid_t pid;
    pipe(fds); //tao pipe
    pid = fork();
    if(pid == (pid_t) 0) {
        // tien trinh con
        FILE *stream;
        close(fds[1]);
        stream = fdopen(fds[0], "r");
        reader(stream);
        close(fds[0]);
    }
    else {
        // tien trinh cha
        FILE *stream;
        close(fds[0]);
        stream = fdopen(fds[1], "w");
        writer("Hello, hello, hello!!!", 5, stream);
        close(fds[1]);
    }

    return 0;
}
