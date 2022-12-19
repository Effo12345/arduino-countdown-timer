#include "SevSeg.h"

SevSeg sevseg;
static unsigned long sec = 120, stre = 1, stre_updte = 0, sleep = 1000, timer = millis(), run = 1;

void setup() {
  byte digitPins[] = {10, 11, 12, 13}, segmentPins[] = {9, 2, 3, 5, 6, 8, 7, 4};
  sevseg.begin(COMMON_CATHODE, 4, digitPins, segmentPins, true);
}

void loop() {
  // put your main code here, to run repeatedly:
  stre *= stre_updte = (analogRead(A0) < 10 && stre % 2 != 0) ? 2 : (analogRead(A0) > 1000 && stre % 3 != 0) ? 3 : (analogRead(A1) < 10 && stre % 5 != 0) ? 5 : (analogRead(A1) > 1000 && stre % 7 != 0) ? 7 : 1;

    if(stre_updte == 2)
      sec = 0;
    else if(stre_updte == 3)
      sec -= 60;
    else if(stre_updte == 5)
      sleep /= 3;
    else if(stre_updte == 7)
      run = false;

    if(millis() >= timer && run) {
      timer += sleep;
      sevseg.setNumber(((int)(sec / 60)) * 100 + (int)(sec % 60));
      sec--;
      if(!sec)
        run = false;
    }

    sevseg.refreshDisplay();
}
