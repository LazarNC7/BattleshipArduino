#include <LedControl.h>
#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DIN_MATRIX1 9
#define CS_MATRIX1 5
#define CLK_MATRIX1 13

#define DIN_MATRIX2 10
#define CS_MATRIX2 6
#define CLK_MATRIX2 13

#define DIN_MATRIX3 3
#define CS_MATRIX3 A3
#define CLK_MATRIX3 13

#define DIN_MATRIX4 A2
#define CS_MATRIX4 A1
#define CLK_MATRIX4 13

#define X_SEGMENTS 8
#define Y_SEGMENTS 8

int playerX = 7;
int playerY = 0;

int matrixActive = 1;

bool buttonPressed = false; 

LedControl lc_M1 = LedControl(DIN_MATRIX1, CLK_MATRIX1, CS_MATRIX1, 1);
LedControl lc_M2 = LedControl(DIN_MATRIX2, CLK_MATRIX2, CS_MATRIX2, 1);
LedControl lc_M3 = LedControl(DIN_MATRIX3, CLK_MATRIX3, CS_MATRIX3, 1);
LedControl lc_M4 = LedControl(DIN_MATRIX4, CLK_MATRIX4, CS_MATRIX4, 1);
LedControl* l = nullptr;

const byte ROWS = 1;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', '4'}
};
byte rowPins[ROWS] = {12}; 
byte colPins[COLS] = {11, 8, 7, 4}; 

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

LiquidCrystal_I2C  lcd(0x27,20,4);

bool hit1[8][8];
bool hit2[8][8];

void setup() {
  lc_M1.shutdown(0, false);
  lc_M1.setIntensity(0, 8);
  lc_M1.clearDisplay(0);

  lc_M2.shutdown(0, false);
  lc_M2.setIntensity(0, 8);
  lc_M2.clearDisplay(0);

  lc_M3.shutdown(0, false);
  lc_M3.setIntensity(0, 8);
  lc_M3.clearDisplay(0);

  lc_M4.shutdown(0, false);
  lc_M4.setIntensity(0, 8);
  lc_M4.clearDisplay(0);

  lcd.init();
  lcd.backlight();



  pinMode(2, INPUT_PULLUP); 
  l = &lc_M1;
  updateLCD(1,false,playerX, playerY);
  randomSeed(millis());
  generateBoats();
  setLedsMatrix();
}



int matrix1[8][8];
int matrix2[8][8];
void generateBoats(){
  int boatsLength[]={2,3,3,4,5};
  
  memset(matrix1, 0, sizeof(matrix1));
  
  memset(matrix2, 0, sizeof(matrix2));
  int x1,x2,y1,y2, pos1,pos2;
  for(int j=0;j<5;j++){
    bool isValid=false;
    pos1=random(0,4);
    pos2=random(0,4);
    while(!isValid){
      
      
      switch(pos1){
        case 0:{//position is to the right
          x1=random(0,8-boatsLength[j]);
          y1=random(0,8);
          for(int i=0;i<boatsLength[j];i++){
            if(matrix1[y1][x1+i]==0){
              matrix1[y1][x1+i]=j+1;
              isValid=true;
            }else{
              
              for(int k=0;k<i;k++){
                matrix1[y1][x1+k]=0;

              }
              
              isValid=false;
              break;
            }
          }
          break;
        }
        case 1:{//position is to the left
          x1=random(0+boatsLength[j],8);
          y1=random(0,8);
          for(int i=0;i<boatsLength[j];i++){
           if(matrix1[y1][x1-i]==0){
              matrix1[y1][x1-i]=j+1;
              isValid=true;
            }else{
              
              for(int k=0;k<i;k++){
                matrix1[y1][x1-k]=0;

              }
              isValid=false;
              break;
            }
          }
          break;
        }
        case 2:{//position is up
          x1=random(0,8);
          y1=random(0,8-boatsLength[j]);
          for(int i=0;i<boatsLength[j];i++){
            if(matrix1[y1+i][x1]==0){
              matrix1[y1+i][x1]=j+1;
              isValid=true;
            }else{
              
              for(int k=0;k<i;k++){
                matrix1[y1+k][x1]=0;

              }
              isValid=false;
              break;
            }
          }
          break;
        }
        case 3:{
          x1=random(0,8);
          y1=random(boatsLength[j], 8);
          for(int i=0;i<boatsLength[j];i++){
            if(matrix1[y1-i][x1]==0){
              matrix1[y1-i][x1]=j+1;
              isValid=true;
            }else{
              
              for(int k=0;k<i;k++){
                matrix1[y1-k][x1]=0;

              }
              isValid=false;
              break;
            }
          }
          break;
        }
        default:{
          Serial.println("The position is out of bounds. There is an error");
        }
      }
    }
    
    isValid=false;
    while(!isValid){
      
      switch(pos2){
        case 0:{//position is to the right
          x2=random(0,8-boatsLength[j]);
          y2=random(0,8);
          for(int i=0;i<boatsLength[j];i++){
            if(matrix2[y2][x2+i]==0){
              matrix2[y2][x2+i]=j+1;
              isValid=true;
            }else{
              
              for(int k=0;k<i;k++){
                matrix2[y2][x2+k]=0;

              }
              isValid=false;
              break;
            }
          }
          break;
        }
        case 1:{//position is to the left
          x2=random(0+boatsLength[j],8);
          y2=random(0,8);
          for(int i=0;i<boatsLength[j];i++){
           if(matrix2[y2][x2-i]==0){
              matrix2[y2][x2-i]=j+1;
              isValid=true;
            }else{
              
              for(int k=0;k<i;k++){
                matrix2[y2][x2-k]=0;

              }
              isValid=false;
              break;
            }
          }
          break;
        }
        case 2:{//position is up
          x2=random(0,8);
          y2=random(0,8-boatsLength[j]);
          for(int i=0;i<boatsLength[j];i++){
            if(matrix2[y2+i][x2]==0){
              matrix2[y2+i][x2]=j+1;
              isValid=true;
            }else{
              
              for(int k=0;k<i;k++){
                matrix2[y2+k][x2]=0;

              }
              isValid=false;
              break;
            }
          }
          break;
        }
        case 3:{
          x2=random(0,8);
          y2=random(boatsLength[j], 8);
          for(int i=0;i<boatsLength[j];i++){
            if(matrix2[y2-i][x2]==0){
              matrix2[y2-i][x2]=j+1;
              isValid=true;
            }else{
              
              for(int k=0;k<i;k++){
                matrix2[y2-k][x2]=0;

              }
              isValid=false;
              break;
            }
          }
          break;
        }
        default:{
          Serial.println("The position is out of bounds. There is an error");
        }
      }
    }
    
  }

  


  
}

int score1=0;
int score2=0;
  
void eliminateM1(int type){
  for(int i=0;i<8;i++){
    for(int j=0;j<8;j++){
      if(matrix1[i][j]==type){
        matrix1[i][j]=0;
        lc_M3.setLed(0,i,j,false);
        hit2[j][i]=1;
       
      }
    }
  }
}

void eliminateM2(int type){
  for(int i=0;i<8;i++){
    for(int j=0;j<8;j++){
      if(matrix2[i][j]==type){
        matrix2[i][j]=0;
        lc_M4.setLed(0,i,j,false);
        hit1[j][i]=1;
        
      }
    }
  }
}




bool isHit1(int x, int y) {
  if(matrix1[y][x]){
    eliminateM1(matrix1[y][x]);
     score1++;
    return true;
  }else{
    hit2[x][y]=1;
  }
  return false;
}

bool isHit2(int x, int y) {
  if(matrix2[y][x]){
    eliminateM2(matrix2[y][x]);
     score2++;
    return true;
  }else{
    hit1[x][y]=1;
  }
  return false;
}


void setLedsMatrix(){
  
    for(int i=0;i<8;i++){
      for(int j=0;j<8;j++){
        if(matrix1[i][j]!=0)
        lc_M3.setLed(0,i,7-j,true);
        else lc_M3.setLed(0,i,7-j,false);
        if(matrix2[i][j]!=0)
        lc_M4.setLed(0,i,7-j,true);
        else lc_M4.setLed(0,i,7-j,false);
      }
    }
}

void setLedsMatrixHits(){
  
    for(int i=0;i<8;i++){
      for(int j=0;j<8;j++){
        if(hit1[i][j]!=0)
        lc_M1.setLed(0,i,j,true);
        else lc_M1.setLed(0,i,j,false);
        if(hit2[i][j]!=0)
        lc_M2.setLed(0,i,j,true);
        else lc_M2.setLed(0,i,j,false);
      }
    }
}


void updateLEDMatrix(LedControl *lc, int x, int y) {
  //(*lc).clearDisplay(0);

  (*lc).setLed(0, x, y, true);
}

void movePlayer(LedControl *l,int x, int y) {
  (*l).setLed(0,playerX, playerY, false);
  playerX = constrain(playerX + x, 0, X_SEGMENTS - 1);
  playerY = constrain(playerY + y, 0, Y_SEGMENTS - 1);
}


void updateLCD(int player, bool hit, int hitX, int hitY) {
  lcd.clear(); // Clear the LCD screen

  String message;
  if (score1 < 5 && score2 < 5) {
    if (player == 1) {
      message = "Battleship P1";
    } else if (player == 2) {
      message = "Battleship P2";
    }

    if (hit) {
      message += " Hit at: ";
      message += String(7 - hitX);
      message += ",";
      message += String(hitY);
    }
  } else {
    if (player == 1) {
      message = "Player 2 WON ";
    } else if (player == 2) {
      message = "Player 1 WON ";
    }
    message += String(score1);
    message += "-";
    message += String(score2);

    if (hit) {
      
      message += " Hit at: ";
      message += String(7 - hitX);
      message += ",";
      message += String(hitY);
    }

    
  }

  // Display each character of the message on the LCD
  for (int i = 0; i < message.length(); i++) {
    lcd.setCursor(i % 16, i / 16); // Set cursor position based on LCD dimensions (16x2)
    lcd.print(message[i]);          // Print character on LCD
    
  }

  
}





void loop() {
  bool currentButtonState = digitalRead(2) == LOW; 
  
  if (currentButtonState && !buttonPressed) {
    if (matrixActive == 1) {
      Serial.print("Here");
      matrixActive = 2;
      l = &lc_M2;
      updateLCD(2, isHit2(playerX, playerY), playerX, playerY); 
      
    } else {
      matrixActive = 1;
      l = &lc_M1;
     updateLCD(1, isHit1(playerX, playerY), playerX, playerY);
    }

    if (matrixActive == 1) {
      lc_M2.setLed(0, playerX, playerY, false);
    } else {
      lc_M1.setLed(0, playerX, playerY, false);
    }
  }

  buttonPressed = currentButtonState; 
  char key = keypad.getKey();
  if (key != NO_KEY) {
    if (key == '1') { // Up
      movePlayer(l, 0, 1);
    } else if (key == '2') {
      movePlayer(l, 0, -1); // Down
    } else if (key == '3') { // Left
      movePlayer(l, 1, 0);
    } else if (key == '4') { // Right
      movePlayer(l, -1, 0);
    }
  }

  

  updateLEDMatrix(l, playerX, playerY);
  setLedsMatrix();
  setLedsMatrixHits();
  if(score1==5||score2==5){
    delay(5000); // Delay for 5 seconds before exiting
    exit(0);    // Exit the sketch
  }

}
