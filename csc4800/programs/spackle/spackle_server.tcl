#!/usr/bin/tclsh
if {![info exists env(SPACKLE_HOME)]} {
	set spackleHome ./
} else {
	set spackleHome $env(SPACKLE_HOME)
}

lappend auto_path $spackleHome
package require Spackle

if {$argc != 1} {
	if {$argc > 1} {
		puts stderr "usage: $argv0 ?port?"
		exit 1
	}
	set port 9002
} else {
	set port [lindex $argv 0]
}

puts "Starting server on port $port..."
Spackle::Portal::startServer $port
puts "Shutting down"
