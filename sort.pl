#!/usr/bin/perl

use strict;
use warnings;

my @array = (
	8, 3, 9, 4, 12, 
	83, 1, 0, 10, 32
);

my @res = sort { $a<=>$b } @array;

map { print "$_, " } @res;

__END__
