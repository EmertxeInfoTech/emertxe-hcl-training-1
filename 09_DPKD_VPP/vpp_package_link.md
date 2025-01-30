# VPP install instructions

Note: DPDK is a dependency

## To install the packages on Ubuntu (<=24.04 LTS versions)
```
# Setup apt repo
curl -s https://packagecloud.io/install/repositories/fdio/release/script.deb.sh | sudo bash
```

```
# Install the packages
sudo apt-get update
sudo apt-get install vpp vpp-plugin-core vpp-plugin-dpdk
```

```
# Install optional packages
sudo apt-get install vpp-api-python python3-vpp-api vpp-dbg vpp-dev
```

## To install the packages on Ubuntu 24.10
```
wget https://test1.emertxe.com/vpp/vpp_deb_packages.zip
unzip vpp_deb_packages.zip
cd vpp_deb_packages
sudo dpkg -i *.deb
```

## Debian package for Ubuntu 24.10

Link 1: https://test1.emertxe.com/vpp/vpp_deb_packages.zip

Link 2 (Alternate): https://drive.google.com/file/d/1EqMQmb6iy77-zR537vmZZIFQbrVlw9ZM/view?usp=drive_link

## References
https://s3-docs.fd.io/vpp/25.02/gettingstarted/installing/index.html

