#!/usr/bin/perl

#########################################################################
#
#   byteswap.pl
#
#   Perl script used for swapping 4 bytes within 4-byte words of
#   a binary file.
#
#   #####################################################################
#
#   <hdrtag2963843>
#
#########################################################################
$arc_cnt = @ARGV;
if ($arc_cnt<2) {
    print ("\n\n This program swaps bytes within words of a binary file\n");
    print (" Useage $0 <in_file> <out_file>\n\n");
    exit -1;
}
$input_file  = $ARGV[0];
$output_file = $ARGV[1];
open (IFILE, "<$input_file") ||
    die("Error: can't open file $input_file \n");
binmode(IFILE);
$length = read(IFILE,$buffer,0x500000);
close (IFILE);
@istream = unpack("C*",$buffer);
# Make sure we got a whole number of words in array
$length = @istream;
while (($length % 4) != 0) {
    push (@istream, 0);
    $length = @istream;
}
# Now swap bytes within word
for ($i=0; $i<$length; $i+=4) {
    $temp          = $istream[$i];
    $istream[$i]   = $istream[$i+3];
    $istream[$i+3] = $temp;
    $temp          = $istream[$i+1];
    $istream[$i+1] = $istream[$i+2];
    $istream[$i+2] = $temp;
}
# Let's pack the new stream and write it to the output file.
$ostream = pack("C*", @istream);
open (OFILE, ">$output_file") ||
    die("Error: can't open file $output_file \n");
binmode(OFILE);
print (OFILE $ostream);
close (OFILE);

