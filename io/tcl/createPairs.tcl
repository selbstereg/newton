#!/usr/bin/tclsh

proc arePairsEqual {pair1 pair2} {
	if {[lindex $pair1 0] == [lindex $pair2 0]} {
		if {[lindex $pair1 1] == [lindex $pair2 1]} {
			return "true"
		}
	} elseif {[lindex $pair1 0] == [lindex $pair2 1]} {
		if {[lindex $pair1 1] == [lindex $pair2 0]} {
			return "true"
		}
	}
	return "false"
}

set trianFile [open "../t05120_a5.0Sphere/triangles" "r"]

gets $trianFile numTrians

# Read trinangles from file.
set triangles ""
while {[gets $trianFile line] >= 0} {
	set triangle "[lindex $line 0] [lindex $line 1] [lindex $line 2]"
	set triangles "$triangles {$triangle}"
}

# Create the pairs.
set pairs ""
for {set i 0} {$i < $numTrians} {incr i} {
	set triangle [lindex $triangles $i]
	set pair1 "[lindex $triangle 0] [lindex $triangle 1]"
	set pair2 "[lindex $triangle 0] [lindex $triangle 2]"
	set pair3 "[lindex $triangle 1] [lindex $triangle 2]"

	set pairs "$pairs {$pair1} {$pair2} {$pair3}"
}

# Sort out double pairs.
set uniquePairs ""
for {set i 0} {$i < [llength $pairs]} {incr i} {
	set curPair [lindex $pairs $i]
	set isInList "false"
	for {set j 0} {$j < [llength $uniquePairs]} {incr j} {
		
		set curUniquePair [lindex $uniquePairs $j]
		if {[arePairsEqual $curPair $curUniquePair]} {
			set isInList "true"
			continue
		}
	}
	if {$isInList == "false"} {
		set uniquePairs "$uniquePairs {$curPair}"
	}
}

set outFile [open "pairs" "w"]

for {set i 0} {$i < [llength $uniquePairs]} {incr i} {
	puts $outFile "[lindex $uniquePairs $i] 2"
}
