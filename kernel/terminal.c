#include "user.h"
#include "fs.h"
#include <stdio.h>
#include <string.h>

void process_adduser_command(const char *command) {
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];
    sscanf(command + 8, "%11s %11s", username, password);
    add_user(username, password, false); // Regular user
}

void process_login_command(const char *command) {
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];
    sscanf(command + 6, "%11s %11s", username, password);
    if (authenticate(username, password)) {
        printf("Login successful!\n");
    } else {
        printf("Login failed.\n");
    }
}

void process_create_command(const char *command) {
    char filename[FILENAME_LENGTH];
    sscanf(command + 7, "%49s", filename);
    create_file(filename);
}

void process_command(const char *command) {
    if (strncmp(command, "adduser ", 8) == 0) {
        process_adduser_command(command);
    } else if (strncmp(command, "login ", 6) == 0) {
        process_login_command(command);
    } else if (strncmp(command, "create ", 7) == 0) {
        process_create_command(command);
    } else if (strncmp(command, "mkdir ", 6) == 0) {
        char dirname[FILENAME_LENGTH];
        sscanf(command + 6, "%49s", dirname);
        create_directory(dirname);
    } else if (strncmp(command, "rmdir ", 6) == 0) {
        char dirname[FILENAME_LENGTH];
        sscanf(command + 6, "%49s", dirname);
        delete_directory(dirname);
    } else if (strncmp(command, "delete ", 7) == 0) {
        char filename[FILENAME_LENGTH];
        sscanf(command + 7, "%49s", filename);
        delete_file(filename);
    } else if (strncmp(command, "cat ", 4) == 0) {
        char filename[FILENAME_LENGTH];
        sscanf(command + 4, "%49s", filename);
        read_file(filename);
    } else if (strcmp(command, "ls") == 0) {
        list_files();
    } else if (strcmp(command, "help") == 0) {
        printf("Available commands: adduser, login, create, mkdir, rmdir, delete, cat, ls, help\n");
    } else {
        printf("Unknown command.\n");
    }
}
