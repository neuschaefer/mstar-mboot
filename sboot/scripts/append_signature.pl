#!/usr/bin/perl

$parameter_count = @ARGV;

if($parameter_count < 3) 
{
    print("Usage: $0 <sig_file> <sig_size> <out_file> <out_addr>\n\n");
    exit -1;
}

$signature_file = $ARGV[0];
$signature_size = hex($ARGV[1]);
$boot_image_file = $ARGV[2];
$boot_image_offset_address = hex($ARGV[3]);

open(hSignatureFile, "< $signature_file") || die("[ERROR] Cannot Open $signature_file \n");
open(hOutputFile, "+< $boot_image_file") || die("[ERROR] Cannot Open $boot_image_file \n");
binmode(hSignatureFile);
binmode(hOutputFile);

seek(hOutputFile, $boot_image_offset_address, 0);

while(<hSignatureFile>)
{
   print hOutputFile $_;
}

close(hSignatureFile);
close(hOutputFile);
