/* ボタンを押したらLEDが点灯する。もう一度押すとLEDが消えるプログラム */

/* インクルードファイル */
#include "iodefine.h"

void setup()
{
/* マクロ定義 */
#define PWPR_PFSWE_CLEAR (0x00) /* PWPR.PFSWEをクリア */
#define PWPR_PFSWE_SET (0x40)   /* PFS.PFSWEを書き込み有効に設定 */
#define PWPR_BOWI_CLEAR (0x00)  /* PFS.BOWIをクリア */
#define PWPR_BOWI_SET (0x80)    /* PFS.BOWIを書き込み禁止に設定 */

  /* マクロ関数 */
#define PWPR_UNLOCK()           \
  do                            \
  {                             \
    REG_PWPR = PWPR_BOWI_CLEAR; \
    REG_PWPR = PWPR_PFSWE_SET;  \
  } while (0) /* PWPRを解除 */
#define PWPR_LOCK()            \
  do                           \
  {                            \
    REG_PWPR = PWPR_PFSWE_SET; \
    REG_PWPR = PWPR_BOWI_SET;  \
  } while (0) /* PWPRをロック */

#define BTN_PULUP() ((P105PFS & (1 << 1)) == 0) /* ボタンの入力状態 */

  /* レジスタ設定 */
  PWPR_UNLOCK();  /* 解除 */
  P112PFS = 0x04; /* PDRを出力に設定 */
  P105PFS = 0x10; /* PCRをプルアップ有効(1)に設定して、PDRを入力(0)に設定 */
  PWPR_LOCK();    /* ロック */
}

void loop()
{

  /* 変数宣言 */
  static unit_8 led_stetas = 0;  /* LEDを点灯・消灯する条件 */
  static unit_8 btn_prev = 0; /* 前のLEDの状態を確認 */
  unit_8 btn_now = BTN_PULUP(); /* ボタンの状態を確認 */

  if (btn_now && !btn_prev) /* ボタンの押下確認 */
  {
    led_stetas = !led_stetas; /* LEDの点灯条件 */

    PWPR_UNLOCK(); /* ロック解除 */
    if (led_stetas)
    {
      /* LED点灯 */
      P112PFS |= (1 << 0); /* PODRをHIGHに設定 */
    }
    else
    {
      /* LED消灯 */
      P112PFS &= ~(1 << 0); /* PODRをLOWに設定 */
    }
    PWPR_LOCK(); /* ロック */
  }
  btn_prev = btn_now; /* 1回目の処理終了時点のLEDの点灯状態を保持させる */
  delay(20); /* チャタリング防止 */
}
