#package require Tk

########################################################
# Create the gui                                       #
########################################################
proc createMainWin {} {
	tk appname "Edit"
	catch {console hide}
	set ::tcl_interactive 0
	# First, lets create the menu
	menu .menubar -type menubar
	.menubar add cascade -label File -menu .menubar.file -underline 0

	#file menu
	menu .menubar.file -tearoff 0
	.menubar.file add command -label "New" -underline 0 \
		-command { new }
	.menubar.file add command -label "Open..." -underline 0 \
		-command { file_get }
	.menubar.file add command -label "Save" -underline 0 \
		-command {  save}
	.menubar.file add command -label "Save As..." -underline 5 \
		-command { file_save_as }
	.menubar.file add separator
	.menubar.file add command -label "Compile" -underline 0 \
		-command { onCompile }
	.menubar.file add separator
	.menubar.file add command -label Exit -underline 1 -command { exit}

	. configure -menu .menubar


	# Now create the editor window
	frame .text
	text .text.t -wrap none -bg white \
		-yscrollcommand {.text.v_scroll set} \
		-xscrollcommand {.text.h_scroll set}

	scrollbar .text.v_scroll -command ".text.t yview"
	scrollbar .text.h_scroll -command ".text.t xview" -orient horizontal
	pack .text.v_scroll -side right -fill y
	pack .text.h_scroll -side bottom -fill x
	pack .text.t -side left -fill both -expand 1
	pack .text -fill both -expand 1

	# now create the messages windo
	frame .frMesg
	text .frMesg.txtMesg -state disabled -height 5	\
		-yscrollcommand {.frMesg.v_scroll set} \
		-xscrollcommand {.frMesg.h_scroll set}

	scrollbar .frMesg.v_scroll -command ".frMesg.txtMesg yview"
	scrollbar .frMesg.h_scroll -command ".frMesg.txtMesg xview" -orient horizontal
	pack .frMesg.v_scroll -side right -fill y
	pack .frMesg.h_scroll -side bottom -fill x
	pack .frMesg.txtMesg -side left -fill both -expand 1
	pack .frMesg -fill both -expand 1

}

# The currently loaded file
set filename ""

####################################################
# This proc is run when the user selects "Compile" #
# from the menu                                    #
####################################################
proc onCompile {} {
	#puts "files: $::filename [file rootname $::filename].exe";
	flush stdout;
	set msg ""
	if {[catch {compile $::filename [file rootname $::filename].exe} results]} {
		set msg $results
	} else {
		catch {
			set fd [open "outfile.txt" r]
			set msg [read $fd]
			close $fd
		}
	}
	if {$msg == ""} {
		set msg "Success."
	}
	#tk_messageBox -title "Compile" -message $msg
	.frMesg.txtMesg configure -state normal 
	.frMesg.txtMesg delete 1.0 end
	.frMesg.txtMesg insert end $msg
	.frMesg.txtMesg configure -state disabled 
	
}

############################################
# We start off with an empty editor        #
# This proc is called when the user        #
# selects "New" from the menu.             #
############################################
proc new { } {
	.text.t delete 1.0 end
	set ::filename ""
	wm title . $::filename
}

############################################
# This proc is called when the user        #
# selects "Open" from the menu.            #
############################################
proc file_get { } {
	set file_types {
		{"C files" { .c } }
		{"All Files" * }
	}
	set fn ""
	set fn [tk_getOpenFile -filetypes $file_types -initialdir pwd \
			-defaultextension .c]
	if {$fn == ""} {
		return
	}
	set ::filename $fn
	.text.t delete 1.0 end
	set filesize [file size $::filename]
	set fileid [open $::filename r]
	set data [read $fileid $filesize]
	close $fileid
	.text.t insert end $data
	wm title . $::filename
}

############################################
# This proc is called when the user        #
# selects "Save" from the menu.            #
############################################
proc save { } {
	set data [.text.t get 1.0 {end -1c}]
	if {![info exists ::filename] || [string equal $::filename ""]} {
		puts "$::filename [info exists ::filename] [string equal $::filename {}]"
		set ::filename ""
		file_save_as
		return
	}
	if {$::filename == ""} { return }
	set fileid [open $::filename w]
	puts -nonewline $fileid $data
	close $fileid
}

############################################
# This proc is called when the user        #
# selects "Save as" from the menu.            #
############################################
proc file_save_as { } {
	global filename
	set data [.text.t get 1.0 {end -1c}]
	set file_types {
		{"C files" { .c } }
		{"All Files" * }
	}

	set filename [tk_getSaveFile -filetypes $file_types\
			-initialdir pwd -initialfile $filename\
			-defaultextension .c]
	if {$::filename == ""} { return }
	wm title . $filename
	set fileid [open $filename w]
	puts -nonewline $fileid $data
	close $fileid
}

# lets go...
createMainWin
