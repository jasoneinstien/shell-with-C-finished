//A project which write a shell with c 
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
//initialzation 
#define LSH_RL_BUFSIZE 1024 
#define LSH_TOK_BUFSIZE 64 
#define LSH_TOK_DELIM " \t\r\n\a" 

//Interprert 
//Terminate 
void lsh_loop(void);
char *lsh_read_line(void);
char **lsh_split_line(char*line);
int lsh_launch(char**args);
int lsh_execute(char **args);

int main(int argc , char ** argv ){
    //argc && argv --> load config file , 
    //argv and argc are how command line arguments are passes to main
    //argc --> number of strings pointed to argv 
    //argv --> argument when run the programm ie) ./main a1 a2 a3 ==> argv will be [a1 ,a2 ,a3] 

    lsh_loop();

    return EXIT_SUCCESS;
}


//baisc loop of a shell 
//Read + Parse + Execute 
//Main loop of the shell
void lsh_loop(void){
    char *line;
    char **args;
    int status;  

    do{
        printf(">");
        line = lsh_read_line();
        args = lsh_split_line(line);
        status = lsh_execute(args);

        free(line);
        free(args);

    }while(status);
}

//Read the command from standard input 
//1. Declarations 
//In the loop store a character with int ie)A = 96
//2. EOF --> end of file
//3. Null the current string avoid += string
//4. It is actually getline() function
//old fashion method before getline()
//check buffer + end of file with EOF --> set position be \0 --> if position >= bufsize ==> + BUFSIZE ==> if buffer == 0 after ++ ==> return failure
//using readline function
//read input 
char * lsh_read_line(void){
    char*line = NULL;
    ssize_t bufsize = 0; 
    //getline(input stream , save here , stop when) 
    //return the number of input ==> check it end or not 
    if(getline(&line , &bufsize , stdin) == -1){
       //test the file end or not
        if(feof(stdin)){
            exit(EXIT_SUCCESS); 
        }//one said end , another didn't end
        else{
            //display an error
            perror("readline");
            exit(EXIT_FAILURE);
        }
    }
    //return to next char pointer link list
    return line; 
}
//reminder of readline function 
//if Ctrl-D --> it will consider end of file 
//eithr finish reading whole file or exit successful , an error will not occur


//parsing the line into argv do not allow backslash escaping
//for simplification , treadt white space as seperation 
//using null terminated pointer
//dynamic expading buffer similar to tradition getline method 

char ** lsh_split_line(char* line){
    //static variable
    int bufsize = LSH_TOK_BUFSIZE , position = 0; 
    char ** tokens = malloc(bufsize* sizeof(char*));
    char *token; 
    
    //error when size of the tokens arrary is equals to 0; 
    if(!tokens){
        fprintf(stderr , "lsh : allocation error\n");
        exit(EXIT_FAILURE);
    }
    //strock: return a pointer to the first token ==> return a pointer to within the string you give ie) line
    token = strtok(line , LSH_TOK_DELIM); 

    //the pointer arrary is not null 
    while(token != NULL){
        //shift one to the right 
        tokens[position] = token;
        position++; 
        //when the positiotn > 64 already 
       if(position >= bufsize){
        //dynmaically enlarge the bufsize 
         bufsize += LSH_TOK_BUFSIZE;
         //realloc the space enlarge it
         tokens = realloc(tokens , bufsize * sizeof(char*));
         //check any error 
         if(!tokens){
            fprintf(stderr , "lsh : allocation error \n");
            exit(EXIT_FAILURE);
         }
       }
       //return a pointer that is null with 64 bytes null
       token = strtok(NULL , LSH_TOK_DELIM);
    }
    //set last posnter to NULL 
    tokens[position] =NULL;
    //return the token for next function
    return tokens; 
}


//start working the shekll
//to start the shell you either start by init it when turn the cp or fork system call 
//when the function is called the operation system which should be in two system will run as parents and child
//exec ==> replact the current running program with new one 
int lsh_launch(char ** args){
    pid_t pid , wpid;
    int status;

    pid = fork();

    if(pid == 0){
    
    }
}











