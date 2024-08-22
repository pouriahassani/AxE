
set nfacs [ gtkwave::getNumFacs ]

set dumpname [ gtkwave::getDumpFileName ]
set dmt [ gtkwave::getDumpType ]

puts "number of signals in dumpfile '$dumpname' of type $dmt: $nfacs"

# create a list for the signals we want to add

set signals_to_add [list]

# now we want to add the signals
# a signal can be: TOP.top.full_adder_2.o_cnt[7:0]

# add all the signals that are found

# no newline for the "{" allowed here

for {set i 0} {$i < $nfacs } {incr i} {
    set facname [ gtkwave::getFacName $i ]
    puts "adding: $facname"
    lappend signals_to_add "$facname"
}

lappend signals_to_add "TOP.top.mem.state\[31:0\]"
lappend signals_to_add "jg"

#~ gtkwave::setTraceHighlightFromNameMatch top.des.clk on

# add the signals to the view

set num_added [ gtkwave::addSignalsFromList $signals_to_add ]
puts "num signals added: $num_added"
