#include <TimeLib.h>
#include <Time.h>

/* Change these values to set the current initial time */
const byte seconds = 0;
const byte minutes = 0;
const byte hours = 16;

/* Change these values to set the current initial date */
const byte mday = 25;
const byte mmonth = 5;
const byte myear = 20;

void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);

  setTime(hours,minutes,seconds,mday,mmonth,myear);
}

void loop() {
  // put your main code here, to run repeatedly:
  SetPhase(year(), month(), day());
  delay(1000);
}

void phase_1(){
  digitalWrite(11, HIGH);
  digitalWrite(9, LOW);
  digitalWrite(12, LOW);
  digitalWrite(8, LOW);
  digitalWrite(13, LOW);
  digitalWrite(10, LOW);
}

void phase_2(){
  digitalWrite(11, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(12, LOW);
  digitalWrite(8, LOW);
  digitalWrite(13, LOW);
  digitalWrite(10, LOW);
}

void phase_3(){
  digitalWrite(11, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(8, LOW);
  digitalWrite(13, LOW);
  digitalWrite(10, LOW);
}

void phase_4(){
  digitalWrite(11, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(13, LOW);
  digitalWrite(10, LOW);
}

void phase_5(){
  digitalWrite(11, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(13, HIGH);
  digitalWrite(10, LOW);
}

void full_moon(){
  digitalWrite(11, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(13, HIGH);
  digitalWrite(10, HIGH);
}

void phase_n_5(){
  digitalWrite(11, LOW);
  digitalWrite(9, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(13, HIGH);
  digitalWrite(10, HIGH);
}


void phase_n_4(){
  digitalWrite(11, LOW);
  digitalWrite(9, LOW);
  digitalWrite(12, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(13, HIGH);
  digitalWrite(10, HIGH);
}

void phase_n_3(){
  digitalWrite(11, LOW);
  digitalWrite(9, LOW);
  digitalWrite(12, LOW);
  digitalWrite(8, HIGH);
  digitalWrite(13, HIGH);
  digitalWrite(10, HIGH);
}

void phase_n_2(){
  digitalWrite(11, LOW);
  digitalWrite(9, LOW);
  digitalWrite(12, LOW);
  digitalWrite(8, LOW);
  digitalWrite(13, HIGH);
  digitalWrite(10, HIGH);
}

void phase_n_1(){
  digitalWrite(11, LOW);
  digitalWrite(9, LOW);
  digitalWrite(12, LOW);
  digitalWrite(8, LOW);
  digitalWrite(13, LOW);
  digitalWrite(10, HIGH);
}

void new_moon(){
  digitalWrite(11, LOW);
  digitalWrite(9, LOW);
  digitalWrite(12, LOW);
  digitalWrite(8, LOW);
  digitalWrite(13, LOW);
  digitalWrite(10, LOW);
}

void SetPhase(int nYear, int nMonth, int nDay){
  float phase;
  double AG, IP;
  long YY, MM, K1, K2, K3, JD;
  YY = nYear - floor((12 - nMonth) / 10);
  MM = nMonth + 9;

  if (MM >= 12) {
    MM = MM - 12;
  }

  K1 = floor(365.25 * (YY + 4712));
  K2 = floor(30.6 * MM + 0.5);
  K3 = floor(floor((YY / 100) + 49) * 0.75) - 38;
  JD = K1 + K2 + nDay + 59;

  if (JD > 2299160) {
    JD = JD - K3;
  }

  IP = MyNormalize((JD - 2451550.1) / 29.530588853);
  AG = IP*29.53;

  bool set = false;
  if ((AG < 2.66) && (!set)){
    set = true;
    new_moon();
  }

  if ((AG < 5.32) && (!set)){
    set = true;
    phase_n_1();
  }

  if ((AG < 7.99) && (!set)){
    set = true;
    phase_n_2();
  }

  if ((AG < 10.65) && (!set)){
    set = true;
    phase_n_3();
  }

  if ((AG < 13.31) && (!set)){
    set = true;
    phase_n_4();
  }

  if ((AG < 15.97) && (!set)){
    set = true;
    phase_n_5();
  }

  if ((AG < 18.63) && (!set)){
    set = true;
    full_moon();
  }

  if ((AG < 21.29) && (!set)){
    set = true;
    phase_5();
  }

  if ((AG < 23.95) && (!set)){
    set = true;
    phase_4();
  }
  
  if ((AG < 26.61) && (!set)){
    set = true;
    phase_3();
  }

  if ((AG < 29.27) && (!set)){
    set = true;
    phase_2();
  }

  if ((AG < 31.93) && (!set)){
    set = true;
    phase_1();
  }

  if (!set){
    set = true;
    new_moon();
  }

}

double MyNormalize(double v){
  v = v - floor(v);
  if (v < 0){
    v = v + 1;
  }
  return v;

}
