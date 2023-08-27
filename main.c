#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

int main ()
{
    int counter = 0, parameter_found = 0, on_star = 0;
    char board[400] = {};
    FILE* ptr;
    char ch;
    int board_size,lenght,width;
    int second_child, third_child, fourth_child;
    
    ptr = fopen("testcase.txt", "r");

    if(NULL == ptr) {
        printf("file could't be opened!\n");

    }

    while(parameter_found < 3)
    {
        if(on_star == 0 && parameter_found == 0)
        {   
            fscanf(ptr, "%d", &board_size);
            on_star = 1;
            parameter_found++;
        }
        else if(on_star == 0 && parameter_found == 1)
        {
            fscanf(ptr, "%d", &lenght);
            on_star = 1;
            parameter_found++;
        }
        else if(on_star == 0 && parameter_found == 2)
        {
            fscanf(ptr, "%d", &width);
            on_star = 1;
            parameter_found++;
        }
        else
        {
            ch = fgetc(ptr);
            if(ch == '*')
            {
                on_star = 0;
            }
        }
    }
    do
    {
        ch = fgetc(ptr);
        if(ch != ' ' && ch != '\n' && ch != EOF && ch != '#')
        {  
            board[counter] = ch;
            counter++;  
        }
    }
    while (ch != EOF);

    fclose(ptr);

    for(int i = 0; i < counter+1; i++)
    {
        printf("%c",board[i]);
    }

    printf("\n");
    int first_child = fork();
    char decode_board[counter];
    if (first_child == 0)
    {
        int counter1 = 0;
        for(int i = 0; i < counter; i++)
        {
            int x = board[counter1];
            if(x >= 97 && x <= 122)
            {
                x-=32;
            }
            decode_board[i] = x-2;
            counter1++;
        }
        int fd = open("sum", O_WRONLY);
        if (fd == -1)
        {
            printf("failed to open\n");
            return 1;
        }
        if(write(fd, decode_board, sizeof(char) * (counter)) == -1)
        {
            printf("failed to write\n");
            return 2;
        }
        close(fd);
        return 6;
    }
    else
    {
        int fd = open("sum", O_RDONLY);
        if (fd == -1)
        {
            printf("failed to open\n");
            return 1;
        }
        if(read(fd, decode_board, sizeof(char)* (counter)) == -1)
        {
            printf("failed to read\n");
            return 2;
        }
        close(fd);
    }
    printf("\n");
    for(int i = 0; i< counter;i++)
    {
        printf("%c", decode_board[i]);
        if(i % board_size == board_size - 1)
        {
            printf("\n");
        }
    }
    second_child = fork();
    if(second_child != 0)
    {
        third_child = fork();
        if(third_child != 0)
        {
            fourth_child = fork();
        }
    }
    if(second_child == 0)
    {
        printf("this is second child and i check the culs!\n");
        char new_board[counter];
        int found_problem = 0;
        int fd1 = open("cul", O_RDONLY);
        if (fd1 == -1)
        {
            printf("failed to open\n");
            return 1;
        }
        if(read(fd1, new_board, sizeof(char)* (counter)) == -1)
        {
            printf("failed to read\n");
            return 2;
        }
        close(fd1);
        int counter1 = 0;
        char board_2d[board_size][board_size];
        for(int i = 0; i < board_size; i++)
        {
            for(int j = 0; j< board_size; j++)
            {
                board_2d[i][j] = new_board[counter1];
                counter1++;
            }
        }
        for(int i = 0; i < board_size-1; i++)
        {
            for(int j = 0;j<board_size; j++)
            {
                char temp = board_2d[i][j];
                for(int f = i + 1; f < board_size; f++)
                {
                    if (temp == board_2d[f][j])
                    {
                        found_problem = 1;
                    }
                }
            }
        }
        int fd3 = open("cul", O_WRONLY);
        if (fd3 == -1)
        {
            printf("failed to open\n");
            return 1;
        }
        if(write(fd3, &found_problem, sizeof(int)) == -1)
        {
            printf("failed to write\n");
            return 2;
        }
        close(fd3);
        
        return 4;
    }
    else if(third_child == 0)
    {
        printf("this is third child and i check the rows!\n");
        char new_board[counter];
        int found_problem = 0;
        int fd2 = open("row", O_RDONLY);
        if (fd2 == -1)
        {
            printf("failed to open\n");
            return 1;
        }
        if(read(fd2, new_board, sizeof(char)* (counter)) == -1)
        {
            printf("failed to read\n");
            return 2;
        }
        close(fd2);
        int counter1 = 0;
        char board_2d[board_size][board_size];
        for(int i = 0; i < board_size; i++)
        {
            for(int j = 0; j< board_size; j++)
            {
                board_2d[i][j] = new_board[counter1];
                counter1++;
            }
        }
        for(int i = 0; i < board_size; i++)
        {
            for(int j = 0;j<board_size-1; j++)
            {
                char temp = board_2d[i][j];
                for(int f = j + 1; f < board_size; f++)
                {
                    if (temp == board_2d[i][f])
                    {
                        found_problem = 1;
                    }
                }
            }
        }
        int fd4 = open("row", O_WRONLY);
        if (fd4 == -1)
        {
            printf("failed to open\n");
            return 1;
        }
        if(write(fd4, &found_problem, sizeof(int)) == -1)
        {
            printf("failed to write\n");
            return 2;
        }
        close(fd4);
        
        return 4;
    }
    else if(fourth_child == 0)
    {
        printf("this is fourth child and i check the rectangles\n");
        char new_board[counter];
        int found_problem = 0;
        int fd5 = open("rec", O_RDONLY);
        if (fd5 == -1)
        {
            printf("failed to open\n");
            return 1;
        }
        if(read(fd5, new_board, sizeof(char)* (counter)) == -1)
        {
            printf("failed to read\n");
            return 2;
        }
        close(fd5);
        int counter1 = 0;
        char board_2d[board_size][board_size];
        for(int i = 0; i < board_size; i++)
        {
            for(int j = 0; j< board_size; j++)
            {
                board_2d[i][j] = new_board[counter1];
                counter1++;
            }
        }

        for(int i = 0; i<board_size; i++)
        {
            for(int j = 0; j<board_size; j++)
            {
                char temp = board_2d[i][j];
                int x = i % lenght;
                int x1 = i - x;
                int y = j % width;
                int y1 = j - y;
                for(int m = x1; m < x1 + lenght; m++)
                {
                    for(int n = y1; n < y1 + width; n++)
                    {
                        if (temp == board_2d[m][n])
                        {
                            found_problem += 1;
                        }
                    }
                }
            }
        }
        if(found_problem > counter)
        {
            found_problem = 1;
        }
        else
        {
            found_problem = 0;
        }
        int fd6 = open("rec", O_WRONLY);
        if (fd6 == -1)
        {
            printf("failed to open\n");
            return 1;
        }
        if(write(fd6, &found_problem, sizeof(int)) == -1)
        {
            printf("failed to write\n");
            return 2;
        }
        close(fd6);
        return 4;
    }
    else
    {
        printf("this is parent\n");
        int row_problem = 0, cul_problem = 0, rec_problem = 0;
        int fd1 = open("cul", O_WRONLY);
        if (fd1 == -1)
        {
            printf("failed to open\n");
            return 1;
        }
        if(write(fd1, decode_board, sizeof(char) * (counter)) == -1)
        {
            printf("failed to write\n");
            return 2;
        }
        close(fd1);
        int fd2 = open("row", O_WRONLY);
        if (fd2 == -1)
        {
            printf("failed to open\n");
            return 1;
        }
        if(write(fd2, decode_board, sizeof(char) * (counter)) == -1)
        {
            printf("failed to write\n");
            return 2;
        }
        close(fd2);

        int fd5 = open("rec", O_WRONLY);
        if (fd5 == -1)
        {
            printf("failed to open\n");
            return 1;
        }
        if(write(fd5, decode_board, sizeof(char) * (counter)) == -1)
        {
            printf("failed to write\n");
            return 2;
        }
        close(fd5);

        int fd3 = open("cul", O_RDONLY);
        if (fd3 == -1)
        {
            printf("failed to open\n");
            return 1;
        }
        if(read(fd3, &cul_problem, sizeof(int)) == -1)
        {
            printf("failed to read\n");
            return 2;
        }
        close(fd3);

        int fd4 = open("row", O_RDONLY);
        if (fd4 == -1)
        {
            printf("failed to open\n");
            return 1;
        }
        if(read(fd4, &row_problem, sizeof(int)) == -1)
        {
            printf("failed to read\n");
            return 2;
        }
        close(fd4);

        int fd6 = open("rec", O_RDONLY);
        if (fd6 == -1)
        {
            printf("failed to open\n");
            return 1;
        }
        if(read(fd6, &rec_problem, sizeof(int)) == -1)
        {
            printf("failed to read\n");
            return 2;
        }
        close(fd6);
        printf("cul problem = %d row prublem = %d rec problem = %d\n", cul_problem, row_problem, rec_problem);
        if(cul_problem + row_problem + rec_problem == 0)
        {
            printf("Sudoku Puzzle constraints satisfied\n");
        }
        else
        {
            printf("Sudoku Puzzle is Wrong\n");
        }
    }
    return 0;
}
