#include <stdio.h>
#include <tcl.h>
#include <tk.h>
#include "myedit.h"


int compileCmd(ClientData clientData, Tcl_Interp *interp,
                int argc, char *argv[]);

int Tcl_AppInit(Tcl_Interp* ti);

int main(int argc, char* argv[]) {

	Tcl_Interp *ti;
	
	ti = Tcl_CreateInterp();

	Tk_Main(argc, argv, Tcl_AppInit);

	return 0;
}

int Tcl_AppInit(Tcl_Interp* ti) {
	int status;
	char* command = "compile";	


	 status = Tcl_Init(ti);

	if (status != TCL_OK) {
		return TCL_ERROR;
	} 

	status = Tk_Init(ti);

	if (status != TCL_OK) {
		return TCL_ERROR;
	}

	if (Tcl_Eval(ti, WINSTRING) != TCL_OK) {
		fprintf(stderr, "Could not load myedit.tcl: ");
		fprintf(stderr, "%s\n", Tcl_GetStringResult(ti));
		exit(1);
	}

	if (Tcl_CreateCommand(ti, command,
			(Tcl_CmdProc *) compileCmd	, NULL, NULL) == NULL) {
			fprintf(stderr, "Cannot create command!\n");
			exit(0);
	}


	return TCL_OK;

}

int compileCmd(ClientData clientData, Tcl_Interp *interp,
                int argc, char *argv[]) {

	char *filename = argv[1];

	if (compile(argv[1], argv[2])) {
		Tcl_SetResult(interp, "Error: Cannot run compiler", TCL_VOLATILE);
		return TCL_ERROR;
	}
	
	return TCL_OK;
}

