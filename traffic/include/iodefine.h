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
#define PMISC_BASE (0x40040D00) //PWPRのベースアドレス

/* レジスタ定義 */
#define REG_PWPR (*(volatile unit_8 *)(PMISC_BASE + 0x03)) // PWPRレジスタ
#define P109PFS (*(volatile unit_32 *)0x40040864UL) // D11ピン (PORT1のベースアドレス4004 0840)
#define P112PFS (*(volatile unit_32 *)0x40040870UL) // D10ピン
#define P303PFS (*(volatile unit_32 *)0x400408CCUL) // D9ピン (PORT3のベースアドレス4004 08C0)
#define P105PFS (*(volatile unit_32 *)0x40040854UL) //D2ピン スイッチ用

/* タイマー関連レジスタ */
#define REG_MSTPCRD  (*(volatile unit_32 *)0x40047008UL) /* モジュールストップ制御 */
#define REG_AGT0     (*(volatile unit_16 *)0x40084000UL) /* カウンタ初期値（16bit） */
#define REG_AGTCR    (*(volatile unit_8  *)0x40084008UL) /* カウント開始/停止 */
#define REG_AGTMR1   (*(volatile unit_8  *)0x40084009UL) /* クロックソース選択 */

/* プロトタイプ宣言 */
void delay_ms(unit_16 ms);


#endif // IODEFONE_H