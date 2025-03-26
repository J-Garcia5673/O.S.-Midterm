int main() {
    int process = fork();
    if (process == 0) {
        close(STDOUT_FILENO);  
        printf("This text will not print.\n");
    } else {
        printf("This text will print.\n");
    }
    return 0;
}

/*
Here, the parent process will print to the console, however, 
because the child process closed the standard output, it will 
not be able to print to the console. 
*/