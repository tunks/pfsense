<?php

$leases_file = "/var/dhcpd/var/db/dhcpd6.leases";
if(!file_exists($leases_file)) {
	exit(1);
}

$fd = fopen($leases_file, 'r');

$duid_arr = array();
while (( $line = fgets($fd, 4096)) !== false) {
	// echo "$line";
	if(preg_match("/^(ia-[np][ad])[ ]+\"(.*?)\"/i", $line, $duidmatch)) {
		$type = $duidmatch[1];
		$duid = $duidmatch[2];
		continue;
	}

	/* is it active? otherwise just discard */
	if(preg_match("/binding state active/i", $line, $activematch)) {
		$active = true;
		continue;
	}

	if(preg_match("/iaaddr[ ]+([0-9a-f:]+)[ ]+/i", $line, $addressmatch)) {
		$ia_na = $addressmatch[1];
		continue;
	}

	if(preg_match("/iaprefix[ ]+([0-9a-f:\/]+)[ ]+/i", $line, $prefixmatch)) {
		$ia_pd = $prefixmatch[1];
		continue;
	}

	/* closing bracket */
	if(preg_match("/^}/i", $line)) {
		switch($type) {
			case "ia-na":
				$duid_arr[$duid][$type] = $ia_na;
				break;
			case "ia-pd":
				$duid_arr[$duid][$type] = $ia_pd;
				break;
		}
		unset($type);
		unset($duid);
		unset($active);
		unset($ia_na);
		unset($ia_pd);
		continue;
	}
}
fclose($fd);

$routes = array();
foreach ($duid_arr as $entry) {
	if(!empty($entry['ia-pd'])) {
		$routes[$entry['ia-na']] = $entry['ia-pd'];
	}
}

// echo "add routes\n";
if(count($routes) > 0) {
	foreach ($routes as $address => $prefix) {
		echo "/sbin/route change -inet6 {$prefix} {$address}\n";
	}
}

/* get clog from dhcpd */
$dhcpdlogfile = "/var/log/dhcpd.log";
$expires = array();
if(file_exists($dhcpdlogfile)) {
	$fd = popen("clog $dhcpdlogfile", 'r');
	while (($line = fgets($fd)) !== false) {
		//echo $line;
		if(preg_match("/releases[ ]+prefix[ ]+([0-9a-f:]+\/[0-9]+)/i", $line, $expire)) {
			if(in_array($expire[1], $routes))
				continue;
			$expires[$expire[1]] = $expire[1];
		}
	}
	pclose($fd);
}

// echo "remove routes\n";
if(count($expires) > 0) {
	foreach ($expires as $prefix) {
		echo "/sbin/route delete -inet6 {$prefix['prefix']}\n";
	}
}

?>
