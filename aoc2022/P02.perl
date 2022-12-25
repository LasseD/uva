$s=0;while(my $q=<>){
$a=ord(substr($q,0,1))-65;
$b=ord(substr($q,2,1))-88;
$s+=(1,2,3,4,5,6,7,8,9)[$a+3*$b];
}print($s);
