#include "LCS.h"

int main(int argc, char *argv[]) {

    if(argc < 2) {
        printf("Usage: %s <-mode>", argv[0]);
        exit(1);
    }

    if( !strcmp(argv[1], "-p") ) {
        printf("You've entered pair comparison mode!\n");

        if(argc < 4) {
            printf("Usage : %s -p <file1> <file2>\n", argv[0]);
            exit(2);
        }

        utility::pair_comparison(argv[2], argv[3], false);

    }
    else if( !strcmp(argv[1], "-t")){
        printf("You've entered tabular mode!\n");

        if(argc < 3) {
            printf("Usage: %s <dir_name> \n", argv[0]);
            exit(5);
        }

        utility::tabular(argv[2]);
    }

    return 0;
}
