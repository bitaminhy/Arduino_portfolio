#ifndef IODEFINE_H
#define IODEFINE_H
/* 正数 */
typedef unsigned char unit_8;   /* 1バイト(8ビット) */
typedef unsigned short unit_16; /* 2バイト(16ビット) */
typedef unsigned long unit_32;  /* 4バイト(32ビット) */

/* 小数 ※ほぼ使用しないかも */
typedef float funit_32; /* 4バイト(32ビット) */
typedef double unit_64; /* 8バイト(64ビット) */

/* レジスタのベースアドレス */
#define PMISC_BASE (0x40040D00)

/* レジスタ定義 */
#define REG_PWPR (*(volatile unit_8 *)(PMISC_BASE + 0x03)) /* PFSに書き込み許可 */
#define P112PFS (*(volatile unit_32 *)0x40040870UL)
#define P105PFS (*(volatile unit_32 *)0x40040854UL)

#endif // IODEFINE_H