<?php 

$count = 10000000;
$showEach = 100000;

for ($i = 0; $i < $count; $i++) {

	$a = $i * 2;

	if (($i % $showEach) == 0) {
		echo 'this the print op of referenced context `0`='. $a.PHP_EOL;
	}
}


