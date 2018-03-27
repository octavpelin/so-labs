#include <stdlib.h>
#include <stdio.h>

#ifdef __linux__

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int my_system(const char* command) {
	pid_t pid;
	int status;
	const char *argv[] = {command, NULL};

	pid = fork();	// simultaneity - SOMA
	switch(pid) {
		case -1:
			/* error forking*/
			return EXIT_FAILURE;
		case 0:
			/* child process */
			execvp(command, (char* const*) argv);

			/* only if exec failed */
			exit(EXIT_FAILURE);
		default:
			/* parent process */
			break;
	}

	/* only if parent process gets here */
	waitpid(pid, &status, 0);
	if(WIFEXITED(status))
		printf("Child %d terminated normally, with code %d\n",
			pid, WEXITSTATUS(status));
	return status;
}

#elif defined(_WIN32)

#include <windows.h>
#include <string.h>

#include "utils.h"

void CloseProcess(LPPROCESS_INFORMATION lppi) {
	CloseHandle(lppi->hThread);
	CloseHandle(lppi->hProcess);
}

#endif


int main(void) {
	#ifdef __linux__

	my_system("ls");
	return 0;

	#elif defined(_WIN32)

	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	DWORD dwRes;
	BOOL bRes;
	CHAR cmdLine[] = "mspaint"

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	/* Start child process */
	bRes = CreateProcess(
			NULL,
			cmdLine,
			NULL,
			NULL,
			FALSE,
			0,
			NULL,
			NULL,
			&si,
			&pi
		);
	DIE(bRes == FALSE, "Create Process");

	/* Wait for the child to finish */
	dwRes = WaitForSingleObject(pi.hProcess, INFINITE);
	DIE(dwRes == WAIT_FAILED, "WaitForSingleObject");

	bRes = GetExitCodeProcess(pi.hProcess, &dwRes);
	DIE(bRes == FALSE, "GetExitCode");

	return 0;

	#endif
}


