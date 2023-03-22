#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <linux/limits.h>

void traverse_directory(char* path, char* str);

void print_file_path(char* path, pid_t pid) {
    printf("%s %d\n", path, pid);
}

void traverse_file(char* path, char* str) {
    FILE* file = fopen(path, "r");
    if (file == NULL) {
        perror("Failed to open file");
        return;
    }
    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, file)) != -1) {
        if (strstr(line, str) == line) {
            print_file_path(path, getpid());
            break;
        }
    }
    free(line);
    fclose(file);
}

void traverse_directory(char* path, char* str) {
    DIR* dir;
    struct dirent* entry;
    struct stat statbuf;
    pid_t pid;

    if ((dir = opendir(path)) == NULL) {
        perror("Failed to open directory");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        char* entry_path = malloc(PATH_MAX);
        snprintf(entry_path, PATH_MAX, "%s/%s", path, entry->d_name);

        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            free(entry_path);
            continue;
        }

        if (lstat(entry_path, &statbuf) == -1) {
            perror("Failed to get file status");
            free(entry_path);
            continue;
        }

        if (S_ISDIR(statbuf.st_mode)) {
            pid = fork();
            if (pid == -1) {
                perror("Failed to fork process");
            } else if (pid == 0) {
                traverse_directory(entry_path, str);
                exit(0);
            }
        } else if (S_ISREG(statbuf.st_mode)) {
            traverse_file(entry_path, str);
        }
        free(entry_path);
    }
    closedir(dir);
}

int main(int argc, char** argv) {
    if (argc != 3) {
        printf("Invalid number of arguments\n", argv[0]);
        return 1;
    }

    char* path = argv[1];
    char* str = argv[2];

    traverse_directory(path, str);

    return 0;
}
