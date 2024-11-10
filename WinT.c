#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//  x86_64-w64-mingw32-gcc -o WinT.exe WinT.c

// Funzione per verificare che la parola inserita dall'utente esista
// Function to verify that the word entered by the user exists
int parola_presente_in_file(const char *nome_file, const char *parola) {

    // Opening file
    FILE *file = fopen(nome_file, "r");
    if (file == NULL) {
        perror("Errore nell'apertura del file");
        return 0;
    }

    char buffer[100];
    // Scorre tutto il file
    // Scrolls through the entire file
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        // Rimozione carattere di newline
        // Removing newline character
        buffer[strcspn(buffer, "\n")] = 0; 

        // Se la parola è stata trovata ritorna 1
        // If the word is found, return 1
        if (strcmp(buffer, parola) == 0) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

// Funzione per stampare gli errori
// Function to print errors
void stampa_errore(int lingua, int posizione){

    const char *errori[][2]={
        {"Input non valido. Riprova.", "Input not valid. Retry."},
        {"Errore nell'apertura del file", "Error opening the file"},
        {"Lunghezza non valida. Riprova.", "Invalid length. Try again."},
        {"Lunghezza del tentativo non valida. Deve essere lunga ", "Invalid attempt length. Must be "},
        {"Tentativo non valido. La parola deve esistere.\n", "Invalid attempt. The word must be exist.\n"},
        {"Hai esaurito i tentativi. La parola era: ", "You've run out of attempts. The word was: "},
    };
    printf("%s", errori[posizione][lingua]);

}

// Funzione per stampare i dialoghi
// Function to print dialogues
void stampa_interfaccia(int lingua, int posizione){
    const char *dialoghi[][2] = {
        {"Cosa vuoi fare? \n 1. Indovina una parola casuale \n 2. Inserisci la tua parola \n --> ", "\nWhat do you want to do? \n 1. Guess a random word \n 2. Enter your word \n --> "},
        {"Inserisci la parola da indovinare: ", "Enter the word to guess: "},
        {"Inserisci la lunghezza della parola (da 4 a 12): ", "Enter the length of the word (from 4 to 12): "},
        {"Inserisci il tuo tentativo: ", "Enter your attempt: "},
        {"Hai indovinato la parola!\n", "You guessed the word!\n"},
        {"Parola scelta: ", "Word choice: "},
        {"Lettere non presenti: ", "Letters not included: "}

    };
    printf("%s", dialoghi[posizione][lingua]);
}

int main() {
    
    // Logo
    printf(" __     __     __     __   __     ______  \n");
    printf("/\\ \\  _ \\ \\   /\\ \\   /\\ \"-.\\ \\   /\\__  _\\ \n");
    printf("\\ \\ \\/ \".\\ \\  \\ \\ \\  \\ \\ \\-.  \\  \\/_/\\ \\/ \n");
    printf(" \\ \\__/\".~\\_\\  \\ \\_\\  \\ \\_\\\\\"\\_\\    \\ \\_\\ \n");
    printf("  \\/_/   \\/_/   \\/_/   \\/_/ \\/_/     \\/_/ \n\n");

    
    //Lunghezza della parola da indovinare
    // Length of the word to guess
    int lunghezza;

    // Nome del file da cui leggere le parole
    // Name of the file from which to read the words
    FILE *file;
    char nome_file[50];

    // Parola selezionata casualmente
    // Randomly selected word
    char parola[100];

    // Righe file da cui viene estratta la parola, utilizzato per scegliere una riga casuale
    // Rows of the file from which the word is extracted, used to choose a random row
    int num_righe = 0;
    int riga_casuale;

    // Array per la lettura del file
    // Array for reading the file
    char buffer[100];

    // Scelta della lingua
    // Language choice
    int lingua;
    do {
        printf("Quale lingua scegli? / Which language do you choose?\n");
        printf(" 0. Italiano \n 1. English \n --> ");
        scanf("%d", &lingua);

        if (lingua != 0 && lingua != 1) {
            printf("Input non valido. Riprova. / Input not valid. Retry.\n");
        }
    } while (lingua != 0 && lingua != 1);


    // Scelta della modalità
    // Mode choice    
    int modalità;
    do{
        stampa_interfaccia(lingua, 0);
        scanf("%d", &modalità);

        if (modalità != 1 && modalità != 2) {
            stampa_errore(lingua, 0);
        }
    } while (modalità != 1 && modalità != 2);


    // Scelta della parola da indovinare
    // Choice of the word to guess
    if(modalità == 2){
        stampa_interfaccia(lingua, 1);
        scanf("%s", parola);
        lunghezza = strlen(parola);

        // Il file da cui leggere la parolà sarà determinato dalla lunghezza scelta dall'utente
        // The file from which to read the word will be determined by the length chosen by the user
        snprintf(nome_file, sizeof(nome_file), "Parole/parole%d.txt", lunghezza);


    }else{
        // Richiesta all'utente della lunghezza della parola da indovinare
        // Request to the user for the length of the word to guess
        do {
            stampa_interfaccia(lingua, 2);
            scanf("%d", &lunghezza);
            if (lunghezza < 4 || lunghezza > 12) {
                stampa_errore(lingua, 2);
            }
        } while (lunghezza < 4 || lunghezza > 12);

        snprintf(nome_file, sizeof(nome_file), "Parole/parole%d.txt", lunghezza);

        // Apetura file
        // Opening file
        file = fopen(nome_file, "r");
        if (file == NULL) {
            stampa_errore(lingua, 1);
            return 1;
        }

        // Conteggio delle righe del file per sceglierne una casuale 
        // Counting the lines of the file to choose a random one
        while (fgets(buffer, sizeof(buffer), file) != NULL) {
            num_righe++;
        }
        srand(time(NULL));
        riga_casuale = rand() % num_righe;

        // Ritorna all'inizio del file
        // Returns to the beginning of the file
        rewind(file);

        // Viene letta ogni riga fino a quella scelta casualmente
        // Reads each line up to the randomly chosen one  
        // Inefficiente, da rivedere
        
        for (int i = 0; i <= riga_casuale; i++) {
            fgets(parola, sizeof(parola), file);
        }

        // Chiusura file
        // Closing file
        fclose(file);

        // Stampa la parola scelta
        // Print the chosen word
        stampa_interfaccia(lingua, 5);
        printf("%s", parola);
    }


    // Rimozione carattere di newline
    // Removing newline character
    parola[strcspn(parola, "\n")] = 0; 

    // Svuota il buffer di input per evitare problemi con la lettura successiva
    // Clears the input buffer to avoid problems with subsequent reading
    while (getchar() != '\n');


    // Utente ha 6 tentativi per indovinare la parola
    // User has 6 attempts to guess the word
    int tentativi = 6;
    
    // Array in cui inserire il tentativo dell'utente
    // Array into which to insert the user's attempt
    char tentativo[100];
    
    // Array per tracciare le lettere indovinate
    // Array to track the guessed letters
    char indovinato[100];

    // Array per tracciare le lettere non presenti nella parola
    // Array to track letters not present in the word
    char lettere_non_presenti[256] = {0}; 

    // Loop di gioco
    // Game Loop
    while (tentativi > 0) {
        
        // Se l'array per le lettere non presenti è vuoto non verrà stampato
        // If the array for letters not present is empty it will not be printed
        int lettere_non_presenti_vuote = 1;
        for (int i = 0; i < 256; i++) {
            if (lettere_non_presenti[i]) {
                lettere_non_presenti_vuote = 0;
                break;
            }
        }

        // Al contrario le stampa
        // Instead it prints them
        if (!lettere_non_presenti_vuote) {
            // Stampa le lettere non presenti
            // Print the letters that are not present
            stampa_interfaccia(lingua, 6);
            for (int i = 0; i < 256; i++) {
                if (lettere_non_presenti[i]) {
                    printf("%c ", i);
                }
            }
            printf("\n");
        }    

        // Input dell'utente per il tentativo 
        // User input for the attempt
        stampa_interfaccia(lingua, 3);
        fgets(tentativo, sizeof(tentativo), stdin);

        // Rimozione carattere di newline
        // Removing newline character
        tentativo[strcspn(tentativo, "\n")] = 0;

        // Controllo della lunghezza dell'input, deve essere equivalente alla parola da indovinare
        // Check the length of the input, it must be equivalent to the word to guess
        if (strlen(tentativo) != lunghezza) {
            stampa_errore(lingua, 3);
            printf("%d\n", lunghezza);
            continue;
        }

        // Controllo se la parola inserita sia effettivamente una parola esistente
        // Check whether the entered word is actually an existing word
        if (!parola_presente_in_file(nome_file, tentativo)) {
            stampa_errore(lingua, 4);
            continue;
        }

        // Array per tracciare le lettere usate
        // Per ogni tentativo vengono inizializzate nell'array tutte le lettere utilizzate come errate '-'
        // Array to track the letters used
        // For each attempt, all the letters used as incorrect '-' are initialized in the array
        int lettere_usate[256] = {0};
        for (int i = 0; i < lunghezza; i++) {
            // Inizializza tutto a '-'
            // Initialize everything to '-'
            indovinato[i] = '-';
        }

        // Array per tenere traccia delle occorrenze di ogni singola lettera
        // Ciò permette di evitare errori relativi a lettere ripetute
        // Es. Parola = "cosa" 
        //     Tentativo = "casa" 
        //     Risultato = "🟩🟥🟨🟩" La prima a non viene presa in considerazione poichè in "cosa" ne è presente solo 1

        // Array to keep track of the occurrences of each individual letter
        // This helps avoid errors related to repeated letters
        // Ex. Word = "home" 
        // Attempt = "holo" 
        // Result = "🟩🟩🟥🟥" The second o is not taken into consideration since only 1 is present in "home"

        int lettere_presente[256] = {0};
        for (int i = 0; i < lunghezza; i++) {
            lettere_presente[(unsigned char)parola[i]]++;
        }

        // Verifica se le lettere nel tentativo corrispondono esattamente alle lettere nella parola
        // Se c'è una corrispondenza esatta, il carattere corrispondente in indovinato viene impostato a corretto '^' 
        // e il contatore in lettere_presente viene decrementato.

        // Check if the letters in the attempt exactly match the letters in the word
        // If there is an exact match, the matching character in guessed is set to correct '^' 
        // and the counter in present_letters is decremented.

        for (int i = 0; i < lunghezza; i++) {
            if (tentativo[i] == parola[i]) {
                indovinato[i] = '^';
                lettere_presente[(unsigned char)tentativo[i]]--;
            }
        }

        /*
            Gestisce le lettere che non sono state già indovinate correttamente indovinato[i] != '^'
            Se la lettera del tentativo è presente nella parola lettere_presente[(unsigned char)tentativo[i]] > 0
                e non è stata già usata !lettere_usate[(unsigned char)tentativo[i]], allora:
                    Il carattere corrispondente in indovinato viene impostato a '*'
                    Il contatore in lettere_presente viene decrementato
                    La lettera viene marcata come usata in lettere_usate
            Se la lettera non è presente o è già stata usata, indovinato[i] rimane '-' e la lettera viene marcata come non presente in lettere_non_presenti
        
            Handles letters that have not already been guessed correctly indovinato[i] != '^'
            If the letter of the attempt is present in the word letters_present [(unsigned char)tentativo[i]] > 0
                and has not already been used !lettere_usate[(unsigned char)tentativo[i]], then:
                    The corresponding character in guessed is set to '*'
                    The lettere_presenti counter is decremented
                    The letter is marked as used in lettere_usate
            If the letter is not present or has already been used, indovinato[i] still '-' and the letter is marked as not present in lettere_non_presenti
        */
        for (int i = 0; i < lunghezza; i++) {
            if (indovinato[i] != '^') {
                if (lettere_presente[(unsigned char)tentativo[i]] > 0 && !lettere_usate[(unsigned char)tentativo[i]]) {
                    indovinato[i] = '*';
                    lettere_presente[(unsigned char)tentativo[i]]--;
                    lettere_usate[(unsigned char)tentativo[i]] = 1;
                } else {
                    indovinato[i] = '-';
                    lettere_non_presenti[(unsigned char)tentativo[i]] = 1;
                }
            }
        }

        
        // Stampa il tentativo con spazi tra le lettere per essere allineate alle emoji
        // Print the attempt with spaces between the letters to align with the emoji
        for (int i = 0; i < lunghezza; i++) {
            printf(" %c", tentativo[i]);
        }
        printf("\n");
        
        // Stampa il risultato sotto forma di emoji emoji
        // Print the result as an emoji
        for (int i = 0; i < lunghezza; i++) {
            if (indovinato[i] == '^') {
                printf("🟩");
            } else if (indovinato[i] == '-') {
                printf("🟥");
            } else if (indovinato[i] == '*') {
                printf("🟨");
            }
        }
        printf("\n");
        
        // Se la parola è stata indovinata si esce dal loop di gioco
        // If the word has been guessed, you exit the game loop
        if (strcmp(tentativo, parola) == 0) {
            stampa_interfaccia(lingua, 4);
            break;
        }

        // Altrimenti decrementa il numero di tentativi
        // Otherwise decrease the number of attempts
        tentativi--;

        // Se i tentativi sono esauriti stampa la parola e terminerà il loop di gioco
        // If you run out of attempts, print the word and the game loop will end
        if (tentativi == 0) {
            stampa_errore(lingua, 5);
            printf("%s\n", parola);
        }
    }
    return 0;
}
