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

     proc wakeup {} {
          after idle [this]::playGame
     }

     proc playGame {} {
       set others [::comm:comm send $::Spackle::AgentSrvr::remoteInterp
           ::Spackle::Portal::who]
       if {[llength $others] > 0} {
         #pick one at random
	 array set aothers $others
	 set names [array names aothers]
	 set size  [llength $names]
	 set which [expr {int (rand()*$size)}]
	 set name  [lindex $names $which]
	 set otherinterp $aothers($name)
	 #call tag
	 if {[catch {::comm:comm send $otherinterp ${name}::tag} result
	   logit "[this]: I missed $name"
	 } else {
	   logit "[this]: You're out $name"
	 }
        } else {
	   logit "[this]: No one to tag!"
	}
     }



 #
 #
 #
 #
 #
proc main {} {
  set computers [lrange $::argv 1 end]
  set count [lindex $::argv 0]
  set fd [open [file join [pwd] taggame.log] "w"]
  close $fd
  for {set k 0} {$k < $count} {incr k} {

    createObject ::tagobject$k

    ::tagobject${k}::setMachines $computers
    set size [llength $computers]
    set which [expr {int (rand()*$size)}]
    set machine [lindex $computers $which]
    set ::tagobject${k}::thisComputer $machine

    puts "phasing to $machine..."

    if{[catch {set interp [::Spackle::Portal::phase ::tagobject$k
       ::tagobject$k $machine]} result]} {
       puts $result
       puts $errorInfo
       puts "Done."
       exit 1
    }
  }
  puts "Done."
}
