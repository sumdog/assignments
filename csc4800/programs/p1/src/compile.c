/* put necessary includes here */


int compile(char *src, char* out) {

	/* remove outfile.txt */

	/* call freopen to make standard error point to outfile.txt */
	/* for a child */
	
	/* Child: call execl to run gcc */
	
	/* Parent: call freopen (on /dev/tty) to restore standard error */

	/* Parent: wait for child */

	/* Return 0 for success, or not zero for failure */
}
