#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

void print_help(const char *prog_name) {
    printf("Welcome to minils!\n");
    printf("Usage: %s [options] [path]\n", prog_name);
    printf("  -h, --help        Show this help message\n");
    printf("  -l, --list        List files (optional, default behavior)\n");
}

int main(int argc, char *argv[]) {
    const char *target_dir = ".";

    // 1. Check for help flag right away
    if (argc > 1 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)) {
        print_help(argv[0]);
        return 0;
    }

    // 2. Determine if argv[1] is a flag or a direct path
    if (argc > 1) {
        if (argv[1][0] == '-') {
            // It's a flag (starts with '-')
            if (strcmp(argv[1], "-l") == 0 || strcmp(argv[1], "--list") == 0) {
                // If a path was provided after the flag (argv[2]), use it
                if (argc > 2) {
                    target_dir = argv[2];
                }
            } else {
                fprintf(stderr, "Error: Unknown option '%s'\n", argv[1]);
                print_help(argv[0]);
                return 1;
            }
        } else {
            // It's not a flag, so treat argv[1] directly as a path! (e.g., ./minils /bin)
            target_dir = argv[1];
        }
    }

    // 3. Open and list the target directory
    DIR *dir = opendir(target_dir);
    if (dir == NULL) {
        perror("Error opening directory");
        return 1;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        // Skip hidden navigation directories '.' and '..'
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        printf("%s  ", entry->d_name);
    }
    printf("\n");
    
    closedir(dir);
    return 0;
}
