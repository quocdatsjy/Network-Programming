#include <stdio.h>
#include <string.h>

int main() {
    char str[] = "[01,02,03,04]";
    char *p = strtok(str, "[,]");
    printf("%s\n", p);
    return 0;
}