int main() {
	pid_t pid = fork();
	if(pid == 0) {
		printf(“Hello\n”);
	}
	else {
	waitpid(pid, NULL,0);
	printf(“Goodbye\n”);
	}
	return 0;
}
