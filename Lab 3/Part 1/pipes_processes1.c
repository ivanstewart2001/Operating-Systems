#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 
  
int main() 
{ 
    int fd[2][2];
  
    char fixed_str1[] = "howard.edu"; 
    char input_str[100]; 
    pid_t p; 
  
    if (pipe(fd[0])==-1) 
    { 
        fprintf(stderr, "Pipe Failed" ); 
        return 1; 
    } 
    if (pipe(fd[1])==-1) 
    { 
        fprintf(stderr, "Pipe Failed" ); 
        return 1; 
    } 
  
    printf("Enter a string to concatenate: ");
    scanf("%s", input_str); 
    p = fork(); 
  
    if (p < 0) 
    { 
        fprintf(stderr, "fork Failed" ); 
        return 1; 
    } 

    else if (p > 0) 
    {   
        close(fd[0][0]);
        close(fd[1][1]);
   
        write(fd[0][1], input_str, strlen(input_str)+1); 

        wait(NULL); 

        char concat_str[100];  
        read(fd[1][0], concat_str, 100);  

        printf("Concatenated string: %s\n", concat_str);

        close(fd[0][1]);
        close(fd[1][0]);
    } 
  
    else
    {   
        close(fd[0][1]);
        close(fd[1][0]);

        char concat_str[100];  
        read(fd[0][0], concat_str, 100);  

        int k = strlen(concat_str);  
        int i;  
        for (i=0; i<strlen(fixed_str1); i++)  
            concat_str[k++] = fixed_str1[i];  

        concat_str[k] = '\0';  

        printf("Concatenated string: %s\n", concat_str);

         printf("Enter a second string to concatenate: ");
         scanf("%s", input_str);

         strcat(concat_str, input_str);

         write(fd[1][1], concat_str, strlen(concat_str)+1);

         close(fd[0][0]);
         close(fd[1][1]);

         exit(0);
     }
}








