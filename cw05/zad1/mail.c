#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_LINE_LENGTH 1024

void sort_emails_by_sender();
void sort_emails_by_date();
void send_email(char* recipient, char* subject, char* body);

int main(int argc, char** argv) {
    if (argc == 2) {
        if (strcmp(argv[1], "nadawca") == 0) {
            sort_emails_by_sender();
        } else if (strcmp(argv[1], "data") == 0) {
            sort_emails_by_date();
        } else {
            printf("Nieprawidłowy argument.\n");
            return -1;
        }
    } else if (argc == 4) {
        send_email(argv[1], argv[2], argv[3]);
    } else {
        printf("Nieprawidłowa liczba argumentów.\n");
        return -1;
    }
    return 0;
}

void sort_emails_by_sender() {
    FILE* pipe = popen("mail -H | sort -t ',' -k 2", "r");
    if (!pipe) {
        printf("Błąd podczas uruchamiania programu mail.\n");
        return;
    }
    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, pipe)) {
        printf("%s", line);
    }
    pclose(pipe);
}

void sort_emails_by_date() {
    FILE* pipe = popen("mail -H | sort -t ',' -k 3", "r");
    if (!pipe) {
        printf("Błąd podczas uruchamiania programu mail.\n");
        return;
    }
    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, pipe)) {
        printf("%s", line);
    }
    pclose(pipe);
}

void send_email(char* recipient, char* subject, char* body) {
    char command[MAX_COMMAND_LENGTH];
    snprintf(command, MAX_COMMAND_LENGTH, "echo '%s' | mail -s '%s' %s", body, subject, recipient);
    int result = system(command);
    if (result != 0) {
        printf("Błąd podczas wysyłania e-maila.\n");
    } else {
        printf("E-mail został wysłany.\n");
    }
}
