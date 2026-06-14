#include "iodefine.h"

/* レジスタ設定値 */
#define PWPR_BOWI_CLEAR (0x00)  /* PWPR.B0W1を0に設定 */
#define PWPR_PFSWE_SET (0x40)   /* PWPR.PFSWEを1に設定 */
#define PWPR_BOWI_SET (0x80)    /* PWPR.B0W1を1に設定 */
#define PWPR_PFSWE_CLEAR (0x00) /* PWPR.PFSWEを0に設定 */

/* マクロ関数 */
#define PWPR_UNLOCK()           \
  do                            \
  {                             \
    REG_PWPR = PWPR_BOWI_CLEAR; \
    REG_PWPR = PWPR_PFSWE_SET;  \
  } while (0)
#define PWPR_LOCK()              \
  do                             \
  {                              \
    REG_PWPR = PWPR_PFSWE_CLEAR; \
    REG_PWPR = PWPR_BOWI_SET;    \
  } while (0)
#define BTN_LED() ((P105PFS & (1 << 1)) == 0)

void setup()
{
  /* レジスタ設定 */
  PWPR_UNLOCK();
  P109PFS = 0x04;
  P112PFS = 0x04;
  P303PFS = 0x04;
  P105PFS = 0x10; /* PCRをプルアップ有効(1)にして、PDRを入力(0)に設定 */
  PWPR_LOCK();
}

void loop()
{
  static unit_8 led_status = 0;
  static unit_8 pre_led = 0;

  unit_8 btn_now = BTN_LED();

/* 緑のLEDは初めは点滅状態 */
PWPR_UNLOCK();
  P109PFS |= (1 << 0);
PWPR_LOCK();

  if (btn_now && !pre_led)
  {
    led_status = !led_status;
    if (led_status)
    {
      PWPR_UNLOCK();
      P109PFS &= ~(1 << 0);
      delay_ms(20);
      PWPR_LOCK();

      PWPR_UNLOCK();
      P112PFS |= (1 << 0);
      delay_ms(10000);
      PWPR_LOCK();

      PWPR_UNLOCK();
      P112PFS &= ~(1 << 0);
      P303PFS |= (1 << 0);
      delay_ms(7000);
      PWPR_LOCK();

      PWPR_UNLOCK();
      P303PFS &= ~(1 << 0);
      PWPR_LOCK();
    }
    else 
    {
      /* 処理なし */
    }
  }
  pre_led = btn_now;
  delay_ms(20);
}

/* タイマー自作関数 */
void delay_ms(unit_16 ms) {
/* AGT0モジュールストップ解除（MSTPD3=0） */
    REG_MSTPCRD &= ~(1 << 3);

    /* クロックソース: PCLKB/8（TCK=001） タイマモード（TMOD=000） */
    REG_AGTMR1 = 0x10;  /* bit6-4(TCK)=001: PCLKB/8 */

    /* 指定ms分ループ */
    unit_16 i;
    for (i = 0; i < ms; i++) {
        /* カウンタに250をセット（1ms分） */
        REG_AGT0 = 250;

        /* カウント開始（TSTART=1） */
        REG_AGTCR = 0x01;

        /* アンダーフロー（TUNDF=1）になるまで待つ */
        while ((REG_AGTCR & (1 << 5)) == 0);

        /* カウント停止（TSTOP=1） */
        REG_AGTCR = 0x04;
    }  

}
