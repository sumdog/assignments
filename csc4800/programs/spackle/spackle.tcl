catch {namespace delete Spackle}

package require comm

package provide Spackle 1.0

namespace eval Spackle {


	namespace eval Serializer {

		proc serialize {oldns {newns {}}} {
			if {$newns == {}} {
				set newns $oldns
			}
			set serial "namespace eval $newns {}\n"
			foreach var [info vars ${oldns}::*] {
				set vname [namespace tail $var]
				if {[array exists $var]} {
					append serial \
						"array set ${newns}::$vname \[list [array get $var]\]\n" 
				} else {
					if {[catch {set val [set $var]}]} {
						append serial \
							"namespace eval $newns { variable $vname }\n"
					}	else {		
						append serial \
							"namespace eval $newns { variable $vname {$val} }\n"
					}

				} 		
			}

			set procs [getProcs $oldns]

			foreach p $procs {
				set thisProc [namespace tail $p]
				set thisArgs [info args $p]
				set pargs {}
				foreach i $thisArgs {
					if {[info default $p $i defval]} {
						# puts "DEFAULT!!!"
						lappend pargs "$i {$defval}"
					} else {
						lappend pargs $i
					} 
				}
				set thisBody [info body $p]
				append serial \
					"proc ${newns}::$thisProc \{$pargs\} \{$thisBody\}\n"
			}

			set children [namespace children $oldns]
			foreach child $children {
				#set mychild [string range $child [string length $ns] end]  
				#namespace eval ${parent}::$mychild "inherits $child"
				regsub ^$oldns $child $newns nchild
				#puts "child will be $nchild"
				append serial [serialize $child $nchild]
			}

			return $serial
		}

		proc getProcs {which} {
			set procs {}
			if {$::tcl_version == "8.2"} {
				set temprocs [namespace eval ${which} {info procs}]
				foreach z $temprocs {
					lappend procs "${which}::${z}"
				}
			} else {
				set procs [info procs ${which}::*]
			}

			return $procs

		}

		proc showSerialize {ns1 {ns2 {}}} {
			puts [serialize $ns1 $ns2]
		}
	}

	namespace eval NameServer {
		variable MSG_ERROR -1
		variable MSG_OK 0
		variable MSG_REGISTER 1
		variable MSG_LOOKUP 2 

		variable lookupTab
		variable stopFlag
		
		proc startup {{port 8002}} {
			socket -server [namespace current]::onMessageReady $port

			vwait [namespace current]::stopFlag
		} 

		proc onMessageReady {channel addr port} {
			variable lookupTab
			variable MSG_ERROR
			variable MSG_OK
			variable MSG_REGISTER
			variable MSG_LOOKUP
			gets $channel requestType
			gets $channel name
			if {$requestType == $MSG_REGISTER} { 
				gets $channel value
				set lookupTab($name) $value
				sendMessage $channel $MSG_OK
			} elseif {$requestType == $MSG_LOOKUP} { 
				if {[info exists lookupTab($name)]} {
					sendMessage $channel $MSG_OK $lookupTab($name)
				} else {
					sendMessage $channel \
						$MSG_ERROR "nothing by the name of \"$name\" registered"
				}
			} else {
				sendMessage $channel $MSG_ERROR \
					"Invalid request \"$requestType\", must be \"$MSG_REGISTER\" or \"$MSG_LOOKUP\""
			}
			close $channel
		}

		proc sendMessage {channel args} {
			if {[llength $args] == 0} {
				error "No message type given"
			}
			set msg {}
			foreach i $args {
				append msg $i "\n"
			}
			puts -nonewline $channel $msg
			flush $channel
		}

		proc register {name value server {port 8002}} {
			variable MSG_REGISTER
			variable MSG_ERROR
			
			set sd [socket $server $port]

			sendMessage $sd $MSG_REGISTER $name $value

			gets $sd retVal

			if {$retVal == $MSG_ERROR} {
				gets $sd emsg
				error $emsg	
			}

			close $sd
		}

		proc lookup {name server {port 8002}} {
			variable MSG_LOOKUP
			variable MSG_ERROR

			set sd [socket $server $port]

			sendMessage $sd $MSG_LOOKUP $name

			gets $sd retVal

			if {$retVal == $MSG_ERROR} {
				gets $sd emsg
				error $emsg	
			}

			gets $sd value

			close $sd

			return $value

		}
	}

	namespace eval Portal {
		variable MSG_ERROR -1
		variable MSG_OK 0
		variable MSG_PHASE 1
		variable MSG_DEVAL 2

		variable agentId 0
		variable agentDone 0
		variable myInterpId [::comm::comm interps]

	# array of agents
		variable agentsByName
		variable agentsByInterp
		variable agentsInit

		variable uniqueReturns
		variable returnId 0
		variable CLEANTIME 30000

		variable registered 


		# I use the following procedure to make tcl clean
		#		up defunct processes (don't ask me why it works).
		proc cleanup {} {
			variable CLEANTIME
			set j [exec tclsh exit.tcl &]
			#puts "cleanup $j"
			after $CLEANTIME [namespace current]::cleanup
		}

		proc startServer {{port 9002}} {
			cleanup
			socket -server [namespace current]::onMessageReady $port

			vwait ::stopFlag
		}

		proc onMessageReady {channel addr port} {
			#puts "onMessageReady..."
			gets $channel msgType
			gets $channel handler
			gets $channel dlen
			set data [read $channel $dlen]
			#puts "  calling: $handler $channel $msgType $data"
			if {[catch {set retVal [$handler $channel $msgType $data]} errVal]} {
				puts -nonewline $channel [constructReturn \
							$::Spackle::Portal::MSG_ERROR $errVal]
				flush $channel
				close $channel
				return
			}

			puts -nonewline $channel [constructReturn \
					$::Spackle::Portal::MSG_OK $retVal]	
			flush $channel
			close $channel
		}

		proc constructReturn {msgType data} {
			set msg $msgType
			set dataLen [string length $data]
			append msg "\n" $dataLen "\n"
			append msg $data

			return $msg
		}

		proc constructMsg {msgType handler data} {
			set msg $msgType
			append msg "\n" $handler "\n"
			set dataLen [string length $data]
			append msg $dataLen "\n"
			append msg $data

			return $msg
		}

		proc sendMessage {msgType handler data dest {port 9002}} {
			set channel [socket $dest $port]
			puts $channel [constructMsg $msgType $handler $data]
			flush $channel
			gets $channel line
			set retVal $line
			set retMsg {}
			gets $channel retLen
			if {$retLen > 0} {
				set retMsg [read $channel $retLen]
			}
			close $channel
			return [list $retVal $retMsg]
		}

		proc phase {ns newname dest {port 9002}} {
			set msgType "$::Spackle::Portal::MSG_PHASE"

			set msg [Spackle::Serializer::serialize $ns $newname]
			append msg "\nset ::Spackle::Portal::lastPhase $newname"

			set retVal [sendMessage $msgType \
					::Spackle::Portal::phaseHandler $msg $dest $port]

			set retType [lindex $retVal 0]
			set data [lindex $retVal 1]

			#puts "retType is $retType, data is $data"
			if {$retType == $::Spackle::Portal::MSG_ERROR} {
				error $data
			}

			return $data
		}

		proc queryHandler {channel msgType query} {
			variable agentsByInterp
			if {$msgType != $::Spackle::Portal::MSG_QUERY} {
				error "Unknown message type ($msgType) for query handler"
			}

			set queryType [string tolower [lindex query 0]]
			switch $queryType {
				agentname {
					set agent [lindex query 1]
					return $agentsByInterp($agent)
				}
				default {
					error "Query $queryType not supported"
				}
			}
		}

		proc phaseHandler {channel msgType object} {

			variable agentId	
			variable myInterpId
			variable agentsInit
			#puts "phaseHandler..."	
			#puts "  args are: $channel $msgType $object"
			if {$msgType != $::Spackle::Portal::MSG_PHASE} {
				error "Unknown message type ($msgType) for phase handler" 
			}

			set id [incr agentId]

			set agentsInit($id) $object
			#puts "  creating agent process"	

			if {[catch {set procid [exec agent.tcl $myInterpId $id &]} errVal]} {	
				puts "cannot execute agent: $errVal"
				exit
			}
		
			#puts "Waiting on agentsInit($id) to change"
			vwait [namespace current]::agentsInit($id)
			set retVal [set [namespace current]::agentsInit($id)]

			if { [lindex $retVal 0] != "OK"} {
				error $retVal
			}

			return [lindex $retVal 1]

		}

		proc setupHandler {agent agentInterp} {
			variable agentsInit
			variable agentDone
			variable agentsByInterp
			variable agentsByName

			#puts "setupHandler()"
			if {![info exists agentsInit($agent)]} {
				puts "error: agent $agent does not exist!"
				return
			}

			#puts "  evaling object"
			set ns [::comm::comm send $agentInterp $agentsInit($agent)]
			#puts "  got results of $ns"

			#puts "  calling object wakeup"
			if {[catch {::comm::comm send $agentInterp ${ns}::wakeup} result]} {
				error $result
			}

			set agentsByName($ns) $agentInterp
			set agentsByInterp($agentInterp) $ns	

			#puts "Changed agentsInit($agent)"
			set agentsInit($agent) "OK $agentInterp" 

			set agentDone [expr 1 - $agentDone]

			return
		} 

		proc errorHandler {agent agentInterp erval} {
			variable agentsInit
			::comm::comm shutdown $agentInterp
			set agentsInit($agent) $erval
		}

		proc registerMe {myName myInterp} {
			variable registered
			set registered($myName) $myInterp 
			return [array get registered]
		}
		proc unregisterMe {myName} {
			variable registered
			catch {unset registered($myName)}
			return [array get registered]
		}
		proc who {} {
			variable registered
			return [array get registered]
		}

		proc shutdownHandler {agentInterp} {
			
			variable agentsByInterp
			if {![info exists agentsByInterp($agentInterp)]} {
				error "agent $agentInterp does not exist!"
			}
			::comm::comm shutdown $agentInterp
			#puts "Portal has shut down agent connect."
			unset agentsByInterp($agentInterp)
		}
	}

	namespace eval AgentSrvr {
		variable done
		variable remoteInterp

		proc die {} {
			variable done
			set done 1
		}

		proc startAgent {controllerInterp id} {
			variable done
			variable remoteInterp ""

			# The following command freezes for a long time
			#   when disconnected from network
			::comm::comm config -local 0
			#puts "startAgent()"
			set myInterp [::comm::comm interps]
			#puts "  callback to setupHandler in $controllerInterp..."
			set remoteInterp $controllerInterp
			if {[catch {::comm::comm send $controllerInterp \
				::Spackle::Portal::setupHandler $id $myInterp} errVal]} {
				puts "agent exiting: $errVal"
				::comm::comm send -async $controllerInterp \
					::Spackle::Portal::errorHandler $id $myInterp \{$errVal\}
				::comm::comm abort
				close stdin
				close stdout
				exit 1
			}
			#puts "waiting..."
			vwait ::Spackle::AgentSrvr::done
			#puts "Agent done, exiting process."
			::comm::comm send -async $controllerInterp \
				::Spackle::Portal::shutdownHandler $myInterp 
			::comm::comm abort
			close stdin
			close stdout
			#exit 0
		}
	}

}
