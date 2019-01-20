/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (C) 2013 Freescale Semiconductor, Inc.
 *
 * Configuration settings for Udoo board.
 */

#ifndef __CONFIG_H
#define __CONFIG_H

#include "mx6_common.h"

#include "imx6_spl.h"

/* Provide the MACH_TYPE value that the vendor kernel requires. */
#define CONFIG_MACH_TYPE		4800

/* Size of malloc() pool */
#define CONFIG_SYS_MALLOC_LEN		(2 * SZ_1M)

#define CONFIG_MXC_UART
#define CONFIG_MXC_UART_BASE		UART2_BASE

//#undef CONFIG_CMD_SATA
#undef CONFIG_SYS_LONGHELP
#undef CONFIG_SYS_HUSH_PARSER
#undef CONFIG_USB_OMAP3
#undef CONFIG_MUSB_HCD
#undef CONFIG_MUSB_UDC
#undef CONFIG_CMD_NET

/* SATA Configs */

#ifdef CONFIG_CMD_SATA
#define CONFIG_SYS_SATA_MAX_DEVICE	1
#define CONFIG_DWC_AHSATA_PORT_ID	0
#define CONFIG_DWC_AHSATA_BASE_ADDR	SATA_ARB_BASE_ADDR
#define CONFIG_LBA48
#endif

/* Network support */

#define CONFIG_FEC_MXC
#define IMX_FEC_BASE                    ENET_BASE_ADDR
#define CONFIG_FEC_XCV_TYPE             RGMII
#define CONFIG_ETHPRIME                 "FEC"
#define CONFIG_FEC_MXC_PHYADDR          6

#define CONFIG_SYS_MEMTEST_START	0x10000000
#define CONFIG_SYS_MEMTEST_END		(CONFIG_SYS_MEMTEST_START + 500 * SZ_1M)

/* MMC Configuration */
#define CONFIG_SYS_FSL_ESDHC_ADDR	0

#ifdef CONFIG_BOOTDELAY
#undef CONFIG_BOOTDELAY
#define CONFIG_BOOTDELAY 0
#endif

#define CONFIG_EXTRA_ENV_SETTINGS \
	"console=ttymxc1,115200\0" \
	"fdt_high=0xffffffff\0" \
	"initrd_high=0xffffffff\0" \
	"fdt_addr=0x18000000\0" \
	"fdt_addr_r=0x18000000\0" \
	"ip_dyn=yes\0" \
	"mmcdev=0\0" \
	"mmcrootfstype=ext4\0" \
	"kernel_addr_r=" __stringify(CONFIG_LOADADDR) "\0" \
	"pxefile_addr_r=" __stringify(CONFIG_LOADADDR) "\0" \
	"ramdisk_addr_r=0x13000000\0" \
	"scriptaddr=" __stringify(CONFIG_LOADADDR) "\0" \
	"image=zImage\0" \
	"console=ttymxc1\0" \
	"splashpos=m,m\0" \
	"fdt_high=0xffffffff\0" \
	"initrd_high=0xffffffff\0" \
	"fdt_file=imx6q-udoo.dtb\0" \
	"fdt_addr=0x18000000\0" \
	"rdaddr=0x12A00000\0" \
	"rdfile=initramfs-linux.img\0" \
	"optargs=\0" \
	"video=\0" \
	"ip_dyn=yes\0" \
	"mmcdev=0\0" \
	"mmcpart=1\0" \
	"bootcmd_mmc0=setenv devnum 0; run mmc_boot\0" \
	"mmcargs=setenv bootargs console=${console},${baudrate} " \
		"${optargs} " \
		"quiet " \
        "rootfstype=${mmcrootfstype} " \
		"root=${root} " \
		"video=${video}\0" \
	"loadimage=echo Loading /${image}..; load mmc ${mmcdev}:${mmcpart} ${loadaddr} /${image}\0" \
	"loadfdt=echo Loading /${fdt_file}..; load mmc ${mmcdev}:${mmcpart} ${fdt_addr} /${fdt_file}\0" \
	"loadrd=load mmc ${bootpart} ${rdaddr} /${rdfile}\0" \
	"mmcboot=mmc dev ${mmcdev}; " \
		"if mmc rescan; then " \
            "part list mmc 0;" \
			"echo SD/MMC found on device ${mmcdev};" \
			"setenv bootpart ${mmcdev}:1; " \
			"part uuid mmc ${bootpart} uuid;" \
			"setenv root PARTUUID=${uuid} ro rootwait;" \
			"echo Checking for: ${bootdir}/uEnv.txt ...;" \
			"if test -e mmc ${bootpart} ${bootdir}/uEnv.txt; then " \
				"load mmc ${bootpart} ${loadaddr} ${bootdir}/uEnv.txt;" \
				"env import -t ${loadaddr} ${filesize};" \
				"echo Loaded environment from ${bootdir}/uEnv.txt;" \
				"echo Checking if uenvcmd is set ...;" \
				"if test -n ${uenvcmd}; then " \
					"echo Running uenvcmd ...;" \
					"run uenvcmd;" \
				"fi;" \
			"fi; " \
			"if run loadimage; then " \
				"if run loadfdt; then " \
					"run mmcargs;" \
                    "bootz ${loadaddr} - ${fdt_addr};" \
				"else " \
					"echo Kernel found, but no device tree found;" \
				"fi;" \
			"else " \
				"echo No kernel found;" \
			"fi;" \
		"fi;\0"

#undef CONFIG_BOOTCOMMAND
#define CONFIG_BOOTCOMMAND \
	"run mmcboot; "

/* Physical Memory Map */
#define PHYS_SDRAM			MMDC0_ARB_BASE_ADDR

#define CONFIG_SYS_SDRAM_BASE		PHYS_SDRAM
#define CONFIG_SYS_INIT_RAM_ADDR	IRAM_BASE_ADDR
#define CONFIG_SYS_INIT_RAM_SIZE	IRAM_SIZE

#define CONFIG_SYS_INIT_SP_OFFSET \
	(CONFIG_SYS_INIT_RAM_SIZE - GENERATED_GBL_DATA_SIZE)
#define CONFIG_SYS_INIT_SP_ADDR \
	(CONFIG_SYS_INIT_RAM_ADDR + CONFIG_SYS_INIT_SP_OFFSET)

/* Environment organization */
#define CONFIG_ENV_SIZE			(8 * 1024)

#define CONFIG_ENV_OFFSET		(6 * 64 * 1024)
#define CONFIG_SYS_MMC_ENV_DEV		0

#endif			       /* __CONFIG_H * */
