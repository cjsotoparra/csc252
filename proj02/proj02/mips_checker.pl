#! /usr/bin/env perl


foreach $line (<STDIN>)
{
#	print "\n";
#	print "LINE: $line";

	# get rid of any comment that might exist.  The s/foo/bar/g regular
	# expression form is for substitution; in this case, we replace
	# anything that looks like a comment with an empty string.
	$line =~ s/#.*//g;
#	print "    comment: $line";

	# remove leading and trailing whitespace, includine newlines.
	# Thanks to
	#     https://perlmaven.com/trim
	# for the elegant regexp.
	$line =~ s/^\s+|\s+$//g;
#	print "    whitesp: $line\n";

	# collapse all whitespace down to single spaces.
	$line =~ s/\s+/ /g;
#	print "    collws : $line\n";

	# remove labels from the front of any line.
	$line =~ s/^\s*[a-zA-Z0-9_]+\s*:\s*//;
#	print "    label  : $line\n";


	# accept blank lines
	if ($line eq "")
	{
		next;
	}
#	print "    blank  : $line\n";


	# accept lines which are simple assembler directives
	if ($line =~ m/^[.](text|data)/)
	{
		next;
	}
#	print "    texdata: $line\n";

	if ($line =~ m/^[.]globl\s+[a-zA-Z0-9_]+$/)
	{
		next;
	}
#	print "    globl  : $line\n";

	if ($line =~ m/^[.](word|half|byte)\s+(-?[0-9]+|0x[0-9a-fA-F]+|[a-zA-Z0-9_]+)$/)
	{
		next;
	}
#	print "    var    : $line\n";

	if ($line =~ m/^[.]asciiz? ".*"$/)
	{
		next;
	}


	# recognize all of the R-format instructions (except shift)
	if ($line =~ m/^(add|sub|slt|and|or|nor|xor) \$[a-z0-9]+ ?, ?\$[a-z0-9]+ ?, ?\$[a-z0-9]+$/)
	{
		next;
	}

	# recognize all of the conditional branch instructions
	if ($line =~ m/^(beq|bne) \$[a-z0-9]+ ?, ?\$[a-z0-9]+ ?, ?[a-zA-Z0-9_]+$/)
	{
		next;
	}

	# recognize all of the I-format (immediate value) instructions, PLUS
	# the shift instructions.
	if ($line =~ m/^(addiu?|slti|andi|ori|nori|xori|sll|srl|sra) \$[a-z0-9]+ ?, ?\$[a-z0-9]+ ?, ?(-?[0-9]{1,5}|0x[0-9a-fA-F]{1,4})/)
	{
		next;
	}

	# recognize the LA instruction here - since it's a real oddball
	if ($line =~ m/la \$[a-z0-9]+ ?, ?[a-zA-Z0-9_]+$/)
	{
		next;
	}

	# recognize all load/store instructions.
	if ($line =~ m/^[ls][whb] \$[a-z0-9]+ ?, ?(-?[0-9]+|0x[0-9a-fA-F]+) ?\( ?\$[a-z0-9]+ ?\)$/)
	{
		next;
	}

	# recognize all of the j-format instructions
	if ($line =~ m/^(j|jal) [a-zA-Z0-9_]+$/)
	{
		next;
	}

	# recognize JR
	if ($line =~ m/jr \$[a-z0-9]+$/)
	{
		next;
	}

#   \$[a-z0-9]+
#    ?, ?
#   [a-zA-Z0-9_]+
#   (-?[0-9]{1,5}|0x[0-9a-fA-F]{1,4)+)

	# recognize syscall - the only non-parameterized instruction
	if ($line eq "syscall")
	{
		next;
	}


	print "ERROR: UNRECOGNIZED LINE: '$line'\n";
}

