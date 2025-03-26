

int main() 
{
    int fileDescriptor = open(“filename.txt”);
    int rc = fork();
    if (rc == 0) { 
        write(fileDescriptor, “This is the child process writing. \n”, 36);
    }
    else { 
        write(fileDescriptor, “This is the parent process writing. \n”, 37);
    }
    close(fileDescriptor);
    }
    