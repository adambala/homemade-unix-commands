/*
 * Copyright (C) 2022  Adam Isakov  <https://github.com/adambala>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/file.h>

int main(int argc, char *argv[]) 
{      
    int *fd; // array of file descriptors
    long long curr_pos, counter;
    short int last_line_break;
    
    short int multiple_files;
    int file_count;

    /*
    * mode:
    *   0 - display n last lines (n = 10 by default)
    *   1 - display from the n-th line 
    */
    short int mode;
    int n = 10; // default

    // auxiliary variables
    short int argc_shift;
    int j;
    char c;
    
    if (!strcmp(argv[1], "-n")) {
        n = atoi(argv[2]);
        mode = 0;
        argc_shift = 3;
    } else if (!strcmp(argv[1], "+n")) {
        n = atoi(argv[2]);
        mode = 1;
        argc_shift = 3;
    } else {
        argc_shift = 1;
    }

    file_count = argc - argc_shift;
    fd = (int *) malloc(file_count * sizeof(int));
    multiple_files = (file_count != 1);

    if (mode == 0) {
        for (j = 0; j < file_count; j++) {
            fd[j] = open(argv[j + argc_shift], O_RDONLY);

            if (fd[j] > 0) {
                // retrieving info about last char in file
                curr_pos = lseek(fd[j], -1, SEEK_END);
                read(fd[j], &c, 1);
                last_line_break = c == '\n' ? 1 : 0;

                counter = 0;
                curr_pos = lseek(fd[j], -1, SEEK_END);
                while ((curr_pos > 0) && (counter < n)) {
                    read(fd[j], &c, 1); // position is shifted forward by 1 byte
                    if (c == '\n')
                        counter++;
                    
                    curr_pos = lseek(fd[j], -2, SEEK_CUR); // shift backwards by 2 bytes (1 additional byte due to read)
                }

                curr_pos = lseek(fd[j], 2, SEEK_CUR); // we don't have to read chars before that position

                if (multiple_files) 
                    printf("%s==> %s <==\n", last_line_break ? "" : "\n", argv[j + argc_shift]);

                while (read(fd[j], &c, 1) > 0)
                    write(0, &c, 1);
            
            } else {
                printf("%stail: %s: No such file or directory\n", last_line_break ? "" : "\n", argv[j + argc_shift]);
            }
        }
    } else if (mode == 1) {
        for (j = 0; j < file_count; j++) {
            fd[j] = open(argv[j + argc_shift], O_RDONLY);

            if ((fd[j] > 0) || (read(fd[j], &c, 1) == 0)) {
                // retrieving info about last char in file
                curr_pos = lseek(fd[j], -1, SEEK_END);
                read(fd[j], &c, 1);
                last_line_break = c == '\n' ? 1 : 0;
                
                counter = 0;
                curr_pos = lseek(fd[j], 0, SEEK_SET);
                while ((curr_pos > 0) && (counter < (n - 1))) {
                    read(fd[j], &c, 1); // position is shifted forward by 1 byte
                    if (c == '\n') 
                        counter++;
                }

                if (multiple_files)
                    printf("%s==> %s <==\n", last_line_break ? "" : "\n", argv[j + argc_shift]);

                while (read(fd[j], &c, 1) > 0)
                    write(0, &c, 1);
            
            } else {
                printf("%stail: %s: No such file or directory\n", last_line_break ? "" : "\n", argv[j + argc_shift]);
            }
        } 

        close(fd[j]);
    }

    return 0;
}