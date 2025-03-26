/*
To write such a shell in C++, refer to the process lecture. As noted in the slide, you can use “execvp()” to create a new child process and have it execute a command. Use also the “waitpid” in the parent process to wait for the child process to finish in case
sequential execution is selected.
For simplicity, assume that the user specifies the full path name for any
command/executable that they wish to execute. Thus, you do not need to deal
with path name completion issues. You can test your shell on programs you
write in C++ (after compiling to machine language).
*/

#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include <cstring>

using namespace std;

int main() {
    string command;
    while (true) {
        cout << "closh> ";
        getline(cin, command);
        if (command.empty()) continue;

        // Convert command string to args array for execvp
        vector<char*> args;
        char* token = strtok(&command[0], " ");
        while (token != nullptr) {
            args.push_back(token);
            token = strtok(nullptr, " ");
        }
        args.push_back(nullptr); // Null-terminate

        cout << "count> ";
        int count;
        cin >> count;
        if (count < 1 || count > 9) {
            cerr << "Count must be between 1 and 9.\n";
            cin.ignore(); // Clear buffer
            continue;
        }

        cout << "[p]arallel or [s]equential> ";
        char mode;
        cin >> mode;
        cin.ignore(); // Clear newline

        vector<pid_t> pids;

        for (int i = 0; i < count; ++i) {
            pid_t pid = fork();
            if (pid < 0) {
                perror("fork");
                exit(1);
            } else if (pid == 0) {
                // Child process
                execvp(args[0], args.data());
                perror("execvp"); // If exec fails
                exit(1);
            } else {
                // Parent process
                if (mode == 's') {
                    // Sequential: wait right after each fork
                    waitpid(pid, nullptr, 0);
                } else if (mode == 'p') {
                    // Parallel: store pid for later wait
                    pids.push_back(pid);
                }
            }
        }

        if (mode == 'p') {
            // Wait for all parallel children
            for (pid_t pid : pids) {
                waitpid(pid, nullptr, 0);
            }
        }
    }

    return 0;
}