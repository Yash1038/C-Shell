#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    char path[1024]; // Assuming a reasonable maximum path length

    while (1) {
        printf("Enter a directory path or 'exit' to quit: ");
        fgets(path, sizeof(path), stdin);

        // Remove newline character from input
        size_t len = strlen(path);
        if (len > 0 && path[len - 1] == '\n') {
            path[len - 1] = '\0';
        }

        if (strcmp(path, "exit") == 0) {
            break;
        }

        if (chdir(path) == 0) {
            printf("Directory changed to: %s\n", getcwd(NULL, 0));
        } else {
            perror("Error");
        }
    }

    return 0;
}
