#include "preprocessor.h"

void main() {
    DIR *d;
    struct dirent *dir;
    if (d = opendir("data/raw")) {
        while ((dir = readdir(d)) != NULL) {
            printf("%s\n", dir->d_name);
        }
        closedir(d);
    }
    return;
}