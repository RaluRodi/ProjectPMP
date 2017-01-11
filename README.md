# ProjectPMP

In ceea ce priveste implementarea proiectului, vom descrie fiecare parte importanta
a codului si vom da exemple relevante.
	Pentru a desena pe LCD caracterele dorite am folosit matrici de 8 octeti si 3 tipuri diferite de caractere. Cele 3 tipuri sunt: naveta, inamicul si banul. B01110,


//naveta spatiala	  //inamic	                //ban
	 
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
 


	In metoda setup() setam cele 4 butoane ca input-uri la pinii 18,19,20 si 21, dupa care atasam intreuperile folosind functia attachInterrupt. Intreruprile se executa pe frontul crescator al butoanelor (la apasarea lor) si se executa functiile butoane1(), butoane2() , butoane3() si butoane4(). Aceste 4 functii au rolul de a modifica pozitia navetei in functie de butonul apasat. Vom da un exemplu pentru una dintre functii, celelalte fiind similare.

void butoane3()
{
      lcd.setCursor(poz_naveta_x,poz_naveta_y);
      lcd.write(3);
      lcd.setCursor(++poz_naveta_x, poz_naveta_y);
      lcd.write(byte(0));
      if(poz_naveta_x==16) poz_naveta_x=0;
     
}

	In aceasta functie setam cursoul la pozitia actuala a navetei si in locul ei desenam caracterul „blank” (se face stergerea navetei de pe pozitia curenta), apoi modificam pozitia cursorului astfel incat aceasta sa fie la un x (coloana) incrementat si acelasi y (linie), dupa care desenam naveta. Astfel, aceasta functie face deplasare la dreapta a navetei spatiale. Pentru a ne asigura ca ramane in limitele dimensiunii afisorului, am programat nevata ca in momentul in care ajunge la ultima coloana (la coloana 16) sa revina la prima coloana (la coloana 0).


	Tot in functia de setup() vom comanda aparitia aleatoare a inamicilor cu urmatorea secventa de cod:

  randomSeed(analogRead(1));

  int n = 0;
  for(int i=0; i<nr_inamici; i++) {
    // alegem random un numar; vrem ca inamicul sa fie mai deprate de naveta
    n += random(2, 9);
    inamici_x[i] = n;
    inamici_y[i] = random(0,2);
  }

	Functia randomSeed asigura faptul ca la rulari consecutive nu se genereaza aceleasi pozitii pentru inamici. Alegem pozitiile inamicilor folosind functia random(min,max) , unde inamici_x[i] reprezinta coloana pe care apare inamicul, iar inamici_y[i] reprezinta linia pe care acesta va fi desenat.

	In functia loop coordonam deplasarea, desenarea inamicilor si testam eventualele coliziuni ale navetei cu celelalte obiecte.
	Pentru a desena inamicii folosim urmatoarea secventa de cod:

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

	Pentru a-i deplasa la stanga cu o pozitie trebuie doar sa decrementam cu 1 coloana in care se afla acestia, iar pentru a-i desenan verificam mai inatai daca pozitiile corespund cu dimensiunile LCD-ului (intre 0 si 16) si apelam lcd.write(1), unde 1 reprezinta id-ul caracterului „inamic”.
	
	
In urmatoarele linii de cod tratam cazurile in care utilizatorul pierde sau castiga jocul:



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
   if(inamici_x[(nr_inamici-1)] < 0 bani==5)
   {
       tone(8, melody[0],noteDurationn); 
       tone(8, melody[1],noteDurationn);
       lcd.clear();
       lcd.setCursor(3, 0);
       lcd.print("AI CASTIGAT!!!");
       lcd.setCursor(5,1);
       lcd.print(bani);
   }


	 Pentru a verifica coloziunea navetei cu un inamic se verifica egalitea dintre pozitiile acestora (linii si coloane). In caz afirmativ, pe LCD apare mesajul “AI PIERDUT!!!” impreuna cu numarul de bani adunati folosind functiile lcd.print(“…”). Sunetul care se aude in acel moment este dat de functia tone(pin, vector_note[i],noteDuration).
	Procedam la fel si in cazul in care naveta reuseste sa ocoleasca toate cele 20 de obstacole si sa colecteze cei 5 banuti pusi la dispozitie.

