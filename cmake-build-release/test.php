<?php 

$count = 10000000;
$showEach = 10000;

for ($i = 0; $i < $count; $i++) {

	if (($i % $showEach) == 0) {
		echo 'this the print op of referenced context `0`='. $i.PHP_EOL;
	}
}


