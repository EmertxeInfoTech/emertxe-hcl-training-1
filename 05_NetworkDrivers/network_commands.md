# Linux networking commands and lscpi

### **PCI Commands**
1. **`lspci -vvv -x`**
   - Provides detailed information about PCI devices, including configuration registers (`-x`) and verbose output (`-vvv`).
2. **`lspci -t`**
   - Displays the PCI device tree, showing how devices are connected to the system.

---

### **Network Interface Commands**
1. **`ifconfig`**
   - Displays and configures network interfaces. Deprecated in favor of `ip` in modern systems.
2. **`ifconfig eth0 down`**
   - Brings down the specified network interface (`eth0`).
3. **`ifconfig eth0 up`**
   - Brings up the specified network interface (`eth0`).
4. **`sudo ifconfig dummy0 10.116.0.2`**
   - Configures a dummy network interface (`dummy0`) with the IP address `10.116.0.2`.

---

### **Ethtool Commands**  
Used to query and control network driver and hardware settings.
1. **`ethtool -S eth0`**
   - Displays NIC statistics for the specified interface (`eth0`).
2. **`ethtool -i eth0`**
   - Displays driver and firmware information for the specified interface (`eth0`).
3. **`sudo ethtool -S eth0`**
   - Runs `ethtool -S` with superuser privileges to get detailed statistics.

#### **Link:**  
- [Ethtool Documentation](https://docs.redhat.com/en/documentation/red_hat_enterprise_linux/6/html/deployment_guide/s1-ethtool#s1-ethtool)

---

### **IP Command**  
A powerful modern replacement for `ifconfig` and `route`, used to configure and manage network interfaces, routes, and IP addresses.
1. **`ip addr`**
   - Displays information about network interfaces and their IP addresses.
2. **`ip link`**
   - Shows details about network links/interfaces.
3. **`ip link set eth0 up`**
   - Brings up the specified network interface (`eth0`).
4. **`ip link set eth0 down`**
   - Brings down the specified network interface (`eth0`).
5. **`ip route`**
   - Displays or manipulates the routing table. Modern replacement for the `route` command.
6. **`ip addr add 192.168.1.10/24 dev eth0`**
   - Assigns an IP address (`192.168.1.10/24`) to the specified network interface (`eth0`).
7. **`ip addr del 192.168.1.10/24 dev eth0`**
   - Removes an assigned IP address from the interface.

---

### **Routing Commands**
1. **`ip route`**
   - Shows or manipulates the IP routing table.
2. **`route`**
   - Displays or manipulates the IP routing table. Older command, less frequently used in modern systems.
3. **Red Hat Documentation on Routes:**  
   - [Static Routes Guide](https://docs.redhat.com/en/documentation/red_hat_enterprise_linux/5/html/deployment_guide/s1-networkscripts-static-routes#s1-networkscripts-static-routes)

---

### **Netstat Command**
Displays network-related information. Deprecated in favor of `ss` but still useful in some scenarios.

**Common Options:**
1. **`netstat -a`**
   - Displays all active connections, including listening ports.
2. **`netstat -t`**
   - Shows only TCP connections.
3. **`netstat -u`**
   - Shows only UDP connections.
4. **`netstat -l`**
   - Displays listening sockets.
5. **`netstat -p`**
   - Shows the process ID (PID) and program name for each connection.
6. **`netstat -r`**
   - Displays the routing table.
7. **`netstat -i`**
   - Displays statistics for network interfaces.
8. **`netstat -s`**
   - Displays network statistics, such as packet counts and errors.

---

### **iPerf Commands**
Used for network performance testing.
1. **`iPerf3 -s`**
   - Starts iPerf in server mode, waiting for client connections.
2. **`iperf -c 192.168.7.2 -p 5201`**
   - Runs iPerf in client mode, testing bandwidth to a server at `192.168.7.2` on port `5201`.

