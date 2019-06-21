#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *in, *out;
    if (argc !=3) {
        printf("Usage: ./problema1 file.in file.out");
        return -1;
    }

    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");

    int fsize = 0;
    char *data;

    fseek(in, 0, SEEK_END);
    fsize = ftell(in);
    rewind(in);

    data = (char*) malloc(sizeof(char) * fsize);
    fread(data, 1, fsize, in);

    printf("%s", data);

    fclose(in);
    fclose(out);

    printf("running...\n");
    return 0;
}
