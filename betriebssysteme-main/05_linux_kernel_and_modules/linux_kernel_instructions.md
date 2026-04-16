# Building a New Linux Kernel

This guide will walk you through the process of building a new Linux kernel from source.

## Prerequisites

- A Linux-based operating system
- Sufficient disk space (at least 15-20 GB)
- Essential build tools and libraries

## Step 1: Install Required Packages

Before starting, ensure you have the necessary packages installed:

```bash
sudo apt-get update
sudo apt-get install build-essential libncurses-dev bison flex libssl-dev libelf-dev bc
```

## Step 2: Download the Kernel Source

Navigate to the `/usr/src` directory and download the kernel source:

```bash
cd /usr/src
sudo wget https://cdn.kernel.org/pub/linux/kernel/v6.x/linux-6.9.1.tar.xz
```

## Step 3: Extract the Kernel Source

```bash
sudo tar -xvf linux-6.9.1.tar.xz
```

## Step 4: Configure the Kernel

Navigate to the kernel source directory:

```bash
cd linux-6.9.1
```

## Step 5: Configure the Kernel

Option 1: Use the existing configuration (from your current kernel):

```bash 
# copy your current kernel configuration into the director as ".config" file
cp /boot/config-$(uname -r) .config
make oldconfig
```
This uses the current configuration as a starting point. You’ll be asked to configure new options if they exist.

Option 2: Use a different configuration (e.g., a generic configuration):

```bash
make menuconfig
```

This opens a menu-based configuration interface. You can navigate using the arrow keys and select/unselect options.

Option 3: Use a pre-configured .config file:

**Attention**: You need to select the right CPU architecture for your kernel (e.g., x86_64, aarch64, arm64):

```bash
wget https://cdn.kernel.org/pub/linux/kernel/v6.x/configs/x86_64/config-6.9.1
cp config-6.9.1 .config
```

### Check Configuration for Deprecated Options (especially recommended when downgrading)

It’s possible that leftover build files from previous kernel versions or attempts might be causing the issue. Before proceeding with another build attempt, clean up the kernel source tree thoroughly:

```bash
make mrproper
```

This command cleans up everything, including the configuration file. Be sure to back up your .config file if you don’t want to lose it, and copy it back after running the command.

### Build with default options

To rule out configuration issues, try building the kernel using the default configuration for your system’s architecture. This is a quick way to check if the issue is with your configuration or something else:

```bash
make defconfig
```

This command creates a default configuration for your architecture, which you can use to attempt a clean build.

## Step 6: Build the Kernel

```bash
make -j$(nproc)
```
The -j$(nproc) option tells make to use all available CPU cores for faster compilation, where `nproc`is the number of CPUs to include in the build process. Dependent on the computer you are building the kernel, as well as the number of modules to include, this may take some time to finish.

## Step 7: Install the Kernel

```bash
sudo make modules_install
sudo make install
```
This installs the kernel image and related files (e.g., vmlinuz, initrd, etc.) to /boot.

## Step 8: Update GRUB

If you’re using GRUB as your bootloader, it’s important to update it so it can boot the new kernel. GRUB is used as the defailt bootloader in Ubuntu, and thus, in our Linux VM.
```bash
sudo update-grub
```

## Step 9: Reboot

```bash
sudo reboot
```

## Troubleshooting

- If you encounter errors related to missing dependencies, install the missing packages using the appropriate package manager for your Linux distribution.
- Ensure you have the correct version of the kernel source that matches your system architecture (e.g., x86_64 for 64-bit systems).

### System still boots in prev. Kernel

Check if the installation of your new kernel was correct by checking the files in the `/boot`directory:

```bash
sudo ls -l /boot
```

If the files of your newly installed kernel are there, you need to repeat the installation instructions. If the files are ther, you can check next if GRUB is pointing correctly to the newly installed kernel via
```bash
sudo nano /boot/grub/grub.cfg
```

If the entries exists, but GRUB is not providing you with the menu option during boot, you can force GRUB to stay in the boot menu option by editing:

```bash
sudo nano /etc/default/grub
```
and set the GRUB_TIMEOUT_STYLE to menu, which forces GRUB to display the menu and increase the GRUB timeout. Sometimes, the default hides the option.

```bash
GRUB_TIMEOUT_STYLE=menu
GRUB_TIMEOUT=5
```

Finally, update GRUB and reboot.

```bash
sudo update-grub
sudo reboot
```

## Conclusion

This guide provides a basic overview of building a new Linux kernel from source. For more advanced configurations and optimizations, refer to the official [Linux Kernel Documentation](https://www.kernel.org/doc/html/latest/index.html).
