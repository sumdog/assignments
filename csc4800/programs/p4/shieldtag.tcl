#!/usr/bin/tclsh
if {![info exists env(SPACKLE_HOME)]} {
    set spackleHome ./
} else {
    set spackleHome $env(SPACKLE_HOME)
}
lappend auto_path $spackleHome
package require Spackle
proc createObject {oname} {
    namespace eval $oname {
	variable thisComputer ""
	variable logfile [pwd]/taggame.log
	variable shield
	variable visited

	proc wakeup {} {
	    after idle [this]::playGame
	}

	proc playGame {} {
	    variable visited

	    set others [::comm::comm send $::Spackle::AgentSrvr::remoteInterp \
			    ::Spackle::Portal::who]
	    if {[llength $others] > 0} {
		# pick one at random
		array set aothers $others
		set names [array names aothers]
		set size [llength $names]
		set which [expr {int (rand()*$size)}]
		#increment value of selected computer (at this point we haven't visited any)
		lset visited $which 1
		set name [lindex $names $which]
		set otherinterp $aothers($name)
		# call tag
		if {[catch {::comm::comm send $otherinterp ${name}::tag} results]} {
		    logit "[this]: I missed $name!"
		} else {
		    logit "[this]: I hit $name!"
		}
	    } else {
		logit "[this]: No one to tag!"
	    }
	    # add self to registry
	    set j [::comm::comm send $::Spackle::AgentSrvr::remoteInterp \
		       ::Spackle::Portal::registerMe [this] [::comm::comm self]]
	    # Let others have a chance
	    set waitTime [expr {int (rand()*3000) + 2000}]
	    #set waitTime 5000
	    after $waitTime [this]::moveOn
	}

	proc moveOn {} {
	    variable computers
	    variable thisComputer
	    variable visited
	    # remove self from registry
	    ::comm::comm send $::Spackle::AgentSrvr::remoteInterp \
		::Spackle::Portal::unregisterMe [this]

	    #if every computer has been visited twice
	    #reset the list
	    set alltwice 0
	    foreach i $visited {
		if [expr $i < 2] {
		    set alltwice 1
		}
	    }
	    if { [expr $alltwice == 0] } {
		for {set y 0} {$y < [llength $visited]} { incr y } {
		    lset visited $y 0
		}
	    }

	    # pick random machine
	    set size [llength $computers]
	    while {1} {
		flush stdout
		set which [expr {int (rand()*$size)}]

		#check to see if we've visited this computer twice
		set twice 0 
		if { [lindex $visited $which] >= 2  } {
		    set twice 1
		}

		set machine [lindex $computers $which]
		if {$thisComputer != $machine} {
		    if { $twice == 0 } {
			break;
		    }
		}
		#If we get here, then we chose ourself || we've hit this place twice, try again
	    }
	    set thisComputer $machine
	    # move
	    # We can do this becuase it only set a flag, and the server kills us at
	    # its leasure
	    ::Spackle::AgentSrvr::die
	    ::Spackle::Portal::phase [this] [this] $machine
	}

	proc setShield {s} {
	    variable shield
	    set shield $s
	}
	    

	proc setMachines {mList} {
	    variable computers
	    #build list of visited comps and set them to 0
	    variable visited
	    set visited [list 0]
	    for {set x 0} {$x <= [llength $mList]} {incr x} {
		lappend visited 0
	    }
	    set computers $mList	    
	}

	proc this {} {
	    return [namespace current]
	}

	proc logit {msg} {
	    variable thisComputer
	    variable logfile
	    catch {
		set fd [open $logfile "a"]
		puts $fd "[format %-30s *$thisComputer*] $msg"
		close $fd
	    }
	}

	proc tag {} {
	    variable shield
	    set shield [expr $shield - 1]
	    if { [expr $shield > 0] } {
		logit "[this]: Shields down to $shield"
	    } else {
		::comm::comm send $::Spackle::AgentSrvr::remoteInterp \
		    ::Spackle::Portal::unregisterMe [this]
		logit "[this]: Shields down! I'm out"
		after 1000 {::Spackle::AgentSrvr::die}
	    }
	}
    }
}
proc main {} {
    # argv 1 is number of tag objects, rest if list of machines
    set computers [lrange $::argv 2 end]
    set count [lindex $::argv 1]
    set shield [lindex $::argv 0]
    set fd [open [pwd]/taggame.log "w"]
    close $fd
    for {set k 0} {$k < $count} {incr k} {
	createObject ::tagobject$k
	::tagobject${k}::setMachines $computers
	::tagobject${k}::setShield $shield
	set size [llength $computers]
	set which [expr {int (rand()*$size)}]
	set machine [lindex $computers $which]
	set ::tagobject${k}::thisComputer $machine
	puts "phasing to $machine..."
	if {[catch {set interp [::Spackle::Portal::phase ::tagobject$k \
				    ::tagobject$k $machine]} result]} {
	    puts $result
	    puts $errorInfo
	    puts "Done."
	    exit 1
	}
    }
    puts "Done."
}
main