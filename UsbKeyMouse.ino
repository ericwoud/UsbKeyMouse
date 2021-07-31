#include <stdio.h> // for function sprintf
#include "HID-Project.h"

#define  SPECIAL_FN   0xFF

#define SPEC    0x0000
#define SYST    0x1000
#define KEYB    0x7000
#define CONS    0xC000

#define KEYBDCOLUMNS 16
uint16_t keypressed[KEYBDCOLUMNS * 8]; // 16x8 matrix
unsigned int keybuffer[KEYBDCOLUMNS * 8]; // 16x8 matrix
const PROGMEM uint16_t keys[] = {
  // TABLE 0
  // 0 //                 // 1 //             // 2 //                 // 3 //                  // 4 //                // 5 //                // 6 //               // 7 //
  KEYB + KEY_DELETE,      0,                  KEYB + KEY_RIGHT_BRACE, KEYB + KEY_BACKSPACE,    KEYB + KEY_QUOTE,      0,                     KEYB + KEY_D,         KEYB + KEY_SLASH,       // 0 //
  KEYB + KEY_LEFT_CTRL,   0,                  0,                      0,                       0,                     KEYB + KEY_RIGHT_CTRL, 0,                    0,                      // 1 //
  KEYB + KEY_PAUSE,       KEYB + KEY_SPACE,   0,                      KEYB + KEY_MINUS,        KEYB + KEY_L,          KEYB + KEY_ENTER,      KEYB + KEY_M,         KEYB + KEY_COMMA,       // 2 //
  0,                      0,                  0,                      KEYB + KEY_LEFT_WINDOWS, 0,                     0,                     0,                    0,                      // 3 //
  KEYB + KEY_F11,         KEYB + KEY_N,       0,                      KEYB + KEY_F12,          KEYB + KEY_9,          KEYB + KEY_O,          0,                    KEYB + KEY_J,           // 4 //
  KEYB + KEY_INSERT,      KEYB + KEY_C,       KEYB + KEY_EQUAL,       KEYB + KEY_Q,            KEYB + KEY_LEFT_BRACE, 0,                     KEYB + KEY_K,         KEYB + KEY_PERIOD,      // 5 //
  0,                      KEYB + KEY_S,       KEYB + KEY_6,           KEYB + KEY_F8,           KEYB + KEY_T,          KEYB + KEY_Y,          KEYB + KEY_G,         KEYB + KEY_V,           // 6 //
  KEYB + KEY_HOME,        KEYB + KEY_0,       KEYB + KEY_BACKSLASH,   KEYB + KEY_PAGE_UP,      KEYB + KEY_PAGE_DOWN,  0,                     KEYB + KEY_END,       KEYB + KEY_SEMICOLON,   // 7 //
  KEYB + KEY_F9,          KEYB + KEY_B,       KEYB + KEY_8,           KEYB + KEY_F10,          KEYB + KEY_7,          KEYB + KEY_U,          KEYB + KEY_I,         KEYB + KEY_H,           // 8 //
  0,                      KEYB + KEY_LEFT_ALT, 0,                     0,                       0,                     0,                     KEYB + KEY_RIGHT_ALT, 0,                      // 9 //
  0,                      0,                  KEYB + KEY_3,           KEYB + KEY_F7,           KEYB + KEY_4,          KEYB + KEY_W,          KEYB + KEY_PRINTSCREEN, KEYB + KEY_F3,        // A //
  KEYB + KEY_RIGHT_ARROW, KEYB + KEY_F5,      KEYB + KEY_5,           KEYB + KEY_E,            KEYB + KEY_F6,         KEYB + KEY_R,          0,                    KEYB + KEY_F,           // B //
  KEYB + KEY_F4,          KEYB + KEY_F2,      KEYB + KEY_1,           KEYB + KEY_X,            KEYB + KEY_2,          KEYB + KEY_F1,         KEYB + KEY_A,         KEYB + KEY_Z,           // C //
  0,                      0,                  KEYB + KEY_LEFT_SHIFT,  0,                       0,                     0,                     0,                    KEYB + KEY_RIGHT_SHIFT, // D //
  KEYB + KEY_LEFT_ARROW,  0,                  KEYB + KEY_TAB,         KEYB + KEY_TILDE,        KEYB + KEY_CAPS_LOCK,  SPEC + SPECIAL_FN,     KEYB + KEY_MENU,      0,                      // E //
  0,                      KEYB + KEY_ESC,     0,                      KEYB + KEY_P,            KEYB + KEY_UP_ARROW,   0,                     KEYB + KEY_DOWN_ARROW, 0,                     // F //
  // 0 //                 // 1 //             // 2 //                 // 3 //                  // 4 //                // 5 //                // 6 //               // 7 //
  // TABLE 1
  // 0 //                 // 1 //             // 2 //                 // 3 //                  // 4 //                // 5 //                // 6 //               // 7 //
  KEYB + KEY_SCROLL_LOCK, 0,                  0,                      0,                       0,                     0,                     0,                    0,                      // 0 //
  0,                      0,                  0,                      0,                       0,                     0,                     0,                    0,                      // 1 //
  0,                      CONS + HID_CONSUMER_AL_POWER_STATUS, 0,     0,                       0,                     0,                     0,                    0,                      // 2 //
  0,                      0,                  0,                      0,                       0,                     0,                     0,                    0,                      // 3 //
  CONS + MEDIA_VOLUME_DOWN, 0,                0,                      CONS + MEDIA_VOLUME_UP,  0,                     0,                     0,                    0,                      // 4 //
  KEYB + KEY_NUM_LOCK,    CONS + CONSUMER_SCREENSAVER, 0,             0,                       0,                     0,                     0,                    0,                      // 5 //
  0,                      0,                  0,                      SYST + HID_SYSTEM_DISPLAY_TOGGLE_INT_SLASH_EXT, 0, 0,                  0,                    0,                      // 6 //
  0,                      0,                  0,                      0,                       0,                     0,                     0,                    0,                      // 7 //
  KEYB + KEY_F21,         0,                  0,                      CONS + MEDIA_VOLUME_MUTE, 0,                    0,                     0,                    0,                      // 8 //
  0,                      0,                  0,                      0,                       0,                     0,                     0,                    0,                      // 9 //
  0,                      0,                  0,                      SYST + HID_SYSTEM_DISPLAY_INVERT, 0,            0,                     0,                    0,                      // A //
  CONS + MEDIA_NEXT,      CONS + CONSUMER_BRIGHTNESS_DOWN, 0,         0,                       CONS + CONSUMER_BRIGHTNESS_UP, 0,             0,                    0,                      // B //
  0,                      CONS + HID_CONSUMER_AL_WIRELESS_STATUS,  0, 0,                       0,                     SYST + SYSTEM_SLEEP,   0,                    0,                      // C //
  0,                      0,                  0,                      0,                       0,                     0,                     0,                    0,                      // D //
  CONS + MEDIA_PREV,      0,                  0,                      0,                       0,                     SPEC + SPECIAL_FN,     0,                    0,                      // E //
  0,                      0,                  0,                      0,                       CONS + MEDIA_STOP,     0,                     CONS + MEDIA_PLAY_PAUSE, 0,                   // F //
  // 0 //                 // 1 //             // 2 //                 // 3 //                  // 4 //                // 5 //                // 6 //               // 7 //
  // TABLE 2
  // 0 //                 // 1 //             // 2 //                 // 3 //                  // 4 //                // 5 //                // 6 //               // 7 //
  0,                      0,                  0,                      0,                       0,                     0,                     0,                    KEYB + KEYPAD_ADD,      // 0 //
  0,                      0,                  0,                      0,                       0,                     0,                     0,                    0,                      // 1 //
  0,                      0,                  0,                      0,                       KEYB + KEYPAD_3,       0,                     KEYB + KEYPAD_0,      0,                      // 2 //
  0,                      0,                  0,                      0,                       0,                     0,                     0,                    0,                      // 3 //
  0,                      0,                  0,                      0,                       KEYB + KEYPAD_9,       KEYB + KEYPAD_6,       0,                    KEYB + KEYPAD_1,        // 4 //
  0,                      0,                  0,                      0,                       0,                     0,                     KEYB + KEYPAD_2,      KEYB + KEYPAD_DOT,      // 5 //
  0,                      0,                  0,                      0,                       0,                     0,                     0,                    0,                      // 6 //
  0,                      KEYB + KEYPAD_DIVIDE, 0,                    0,                       0,                     0,                     0,                    KEYB + KEYPAD_SUBTRACT, // 7 //
  0,                      0,                  KEYB + KEYPAD_8,        0,                       KEYB + KEYPAD_7,       KEYB + KEYPAD_4,       KEYB + KEYPAD_5,      0,                      // 8 //
  0,                      0,                  0,                      0,                       0,                     0,                     0,                    0,                      // 9 //
  0,                      0,                  0,                      0,                       0,                     0,                     0,                    0,                      // A //
  0,                      0,                  0,                      0,                       0,                     0,                     0,                    0,                      // B //
  0,                      0,                  0,                      0,                       0,                     0,                     0,                    0,                      // C //
  0,                      0,                  0,                      0,                       0,                     0,                     0,                    0,                      // D //
  0,                      0,                  0,                      0,                       0,                     SPEC + SPECIAL_FN,     0,                    0,                      // E //
  0,                      0,                  0,                      KEYB + KEYPAD_MULTIPLY,  0,                     0,                     0,                    0,                      // F //
  // 0 //                 // 1 //             // 2 //                 // 3 //                  // 4 //                // 5 //                // 6 //               // 7 //
};

#define RXLED 17  // The RX LED has a defined Arduino pin

//                N.C. --- TOUCHPAD      PIN  1
// SWITCH TO GND RIGHT --- TOUCHPAD    R PIN  2
// SWITCH TO GND  LEFT --- TOUCHPAD    L PIN  3
//                N.C. --- TOUCHPAD      PIN  4
//                N.C. --- TOUCHPAD      PIN  5
//                N.C. --- TOUCHPAD      PIN  6
//                 GND --- TOUCHPAD  GND PIN  7
//                 GND --- TOUCHPAD  GND PIN  8
#define  MCLK 1 //   1 --- TOUCHPAD  CLK PIN  9
#define MDATA 0 //   0 --- TOUCHPAD DATA PIN  10
//                 VCC --- TOUCHPAD  +5V PIN  11
//                 VCC --- TOUCHPAD  +5V PIN  12

byte mouse_passed = 0; /* should be 0xaa when mouse ok after reset */
byte mouse_id =  0xff; /* should be 0x00 when mouse ok after reset */
byte mouse_left = 0;
byte mouse_right = 0;
bool mouse_error = false;
unsigned long mouse_maxtime = 0L;
const unsigned long mouse_MAXWAIT = 200UL;

const unsigned long CYCLE_TIME = 2500UL; // microseconds
unsigned long proces_mintime = 0xFFFFUL, proces_avgtime = 0UL, proces_maxtime = 0UL;
unsigned long proces_lastmicros;
bool proces_firstrun = true;

bool keyboard_fn_pressed = false;
uint8_t keyboard_leds = 0;

void mouse_gohi(int pin)
{
  pinMode(pin, INPUT);
  digitalWrite(pin, HIGH);
}

void mouse_golo(int pin)
{
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
}

void mouse_wait(int state)
{
  long count = 0L;
  unsigned long starttime, totaltime, timeout, now;
  starttime = micros();
  timeout = starttime + mouse_MAXWAIT;
  while ((digitalRead(MCLK) == state) && ((now = micros()) < timeout)) ++count;
  if (now == timeout) mouse_error = true;
  totaltime = micros() - starttime;
  if (totaltime > mouse_maxtime) mouse_maxtime = totaltime;
}

void mouse_write(char data)
{
  char i;
  char parity = 1;
  if (mouse_error == false) {
    mouse_gohi(MDATA);  /* put pins in output mode */
    mouse_gohi(MCLK);
    delayMicroseconds(300);
    mouse_golo(MCLK);
    delayMicroseconds(300);
    mouse_golo(MDATA);
    delayMicroseconds(10);
    mouse_gohi(MCLK);   /* start bit */
    mouse_wait(HIGH);   /* wait for mouse to take control of clock); */
    for (i = 0; i < 8; i++) {            /* clock is low, and we are clear to send data */
      if (data & 0x01) mouse_gohi(MDATA);
      else             mouse_golo(MDATA);
      mouse_wait(LOW);     /* wait for clock cycle */
      mouse_wait(HIGH);
      parity ^= data & 0x01;
      data = data >> 1;
    }
    if (parity) mouse_gohi(MDATA);   /* parity */
    else        mouse_golo(MDATA);
    mouse_wait(LOW);
    mouse_wait(HIGH);
    mouse_gohi(MDATA);   /* stop bit */
    delayMicroseconds(50);
    mouse_wait(HIGH);
    mouse_wait(LOW);   /* wait for mouse to switch modes DELETED SOME, STILL WORKS*/
    mouse_golo(MCLK);   /* put a hold on the incoming data. */
  }
}

char mouse_read(void)
{
  char data = 0x00;
  int i;
  char bit = 0x01;
  if (mouse_error == false) {
    mouse_gohi(MCLK);   /* start the clock */
    mouse_gohi(MDATA);
    delayMicroseconds(50);
    mouse_wait(HIGH);
    delayMicroseconds(5);  /* not sure why */
    mouse_wait(LOW); /* eat start bit */
    for (i = 0; i < 8; i++) {
      mouse_wait(HIGH);
      if (digitalRead(MDATA) == HIGH) data |= bit;
      mouse_wait(LOW);
      bit = bit << 1;
    }
    mouse_wait(HIGH);   /* eat parity bit, which we ignore */
    mouse_wait(LOW);
    mouse_wait(HIGH);   /* eat stop bit */
    mouse_wait(LOW);
    mouse_golo(MCLK);
    return data;
  }
}

void proceskb()
{
  byte temp, portf, inbyte, col, rowbit;
  int keypos;
  char str[256];        // long enough
  uint16_t key;
  unsigned long currentmicros;
  unsigned long proces_time;

  if (!proces_firstrun) {
    currentmicros = micros();
    proces_time = (currentmicros - proces_lastmicros);
    if (proces_time > proces_maxtime) proces_maxtime = proces_time;
    if (proces_time < proces_mintime) proces_mintime = proces_time;
    proces_avgtime = ((proces_avgtime * 99) + proces_time) / 100;
    if (proces_time < CYCLE_TIME) delayMicroseconds(CYCLE_TIME - proces_time);
  }

  proces_firstrun = false;
  proces_lastmicros = micros(); // start point of cycle time measurement
  for (col = 0; col < KEYBDCOLUMNS; col++) {
    portf =  PORTF;
    portf ^= (col << 4);
    portf &= B11110000;
    PORTF ^= portf;
    delayMicroseconds(5); // minimal 4
    temp   = PIND;
    inbyte = PINB;
    //    temp   &= B10000001;
    inbyte &= B01111110;
    inbyte |= temp      & B10000000;
    inbyte |= (temp >> 4) & B00000001;
    inbyte = ~inbyte;

    //if (BootKeyboard.getLeds() & LED_CAPS_LOCK)
    keyboard_leds = BootKeyboard.getLeds();
    for (rowbit = 0; rowbit < 8; rowbit++) {
      keypos = (col << 3) + rowbit;
      keybuffer[keypos] = keybuffer[keypos] >> 1;
      if (((1 << rowbit) & inbyte) != 0) keybuffer[keypos] |= 0x8000;
      if (keybuffer[keypos] == 0x8000) {
        key = 0;
        if (keyboard_fn_pressed)                          key = pgm_read_word(keys + (1 * KEYBDCOLUMNS * 8) + keypos);
        if ((key == 0) && (keyboard_leds & LED_NUM_LOCK)) key = pgm_read_word(keys + (2 * KEYBDCOLUMNS * 8) + keypos);
        if (key == 0)                                     key = pgm_read_word(keys + (0 * KEYBDCOLUMNS * 8) + keypos);
        keypressed[keypos] = key;
        switch (key & 0xF000) {
          case SPEC:
            if (key == (SPEC + 0)) break;
            if (key == (SPEC + SPECIAL_FN)) keyboard_fn_pressed = true;
            break;
          case KEYB:
            BootKeyboard.press((KeyboardKeycode)lowByte(key));
            break;
          case CONS:
            Consumer.press((ConsumerKeycode)(key & 0xFFF));
            break;
          case SYST:
            System.press((SystemKeycode)lowByte(key));
            break;
        }
        sprintf(str, "DN: %04x  ROW: %02x  COL: %02x", key, rowbit, col ); Serial.println(str);
      }
      else if (keybuffer[keypos] == 0x0001) {
        keybuffer[keypos] = 0;
        key = keypressed[keypos];
        keypressed[keypos] = 0;
        switch (key & 0xF000) {
          case SPEC:
            if (key == 0) break;
            if (key == (SPEC + SPECIAL_FN)) keyboard_fn_pressed = false;
            break;
          case KEYB:
            BootKeyboard.release((KeyboardKeycode)lowByte(key));
            break;
          case CONS:
            Consumer.release((ConsumerKeycode)(key & 0xFFF));
            break;
          case SYST:
            System.release();
            break;
        }
        sprintf(str, "UP: %04x  ROW: %02x  COL: %02x", key, rowbit, col ); Serial.println(str);
        sprintf(str, "mouse_maxtime: %ld", mouse_maxtime ); Serial.println(str);
        sprintf(str, "proces_mintime: %ld proces_avgtime: %ld proces_maxtime: %ld", proces_mintime , proces_avgtime , proces_maxtime ); Serial.println(str);
        if (mouse_error == true) Serial.println("MOUSE ERROR!");
//        for (int ii = 0; ii < CIE_INPUT_SIZE; ii++) Serial.println(cie[ii]);
      }
    }
  }
}

void mouse_init()
{
  delay(1000);
  mouse_error = false;
  mouse_gohi(MCLK);
  mouse_gohi(MDATA);
  //Serial.print("Sending reset to mouse\n");
  mouse_write(0xff);
  mouse_error = false;
  mouse_read();                 /* ack byte */
  mouse_error = false;
  mouse_passed = mouse_read();  /* should be 0xaa */
  mouse_error = false;
  //Serial.println(mouse_passed, HEX);
  mouse_id     = mouse_read();  /* should be 0x00 */
  //Serial.print("Sending remote mode code\n");
  mouse_error = false;          /* reset error status and counters, after reset always a long delay */
  mouse_maxtime = 0UL;
  mouse_write(0xf0);  /* remote mode */
  mouse_read();  /* ack */
  //Serial.print("Read ack byte2\n");
  delayMicroseconds(100);
}

void setup()
{

  pinMode(RXLED, OUTPUT);  // Set RX LED as an output
  // TX LED is set as an output behind the scenes

  Serial.begin(9600); //This pipes to the serial monitor

  pinMode( 4, INPUT_PULLUP);   // PD4  ---  KEYBD KSI0 PIN 12
  pinMode(15, INPUT_PULLUP);   // PB1  ---  KEYBD KSI1 PIN  7
  pinMode(16, INPUT_PULLUP);   // PB2  ---  KEYBD KSI2 PIN 11
  pinMode(14, INPUT_PULLUP);   // PB3  ---  KEYBD KSI3 PIN 13
  pinMode( 8, INPUT_PULLUP);   // PB4  ---  KEYBD KSI4 PIN 10
  pinMode( 9, INPUT_PULLUP);   // PB5  ---  KEYBD KSI5 PIN  6
  pinMode(10, INPUT_PULLUP);   // PB6  ---  KEYBD KSI6 PIN  9
  pinMode( 6, INPUT_PULLUP);   // PD7  ---  KEYBD KSI7 PIN  8

  //            RESISTOR TO GND ---  MUX SIG
  pinMode(A3, OUTPUT);  // PF4  ---  MUX  S0
  pinMode(A2, OUTPUT);  // PF5  ---  MUX  S1
  pinMode(A1, OUTPUT);  // PF6  ---  MUX  S2
  pinMode(A0, OUTPUT);  // PF7  ---  MUX  S3
  //                       N.C. ---  MUX  EN
  //                        VCC ---  MUX VCC
  //                        GND ---  MUX GND

  // MUX  C0  ---  KEYBD KSO0  PIN 23
  // MUX  C1  ---  KEYBD KSO1  PIN  4
  // MUX  C2  ---  KEYBD KSO2  PIN 20
  // MUX  C3  ---  KEYBD KSO3  PIN  3
  // MUX  C4  ---  KEYBD KSO4  PIN 19
  // MUX  C5  ---  KEYBD KSO5  PIN 21
  // MUX  C6  ---  KEYBD KSO6  PIN 17
  // MUX  C7  ---  KEYBD KSO7  PIN 22
  // MUX  C8  ---  KEYBD KSO8  PIN 18
  // MUX  C9  ---  KEYBD KSO9  PIN  2
  // MUX C10  ---  KEYBD KSO10 PIN 15
  // MUX C11  ---  KEYBD KSO11 PIN 16
  // MUX C12  ---  KEYBD KSO12 PIN 14
  // MUX C13  ---  KEYBD KSO13 PIN  5
  // MUX C14  ---  KEYBD KSO14 PIN  1
  // MUX C15  ---  KEYBD KSO15 PIN 24

  mouse_init();
  BootKeyboard.begin();
  System.begin();
  Consumer.begin();
  Mouse.begin();
}

void loop()
{
  static int count, avail, numread;
  static byte receivedByte1=22,receivedByte2=33,receivedByte3=44, dbgprintcnt=0;

  // Bit 7       Bit 6       Bit 5   Bit 4   Bit 3     Bit 2   Bit 1  Bit 0
  byte mstat; // Y overflow  X overflow  Y sign  X sign  Always 1  Middle  Right  Left
  char mx;
  char my;
  char str[256];        // long enough

  proceskb();
  mouse_write(0xeb);  /* give me data! */
  proceskb();
  mouse_read();      /* ignore ack */
  proceskb();
  mstat = mouse_read();
  proceskb();
  mx = mouse_read();
  proceskb();
  my = mouse_read();
  if (mouse_error == false) {
    if      ( ((mstat & B01) != 0) && (mouse_left  == 0) ) {
      mouse_left = 1;
      Mouse.press(  MOUSE_LEFT);
    }
    else if ( ((mstat & B01) == 0) && (mouse_left  != 0) ) {
      mouse_left = 0;
      Mouse.release(MOUSE_LEFT);
    }
    if      ( ((mstat & B10) != 0) && (mouse_right == 0) ) {
      mouse_right = 1;
      Mouse.press(  MOUSE_RIGHT);
    }
    else if ( ((mstat & B10) == 0) && (mouse_right != 0) ) {
      mouse_right = 0;
      Mouse.release(MOUSE_RIGHT);
    }
    if ((mx != 0) || (my != 0)) {
      Mouse.move(mx, -my);
      //Serial.print(mstat, BIN); Serial.print("\tX="); Serial.print(mx, DEC); Serial.print("\tY="); Serial.print(my, DEC); Serial.println();
    }
  }
  proceskb();
  if (count >= 20) {
    count = 0;
    if (digitalRead(RXLED) == HIGH) {
      digitalWrite(RXLED, LOW);   // set the RX LED ON
      TXLED0; //TX LED is not tied to a normally controlled pin so a macro is needed, turn LED OFF
    }
    else {
      digitalWrite(RXLED, HIGH);    // set the RX LED OFF
      TXLED1; //TX LED macro to turn LED ON
    }
  }
  count++;
}
