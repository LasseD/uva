$best = 0;
$cur = 0;
while(my $line = <>) {
    if($line eq "\n"){
	$best = $cur >= $best ? $cur : $best;
	$cur = 0;
    }
    else {
	$cur += $line;
    }
}
$best=$cur>=$best?$cur:$best;
print($best);
