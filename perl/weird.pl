#!/usr/bin/perl


my %a;

for ( my $i = 0; $i < 100; ++$i ){
    $a{$i-(int($i/10)+($i%10))} = 1;
}

foreach (keys%a){
    print "$_\n";
}
