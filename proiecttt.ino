#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int ROW_NUM = 4; //four rows
const int COLUMN_NUM = 4; //four columns
char Data[4];

LiquidCrystal_I2C lcd(0x27, 16, 2);
struct cont {
  String pin;
  int balance;
};

cont pers1 = {"1234", 1000};
cont pers2 = {"1111", 200};

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte pin_rows[ROW_NUM] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

String inputSecretCode() {
  delay(1000);
  Serial.print("Password:");
  lcd.clear();
  lcd.print("Password:");
  String result = "";
  while (result.length() < 4) {
    char key = keypad.getKey();
    if (key >= '0' && key <= '9') {
      Serial.print('*');
      lcd.print("*");
      result += key;

    }
  }
  //Serial.println(result);
  return result;

}

void verificareParola() {
  String password = inputSecretCode();
  Serial.println(password);
  if (password.equals(pers1.pin)) {
    delay(1500);
    lcd.clear();
    lcd.print("Welcome Account1");
    language(pers1);
  }
  else if (password.equals(pers2.pin)) {
    delay(1000);
    lcd.clear();
    lcd.print("Welcome Account2");
    language(pers2);
  }
  else {
    lcd.clear();
    lcd.print("Incorrect");
    verificareParola();
  }
}

void language(cont pers) {
  delay(1500);
  lcd.clear();
  lcd.print("Choose language");
  lcd.clear();
  lcd.print("A.English C.Back ");
  lcd.setCursor(3, 1);
  lcd.print("B.Romanian");
  String result = "";
  while (result.length() < 1) {
    char key = keypad.getKey();
    if (key == 'A') engleza(pers);
    else if (key == 'B') {
      romana(pers);
      break;
    }
    //result += key;
    else if (key == 'C') {
      verificareParola();
      break;
    }
  }
}
void romana(cont pers)
{
  delay(1500);
  lcd.clear();
  lcd.print("1.Sold 3.Inapoi");
  lcd.setCursor(0, 1);
  lcd.print("2.Adauga bani");
  delay(2500);
  lcd.clear();
  lcd.print("4.Transfer");
  String result = "";
  while (result.length() < 1) {
    char key = keypad.getKey();
    if (key == '1')
    {
      delay(1500);
      lcd.clear();
      lcd.print(pers.balance);
      romana(pers);
    }
    else if (key == '3') language(pers);
    else if (key == '2') {
      delay(1500);
      lcd.clear();
      lcd.print("Cati bani doriti ");
      lcd.setCursor(0, 1);
      lcd.print("sa adaugati?");
      delay(2000);
      lcd.clear();
      lcd.print("1.10 2.50 3.100");
      String result = "";

      while (result.length() < 1)
      {
        char key = keypad.getKey();
        if (key == '1') {
          pers.balance = pers.balance + 10;
          delay(1500);
          lcd.clear();
          lcd.print(pers.balance);
          romana(pers);
        }
        else if (key == '2') {
          pers.balance = pers.balance + 50;
          delay(1500);
          lcd.clear();
          lcd.print(pers.balance);
          romana(pers);
        }
        else if (key == '3') {
          pers.balance = pers.balance + 100;
          delay(1500);
          lcd.clear();
          lcd.print(pers1.balance);
          romana(pers);
        }
      }

    }
    else if (key == '4') {
      delay(1500);
      lcd.clear();
      lcd.print("cati bani doriti");
      lcd.setCursor(0, 1);
      lcd.print("sa transferati?");
      delay(1500);
      lcd.clear();
      lcd.print("1.10 2.50 3.100");

      String result2 = "";
      while (result2.length() < 1) {
        char key2 = keypad.getKey();
        if (key2 == '1') {
          if (pers.pin.equals("1234"))
          { pers2.balance = pers2.balance + 10;
            pers1.balance = pers1.balance - 10;
            Serial.println(pers2.balance);
            delay(1500);
            lcd.clear();
            lcd.print(pers2.balance);
          }
          else
          { pers1.balance = pers1.balance + 10;
          pers2.balance=pers2.balance-10;
            Serial.println(pers1.balance);
            delay(1500);
            lcd.clear();
            lcd.print(pers1.balance);
          }
          Serial.println("s-au transf 10lei");
          delay(1500);
          lcd.clear();
          lcd.print("s-au transf 10lei");
          engleza(pers);
        }
        else if (key2 == '2')
        {
          if (pers.pin.equals("1234"))
          { pers2.balance = pers2.balance + 50;
          pers1.balance=pers1.balance-50;
            Serial.println(pers2.balance);
            delay(1500);
            lcd.clear();
            lcd.print(pers2.balance);
          }
          else
          { pers1.balance = pers1.balance + 50;
          pers2.balance=pers2.balance-50;
            Serial.println(pers1.balance);
            delay(1500);
            lcd.clear();
            lcd.print(pers1.balance);
          }
          Serial.println("sau transf 50lei");
          engleza(pers);
        }

        else if (key2 == '3')
        {
          if (pers.pin.equals("1234"))
          { pers2.balance = pers2.balance + 100;
          pers1.balance=pers1.balance-100;
            Serial.println(pers2.balance);
            delay(1500);
            lcd.clear();
            lcd.print(pers2.balance);
          }
          else
          { pers1.balance = pers1.balance + 100;
          pers2.balance=pers2.balance-100;
            Serial.println(pers1.balance);
            delay(1500);
            lcd.clear();
            lcd.print(pers1.balance);
          }
          Serial.println("s-au transf 100lei");
          engleza(pers);
        }
      }
    }
    //Serial.println(result);
    // return result;

  }
}
void engleza(cont pers)
{
  delay(1500);
  lcd.clear();
  lcd.print("1.Balance 3.Back");
  lcd.setCursor(0, 1);
  lcd.print("2.Update balance");
  delay(2500);
  lcd.clear();
  lcd.print("4.Transfer money");

  String result = "";
  while (result.length() < 1) {
    char key = keypad.getKey();


    if (key == '1') {
      delay(1500);
      lcd.clear();
      lcd.print(pers.balance);
      engleza(pers);
    }


    else if (key == '3') language(pers);


    else if (key == '4') {
      delay(1500);
      lcd.clear();
      lcd.print("select money");
      lcd.setCursor(0, 1);
      lcd.print("to transfer");
      delay(1500);
      lcd.clear();
      lcd.print("1.10 2.50 3.100");

      String result2 = "";
      while (result2.length() < 1) {
        char key2 = keypad.getKey();
        if (key2 == '1') {
          if (pers.pin.equals("1234"))
          { pers2.balance = pers2.balance + 10;
          pers1.balance=pers1.balance-10;
            Serial.println(pers2.balance);
            delay(1500);
            lcd.clear();
            lcd.print(pers2.balance);
          }
          else
          { pers1.balance = pers1.balance + 10;
          pers2.balance=pers2.balance-10;
            Serial.println(pers1.balance);
            delay(1500);
            lcd.clear();
            lcd.print(pers1.balance);
          }
          Serial.println("transferred 10lei");
          delay(1500);
          lcd.clear();
          lcd.print("transferred 10lei");
          engleza(pers);
        }
        else if (key2 == '2')
        {
          if (pers.pin.equals("1234"))
          { pers2.balance = pers2.balance + 50;
          pers1.balance=pers1.balance-50;
            Serial.println(pers2.balance);
            delay(1500);
            lcd.clear();
            lcd.print(pers2.balance);
          }
          else
          { pers1.balance = pers1.balance + 50;
          pers2.balance=pers2.balance-50;
            Serial.println(pers1.balance);
            delay(1500);
            lcd.clear();
            lcd.print(pers1.balance);
          }
          Serial.println("s au transferat 50 lei");
          lcd.clear();
          lcd.print("transferred 50lei");
          engleza(pers);
        }

        else if (key2 == '3')
        {
          if (pers.pin.equals("1234"))
          { pers2.balance = pers2.balance + 100;
          pers1.balance=pers1.balance-100;
            Serial.println(pers2.balance);
            delay(1500);
            lcd.clear();
            lcd.print(pers2.balance);
          }
          else
          { pers1.balance = pers1.balance + 100;
          pers2.balance=pers2.balance-100;
            Serial.println(pers1.balance);
            delay(1500);
            lcd.clear();
            lcd.print(pers1.balance);
          }
          Serial.println("s au transferat 100 lei");
          lcd.clear();
          lcd.print("transferred 100lei");
          engleza(pers);
        }
      }
    }


    else if (key == '2') {
      delay(1500);
      lcd.clear();
      lcd.print("Select money ");
      lcd.setCursor(0, 1);
      lcd.print("to insert");
      delay(1500);
      lcd.clear();
      lcd.print("1.10 2.50 3.100");

      String result = "";
      while (result.length() < 1) {
        char key = keypad.getKey();
        if (key == '1') {
          pers.balance = pers.balance + 10;
          Serial.println("inserted 10lei");
          delay(1500);
          lcd.clear();
          lcd.print(pers.balance);
          engleza(pers);
        }
        else if (key == '2') {
          pers.balance = pers.balance + 50;
          Serial.println("s au adaugat 50 lei");
          delay(1500);
          lcd.clear();
          lcd.print(pers.balance);
          engleza(pers);
        }
        else if (key == '3') {
          pers.balance = pers.balance + 100;
          Serial.println("s au adaugat 100 lei");
          delay(1500);
          lcd.clear();
          lcd.print(pers.balance);
          engleza(pers);
        }
      }
    }

  }
}


void start() {
  verificareParola();
}
void setup()
{
  // put your setup code here, to run once:
  lcd.begin();
  Serial.begin(9600);
  Serial.println("atm");
  lcd.setCursor(6, 1);
  lcd.print("ATM");
  delay(200);
  //lcd.clear();


}

void loop()
{
  // put your main code here, to run repeatedly:
  // String s= inputSecretCode();
  start();
  delay(20000000000);


}

//else verificareParola();
//delay(20000);
