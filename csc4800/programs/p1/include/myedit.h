#define WINSTRING \
        "#package require Tk\n"\
        "\n"\
        "########################################################\n"\
        "# Create the gui                                       #\n"\
        "########################################################\n"\
        "proc createMainWin {} {\n"\
        "	tk appname \"Edit\"\n"\
        "	catch {console hide}\n"\
        "	set ::tcl_interactive 0\n"\
        "	# First, lets create the menu\n"\
        "	menu .menubar -type menubar\n"\
        "	.menubar add cascade -label File -menu .menubar.file -underline 0\n"\
        "\n"\
        "	#file menu\n"\
        "	menu .menubar.file -tearoff 0\n"\
        "	.menubar.file add command -label \"New\" -underline 0 \\\n"\
        "		-command { new }\n"\
        "	.menubar.file add command -label \"Open...\" -underline 0 \\\n"\
        "		-command { file_get }\n"\
        "	.menubar.file add command -label \"Save\" -underline 0 \\\n"\
        "		-command {  save}\n"\
        "	.menubar.file add command -label \"Save As...\" -underline 5 \\\n"\
        "		-command { file_save_as }\n"\
        "	.menubar.file add separator\n"\
        "	.menubar.file add command -label \"Compile\" -underline 0 \\\n"\
        "		-command { onCompile }\n"\
        "	.menubar.file add separator\n"\
        "	.menubar.file add command -label Exit -underline 1 -command { exit}\n"\
        "\n"\
        "	. configure -menu .menubar\n"\
        "\n"\
        "\n"\
        "	# Now create the editor window\n"\
        "	frame .text\n"\
        "	text .text.t -wrap none -bg white \\\n"\
        "		-yscrollcommand {.text.v_scroll set} \\\n"\
        "		-xscrollcommand {.text.h_scroll set}\n"\
        "\n"\
        "	scrollbar .text.v_scroll -command \".text.t yview\"\n"\
        "	scrollbar .text.h_scroll -command \".text.t xview\" -orient horizontal\n"\
        "	pack .text.v_scroll -side right -fill y\n"\
        "	pack .text.h_scroll -side bottom -fill x\n"\
        "	pack .text.t -side left -fill both -expand 1\n"\
        "	pack .text -fill both -expand 1\n"\
        "\n"\
        "	# now create the messages windo\n"\
        "	frame .frMesg\n"\
        "	text .frMesg.txtMesg -state disabled -height 5	\\\n"\
        "		-yscrollcommand {.frMesg.v_scroll set} \\\n"\
        "		-xscrollcommand {.frMesg.h_scroll set}\n"\
        "\n"\
        "	scrollbar .frMesg.v_scroll -command \".frMesg.txtMesg yview\"\n"\
        "	scrollbar .frMesg.h_scroll -command \".frMesg.txtMesg xview\" -orient horizontal\n"\
        "	pack .frMesg.v_scroll -side right -fill y\n"\
        "	pack .frMesg.h_scroll -side bottom -fill x\n"\
        "	pack .frMesg.txtMesg -side left -fill both -expand 1\n"\
        "	pack .frMesg -fill both -expand 1\n"\
        "\n"\
        "}\n"\
        "\n"\
        "# The currently loaded file\n"\
        "set filename \"\"\n"\
        "\n"\
        "####################################################\n"\
        "# This proc is run when the user selects \"Compile\" #\n"\
        "# from the menu                                    #\n"\
        "####################################################\n"\
        "proc onCompile {} {\n"\
        "	#puts \"files: $::filename [file rootname $::filename].exe\";\n"\
        "	flush stdout;\n"\
        "	set msg \"\"\n"\
        "	if {[catch {compile $::filename [file rootname $::filename].exe} results]} {\n"\
        "		set msg $results\n"\
        "	} else {\n"\
        "		catch {\n"\
        "			set fd [open \"outfile.txt\" r]\n"\
        "			set msg [read $fd]\n"\
        "			close $fd\n"\
        "		}\n"\
        "	}\n"\
        "	if {$msg == \"\"} {\n"\
        "		set msg \"Success.\"\n"\
        "	}\n"\
        "	#tk_messageBox -title \"Compile\" -message $msg\n"\
        "	.frMesg.txtMesg configure -state normal \n"\
        "	.frMesg.txtMesg delete 1.0 end\n"\
        "	.frMesg.txtMesg insert end $msg\n"\
        "	.frMesg.txtMesg configure -state disabled \n"\
        "	\n"\
        "}\n"\
        "\n"\
        "############################################\n"\
        "# We start off with an empty editor        #\n"\
        "# This proc is called when the user        #\n"\
        "# selects \"New\" from the menu.             #\n"\
        "############################################\n"\
        "proc new { } {\n"\
        "	.text.t delete 1.0 end\n"\
        "	set ::filename \"\"\n"\
        "	wm title . $::filename\n"\
        "}\n"\
        "\n"\
        "############################################\n"\
        "# This proc is called when the user        #\n"\
        "# selects \"Open\" from the menu.            #\n"\
        "############################################\n"\
        "proc file_get { } {\n"\
        "	set file_types {\n"\
        "		{\"C files\" { .c } }\n"\
        "		{\"All Files\" * }\n"\
        "	}\n"\
        "	set fn \"\"\n"\
        "	set fn [tk_getOpenFile -filetypes $file_types -initialdir pwd \\\n"\
        "			-defaultextension .c]\n"\
        "	if {$fn == \"\"} {\n"\
        "		return\n"\
        "	}\n"\
        "	set ::filename $fn\n"\
        "	.text.t delete 1.0 end\n"\
        "	set filesize [file size $::filename]\n"\
        "	set fileid [open $::filename r]\n"\
        "	set data [read $fileid $filesize]\n"\
        "	close $fileid\n"\
        "	.text.t insert end $data\n"\
        "	wm title . $::filename\n"\
        "}\n"\
        "\n"\
        "############################################\n"\
        "# This proc is called when the user        #\n"\
        "# selects \"Save\" from the menu.            #\n"\
        "############################################\n"\
        "proc save { } {\n"\
        "	set data [.text.t get 1.0 {end -1c}]\n"\
        "	if {![info exists ::filename] || [string equal $::filename \"\"]} {\n"\
        "		puts \"$::filename [info exists ::filename] [string equal $::filename {}]\"\n"\
        "		set ::filename \"\"\n"\
        "		file_save_as\n"\
        "		return\n"\
        "	}\n"\
        "	if {$::filename == \"\"} { return }\n"\
        "	set fileid [open $::filename w]\n"\
        "	puts -nonewline $fileid $data\n"\
        "	close $fileid\n"\
        "}\n"\
        "\n"\
        "############################################\n"\
        "# This proc is called when the user        #\n"\
        "# selects \"Save as\" from the menu.            #\n"\
        "############################################\n"\
        "proc file_save_as { } {\n"\
        "	global filename\n"\
        "	set data [.text.t get 1.0 {end -1c}]\n"\
        "	set file_types {\n"\
        "		{\"C files\" { .c } }\n"\
        "		{\"All Files\" * }\n"\
        "	}\n"\
        "\n"\
        "	set filename [tk_getSaveFile -filetypes $file_types\\\n"\
        "			-initialdir pwd -initialfile $filename\\\n"\
        "			-defaultextension .c]\n"\
        "	if {$::filename == \"\"} { return }\n"\
        "	wm title . $filename\n"\
        "	set fileid [open $filename w]\n"\
        "	puts -nonewline $fileid $data\n"\
        "	close $fileid\n"\
        "}\n"\
        "\n"\
        "# lets go...\n"\
        "createMainWin\n"\
        ""
