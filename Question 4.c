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