#include <stdio.h>
#include <math.h>
#include <string.h>

int variabile_globale; 
extern int variabile_in_altro_file;
/* gcc -Wall file.c | Crea eseguibile di default è a.out, -o prog_nome.o per specificare nome eseguibile
   per eseguirlo ./a.out */

int main(){ 
	printf("Spam Eggs\n");
	printf("Spam\\Eggs");
	printf("Spam\tEggs");
	
	
	// Variabili
	int x = 123;			   // (-2.147.483.648 - 2.147.483.647) %d
	unsigned int x2;	           // (0 - 4.294.967.295) %u
	
	short int x3;			   // (-32.768 - 32.767) %d
	unsigned short int x4;             // (0 - 65.535) %d
	
	long long int x5;		   // (-9 quintillioni - 9 quintillioni) %lld
	unsigned long long int x6;	   // (0 - 18 quintillioni) %llu
	
	float pi = 3.14; 		   // 6-7 numeri %f
	double pi2 = 3.1415926535897;       // 15-16 numeri %lf
	
	char carattere = 'C'; 	      	   // %d come numero, %c come carattere. Può essere dichiarato anche come numero ascii (-128 - 127)
	unsigned char carattere2 = 221;    // Come sopra ma ascii (0 - 255)
	char stringa[] = "Valerio";	   // %s
	
	//bool e = true; 		           // %d
	
	printf("\nNumero %d, Carattere %c", x, carattere);
	
	const PI = 3.14159;
	
	/*  Operatori
	    + - * / % ++ --
	    += -= *= /= %=
	    && || !
	*/ 
	
	// Input
	int age;
	scanf("%d", &age); // (formattatore, &nome_variabile già dichiarata)
	
	char nome[25];
	fgets(nome, 25, stdin); // Include gli spazi
	
	// <math.h>
	
	double radice = sqrt(9);
	double potenza = pow(2,4);
	int approssima = round(3.14);
	int eccesso = ceil(3.15);
	int difetto = floor(3.98);
	double modulo = fabs(-10);;
	double logaritmo = log(3);
	double seno = sin(45);
	double coseno = cos(45);
	double tangente = tan(45);
	
	// <string.h>
	char string1[] = "Spam";
	char string2[] = "Eggs";
	
	strlwr(string1);
	strupr(string1);
	strcat(string1, string2);       // Concatena le due tringhe
	strncat(string1, string2, 2);   // Concatena solo n char della 2
	strcpy(string1, string2);       // Copia la 2 in 1
	strncpy(string1, string2, 4);   // Copia solo primi n char 
	
	strset(string1, '?');           // Imposta tutti char di 1 nel carattere specificato
	strnset(string1, '?', 2);	 	// Solo primi n
	strrev(string1);				// Inverte
	
	int lunghezza = strlen(string1); 
	int compara = strcmp(string1, string2);
	int compara_n = strncmp(string1, string2, 3);
	int compara_ignora_case = strcmpi(string1, string2);
	int compara_ignora_case_n = strnicmp(string1, string2, 3);
	
	
	/* If
	   continue passa a iterazione successiva */
	if(age >= 18){
		printf("Sei maggiorenne");
	}
	else if(age < 0){
		printf("Età errata");
	}
	else if(age == 69){
		printf("Kekw");
	}
	else{
		printf("Sei minorenne");
	}
	
	// Switch
	char voto;
	
	printf("Inserisci voto in lettere");
	scanf("%c", voto);
	
	switch(voto){
		case 'A':
			printf("Perfetto");
			break;
		case 'B':
			printf("ottimo");
			break;
		case 'C':
			printf("Buono");
			break;
		default:
			printf("Inserisci un voto valido");
		
	}
	
	
	// break interrompe ciclo
	/* For
	  variabile; condizione; operazione  */
	for(int i = 1; i <= 10; i++){
		// Code
	}
	
	// While
	
	while(age < 18){
		// Code
	}
	
	// Do While
	
	do{
		// Code viene eseguito anche prima della condizione
	}while(age > 18);
	
	// Array
	
	double prezzi1[] = {5.99, 10.0, 9.99};
	printf("%lf", prezzi1[0]);
	
	double prezzi2[5];  // Dimensione già definita
	prezzi2[0] = 5.0;  // Rimpiazzo
	
	double prezzi3[10] = {5.99, 10.0, 9.99};

	// 2D Array
	int numeri[2][3] = {{1,2,3},{4,5,6}};
					
	int numeri2[2][3];  // [righe][colonne]
	numeri2[0][2] = 3;  // assegnazione o rimpiazzo [riga][colonna]
	
	for(int i = 0; i<2; i++){
		for(int j = 0; j<3; j++){
			printf("%d", numeri[i][j]);
		}
	}
	
	// Array di Stringhe
	
	char cars[][10] = {"Mustang","Tesla","Camaro"};
	
	strcpy(cars[0], "Ferrari"); // rimpiazzo con numero index
	
	// Invertire 2 stringhe
	char x[] = "ABC";
	char y[] = "EFG";
	char temp[5];
	
	strcpy(temp,x);
	strcpy(x,y);
	strcpy(y,temp);
	
	
	// File
	
	/* Passaggio file da linea di comando
		int main(int argc, char *argv[])
	    FILE *pf = fopen(argv[1], "r")
	*/


	FILE *pF = fopen("test.txt", "w");    // Apre per la scrittura
	fprintf(pF, "Spam Eggs");             // Scrive
	

	FILE *pF = fopen("test.txt", "a");    // Apre per aggiungere
	fputs("1234", pF);					  // Aggiunge


	if(pF == NULL){
		printf("Non Esiste");	
	}

	remove("test.txt");
	
	if(remove("test.txt") == 0){
	
		printf("File rimosso");
	}
	
	
	FILE *pF = fopen("test.txt", "r");    // Apre per la lettura
	
	char buffer[256]; 					  // Immagazzinare file letto
	fgets(buffer, 255, pF);    			  // Solo una riga
	
	char s[100];
	fscanf(pF, "%s", &s); 				  // Utente scrive, se nel file inserisce in s

	while(fgets(buffer, 255, pF)!= NULL){
		printf("%s", buffer);
	}
	
	
	fclose(pF);


	//Allocazione dinamica
	
	int n = 5;
	int *nptr;
	
	nptr = &n;
	
	nptr++;   //aumenta 4 byte
	*nptr = *nptr + 1;
	
	
	int vector[10];
	int *vptr = NULL; 	//puntatore nullo
	vptr = &vector[0];   //puntatore al primo elemento
	vptr = vector;	  //puntatore all'array
	
	void *calloc(size_t nmemb, size_t size);  //richiedo memoria inizzializzata a 0, nmemb numero zone di memoria con size grandezza 
	
	char *strPtr = NULL;
	strPtr = (char *) malloc(30);         //richiedo memoria di grandezza size in byte

	int *intPtr = NULL;
	intPtr = (int *) malloc(30*sizeof(int));  

	void free(void *ptr);  				      //libero memoria
	


	// Puntatori
	
	int i;
	char c;
	
	int *iPtr;
	char *cPtr;

	iPtr = &i;
	cPtr = &c;

	print("Indirizzo memoria di i %d e di c", iPtr, cPtr); //Valore del puntatore
	print("Valori di i %d = %d", i , *iPtr);	//Prende valore della cella puntata


	//Strutture

	//Assegno gli attributi
	strcpy(artista1.stage_name, "Eminem");
	strcpy(artista1.full_name, "Bruce Marshall Matheers");
	artista1.year = 1972;

	printf("%s, %s, %d\n", artista1.full_name, artista1.stage_name, artista1.year);

	
	strcpy(traccia.title, "Black Magic");
	traccia.duration = 2.55;
	traccia.artista = artista1;

	printf("%s, %f, %s, %s, %d", traccia.title, traccia.duration, traccia.artista.stage_name, traccia.artista.full_name, traccia.artista.year);
	
	
	//Allocazione dinamica / Array dinamici
	//Grandezza mem da assegnare decisa durante esecuzione

	int numElem = 10;
	int *m;
	int *c;

	//Meglio castarlo per il tipo di puntatore
	m = (int*) malloc(numElem * sizeof(int)); //Moltiplico elementi per la dimensione = dimensione totale
	
	//Calloc azzera tutte le celle di memoria che prende
	c = (int*) calloc(numElem, sizeof(int));

	numElem = 15;
	m = (int*) realloc(m, numElem * sizeof(int)); //Modifica dimensione

	free(m);
	free(c);

	char str[] = "Spam Eggs";
	//Pone 4byte di str come -
	memset(str, "-", 4); // output --> "---- Eggs"

	char spam[] = "Spam";
	char eggs[] = "Eggs";

	//Copia contenuto di eggs in spam
	memcpy(spam, eggs, sizeof(eggs));

	
	//Fork()
	#include <unistd.h>
	#include <sys/types.h>

	pid_t pID = fork(); //Processo figlio, riceve una copia delle variabili su cui lavorare
	printf("Ritorna del processo chiamante pid: %d, ppid: %d, uid: %d", getpid(), getppid(), getuid());

	if(pID < 0){
		printf("Errore");
	}else if(pID == 0){
		printf("Codice figlio");
	}else{
		printf("Codice padre");
	}
	printf("Codice condiviso da entrambi");


	//Exit()
	#include <unistd.h>
	_exit(0); //Chiude tutto

	atexit(somma);
	exit(0);  //Alla chiusura esegue le funzioni salvate con atexit()
	
	//Wait()
	#include <sys/wait.h>
	#include <sys/types.h>
	int status;
	
	wait(&status); //Attende il primo figlio che termina
	
	/* waitpid(pid, &status, options); 
	pid: -1 qualunque
	options: WNHANG ritorna subito se nessun figlio fa exit
			 WUNTRACED ritorna se figlio arrestato
			 WCONTINUED ritorna anche se figlio arrestato e riesumato
			 possono essere messi in or
	*/

	WIFEXITED(status); //Ritorna true se termina normalmente


	//Segnali man 7 signal per vederli




	/*-------------------------------------------------*/
	somma(21,39);
	double risultato = moltiplicazione(3.2, 86.53);
	int massimo = trova_massimo(4,7);
	
	
	return 0; //Indica programma è terminato con successo
}

/*
	Le funzioni si dichiarano al di fuori se ritornano qualcosa si scrive il tipo di variabile altrimenti void, 
	la chiamata si funzione nome_funzione();
	Se non inserisco tutti gli argomenti compilerà comunque ma inserirà elementi non conformi, inserisco prima del main
	ad es. void somma(int num1, int num2); per evitare ciò.

*/
	
void somma(int num1, int num2){
	printf(num1+num2);
}

double moltiplicazione(double num1, double num2){
	return num1 * num2;
}
	
int trova_massimo(int num1, int num2){
	return (num1 > num2) ? num1 : num2;
	//       condizione  ? vero : falso
}


//Strutture  Simile alle classi = strutture sono contenitori di dati

	  //nome_struttura
struct struct_artist{

	//Attributi
	char stage_name[20];
	char full_name[50];
	int year;

} artista2, artista3;   //Posso dichiarare oggetti da qui

struct struct_artist artista1;  //Riserva in memoria spazio artista1 = oggetti delle classi

//Vai nel main 

struct struct_track{

	struct struct_artist artista; //track contiene anche gli attributi di artist
	char title[100];
	float duration;

} traccia, album[20];

//Vai nel main 


struct struct_point{
	int x;
	int y;
	int z;
} point;

//Vai nel main 



