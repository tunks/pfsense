<?php
/* $Id$ */
/*
	Copyright (C) 2012 Jim Pingle
	All rights reserved.

	Copyright (C) 2007, 2008 Scott Ullrich <sullrich@gmail.com>
	All rights reserved.

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are met:

	1. Redistributions of source code must retain the above copyright notice,
	   this list of conditions and the following disclaimer.

	2. Redistributions in binary form must reproduce the above copyright
	   notice, this list of conditions and the following disclaimer in the
	   documentation and/or other materials provided with the distribution.

	THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,
	INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
	AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
	AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
	OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
	SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
	INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
	CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
	ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
	POSSIBILITY OF SUCH DAMAGE.

*/

/*
	pfSense_MODULE:	system
*/

// On the page, add in like so:
//   $shortcut_section = "relayd";

/* Load and process custom shortcuts. */
function get_shortcut_files($directory) {
	$dir_array = array();
	if(!is_dir($directory)) 
		return;
	if ($dh = opendir($directory)) {
		while (($file = readdir($dh)) !== false) {
			$canadd = 0;
			if($file == ".") 
				$canadd = 1;
			if($file == "..") 
				$canadd = 1;
			if($canadd == 0)
				array_push($dir_array, $file);
		}
		closedir($dh);
	}
	if(!is_array($dir_array))
		return;
	return $dir_array;
}

// Load shortcuts
$dir_array = get_shortcut_files("/usr/local/www/shortcuts");
foreach ($dir_array as $file) 
	if (!is_dir("/usr/local/www/shortcuts/{$file}") && stristr($file,".inc")) 
		include("/usr/local/www/shortcuts/{$file}");
if(is_dir("/usr/local/pkg/shortcuts")) {
	$dir_array = get_shortcut_files("/usr/local/pkg/shortcuts");
	foreach ($dir_array as $file) 
		if (!is_dir("/usr/local/pkg/shortcuts/{$file}") && stristr($file,".inc")) 
			include("/usr/local/pkg/shortcuts/{$file}");
}

$shortcuts['relayd'] = array();
$shortcuts['relayd']['main'] = "load_balancer_pool.php";
$shortcuts['relayd']['log'] = "diag_logs_relayd.php";
$shortcuts['relayd']['status'] = "status_lb_pool.php";
$shortcuts['relayd']['service'] = "relayd";

$shortcuts['relayd-virtualservers'] = array();
$shortcuts['relayd-virtualservers']['main'] = "load_balancer_virtual_server.php";
$shortcuts['relayd-virtualservers']['log'] = "diag_logs_relayd.php";
$shortcuts['relayd-virtualservers']['status'] = "status_lb_vs.php";
$shortcuts['relayd-virtualservers']['service'] = "relayd";

$shortcuts['captiveportal'] = array();
$shortcuts['captiveportal']['main'] = "services_captiveportal_zones.php";
$shortcuts['captiveportal']['log'] = "diag_logs_auth.php";
$shortcuts['captiveportal']['status'] = "status_captiveportal.php";
$shortcuts['captiveportal']['service'] = "captiveportal";

$shortcuts['captiveportal-vouchers'] = array();
$shortcuts['captiveportal-vouchers']['log'] = "diag_logs_auth.php";
$shortcuts['captiveportal-vouchers']['status'] = "status_captiveportal_vouchers.php";
$shortcuts['captiveportal-vouchers']['service'] = "captiveportal";

$shortcuts['dhcp'] = array();
$shortcuts['dhcp']['main'] = "services_dhcp.php";
$shortcuts['dhcp']['log'] = "diag_logs_dhcp.php";
$shortcuts['dhcp']['status'] = "status_dhcp_leases.php";
$shortcuts['dhcp']['service'] = "dhcpd";

$shortcuts['dhcp6'] = array();
$shortcuts['dhcp6']['main'] = "services_dhcpv6.php";
$shortcuts['dhcp6']['log'] = "diag_logs_dhcp.php";
$shortcuts['dhcp6']['status'] = "status_dhcpv6_leases.php";


$shortcuts['ipsec'] = array();
$shortcuts['ipsec']['main'] = "vpn_ipsec.php";
$shortcuts['ipsec']['log'] = "diag_logs_ipsec.php";
$shortcuts['ipsec']['status'] = "diag_ipsec.php";
$shortcuts['ipsec']['service'] = "racoon";

$shortcuts['openvpn'] = array();
$shortcuts['openvpn']['main'] = "vpn_openvpn_server.php";
$shortcuts['openvpn']['log'] = "diag_logs_openvpn.php";
$shortcuts['openvpn']['status'] = "status_openvpn.php";
$shortcuts['openvpn']['service'] = "openvpn";

$shortcuts['firewall'] = array();
$shortcuts['firewall']['main'] = "firewall_rules.php";
$shortcuts['firewall']['log'] = "diag_logs_filter.php";
$shortcuts['firewall']['status'] = "status_filter_reload.php";

$shortcuts['routing'] = array();
$shortcuts['routing']['main'] = "system_routes.php";
$shortcuts['routing']['log'] = "diag_logs_routing.php";
$shortcuts['routing']['status'] = "diag_routes.php";

$shortcuts['gateways'] = array();
$shortcuts['gateways']['main'] = "system_gateways.php";
$shortcuts['gateways']['log'] = "diag_logs_gateways.php";
$shortcuts['gateways']['status'] = "status_gateways.php";

$shortcuts['gateway-groups'] = array();
$shortcuts['gateway-groups']['main'] = "system_gateway_groups.php";
$shortcuts['gateway-groups']['log'] = "diag_logs_gateways.php";
$shortcuts['gateway-groups']['status'] = "status_gateway_groups.php";

$shortcuts['interfaces'] = array();
$shortcuts['interfaces']['main'] = "interfaces_assign.php";
$shortcuts['interfaces']['status'] = "status_interfaces.php";

$shortcuts['trafficshaper'] = array();
$shortcuts['trafficshaper']['main'] = "firewall_shaper.php";
$shortcuts['trafficshaper']['status'] = "status_queues.php";

$shortcuts['resolver'] = array();
$shortcuts['resolver']['main'] = "services_dnsmasq.php";
$shortcuts['resolver']['log'] = "diag_logs_resolver.php";
$shortcuts['resolver']['service'] = "dnsmasq";

$shortcuts['wireless'] = array();
$shortcuts['wireless']['main'] = "interfaces_wireless.php";
$shortcuts['wireless']['log'] = "diag_logs_wireless.php";
$shortcuts['wireless']['status'] = "status_wireless.php";

$shortcuts['ntp'] = array();
$shortcuts['ntp']['main'] = "services_ntpd.php";
$shortcuts['ntp']['log'] = "diag_logs_ntpd.php";
$shortcuts['ntp']['status'] = "status_ntpd.php";
$shortcuts['ntp']['service'] = "ntpd";

$shortcuts['pptps'] = array();
$shortcuts['pptps']['main'] = "vpn_pptp.php";
$shortcuts['pptps']['log'] = "diag_logs_vpn.php";

$shortcuts['pppoes'] = array();
$shortcuts['pppoes']['main'] = "vpn_pppoe.php";
$shortcuts['pppoes']['log'] = "diag_logs_vpn.php?vpntype=poes";

$shortcuts['l2tps'] = array();
$shortcuts['l2tps']['main'] = "vpn_l2tp.php";
$shortcuts['l2tps']['log'] = "diag_logs_vpn.php?vpntype=l2tp";

$shortcuts['carp'] = array();
$shortcuts['carp']['main'] = "system_hasync.php";
$shortcuts['carp']['status'] = "carp_status.php";
?>