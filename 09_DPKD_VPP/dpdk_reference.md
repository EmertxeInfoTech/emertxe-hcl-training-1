
Main Probe
https://elixir.bootlin.com/dpdk/v24.11.1/source/drivers/bus/pci/pci_common.c#L290

BAR addresses are getting mapped
https://elixir.bootlin.com/dpdk/v24.11.1/source/drivers/bus/pci/linux/pci.c#L74

Sample of E1000, similar to the kernel driver
https://elixir.bootlin.com/dpdk/v24.11.1/source/drivers/net/e1000/em_ethdev.c#L246

Include file of RTE PMD Registration Interface
https://elixir.bootlin.com/dpdk/v24.11.1/source/lib/eal/include/rte_dev.h

Include file RTE malloc
https://elixir.bootlin.com/dpdk/v24.11.1/source/lib/eal/include/rte_malloc.h

Mempool
https://elixir.bootlin.com/dpdk/v24.11.1/source/lib/mempool/rte_mempool.h

Registers the callback for the specific interrupt/Net Device
https://elixir.bootlin.com/dpdk/v24.11.1/source/lib/eal/include/rte_interrupts.h#L84

A structure containing the functions exported by an Ethernet driver "struct eth_dev_ops ".
https://elixir.bootlin.com/dpdk/v24.11.1/source/lib/ethdev/ethdev_driver.h#L1373


Contains a packet mbuf, similar to sk buffs
https://elixir.bootlin.com/dpdk/v24.11.1/source/lib/mbuf/rte_mbuf_core.h#L467

Include of EAL
https://elixir.bootlin.com/dpdk/v24.11.1/source/lib/eal/include/rte_eal.h

Initialize the Environment Abstraction Layer (EAL).
https://elixir.bootlin.com/dpdk/v24.11.1/source/lib/eal/include/rte_eal.h#L112

Get the number of ports which are usable for the application.
https://elixir.bootlin.com/dpdk/v24.11.1/source/lib/ethdev/rte_ethdev.h#L2308


DPDK API's
https://doc.dpdk.org/api/


VPP reference
https://s3-docs.fd.io/vpp/25.02/


-------------------------------------------------

Steps/commands used:-

https://core.dpdk.org/doc/quick-start/

DPDK Getting Started Guide for Linux
https://doc.dpdk.org/guides/linux_gsg/index.html


dpdk-devbind.py   -s

sudo dpdk-devbind.py  -b uio_pci_generic xxxx:xxx:xx


sudo apt install   linux-modules-extra-6.11.0-13-generic


modprobe uio_pci_generic


Our Net device 0x1AF4
https://elixir.bootlin.com/dpdk/v24.11.1/source/drivers/net/virtio/virtio_pci.h#L21
https://elixir.bootlin.com/dpdk/v24.11.1/source/drivers/net/virtio/virtio_pci_ethdev.c#L31


The rte_eth_rx_burst() get the packets
https://elixir.bootlin.com/dpdk/v24.11.1/source/lib/ethdev/rte_ethdev.h#L6262


EAL parameters
https://doc.dpdk.org/guides/linux_gsg/linux_eal_parameters.html


Send any packets queued up for transmission on a port and HW queue
https://elixir.bootlin.com/dpdk/v24.11.1/source/lib/ethdev/rte_ethdev.h#L6800




To use DPDK from source, we can also install DPDK from apt as well. 


# Download the source
https://fast.dpdk.org/rel/dpdk-22.11.7.tar.xz

# install few packages
apt install build-essential

apt install meson




apt install ninja-build

apt install python3-pyelftools


apt install libnuma-dev

--------------------------------

tar  -xvf dpdk-22.11.7.tar.xz

cd  dpdk-stable-22.11.7



meson setup build

# To build Examples  meson -Dexamples=all build  (meson setup  -Dexamples=all  build)

Once configured, to build and then install DPDK system-wide use:

ninja -C build

meson install
ldconfig


-------------------------------------------------
 Install dpdk packages using apt
dpkg -L dpdk-doc |grep hello
sudo apt install dpdk dpdk-dev dpdk-doc

-----------------------------------------------


sudo ./helloworld  -l   0-2  -n 1 

sudo ./helloworld  -l   0-2  -n 1  -b 00:03.0
sudo ./helloworld  -l   0-2  -n 1  -a 00:04.0


## TO run 
 sudo ./l2fwd   -l 0-3 -n 4 -- -q 8 -p 1




VPP
set  interface state GigabitEthernet0/4/0  up

 set interface ip address  GigabitEthernet0/4/0  10.116.0.2/24












