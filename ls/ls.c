#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <limits.h>


static char *option_errmsg = 
"ls: invalid option -- %c\n"
"usage: ls [-al] [file]\n";

static char *dir_errmsg = 
"ls: %s: No such file or directory\n";

enum { FILENAMES_PER_LINE = 5 };

typedef enum Bool 
{
    FALSE = 0,
    TRUE = 1
} Bool;

static Bool a_option = FALSE; // emulates -a
static Bool l_option = FALSE; // emulates -1 (-one)


int get_options(int argc, char *argv[])
{
    int curr_arg = 1;
    int dir_position = 1;
    char *arg_char_pointer;

    // if there is no arguments except command name
    if (argc == 1)
        return dir_position;

    while((argv[curr_arg] != NULL) && (*(arg_char_pointer = argv[curr_arg]) == '-')) {
        arg_char_pointer++;
        while (*arg_char_pointer != '\0') {
            switch (*arg_char_pointer) {
            case 'a':
                a_option = TRUE;
                break;
            case 'l':
                l_option = TRUE;
                break;
            default:
                fprintf(stderr, option_errmsg, *arg_char_pointer);
                return -1;
            }

            arg_char_pointer++;
        }
        dir_position++;
        curr_arg++;
    }

    return dir_position;
}


int main(int argc, char *argv[]) 
{   
    DIR *dir;
    struct dirent *file_info;
    int dir_argv_position;
    short int curr_num_files;

    if ((dir_argv_position = get_options(argc, argv)) < 0)
        exit(1);

    if (argv[dir_argv_position] != NULL) {
        if ((dir = opendir(argv[dir_argv_position])) == NULL) {
            fprintf(stderr, dir_errmsg, argv[dir_argv_position]);
            exit(1);
        }
    } else
        dir = opendir("."); // current directory

    curr_num_files = 1;
    while ((file_info = readdir(dir)) != NULL) {
        if ((*(file_info -> d_name) == '.') && (!a_option))
            continue;

        printf("%-16s%c", file_info -> d_name, 
            (curr_num_files % FILENAMES_PER_LINE == 0) || (l_option) ? '\n' : ' '); 
        curr_num_files++;
    }

    printf("\n");

    closedir(dir);
    exit(0);
}
