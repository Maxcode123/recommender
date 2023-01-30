#include "preprocessor.h"

void main() {
    DIR *d;
    struct dirent *dir;
    if (d = opendir("data/raw")) {
        char buff[100];
        int i = 0;
        while ((dir = readdir(d)) != NULL) {
            strcpy(buff, dir->d_name);
            if (strcmp(buff, "..") == 0 || strcmp(buff, ".") == 0) continue;
            char read[108] = "data/raw/";
            char write[117] = "data/preprocessed/";
            strcat(read, buff);
            strcat(write, buff);
            prescan(read, write);
            printf("%d preprocessed %s\n", ++i, read);
        }
        closedir(d);
    }
    return;
}