

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
    

/* 
Yes, both the parent and the child can access the file at the same time, since the call 
fork() duplicates the process, and all the variables associated with it. They then execute 
at the same time and write to the file at the same time, although one would appear to be 
finished before the other.
*/