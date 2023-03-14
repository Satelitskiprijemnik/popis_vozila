/*
Goran Glavocevic - AISP projekt - Popis vozila
CHANGELOG: 
1. funkcija promjene stavljena u VOID -gotovo
2. dodano brisanje cijele liste (uz pojedinacno brisanje). -gotovo
3. dodan-povratak iz menija za brisanje u glavni meni, -gotovo
4. petlja koja ne dopusta rusenje podizbornika za brisanje. -gotovo
5. dodane provjere snage kod promjene i ubacivanja -gotovo
6. godina proizvodnje iz char-a prebacena u int -gotovo
7. dodana provjera godista u ubacivanje -gotovo
8. dodana provjera godista u promjeni -gotovo
9. podizbornik brisanja prebacen na char i switch case umjesto brojeva i if else-a, ubacena do while provjera na taj podizbornik	BRISANJE RIJESENO -gotovo
10. dodan if u glavni izbornik  GLAVNI IZBORNIK RIJESEN -gotovo
11. ubacena provjera znakova na izborniku za promjenu i brisanje pojedinacnog vozila,  ubacena provjera duljine na unos i promjenu -gotovo
12. UREDITI KOD -gotovo
*/

#include <stdio.h>
#include <conio.h>
#include <string.h>							//zbog strlen
#include <windows.h>						//zbog CLS
#define MAX 50								// maksimalan broj vozila
#include <ctype.h>							// zbog isalpha(isdigit) naredbe


// struktura podataka o vozilu
typedef struct {							
	char proizvodjac [30+1];
	char model [30+1];
	char boja [30+1];
	char regoznake [30+1];
	int godProizvodnje;
	int snaga;

	
} Vozilo;


// deklaracija liste
typedef struct{								
 	int zadnji; 
	Vozilo elementi[MAX];
} LISTA;


// ubacivanje u listu
void UBACI (Vozilo x, int pozicija_ubacivanja, LISTA *pokLista)
{
  	int pozicija;
  		if (pokLista->zadnji >= MAX-1)
	  		{
  				printf(" Lista je puna! ");
			}
 	
	 	else if ((pozicija_ubacivanja>pokLista->zadnji+1) || (pozicija_ubacivanja<0)) 
	 
			{
 				printf(" Pozicija ne postoji! ");
			}
  		
		  else {
            
			for (pozicija=pokLista->zadnji; pozicija >= pozicija_ubacivanja; pozicija--)
			{
            	pokLista->elementi[pozicija+1]= pokLista->elementi[pozicija];
        	}
			pokLista->zadnji++;
            pokLista->elementi[pozicija_ubacivanja] = x;
           
		   	}
}



// ispis liste
void ISPIS(LISTA *pokLista){
  	int pozicija; 

  	printf("Br.\tProizvodjac\tModel\t\tBoja\t\tReg. ozn.  Godiste  Snaga\n");
  			
			  for (pozicija=0; pozicija <= pokLista->zadnji; pozicija++)
			{	
				
				
				printf("\n%d\t%-15s\t%-10s\t%-10s\t%-10s  %-4d.    %-3d KW", 	
																		pozicija+1, 	  
		 																pokLista->elementi[pozicija].proizvodjac, 
															    		pokLista->elementi[pozicija].model, 
																		pokLista->elementi[pozicija].boja, 
																		pokLista->elementi[pozicija].regoznake, 
																		pokLista->elementi[pozicija].godProizvodnje, 
																		pokLista->elementi[pozicija].snaga
																		);
	 																													}
	printf("\n\n");																								// rijesava probleme sa prikazom glavnog izbornika
}


// funkcija spremanja u datoteku
void SPREMI_U_DATOTEKU (char *nazivDatoteke, LISTA *pokLista){
	FILE *datoteka;
	datoteka = fopen(nazivDatoteke, "wb");
	
	if( datoteka == NULL )
	{
		printf("Problem u otvaranju datoteke! ");
	}
	
	else
	{
		fwrite(pokLista, sizeof(*pokLista), 1, datoteka);
	}
	
	fclose(datoteka);
}

// funkcija citanja iz datoteke
void PROCITAJ_IZ_DATOTEKE(char *nazivDatoteke, LISTA *pokLista) {
  FILE *datoteka;
 
  datoteka = fopen(nazivDatoteke, "rb");
  
 	 if( datoteka == NULL ) 
  {
    	printf("Problem u otvaranju datoteke!\n");
  }
  
  else
  {
    fread(pokLista, sizeof(*pokLista), 1, datoteka);
  }    
  	fclose(datoteka );   
}


//funkcija brisanja
void OBRISI (int pozicija_brisanja, LISTA *pokLista) {
  int pozicija;
  if ( (pozicija_brisanja>pokLista->zadnji ) || (pozicija_brisanja<0) )
  	{
		printf("Pozicija ne postoji!");
	}
  else {
    pokLista->zadnji--;    
    for (pozicija=pozicija_brisanja; pozicija<=pokLista->zadnji; pozicija++)
       pokLista->elementi[pozicija] = pokLista->elementi[pozicija+1];
   }
}



// funkcija promjene odabranog vozila
void PROMIJENI (int brojPromjeneVozila, LISTA *pokLista){
		
		

		char brojPromjenePodatka;
		
		do{
		
		
		printf("\nKoji podatak vozila zelite promijeniti?");
		printf("\n(1) Proizvodjac %d. vozila", brojPromjeneVozila);
		printf("\n(2) Model %d. vozila", brojPromjeneVozila);
		printf("\n(3) Boja %d. vozila", brojPromjeneVozila);
		printf("\n(4) Registracijske oznake %d. vozila", brojPromjeneVozila);
		printf("\n(5) Godina proizvodnje %d. vozila", brojPromjeneVozila);
		printf("\n(6) Snaga %d. vozila\n", brojPromjeneVozila);
		
		scanf(" %c", &brojPromjenePodatka);
		
		switch(brojPromjenePodatka){
		
		
		case '1':
			
			int duzinaNazivaProizvodjacaPromjena;											// provjera duzine naziva proizvodjaca kod promjene
			do{
			
			printf("Unesite proizvodjaca %d. vozila:", brojPromjeneVozila);						
			scanf("%s", &pokLista->elementi[brojPromjeneVozila-1].proizvodjac); 
			duzinaNazivaProizvodjacaPromjena = strlen(pokLista->elementi[brojPromjeneVozila-1].proizvodjac);
			
			if(duzinaNazivaProizvodjacaPromjena>15)
			{
				printf("\nDuzina naziva proizvodjaca ne smije biti duza od 15 znakova!\n\n");
			}
			
			}while(duzinaNazivaProizvodjacaPromjena>15);
			
	
			
		break;
		
		
		case '2':
			
			int duzinaNazivaModelaPromjena;														// provjera duzine naziva modela kod promjene
			do{
			
			printf("Unesite model %d. vozila:", brojPromjeneVozila);
			scanf("%s", &pokLista->elementi[brojPromjeneVozila-1].model);
			duzinaNazivaModelaPromjena = strlen(pokLista->elementi[brojPromjeneVozila-1].model);
			
			if(duzinaNazivaModelaPromjena>10)
			{
				printf("\nDuzina naziva modela ne smije biti duza od 10 znakova!\n\n");
			}
			
			}while(duzinaNazivaModelaPromjena>10);

		
		break;
		
		
		case '3':																			// // provjera duzine naziva boje kod promjene
			
			int duzinaNazivaBojePromjena;
			do{
			
			printf("Unesite boju %d. vozila:", brojPromjeneVozila);
			scanf("%s", &pokLista->elementi[brojPromjeneVozila-1].boja);		
			duzinaNazivaBojePromjena = strlen(pokLista->elementi[brojPromjeneVozila-1].boja);
			
			if(duzinaNazivaBojePromjena>10)
			{
				printf("\nDuzina naziva boje ne smije biti duza od 10 znakova!\n\n");
			}
			
			}while(duzinaNazivaBojePromjena>10);


		break;
		
		
		case '4':
			
			int duzinaNazivaRegPromjena;
			do{
			
			printf("Unesite registracijske oznake %d. vozila:", brojPromjeneVozila);
			scanf("%s", &pokLista->elementi[brojPromjeneVozila-1].regoznake);
			duzinaNazivaRegPromjena = strlen(pokLista->elementi[brojPromjeneVozila-1].regoznake);
			
			if(duzinaNazivaRegPromjena>10)
			{
			printf("\nDuzina registracijskih oznaka ne smije biti duza od 10 znakova!\n\n");
			}
		
			}while(duzinaNazivaRegPromjena>10);


		break;
		
		
		case '5':																					// provjera godista kod promjene

			printf("Unesite godinu proizvodnje %d. vozila (bez tocke na kraju!):", brojPromjeneVozila);
		scanf("%d", &pokLista->elementi[brojPromjeneVozila-1].godProizvodnje);	
		
		while(pokLista->elementi[brojPromjeneVozila-1].godProizvodnje<1900 || pokLista->elementi[brojPromjeneVozila-1].godProizvodnje>2015){					
			
		if(pokLista->elementi[brojPromjeneVozila-1].godProizvodnje<1900)
		{
			printf("Godina proizvodnje ne moze biti prije 1900.!\n");
		}
		
		else if(pokLista->elementi[brojPromjeneVozila-1].godProizvodnje>2015)
		{
			printf("Godina proizvodnje ne moze biti u buducnosti!\n");
		}
		
		printf("Unesite godinu proizvodnje %d. vozila (bez tocke na kraju!):", brojPromjeneVozila);
		scanf("%d", &pokLista->elementi[brojPromjeneVozila-1].godProizvodnje);	
		//fgets(pokLista->elementi[brojPromjeneVozila-1].godProizvodnje,4,stdin);
			
		}	
	        
				
		break;
		
		
		case '6':
			do{
				printf("Unesite snagu u KW %d. vozila:", brojPromjeneVozila);						// provjera za snagu kod promjene
				scanf("%d", &pokLista->elementi[brojPromjeneVozila-1].snaga);	
				
				if(pokLista->elementi[brojPromjeneVozila-1].snaga<1)
				{
					printf("Snaga ne moze biti 0 ili negativna! \n");
				}
				
				if(pokLista->elementi[brojPromjeneVozila-1].snaga>999)
				{
					printf("Snaga ne moze biti veca od 999! \n");
				}
				
				} while(pokLista->elementi[brojPromjeneVozila-1].snaga<1 || pokLista->elementi[brojPromjeneVozila-1].snaga>999);
				

		break;
		
		
		}
		if(brojPromjenePodatka!='1' && brojPromjenePodatka!='2' && brojPromjenePodatka!='3' &&  brojPromjenePodatka!='4' && brojPromjenePodatka!='5' && brojPromjenePodatka!='6')
		{
			printf("\nUnos mora biti 1, 2, 3, 4, 5 ili 6!\n");		// poruka o gresci u izborniku promjene
		}	
	
	}while(brojPromjenePodatka!='1' && brojPromjenePodatka!='2' && brojPromjenePodatka!='3' &&  
	brojPromjenePodatka!='4' && brojPromjenePodatka!='5' && brojPromjenePodatka!='6'); // petlja pogresnog unosa u promjeni)
}				// kraj funkcije promijeni



main(){
	
	Vozilo podaciOVozilu;
	int brojUnosa;
	LISTA listaVozila;

	
	
	listaVozila.zadnji = -1; // cisti od smeca
	
	PROCITAJ_IZ_DATOTEKE ("ListaVozila.car", &listaVozila);
	
	char odabir;
	
	do{
	
	printf("GLAVNI IZBORNIK\n");
	printf("\nUnesite odabir:\n");
	printf("(U) Unos novih vozila\n");
	printf("(I) Ispis vozila\n");	
	printf("(C) Ciscenje konzole\n");
	printf("(B) Brisanje vozila\n");
	printf("(P) Promjena postojecih vozila\n");
	printf("(S) Spremanje\n");								// izbornik
	printf("(X) Izlaz\n");
	printf("\nOdabir je:\n");
	scanf(" %s", &odabir);
	
	if(odabir!='U' && odabir!='u' && odabir!='I' &&  odabir!='i' && odabir!='C' && odabir!='c' && odabir!='B' 				// poruka pogresnog unosa u glavnom izborniku
	&& odabir!='b' && odabir!='P' && odabir!='p' && odabir!='S' && odabir!='s' && odabir!='X' && odabir!='x')
	{
	printf("\nPogreska! Unesite U, I, C, B, P, S ili X!\n\n");	
	}
	
	switch(odabir){
		case 'U':
		case 'u':	
	
															

	char brojVozilaChar;												
	int brojVozila;														// u ovoj varijabli se nalazi broj vozila koje unosimo
	
	do{																		// provjera unosa broja kod unosa broja vozila
	
	printf("Koliko vozila zelite unijeti?");
	scanf(" %s", &brojVozilaChar);
		if(isalpha(brojVozilaChar))
					{
					printf("\nUnesena vrijednost nije broj!\n");
					}
					
	}while(isalpha(brojVozilaChar));
	
	
	brojVozila = brojVozilaChar-48;
	//printf("int %d, char %c", brojVozila, brojVozilaChar);
																	// kraj provjere unosa broja vozila
	
	
	for(brojUnosa = 1; brojUnosa <=brojVozila; brojUnosa++){				// broj unosa
		
		
		int duzinaNazivaProizvodjaca;																			//ubacivanje sa provjerama duzine
		do{
			printf("Unesite proizvodjaca %d. vozila:", brojUnosa);						
			scanf("%s", &podaciOVozilu.proizvodjac);
		duzinaNazivaProizvodjaca = strlen(podaciOVozilu.proizvodjac);
		if(duzinaNazivaProizvodjaca>15)
		{
			printf("Duzina naziva proizvodjaca ne smije biti duza od 15 znakova!\n");
		}
		
		}while(duzinaNazivaProizvodjaca>15);
		
		
		int duzinaNazivaModela;
		do{
			printf("Unesite model %d. vozila:", brojUnosa);
			scanf("%s", &podaciOVozilu.model);
		
		duzinaNazivaModela = strlen(podaciOVozilu.model);
		if(duzinaNazivaModela>10)
		{
			printf("Duzina naziva modela ne smije biti duza od 10 znakova!\n");
		}
		
		}while(duzinaNazivaModela>10);
		
		
		
		
		
		int duzinaNazivaBoje;
		do{
			printf("Unesite boju %d. vozila:", brojUnosa);
			scanf("%s", &podaciOVozilu.boja);		
		duzinaNazivaBoje = strlen(podaciOVozilu.boja);
		if(duzinaNazivaBoje>10)
		{
			printf("Duzina naziva boje ne smije biti duza od 10 znakova!\n");
		}
		
		}while(duzinaNazivaBoje>10);
		
		
		
		
		int duzinaNazivaReg;
		do{
			printf("Unesite registracijske oznake %d. vozila:", brojUnosa);
			scanf("%s", &podaciOVozilu.regoznake);
			duzinaNazivaReg = strlen(podaciOVozilu.regoznake);
		if(duzinaNazivaReg>10)
		{
			printf("Duzina registracijskih oznaka ne smije biti duza od 10 znakova!\n");
		}
		
		}while(duzinaNazivaReg>10);

		
		

		
		printf("Unesite godinu proizvodnje %d. vozila (bez tocke na kraju!):", brojUnosa);
		scanf("%d", &podaciOVozilu.godProizvodnje);	
		
	
		
		while(podaciOVozilu.godProizvodnje<1900 || podaciOVozilu.godProizvodnje>2015){						// provjera starosti vozila kod ubacivanja
			
		if(podaciOVozilu.godProizvodnje<1900)
		{
			printf("Godina proizvodnje ne moze biti prije 1900.!\n");
		}
		
		else if(podaciOVozilu.godProizvodnje>2015)
		{
			printf("Godina proizvodnje ne moze biti u buducnosti!\n");
		}
	 
		printf("Unesite godinu proizvodnje %d. vozila (bez tocke na kraju!):", brojUnosa);
		scanf("%d", &podaciOVozilu.godProizvodnje);	
	
			
		}
		
		
	
		
		
		
		printf("Unesite snagu u KW %d. vozila:", brojUnosa);
		scanf("%d", &podaciOVozilu.snaga);
	
		
		while(podaciOVozilu.snaga<1 || podaciOVozilu.snaga>999){																			// provjera za snagu kod ubacivanja
			
			if(podaciOVozilu.snaga<1)
			{
			printf("Snaga ne moze biti 0 ili negativna! \n");
			}
			
			if(podaciOVozilu.snaga>999)
			{
				printf("Snaga ne moze biti veca od 999! \n");
			}			
			
			printf("Unesite snagu u KW %d. vozila:", brojUnosa);
			scanf("%d", &podaciOVozilu.snaga);	
			

			} 
		

		
		UBACI (podaciOVozilu, listaVozila.zadnji + 1, &listaVozila);
}																		// od for naredbe
		
		SPREMI_U_DATOTEKU ("ListaVozila.car", &listaVozila);

		printf("Spremljeno! \a\n\n");
		
		break;
	
	
	case 'I':
	case 'i':
		
		PROCITAJ_IZ_DATOTEKE ("ListaVozila.car", &listaVozila);
		ISPIS (&listaVozila);
		
	
		break;	
	
	
	case 'C':
	case 'c':
		
			system("CLS");													// ciscenje konzole
		
		
		break;
		
		
	case 'B':																// Brisanje jednog vozila ili cijele liste
	case 'b':
		
		
		
			char vrstaBrisanja;
			do{																		// do while za odabir podizbornika brisanja 
			
			printf("\nPODIZBORNIK BRISANJA\n");
			printf("\n(B)Brisanje odredjenog vozila");
			printf("\n(S)Brisanje svih vozila \n");
			printf("\n\n(P) Povratak na glavni izbornik");
	
			
			
			printf("\nOdabir je:");
			scanf(" %c", &vrstaBrisanja);
			
			if(vrstaBrisanja!='B' && vrstaBrisanja!='b' && vrstaBrisanja!='S' &&  vrstaBrisanja!='s' && vrstaBrisanja!='P' &&  vrstaBrisanja!='p')
			{
			printf("\nPogreska! Unesite B, S ili P!\n");	
			}
			
			
			}while(vrstaBrisanja!='B' && vrstaBrisanja!='b' && vrstaBrisanja!='S' &&  vrstaBrisanja!='s' && vrstaBrisanja!='P' &&  vrstaBrisanja!='p');
			
			switch(vrstaBrisanja){													// podswitch za opcije brisanja

				
			
		
				case 'B':
				case 'b':
		
		
	
					char odabirBrisanja;
					
																											// provjera unesenog znaka na mjestu unosa broja rednog vozila za brisanje
					do{																											
					printf("\nOdabrano je brisanje odredjenog vozila. \nUnesite redni broj vozila koje zelite obrisati:\n");
					scanf(" %s", &odabirBrisanja);
					
					if(isalpha(odabirBrisanja))
					{
					printf("\nUnesena vrijednost nije broj!\n");
					}
					
					}while(isalpha(odabirBrisanja));
			
			
					int odabirBrisanjaInt;
					odabirBrisanjaInt = odabirBrisanja-48;
					
					//printf("%d, %c", odabirBrisanjaInt, odabirBrisanja);
					
					OBRISI(odabirBrisanjaInt-1, &listaVozila);
					SPREMI_U_DATOTEKU ("ListaVozila.car", &listaVozila);

					printf("Spremljeno!\n\n \a");
					
					break;
		
				case 'S':
				case 's':
	
					printf("Odabrano je brisanje svih vozila. ");
					listaVozila.zadnji = -1;
					SPREMI_U_DATOTEKU ("ListaVozila.car", &listaVozila);

					printf("Obrisano i spremljeno!\n\n \a");
		
					break;
				
		
				case 'P':																				// povratak na glavni izbornik i ciscenje konzole
				case 'p':			
								system("CLS");															
					break;
				} // od podswitcha
				
				break;						// kraj funkcije brisanja
			
													
	case 'P':
	case 'p':
		
		char brojPromjene;

		
		do{																									// provjera unesenog znaka na mjestu unosa broja rednog vozila za promjenu
			
		printf("\nUnesite redni broj vozila cije podatke zelite promijeniti:");
		scanf(" %s", &brojPromjene);
		
		if(isalpha(brojPromjene))
		{
			printf("\nUnesena vrijednost nije broj!\n");
		}
		
		}while(isalpha(brojPromjene));
		
		int brojPromjeneInt;
		brojPromjeneInt = brojPromjene - 48;															// -48 jer bez toga redni broj vozila bjezi za 48
		
		PROMIJENI(brojPromjeneInt, &listaVozila);
		SPREMI_U_DATOTEKU ("ListaVozila.car", &listaVozila);
		
		printf("Spremljeno! \n\n \a");
		
		
		break;
	
	
	case 'S':
	case 's':
		
			SPREMI_U_DATOTEKU ("ListaVozila.car", &listaVozila);

		printf("Spremljeno!\n\n\a");
		
		break;
	
	
	case 'X':
	case 'x':			
		printf("\nOdabran je izlaz.");		
	
		break;
			
			
			
			
			}		// od SWITCHA
	
	
	}while(odabir!='X' && odabir!='x');		//drugi kraj do_while petlje


}	//od maina
