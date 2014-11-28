#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Servo.h>
#include <string.h>

const byte rows = 4; //four rows
const byte cols = 3; //three columns
char keys[rows][cols] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[rows] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
byte colPins[cols] = {8, 7, 6}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);

char key;
char key_aux;

LiquidCrystal lcd(14, 15, 9, 10, 11, 12);

const int ledPin = 16;

int state = 0;
int pos_aux = 0;
int pos = 0;
int cont = 0;
int tamanho_senha;

int senha[10];
int senha_aux[10];
int reverse_senha[10];

Servo servo1;

void setup() {
  servo1.attach(13);
  servo1.write(0);

  pinMode(ledPin,OUTPUT);

  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("Password size:");
  lcd.setCursor(0,1);
  lcd.blink();
}

void loop(){

  while(state == 0) {
    make_password();
    state++;
  }


  while(pos_aux < tamanho_senha){
    while(key == NO_KEY)
      key = keypad.getKey();
    if(key){
      lcd.clear();
      lcd.print("Reading:");
      senha_aux[pos_aux] = key;
      lcd.setCursor(0,1);
      print_reading();
      pos_aux++;
    }
    key = NO_KEY;
  }

  /*cont = password_check_reverse();
  if(cont == 1){
    setup();
  }*/

  if(pos_aux == tamanho_senha){
    lcd.clear();
    lcd.print("Read!");
    lcd.setCursor(0,1);
    lcd.print("* to unlock: ");
    pos_aux++;
  }
  while(key_aux == NO_KEY)
    key_aux = keypad.getKey();

  if(key_aux != '*'){
    lcd.clear();
    lcd.print(key_aux);
    lcd.setCursor(1,0);
    lcd.print(" Not valid!");
    lcd.setCursor(0,2);
    lcd.print("* to unlock: ");
    key_aux = NO_KEY;
  }

  while(key_aux == '*') {
    lcd.clear();
    lcd.print("Access Granted!");
    lcd.setCursor(0,1);
    lcd.print("# to lock: ");
    while(password_check()) {
      digitalWrite(ledPin, HIGH);
      servo1.write(180);
      while (key == NO_KEY)
        key = keypad.getKey();   
      if(key != '#'){
          lcd.clear();
          lcd.print(key);
          lcd.setCursor(1,0);
          lcd.print(" Not valid!");
          lcd.setCursor(0,2);
          lcd.print("# to lock: ");
          key = NO_KEY;
      }
      else {
        lcd.clear();
        lcd.print("Locked!");
        key = NO_KEY;
        memset(senha_aux, 0, sizeof(senha_aux));
        pos_aux = 0;
        lcd.setCursor(0,1);
        lcd.print("Ready to read ->");
        servo1.write(0);
        digitalWrite(ledPin, LOW);
        key_aux = NO_KEY;
        loop();
      }
    }
    lcd.clear();
    lcd.print("Access Denied! ");
    lcd.setCursor(0,1);
    lcd.print("Try again: ");
    memset(senha_aux, 0, sizeof(senha_aux));
    pos_aux = 0;
    key_aux = NO_KEY;
  }
}

void make_password() {
  while (key == NO_KEY)
    key = keypad.getKey();
  if(key){
    if(key == '*' || key == '#' || key == '0'){
      lcd.clear();
      lcd.print(key);
      lcd.setCursor(1,0);
      lcd.print(" Not valid!");
      lcd.setCursor(0,1);
      lcd.print("Try again: ");
      lcd.blink();
      key = NO_KEY;
      make_password();
    }
    else{
      lcd.clear();
      lcd.noBlink();
      tamanho_senha = key - 48;
      lcd.setCursor(0,0);
      lcd.print("Size: ");
      lcd.print(tamanho_senha);
      key = NO_KEY;
    }
  }
  lcd.setCursor(0,1);
  lcd.print("Make Password:");
  while(pos < tamanho_senha){
    while(key == NO_KEY){
      key = keypad.getKey();
    }
    if(key){
      lcd.clear();
      lcd.print("Make Password:");
      lcd.blink();
      senha[pos] = key;
      print_password();
      key = NO_KEY;
      pos++;
    }
  }
  reverse();
  lcd.clear();
  lcd.print("Password OK!");
  lcd.setCursor(0,1);
  lcd.print("Ready to read -> ");
}

void print_password(){
  switch (pos) {
      case 0:
        lcd.setCursor(0,1);
        lcd.print("*");
        break;
      case 1:
        lcd.setCursor(0,1);
        lcd.print("**");
        break;
      case 2:
        lcd.setCursor(0,1);
        lcd.print("***");
        break;
      case 3:
        lcd.setCursor(0,1);
        lcd.print("****");
        break;
      case 4:
        lcd.setCursor(0,1);
        lcd.print("*****");
        break;
      case 5:
        lcd.setCursor(0,1);
        lcd.print("******");
        break;
      case 6:
        lcd.setCursor(0,1);
        lcd.print("*******");
        break;
      case 7:
        lcd.setCursor(0,1);
        lcd.print("********");
        break;
      case 8:
        lcd.setCursor(0,1);
        lcd.print("*********");
        break;
  }
}

void print_reading(){
  switch (pos_aux) {
      case 0:
        lcd.print("*");
        break;
      case 1:
        lcd.print("**");
        break;
      case 2:
        lcd.print("***");
        break;
      case 3:
        lcd.print("****");
        break;
      case 4:
        lcd.print("*****");
        break;
      case 5:
        lcd.print("******");
        break;
      case 6:
        lcd.print("*******");
        break;
      case 7:
        lcd.print("********");
        break;
      case 8:
        lcd.print("*********");
        break;
  }
}

int password_check(){
  int i;
  for(i=0;i<tamanho_senha;i++){
    if(senha_aux[i] != senha[i])
      return 0;
  }
  return 1;
}

/*int password_check_reverse(){
  int i,j;
  for(i=0;i<tamanho_senha;i++){
    if(reverse_senha[i] == senha_aux[i])
      return 0;
  }
  return 1;
}

void reverse(){
  int i,j;
  for (i = tamanho_senha - 1, j = 0; i >= 0; i--, j++)
    reverse_senha[j] = senha[i];
}*/
