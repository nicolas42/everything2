#include <stdio.h>
#include <errno.h>
/* For strerrno. */
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
/* For "pipe". */
#include <unistd.h>
/* For "exit". */
#include <stdlib.h>

/* Close a file descriptor, and exit if there was an error. */

static void
close_or_die (int fd)
{
    int status;
    status = close (fd);
    if (status != 0) {
	fprintf (stderr, "close %d failed: %s\n", fd, strerror (errno));
	exit (EXIT_FAILURE);
    }
}

/* Run the command and print it to the pipe's write descriptor
   "outfd". */

static void
run_command (int outfd, char* command)
{
    int status;
//    char * command;
    char * argv[4] = {
	"sh",
	"-c",
	0,
	0,
    };
    if (outfd != STDOUT_FILENO) {
	status = dup2 (outfd, STDOUT_FILENO);
	if (status == -1) {
	    fprintf (stderr, "dup2 %d failed: %s\n", outfd, strerror (errno));
	    exit (EXIT_FAILURE);
	}
    }
    close_or_die (outfd);
//    command = "ls -l";
    argv[2] = command;
    execve ("/bin/sh", argv, 0);
    fprintf (stderr, "execve %s returned.\n", command);
    exit (EXIT_FAILURE);
}

#define SIZE 0x100

static void
read_print_pipe (FILE * p)
{
    char buf[SIZE];
    while (! feof (p)) {
	int bytes;
	bytes = fread (buf, sizeof (char), SIZE, p);
	printf ("%.*s", bytes, buf);
    }
}

int run_command_main (char *command)
{
    pid_t pid;
    int status;
    int pfd[2];
    FILE * p;
    status = pipe (pfd);
    if (status != 0) {
	fprintf (stderr, "Error with pipe: %s\n", strerror (errno));
	exit (EXIT_FAILURE);
    }
    pid = vfork ();
    if (pid < 0) {
	fprintf (stderr, "Error with fork: %s\n", strerror (errno));
	exit (EXIT_FAILURE);
    }
    if (pid == 0) {
	close_or_die (pfd[0]);
	run_command (pfd[1], command);
	exit (EXIT_SUCCESS);
    }
    close_or_die (pfd[1]);
    p = fdopen (pfd[0], "r");
    read_print_pipe (p);
    fclose (p);
    wait4 (pid, & status, 0, 0);
    if (status != 0) {
	fprintf (stderr, "Bad status %d from child.\n", status);
	exit (EXIT_FAILURE);
    }
    return 0;
}

int main(int argc, char **argv)
{
    char *command = argv[1];
    run_command_main(command);
    return 0;
}

/*
Examples
---------------------------
gcc run_command.c ; ./a.out "ls -l"
gcc run_command.c ; ./a.out ls
*/
