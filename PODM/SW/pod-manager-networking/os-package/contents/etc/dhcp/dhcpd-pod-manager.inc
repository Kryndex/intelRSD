# Copyright (c) 2015-2017 Intel Corporation
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# iPXE specific settings
option space ipxe;
option iscsi-initiator-iqn code 203 = string;

ddns-update-style none;

default-lease-time 100;
max-lease-time 720;

log-facility local7;

#
# Production Network
#
subnet 10.1.0.0 netmask 255.255.248.0 {
	range 10.1.0.2 10.1.7.254;
	option routers 10.1.0.1;
	next-server 10.1.0.1;
}

#
# Storage Management / Access Network
#
subnet 10.2.0.0 netmask 255.255.255.0 {
	range 10.2.0.2 10.2.0.254;
	option routers 10.2.0.1;
	option ntp-servers 10.2.0.1;

	# For the iPXE boot
	if exists user-class and option user-class = "iPXE" {
		filename "";
	} else {
		filename "podmipxe.0";
	}

	next-server 10.2.0.1;

	if (substring((option host-name),0,7) = "storage") {
		set lease_hostname = "storage";
		set ip_addr = binary-to-ascii(10, 8, ".", leased-address);
		set mac_addr = concat(
				suffix(concat("0",binary-to-ascii(16,8,"",substring(hardware,1,1))),2),":",
				suffix(concat("0",binary-to-ascii(16,8,"",substring(hardware,2,1))),2),":",
				suffix(concat("0",binary-to-ascii(16,8,"",substring(hardware,3,1))),2),":",
				suffix(concat("0",binary-to-ascii(16,8,"",substring(hardware,4,1))),2),":",
				suffix(concat("0",binary-to-ascii(16,8,"",substring(hardware,5,1))),2),":",
				suffix(concat("0",binary-to-ascii(16,8,"",substring(hardware,6,1))),2)
				);

		on commit {
			execute("/usr/bin/python3", "/usr/bin/parse_leases.py", "-i", ip_addr, "-e", "commit", "-n", lease_hostname, "-d", mac_addr);
		}
		on release {
			execute("/usr/bin/python3", "/usr/bin/parse_leases.py", "-i", ip_addr, "-e", "release", "-n", lease_hostname, "-d", mac_addr);
		}
		on expiry {
			# "zero-mac" string is a temporary workaround for isc-dhcp issue : ISC-Bugs #24584
			execute("/usr/bin/python3", "/usr/bin/parse_leases.py", "-i", ip_addr, "-e", "expiry", "-n", lease_hostname, "-d", "00:00:00:00:00:00");
		}
	}
}

#
# Services Management Network
#
subnet 10.3.0.0 netmask 255.255.252.0 {
	range 10.3.0.2 10.3.3.254;
	option ntp-servers 10.3.0.1;

	set lease_hostname = option host-name;
	if (substring((option host-name),0,4) = "psme") {
		set lease_hostname = "psme";
	}
	if (substring((option host-name),0,3) = "rmm") {
		set lease_hostname = "rmm";
	}

	set ip_addr = binary-to-ascii(10, 8, ".", leased-address);
	set mac_addr = concat(
			suffix(concat("0",binary-to-ascii(16,8,"",substring(hardware,1,1))),2),":",
			suffix(concat("0",binary-to-ascii(16,8,"",substring(hardware,2,1))),2),":",
			suffix(concat("0",binary-to-ascii(16,8,"",substring(hardware,3,1))),2),":",
			suffix(concat("0",binary-to-ascii(16,8,"",substring(hardware,4,1))),2),":",
			suffix(concat("0",binary-to-ascii(16,8,"",substring(hardware,5,1))),2),":",
			suffix(concat("0",binary-to-ascii(16,8,"",substring(hardware,6,1))),2)
			);

	on commit {
		execute("/usr/bin/python3", "/usr/bin/parse_leases.py", "-i", ip_addr, "-e", "commit", "-n", lease_hostname, "-d", mac_addr);
	}
	on release {
		execute("/usr/bin/python3", "/usr/bin/parse_leases.py", "-i", ip_addr, "-e", "release", "-n", lease_hostname, "-d", mac_addr);
	}
	on expiry {
		# "zero-mac" string is a temporary workaround for isc-dhcp issue : ISC-Bugs #24584
		execute("/usr/bin/python3", "/usr/bin/parse_leases.py", "-i", ip_addr, "-e", "expiry", "-n", lease_hostname, "-d", "00:00:00:00:00:00");
	}
}

#
# In-Band Management Network
#
subnet 10.5.0.0 netmask 255.255.255.0 {
        range 10.5.0.2 10.5.0.254;
	option routers 10.5.0.1;
	option ntp-servers 10.5.0.1;

    set lease_hostname = option host-name;
	if ((lease_hostname = "lui") or (lease_hostname = "inband")) {
		set ip_addr = binary-to-ascii(10, 8, ".", leased-address);
		set mac_addr = concat(
				suffix(concat("0",binary-to-ascii(16,8,"",substring(hardware,1,1))),2),":",
				suffix(concat("0",binary-to-ascii(16,8,"",substring(hardware,2,1))),2),":",
				suffix(concat("0",binary-to-ascii(16,8,"",substring(hardware,3,1))),2),":",
				suffix(concat("0",binary-to-ascii(16,8,"",substring(hardware,4,1))),2),":",
				suffix(concat("0",binary-to-ascii(16,8,"",substring(hardware,5,1))),2),":",
				suffix(concat("0",binary-to-ascii(16,8,"",substring(hardware,6,1))),2)
				);

		on commit {
			execute("/usr/bin/python3", "/usr/bin/parse_leases.py", "-i", ip_addr, "-e", "commit", "-n", lease_hostname, "-d", mac_addr);
		}
		on release {
			execute("/usr/bin/python3", "/usr/bin/parse_leases.py", "-i", ip_addr, "-e", "release", "-n", lease_hostname, "-d", mac_addr);
		}
		on expiry {
			# "zero-mac" string is a temporary workaround for isc-dhcp issue : ISC-Bugs #24584
			execute("/usr/bin/python3", "/usr/bin/parse_leases.py", "-i", ip_addr, "-e", "expiry", "-n", lease_hostname, "-d", "00:00:00:00:00:00");
		}
	}
}
