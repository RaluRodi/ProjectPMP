#include <LiquidCrystal.h>
#include "pitches.h"
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

//butoane
volatile int b1;
volatile int b2;
volatile int b3;
volatile int b4; 


//naveta spatiala
byte naveta[8] = {
B10000,
B11000,
B11100,
B11111,
B11111,
B11100,
B11000,
B10000,
};

//inamic
byte inamic[8] = {
B00000,
B00000,
B00000,
B01010,
B10101,
B10101,
B01010,
B00000,
};

//ban
byte ban[8] = {
B00000,
B00000,
B00000,
B00000,
B01110,
B01110,
B00000,
B00000,
};

byte gol[8] = {
B00000,
B00000,
B00000,
B00000,
B00000,
B00000,
B00000,
B00000,
};

//melodie 
int melody[] = {NOTE_C6, NOTE_G3,NOTE_F4};
int noteDurations[] = {1, 1,1 };
int noteDurationn = 1000/noteDurations[1]; 


int nr_inamici = 20;
int inamici_x[20];
int inamici_y[20];
int poz_naveta_x=1;
int poz_naveta_y=0;
int bani=0;




void setup()
{

  b1=0;
  b2=0;
  b3=0;
  b4=0;
  
  pinMode(18, INPUT);
  pinMode(19, INPUT);
  pinMode(20, INPUT);
  pinMode(21, INPUT);


 attachInterrupt(digitalPinToInterrupt(18), butoane1, RISING); 
 attachInterrupt(digitalPinToInterrupt(19), butoane2, RISING);
 attachInterrupt(digitalPinToInterrupt(20), butoane3, RISING);
 attachInterrupt(digitalPinToInterrupt(21), butoane4, RISING);
 
  Serial.begin(9600);
  lcd.begin(16,2);

  lcd.createChar(0 ,naveta);
  lcd.createChar(1, inamic);
  lcd.createChar(2,ban);
  lcd.createChar(3,gol);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Incepe jocul!");
  lcd.setCursor(0,1);
  lcd.print("Succes!");

  delay(1000);

  lcd.clear();
  lcd.setCursor(poz_naveta_x,poz_naveta_y);
  lcd.write(byte(0)); 

  //banii
  lcd.setCursor(7,0);
  lcd.write(2);
  lcd.setCursor(9,1);
  lcd.write(2);
  lcd.setCursor(11,1);
  lcd.write(2);
  lcd.setCursor(14,0);
  lcd.write(2);

  randomSeed(analogRead(1));

  int n = 0;
  for(int i=0; i<nr_inamici; i++) {
    // alegem random un numar; vrem ca inamicul sa fie mai deprate de naveta
    n += random(2, 9);
    inamici_x[i] = n;
    inamici_y[i] = random(0,2);
  }

  delay(3000);
}

void butoane1()
{
      lcd.setCursor(poz_naveta_x,0);
      lcd.write(3);
      lcd.setCursor(poz_naveta_x, 1);
      lcd.write(byte(0));

}

void butoane2()
{
      lcd.setCursor(poz_naveta_x,1);
      lcd.write(3);
      lcd.setCursor(poz_naveta_x, 0);
      lcd.write(byte(0));
     
}

void butoane3()
{
      lcd.setCursor(poz_naveta_x,poz_naveta_y);
      lcd.write(3);
      lcd.setCursor(++poz_naveta_x, poz_naveta_y);
      lcd.write(byte(0));
      if(poz_naveta_x==16) poz_naveta_x=0;
     
}

void butoane4()
{
      lcd.setCursor(poz_naveta_x,poz_naveta_y);
      lcd.write(3);
      lcd.setCursor(--poz_naveta_x, poz_naveta_y);
      lcd.write(byte(0));
      if(poz_naveta_x==0) poz_naveta_x=16;
     
}

void loop()
{
  

  if((poz_naveta_x==7 && poz_naveta_y==0) || (poz_naveta_x==9 && poz_naveta_y==1)
  || (poz_naveta_x==11 && poz_naveta_y==1) || (poz_naveta_x==14 && poz_naveta_y==0))
  {
     tone(8, melody[2],noteDurationn); 
     bani+=1;
  }

   // fiecare inamic se muta la stanga cu o pozitie
   for(int i=0; i<nr_inamici; i++) {
      inamici_x[i] = inamici_x[i] - 1;
      
  
    // il desenam
   if(inamici_x[i] >= 0 && inamici_x[i] <= 16)
   { 
       lcd.setCursor(inamici_x[i], inamici_y[i]);
       lcd.write(1);
       delay(1000);
       lcd.setCursor(inamici_x[i], inamici_y[i]);
       lcd.write(3);
   }
  
    // daca se ating, afisam AI PIERDUT
    if((inamici_x[i] == poz_naveta_x) && (inamici_y[i] == poz_naveta_y)) 
    {
        tone(8, melody[1],noteDurationn); 
        lcd.clear();
        lcd.setCursor(2, 0);
        lcd.print("AI PIERDUT!!!");
        lcd.setCursor(5,1);
        lcd.print(bani);
         delay(100000);
     }
  }
  
        // daca au trecut cei 20 de inamici, afisam AI CASTIGAT
  // nu stim indicele ultimului inamic
   if(inamici_x[(nr_inamici-1)] < 0 & bani==5)
   {
       tone(8, melody[0],noteDurationn); 
       tone(8, melody[1],noteDurationn);
       lcd.clear();
       lcd.setCursor(3, 0);
       lcd.print("AI CASTIGAT!!!");
       lcd.setCursor(5,1);
       lcd.print(bani);
   }
    

     
}












