#!/usr/bin/tclsh
lappend auto_path ../tcllib/lib/tcllib1.3
source spackle.tcl

Spackle::AgentSrvr::startAgent [lindex $argv 0] [lindex $argv 1]
