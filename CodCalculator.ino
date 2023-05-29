//Includem librariile

#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

const byte ROWS = 4; 
const byte COLS = 4;   
const int interval = 1000;
unsigned long startMillis; // retine valoarea la un moment de timp
unsigned long elapsedtime; // o variabila care numara cat timp a trecut de cand am apasat tasta A sau B
boolean timer = false; // o variabila ajutatoare

//definim keyboard-ul
char keys[ROWS][COLS] = {

  {'1','2','3','A'},

  {'4','5','6','B'},

  {'7','8','9','C'},

  {'*','0','#','D'}

};

byte rowPins[ROWS] = { 2, 3, 4, 5 }; //Conectam ROW0, ROW1, ROW2 si ROW3 la pinii arduino
byte colPins[COLS] = { 6, 7, 8, 9 }; //Conectam COL1, COL2, COL3, COL4 la pinii arduino

Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS ); //  creare tastatura

LiquidCrystal_I2C lcd(0x27, 16, 2); //apelam constructorul clasei LiquidCrystal
 long Num1,Num2,Number,Num3;
 char key,action;
 boolean result = false;

 
void setup() {
  lcd.begin(16, 2); //initializez ecranul
  lcd.backlight();
  lcd.print("Calculator cu"); //mesaj initial
  lcd.setCursor(0, 1); 
  lcd.print("Arduino"); //mesaj initial pe randul 2
  delay(2000); 
  lcd.clear(); 
}

void loop() {
  
key = kpd.getKey(); //se memoreaza valoarea tastei apasate

if (key!=NO_KEY)
DetectButtons(); 

if (result==true)
CalculateResult();

DisplayResult();   
}

void DetectButtons()
{ 
     lcd.clear(); 
    if (key=='*') //buton de anulare operatie
    { Number=Num1=Num2=0; result=false; timer = false;}
    
     if (key == '1') 
    {
    if (Number==0)
    Number=1;
    else
    Number = (Number*10) + 1; //butonul apasat de 2 ori
    }
    
     if (key == '4') 
    {
    if (Number==0)
    Number=4;
    else
    Number = (Number*10) + 4; 
    }
    
     if (key == '7') 
    {
    if (Number==0)
    Number=7;
    else
    Number = (Number*10) + 7; 
    } 
  

    if (key == '0')
    {
    if (Number==0)
    Number=0;
    else
    Number = (Number*10) + 0; 
    }
    
     if (key == '2') 
    {
     if (Number==0)
    Number=2;
    else
    Number = (Number*10) + 2; 
    }
    
     if (key == '5')
    {
     if (Number==0)
    Number=5;
    else
    Number = (Number*10) + 5; 
    }
    
     if (key == '8')
    { 
     if (Number==0)
    Number=8;
    else
    Number = (Number*10) + 8; 
    }   
  

    if (key == '#')
    {
    Num2=Number;
    result = true;
    }
    
     if (key == '3'){
     if (Number==0)
    Number=3;
    else
    Number = (Number*10) + 3; 
    }
    
     if (key == '6'){
    if (Number==0)
    Number=6;
    else
    Number = (Number*10) + 6; 
    }
    
     if (key == '9'){
    if (Number==0)
    Number=9;
    else
    Number = (Number*10) + 9; 
    }  

      if (key == 'A' || key == 'B' || key == 'C' || key == 'D') //Butoanele din a patra coloana
  {
    Num1 = Number;    
    Number =0;
    //initializam butoanele de pe tastatura pentru efectuarea operatiilor
     if (key == 'A'){ action = '+';}
     if (key == 'B'){ action = '-';}
     if (key == 'C'){ action = '*';}
     if (key == 'D'){ action = '/';}  

    delay(100);
  }
  
}

void CalculateResult()
{
  if (action=='+')
  {
    if(timer==false)
    {
      Num3 = Num1;
      Number = Num1+Num2;
      startMillis = millis(); // cat timp a trecut de cand a pornit programul
      timer = true;
    }
  
    elapsedtime = millis()-startMillis; // verifica daca a trecut mai mult de o secunda ca sa putem apasa a 2a oara
  
    if (elapsedtime >= interval)
    {
      if(key == 'A')
      {
      Num1 = Num3;
      Number = pow(Num1, Num2)+ 0.1; // functia in arduino are rezultatul cu 0,001 mai mic si ecranul afiseaza doar partea intreaga
       action = '^';
      }
    }
  }

  if (action=='-')
  {
    if(timer==false)
    {
    Number = Num1-Num2;
    startMillis = millis();
     timer = true;
    }
    
    elapsedtime = millis()-startMillis;
    
    if (elapsedtime >= interval)
    {
      if(key == 'B')
      {
      Number = 1;
      for(int i = 1 ; i<= Num1 ; i++){
      Number = Number * i;
      }
      Num2 = NULL;
      action = '!';
      }
    }
  }

  if (action=='*')
    Number = Num1*Num2;

  if (action=='/')
    Number = Num1/Num2; 
}

void DisplayResult()
{
  lcd.setCursor(0, 0);   
  lcd.print(Num1); lcd.print(action); lcd.print(Num2);

  if (result==true)
  {lcd.print(" = "); lcd.print(Number);} //Afisare rezultat
  
  lcd.setCursor(0, 1);  
  lcd.print(Number); //Afisare rezultat

}
