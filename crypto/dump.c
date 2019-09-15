#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void dumpBuffer(const char *description, const  void *buf, int len) {
    FILE *fd;
    char * filename = getenv("OPENSSL_DUMP_FILE");

    if (filename != NULL) {
        fd = fopen("/tmp/dump.data.txt", "a+");
        if (fd == NULL) {
            return;
        }
    } else {
        // Default to standard output
        fd = stdout;
    }

    fprintf(fd, "%s\n", description);

    int i, pos;
    for (i = 0;; i++) {
        // Print length
        fprintf(fd, "%.4x | ", i*16);

        // Print as hex
        for (pos = i * 16; pos < (i + 1) * 16; pos++) {
            if (pos < len) {
                fprintf(fd, "%.2x ", ((const char*)buf)[pos]);
            }
            else {
                fprintf(fd, "   ");
            }
        }

        fprintf(fd, "|");

        // Print ASCII representations
        for (pos = i * 16; pos < (i + 1) * 16; pos++) {
            if (pos < len) {
                if (isprint(((char *)buf)[pos] & 0xff)) {
                    fprintf(fd, "%c", ((const char *)buf)[pos] & 0xff);
                }
                else {
                    fprintf(fd, ".");
                }
            }
            else {
                fprintf(fd, " ");
            }
        }
        fprintf(fd, "|\n");

        if (pos>=len) {
            break;
        }
    }

    if (filename != NULL) {
        fclose(fd);
    }
}