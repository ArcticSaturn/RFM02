/*
 * rfm02_M16_TX_init_fctns.h
 *
 *  Created on: 18.09.2014
 *
 *  Last changed: 18.09.2014
 *
 *      Author: joeder
 */


/******************************************************************************/
/*         RFM02_Transmitter  Defines                                         */
/******************************************************************************/



/*    Control Register                                                        */
/******************************************************************************/
/*    RF-Config-Register  Initvalue: 8080hex -> For 430MHz-Band , b1(0) b0(1) */
/*                                                                            */
/*    Bits:  15  14  13  12  11  10   9   8   7   6   5   4   3   2   1   0   */
/*            1   0   0  b1  b0  d2  d1  d0  x3  x2  x1  x0  ms  m2  m1  m0   */
/*                                                                            */
/*    default 1   0   0   0   1   0   0   0   1   0   0   0   0   0   0   0   */
/*                                                                            */
/*                                                                            */
/*    Frequency Deviation [kHz]:  m2  m1  m0   value                          */
/*                                 0   0   0    30    *                       */
/*                                 0   0   1    60                            */
/*                                 0   1   0    90                            */
/*                                 0   1   1   120                            */
/*                                 1   0   0   150                            */
/*                                 1   0   1   180                            */
/*                                 1   1   0   210                            */
/*                                                                            */
/*    Modulation Polarity:         ms  value                                  */
/*                                  0   +180°  *                              */
/*                                  1   -180°                                 */
/*                                                                            */
/*    Crystal Load Capacity:       x3  x2  x1  x0   value                     */
/*                                  0   0   0   0   8.5 pF                    */
/*                                  0   0   0   1   9.0 pF                    */
/*                                  0   0   1   0   9.5 pF                    */
/*                                  0   0   1   1   10  pF                    */
/*                                  .   .   .   .                             */
/*                                  .   .   .   .   12.5 pF    *              */
/*                                  .   .   .   .                             */
/*                                  1   1   1   1   16.0 pF                   */
/*                                                                            */
/*    Frequency of Pin CLK:        d2  d1  d0   value                         */
/*                                  0   0   0   1    MHz   *                  */
/*                                  0   0   1   1.25 MHz                      */
/*                                  0   1   0   1.66 MHz                      */
/*                                  0   1   1   2.0  MHz                      */
/*                                  1   0   0   2.5  MHz                      */
/*                                  1   0   1   3.33 MHz                      */
/*                                  1   1   0   5    MHz                      */
/*                                  1   1   1   10   MHz                      */
/*                                                                            */
/*    If the CLK-Pin is not usesd to clock an external mikrocontroller        */
/*    set the dc-Bit in the Power Management Register.                        */
/*                                                                            */
/*    Band Selection:                   b1  b0  value                         */
/*                                      0   0   315 MHz                       */
/*                                      0   1   433 MHz   *                   */
/*                                      1   0   868 MHz                       */
/*                                      1   1   915 MHz                       */
/*    *: default value                                                        */
/******************************************************************************/
// set:  433MHz, Deviation 90kHz default: CLK 1MHz, Cap 12.0pF, Modularity +180°
//#define mrc_QuickSet_RFM02_TX()     CONFIG_CMD|=FREQ_DEV_90kHz+BAND_SELECT_433MHz

#define CONFIG_CMD          0x8000

/*    Frequency Deviation [kHz]:  m2  m1  m0   value                          */
#define FREQ_DEV_30kHz      0x00       // 0 0 0 0 0 0 0 0
#define FREQ_DEV_60kHz      0x01
#define FREQ_DEV_90kHz      0x02
#define FREQ_DEV_120kHz     0x03
#define FREQ_DEV_150kHz     0x04
#define FREQ_DEV_180kHz     0x05
#define FREQ_DEV_210kHz     0x06       // 0 0 0 0 0 1 1 0

/*    Modulation Polarity:         ms  value                                  */
#define MOD_POLTY_180_NEG          0x08  // 0 0 0 0 1 0 0 0
#define MOD_POLTY_180_POS          0x00

/*    Crystal Load Capacity:       x3  x2  x1  x0   value                     */
#define CRYSTAL_LD_CAP_08_5PF       0x00            // 8,5pF
#define CRYSTAL_LD_CAP_09_0PF       0x10            // ...
#define CRYSTAL_LD_CAP_09_5PF       0x20
#define CRYSTAL_LD_CAP_10_0PF       0x30
#define CRYSTAL_LD_CAP_10_5PF       0x40
#define CRYSTAL_LD_CAP_11_0PF       0x50
#define CRYSTAL_LD_CAP_11_5PF       0x60
#define CRYSTAL_LD_CAP_12_0PF       0x70
#define CRYSTAL_LD_CAP_12_5PF       0x80
#define CRYSTAL_LD_CAP_13_0PF       0x90
#define CRYSTAL_LD_CAP_13_5PF       0xA0
#define CRYSTAL_LD_CAP_14_0PF       0xB0
#define CRYSTAL_LD_CAP_14_5PF       0xC0
#define CRYSTAL_LD_CAP_15_0PF       0xD0
#define CRYSTAL_LD_CAP_15_5PF       0xE0
#define CRYSTAL_LD_CAP_16_0PF       0xF0

/*    Frequency of Pin CLK:      d2  d1  d0   value                         */
#define CLK_PIN_FREQ_1_00MHZ        0x0000      // 0 0 0 0 0 0 0 0
#define CLK_PIN_FREQ_1_25MHZ        0x0100
#define CLK_PIN_FREQ_1_66MHZ        0x0200      // ...
#define CLK_PIN_FREQ_2_00MHZ        0x0300
#define CLK_PIN_FREQ_2_50MHZ        0x0400
#define CLK_PIN_FREQ_3_33MHZ        0x0500
#define CLK_PIN_FREQ_5_00MHZ        0x0600
#define CLK_PIN_FREQ_10_00MHZ       0x0700     // 0 0 0 0 0 1 1 1 0 0 0 0 0 0 0 0

/*    Band Selection:               b1  b0    value ...                        */
#define BAND_SELECT_433MHz          0x0800
#define BAND_SELECT_868MHz          0x1000
#define BAND_SELECT_915MHz          0x1800




/******************************************************************************/
/*    RF-Frequency-Adjust-Register  Initvalue:  A7D0hex                       */
/*                                                                            */
/*    Bits:  15  14  13  12  11  10   9   8   7   6   5   4   3   2   1   0   */
/*            1   0   1   0  f11 f10 f9  f8  f7  f6  f5  f4  f3  f2  f1  f0   */
/*                                                                            */
/*              C1   C2                                                       */
/*     433band: 1    43                                                       */
/*     868band: 2    43                                                       */
/*     915band: 3    30                                                       */
/*                                                                            */
/*     value ranges from 0x0060..0x0F3F                                       */
/*                                                                            */
/*     f = 10MHz * C1 * (C2 + F/4000)      default: 435 MHz                   */
/*                                                                            */
/*                                                                            */
/******************************************************************************/
#define CONFIG_RF_FREQUENY_CMD    0xA000
// Nothing to do ! leave at 435 MHz

// Value for frequency must be calculated for the define
// Value for 439.7575 MHz
#define RF_FRQUENCY_439_7575_MHZ  0x0F3F   // max value

#define RF_FRQUENCY_435_0000_MHZ  0x07D0   // default

#define RF_FRQUENCY_430_2400_MHZ  0x0060  // min. value

/******************************************************************************/
/*    Baudrate-Adjust-Register  Initvalue:   C800hex                          */
/*                                                                            */
/*    Bits:  15  14  13  12  11  10   9   8   7   6   5   4   3   2   1   0   */
/*            1   1   0   0   1   0   0   0  r7  r6  r5  r4  r3  r2  r1  r0   */
/*                                                                            */
/*     Baud Rate = 10MHz/29/(R+1)                                             */
/*                                                                            */
/*     R ranges from 0..255                                                   */
/*                                                                            */
/*     --> Baud Rate can be set from 1,35 kBit/s  ..  344,8 kBit/s            */
/*                                                                            */
/*     Common values range from 9600 Bit/s .. 115.000 Bit/s                   */
/******************************************************************************/
#define CONFIG_BAUD_RATE_CMD           0xC800

#define mcr_QuickSet_BaudRate_9600()    BAND_SELECT_433MHz|=BAUD_RATE_09_600_BPS
// Value for baud rate must be calculated for the define
// Value for 38.400 bps  is 7.97988  --> 8

#define BAUD_RATE_115_000_BPS 0x02
#define BAUD_RATE_38_400_BPS  0x08
#define BAUD_RATE_19_200_BPS  0x11
#define BAUD_RATE_09_600_BPS  0x23  
#define BAUD_RATE_04_800_BPS  0x47


/******************************************************************************/
/*    RF-Power-Register  Initvalue:  B0hex                                    */
/*                                                                            */
/*    Bits:   7   6   5   4   3   2   1   0                                   */
/*            1   0   1   1  OOK  p2  p1  p0                                  */
/*                                                                            */
/*     RF-Power = 9 dBm - P - 1                                               */
/*                                                                            */
/*     P ranges from 0..7                                                     */
/*                                                                            */
/*     --> RF-Transmit-Power can be set from 1 .. 8 dBm                       */
/*                                                                            */
/*    OOK-Mode: On-Off-Keying via the FSK pin to en/disable the PowerAmp      */
/*                                                                            */
/*    When OOK is set, Transmit Data must be put in via the SPI-Port, as      */
/*    FSK-Input is only the Switch-Input for the Amplifier                    */
/*                                                                            */
/*                                                                            */
/******************************************************************************/
#define CONFIG_RF_PWR_CMD     0x00B0
// nothing to do when using FSK as Data-Input
#define RF_PWR_8DBM    0x0000   // Pmax (default)
// ...
#define RF_PWR_4DBM    0x0004
// ...
#define RF_PWR_1DBM    0x0007   // Pmin

#define OOK_ENABLED    0x0080   // TX-Data via SPI, FSK is en/disable RF-Amplifier
#define OOK_DISABLED   0x0000   // TX-Data via FSK   default

/******************************************************************************/
/*    WakeUp-Timer-Adjust-Register  Initvalue:  E000hex                       */
/*                                                                            */
/*    Bits:  15  14  13  12  11  10   9   8   7   6   5   4   3   2   1   0   */
/*            1   1   1  r4  r3  r2   r1  r0  m7  m6  m5  m4  m3  m2  m1  m0  */
/*                                                                            */
/*     Twu = M * 2^R  in ms       R: 0..23                                    */
/*                                                                            */
/*     Twu_max = 255 * 2^23 = 24,75 days                                      */
/*                                                                            */
/*     Twu_1min = 60000ms -->  =  117 * 2^9  --> m=117 r=9   --> 0xE975       */
/*                                                                            */
/*     15s: = 15000ms , 15000/255=58 -> Rmin=58 -> R=6 -> 2^6=64  -> R=6      */
/*                      15000/64=234 -> M=234  Value = 0xE6EA                 */
/*                                                                            */
/******************************************************************************/
#define CONFIG_WAKEUP_TIMER_CMD    0xE000

#define WAKEUP_TIME_01MIN   0xE975
#define WAKEUP_TIME_15s     0xE6EA


/******************************************************************************/
/*    LowBattDetect and TxD-sync-Bit-Register  Initvalue: C200hex             */
/*                                                                            */
/*    Bits:  15  14  13  12  11  10   9   8   7   6   5   4   3   2   1   0   */
/*            1   1   0   0   0   0   1   0  dwc  0  ebs  t4  t3  t2  t1  t0  */
/*                                                                            */
/*     Threshold Voltage is set by t4..t0 with Vlb = 2.2 V + T * 0.1 V        */
/*                                                                            */
/*     Threshold ranges from 2.2V .. 5.4V                                     */
/*                                                                            */
/*     ebs  -  Enable TX Bit synchronisation function                         */
/*                                                                            */
/*     dwc  -  Disable wake-up-timer periodical calibration                   */
/*                                                                            */
/******************************************************************************/
#define CONFIG_LOW_BATT_TRESHOLD  0xC200
// default: 2,2V  , no TX Bitsync, WUT-Calibration enabled ---> nothing to do
#define LOW_BATT_THLD_5_4_V       0x1F
#define LOW_BATT_THLD_3_2_V       0x0A
//       ...
#define LOW_BATT_THLD_2_8_V       0x06
#define LOW_BATT_THLD_2_2_V       0x00

#define TXBIT_SYNC_DISABLED       0x00
#define TXBIT_SYNC_ENABLED        0x20

#define DISABLE_WAKEUP_TIMER_CAL  0x80
#define ENABLE_WAKEUP_TIMER_CAL   0x00

/******************************************************************************/
/*    Power-Management-Register  Initvalue: C000hex                           */
/*                                                                            */
/*    Bits:  15  14  13  12  11  10   9   8   7   6   5   4   3   2   1   0   */
/*            1   1   0   0   0   0   0   0  a1  a0  ex  es  ea  eb  et  dc   */
/*                                                                            */
/*    dc  -   disable CLK  at  Pin CLK, if not used for the Control MCU       */
/*    et  -   enable wake-up-timer                                            */
/*    eb  -   enable low battery detection hardware                           */
/*    ea  -   enable power amplifier                                          */
/*    es  -   enable synthesizer                                              */
/*    ex  -   enable crystal oscillator                                       */
/*                                                                            */
/*    a0  -   if set, power amplifier is enabled by the data transmit command */
/*            and disabled via the sleep command                              */
/*                                                                            */
/*    a1  -   if set, crystal oscillator and synthesizer are enabled via the  */
/*            transmit command, and disabled via the sleep command            */
/******************************************************************************/
// default: CLK-Pin disabled, WUT disabled, LBD disabled, PowerAmp disabled, Syth. disabled, osz disabled, 
//          a0, a1 Auto-Mode ctrl-bit  no Auto-Mode

// Send-CMD_PowerOn: CLK disabl, WUT disabl, LBD disabl, PA en, Synth en, Osz en, Auto-PWR dis (0x38 + cmd)

#define CONFIG_PWR_CMD           0xC000

#define CLK_PIN_DISABLED          0x01
#define CLK_PIN_ENABLED           0x00
#define WAKE_UP_TIMER_ENABLED     0x02
#define WAKE_UP_TIMER_DISABLED    0x00
#define LOW_BATT_DET_ENABLED      0x04
#define LOW_BATT_DET_DISABLED     0x00
#define POWER_AMP_ENABLED         0x08
#define POWER_AMP_DISABLED        0x00
#define SYNTHESSIZER_ENABLED      0x10
#define SYNTHESSIZER_DISABLED     0x00
#define CRYSTAL_OSC_ENABLED       0x20
#define CRYSTAL_OSC_DISABLED      0x00
#define AUTO_PWR_AMP_ENABLED      0x40
#define AUTO_PWR_AMP_DISABLED     0x00
#define AUTO_PWR_SYN_OSC_ENABLED  0x80
#define AUTO_PWR_SYN_OSC_DISABLED 0x00

#define NORMAL_MODE 0x38
#define AUTO_MODE   0xC0

#define DISABLED    0x00
#define ENABLED     0x01