#define EB_NO_COUNTER
#define EB_CLICK_TIME 140  // таймаут ожидания кликов (кнопка)

#include <Arduino.h>
#include <EncButton.h>
#include <Joystick.h>

//энкодер 1
#define btn1_CLK 9
#define btn1_SW 10
#define btn1_DT 8

//энкодер 2
#define btn2_DT 6
#define btn2_CLK 7
#define btn2_SW 5

//энкодер 3
#define btn3_DT 3
#define btn3_CLK 4
#define btn3_SW 2

//энкодер 4
#define btn4_CLK 16
#define btn4_SW 15
#define btn4_DT 14

Joystick_ joystick(JOYSTICK_DEFAULT_REPORT_ID,
  JOYSTICK_TYPE_JOYSTICK, 50, 0,
  false, false, false, false, false, false,
  false, false, false, false, false);


EncButton enc1(btn1_CLK, btn1_DT, btn1_SW);  // для работы c кнопкой
EncButton enc2(btn2_CLK, btn2_DT, btn2_SW);  // для работы c кнопкой
EncButton enc3(btn3_CLK, btn3_DT, btn3_SW);  // для работы c кнопкой
EncButton enc4(btn4_CLK, btn4_DT, btn4_SW);  // для работы c кнопкой

int eventENC(EncButton enc) {
  if(enc.hasClicks()) {
    switch (enc.getClicks()) {
      case 1: return 5; // 1 нажатие на энкодер  1 click on the encoder
      case 2: return 6; // 2 нажатия на энкодер  2 clicks on the encoder
      case 3: return 7; // 3 нажатия на энкодер  3 clicks on the encoder
      case 4: return 8; // 4 нажатия на энкодер  4 click on the encoder
      case 5: return 9; // 5 нажатий на энкодер  5 clicks on the encoder
      default: return -1;
    }
  }

  if(enc.fast()) {
    switch (enc.dir()) {
      case -1: return 2; // быстрое врощение налево   fast left rotation
      case 1:  return 4; // быстрое вращение направо  fast right rotation
      default: return -1;
    }
  } else {
    switch (enc.dir()) {
      case -1: return 1; // вращение налево   rotation to the left
      case 1:  return 3; // вращение направо  rotation to the right
      default: return -1;
    }
  }

}

void encClickMy(EncButton enc, int numENC) {
  if(enc.turn() || enc.hasClicks()) {
    const int numberEvent = eventENC(enc);
    const int result = (String(numENC) + String(numberEvent)).toInt() - 10;


    if (numberEvent == 2 || numberEvent == 4) {
      for (size_t i = 0; i < 3; i++)
      {
        joystick.pressButton(result);
        joystick.releaseButton(result);

      }

    }

    joystick.pressButton(result);
    joystick.releaseButton(result);

  }

}

void setup() {
  joystick.begin();

}

void loop() {
  enc1.tick();
  enc2.tick();
  enc3.tick();
  enc4.tick();
  encClickMy(enc1, 1);
  encClickMy(enc2, 2);
  encClickMy(enc3, 3);
  encClickMy(enc4, 4);

}
