#include <LiquidCrystal.h>

LiquidCrystal lcd(12,11,5,4,3,2);        //RS 핀, E핀, 데이터 핀 4개
String lcdString = "";                   //객체 선언 : 출력 할 글자 저장

void setup() {

  pinMode(8,INPUT);
  Serial.begin(115200);

  lcd.begin(16,2);                       //LCD 크기 지정, 2줄 16칸
  lcd.clear();                           //화면 초기화

}

unsigned long pulse = 0;

float ugm3 = 0;

void loop() {

  pulse = pulseIn(8,LOW,20000);

  ugm3 = pulse2ugm3(pulse);

  Serial.print(ugm3,4);
  Serial.println("\tug/m3");

  lcd.setCursor(0,0);                    //커서를 0,0에 지정
  lcd.print(ugm3,4);
  lcd.print(" ug/m3     ");

  lcd.setCursor(0,1);
  if (ugm3 <= 30) {
    lcd.print("");
    lcd.print("GOOD        ");
  } 
  else if (ugm3 <= 80) {
    lcd.print("");
    lcd.print("NORMAL      ");
  }
  else if (ugm3 <= 150) {
    lcd.print("");
    lcd.print("BAD     ");
  }
  else {
    lcd.print("");
    lcd.print("FUCK     ");
  }

  delay(1000);
}



float pulse2ugm3(unsigned long pulse){

  float value = (pulse-1400)/14.0;

  if(value > 300){
    value = 0;
  }
  return value;
}
