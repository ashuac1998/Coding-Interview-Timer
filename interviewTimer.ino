#include <LiquidCrystal.h>
LiquidCrystal lcd(1,2,4,5,6,7);

int buzz = 13;
int button = 12;
int minutes = 44;

bool pressed = false;
bool timerPaused = false;
static int pressCount = 0;


static void smallBeep(){
  digitalWrite(buzz, HIGH);
  delay(50);
  digitalWrite(buzz, LOW);
}

static int printMessage(int mins, int secs, String str1, String str2){
      lcd.setCursor(0,0);
      lcd.print(mins);
      lcd.print(":");
      lcd.print(secs);
      lcd.setCursor(0, 1);
      lcd.print("Remaining");
      delay(100);
      lcd.clear();
      smallBeep();
      lcd.print(str1);
      lcd.setCursor(0,1);
      lcd.print(str2);
      delay(1000);
      lcd.clear();
      lcd.setCursor(0,0);

      return secs-1;
  };
bool checkState(){
  bool currentState = digitalRead(button);
  if(currentState == pressed){
      pressCount += 1;
      smallBeep();
      while(digitalRead(button) == pressed){}//Do nothing
    }
  if(pressCount%2 == 1){
    return false;
  }else{
    return true;
  }
}

void setup() {
  lcd.begin(16, 2);
  pinMode(buzz, OUTPUT);
  pinMode(button, INPUT_PULLUP);
}
//void printIntro
void loop() {

int seconds = 59;
  while(minutes >= 0){
    if(seconds <= 0){
        seconds = 59;
      }
    timerPaused = checkState();
    
    if(timerPaused == false){
      //timerPaused = checkState();
        while(seconds >= 0){
          timerPaused = checkState();
          if(timerPaused == true){
            break;
          }
          lcd.setCursor(0,0);
          lcd.print(minutes);
          lcd.print(":");
          lcd.print(seconds);
          lcd.setCursor(0, 1);
          lcd.print("Remaining");
          seconds--;
          delay(900);
          lcd.clear();
          delay(100);
          timerPaused = checkState();
          if(timerPaused == true){
            minutes++;
            break;
          }
          if(minutes == 40 && seconds == 0){
            seconds = printMessage(minutes, seconds, "Discussion Time", "Over");
          }else if(minutes == 30 && seconds == 0){
            seconds = printMessage(minutes, seconds, "Problem Analysis", "Time Over");
          }else if(minutes == 5 && seconds == 0){
            seconds = printMessage(minutes, seconds, "Coding Time", "Over");
          }else if(minutes == 0 && seconds == 0){
            seconds = printMessage(minutes, seconds, "Follow Up", "Time Over");
          }
         }
         minutes--;
    }else{
      //timerPaused = checkState();
      while(timerPaused == true){
        timerPaused = checkState();
        if(timerPaused == false){
          break;
        }
        lcd.setCursor(0,0);
        lcd.print(minutes);
        lcd.print(":");
        lcd.print(seconds);
        lcd.setCursor(0, 1);
        lcd.print("Remaining");
        delay(200);
        lcd.clear();

      }
    }  
  }
  printMessage(0, 0, "Interview", "Time Over");
  
}
