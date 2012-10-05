//daemon.c//

pid_t pid;

/* Clone ourself - parent gets pid of child, child pid = 0 */
pid = fork();

if (pid < 0)
{
	exit(EXIT_FAILURE);
}

/* Kill the parent */
if (pid > 0)
{
	exit(EXIT_SUCCESS);
}

/* Only child will get to this point */
umask(0);

/* Open syslog */
openlog(argv[0], LOG_NOWAIT|LOG_PID, LOG_USER);

syslog(LOG_NOTICE, "Daemon started successfully\n")

/* Call when deamon finishes running */
closelog();

/* Get rid of process id inherited from parent, 
   create our own process group and become our own process leader */

pid_t sid;

sid = setsid();
if (sid < 0)
{
	syslog(LOG_ERR, "Could not create process group\n");
	exit(EXIT_FAILURE);
}

/* Change working directory to root which cannot me unmounted */

if ((chdir("/")) < 0)
{
	syslog(SYS_ERR, "Could not change working dir to root\n")
	exit(EXIT_FAILURE);
}

/* Close stdin, stdout and stderr as user cannot interact with daemon */
close(STDIN_FILENO);
close(STDOUT_FILENO);
close(STDERR_FILENO);
