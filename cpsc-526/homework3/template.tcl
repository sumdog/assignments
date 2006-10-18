#!/usr/bin/env ns
set ns [new Simulator]

set nf [open out.nam w]
$ns namtrace-all $nf

proc finish {} {
	global ns nf
	$ns flush-trace
	close $nf
	exec nam out.nam &
	exit 0
}

#insert code for topology creation and agent definition

ns at 5.0 "finish"
$ns run
