# ETeam Linux Distribution

This distro is used on UDOO Quad to control the car display. It's based on ARCH and use a custom kernel. The idea is to use the ATMEL SAM3X8E ARM processor to compute real time things(steering wheel control) and use the ARM i.MX6 NPX processor to show infos on display.
The communication between the two processors is serial(UART):
- SAM3X8E get data from CAN-bus and send filtered data to i.MX6 (es. engine rpm)
- i.MX6 receive data and display it

## Install to a micro SD card

1. Zero the beginning of the SD card:
```
dd if=/dev/zero of=/dev/mmcblk0 bs=1M count=8
```
2. Partition the SD card:
```
fdisk /dev/mmcblk0
```
3. Type these commands:
    - o enter
    - p enter
    - n enter
    - p enter
    - 1 enter
    - 8192 enter
    - enter
    - w
4. Create the filesystem:
```
mkfs.ext4 /dev/mmcblk0p1
```
5. Mount the filesystem
```
mkdir mnt
mount /dev/mmcblk0p1 mnt
```
6. download and extract latest ETeamLinux
```
wget https://github.com/E-TeamUnipi/ETeamLinux/releases/download/latest/ETeamLinux.tar.gz
bsdtar -xpf ETeamLinux.tar.gz -C mnt
sync
umount mnt
```
7. Install u-boot:
```
wget https://github.com/E-TeamUnipi/ETeamLinux/releases/download/latest/SPL
wget https://github.com/E-TeamUnipi/ETeamLinux/releases/download/latest/u-boot.img
dd if=SPL of=/dev/mmcblk0 seek=1 bs=1k
dd if=u-boot.img of=/dev/mmcblk0 seek=69 bs=1k
sync
```
8. Extract the SD card and insert it into UDOO Quad
9. Connect to serial console with a micro USB connector on CN6
    - login: alarm, password: alarm
    - root password: root

## Update the display

To update the display connect the UDOO Quad to an ethernet port. Next apply the power and enter the serial console.

1. Enter root (su)
2. Run ./update.sh
3. Wait it finish

