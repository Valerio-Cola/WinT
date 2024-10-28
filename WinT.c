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
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        // Rimozione carattere di newline
        buffer[strcspn(buffer, "\n")] = 0; 

        // Se la parola è stata trovata ritorna 1
        if (strcmp(buffer, parola) == 0) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

int main() {

    
    //Lunghezza della parola da indovinare
    int lunghezza;

    // Nome del file da cui leggere le parole
    FILE *file;
    char nome_file[50];

    // Parola selezionata casualmente
    char parola[100];

    // Righe file da cui viene estratta la parola, utilizzato per scegliere una riga casuale
    int num_righe = 0;
    int riga_casuale;

    // Array per la lettura del file
    char buffer[100];

    int lingua;

    do {
        printf("Quale lingua scegli? / Which language do you choose?\n");
        printf("1. Italiano 2. English --> ");
        scanf("%d", &lingua);

        if (lingua != 1 && lingua != 2) {
            printf("Input non valido. Riprova. / Input not valid. Retry.\n");
        }
    } while (lingua != 1 && lingua != 2);


    if (lingua == 1){
        // Richiesta all'utente della lunghezza della parola da indovinare
        do {
            printf("Inserisci la lunghezza della parola (da 4 a 12): ");
            scanf("%d", &lunghezza);
            if (lunghezza < 4 || lunghezza > 12) {
                printf("Lunghezza non valida. Riprova.\n");
            }
        } while (lunghezza < 4 || lunghezza > 12);

        // Il file da cui leggere la parolà sarà determinato dalla lunghezza scelta dall'utente
        snprintf(nome_file, sizeof(nome_file), "Parole/parole%d.txt", lunghezza);

        // Apetura file
        file = fopen(nome_file, "r");
        if (file == NULL) {
            perror("Errore nell'apertura del file");
            return 1;
        }

        // Conteggio delle righe del file per sceglierne una casuale 
        while (fgets(buffer, sizeof(buffer), file) != NULL) {
            num_righe++;
        }
        srand(time(NULL));
        riga_casuale = rand() % num_righe;

        // Ritorna all'inizio del file
        rewind(file);

        // Viene letta ogni riga fino a quella scelta casualmente
        // Inefficiente, da rivedere
        for (int i = 0; i <= riga_casuale; i++) {
            fgets(parola, sizeof(parola), file);
        }

        // Stampa la parola scelta
        printf("Parola scelta: %s", parola);
        
        // Rimozione carattere di newline
        parola[strcspn(parola, "\n")] = 0; 

        // Svuota il buffer di input per evitare problemi con la lettura successiva
        while (getchar() != '\n');

        // Chiusura file
        fclose(file);

        // Utente ha 6 tentativi per indovinare la parola
        int tentativi = 6;
        // Array in cui inserire il tentativo dell'utente
        char tentativo[100];
        // Array per tracciare le lettere indovinate
        char indovinato[100];

        // Array per tracciare le lettere non presenti nella parola
        char lettere_non_presenti[256] = {0}; 

        // Loop di gioco
        while (tentativi > 0) {
            
            // Se l'array per le lettere non presenti è vuoto non verrà stampato
            int lettere_non_presenti_vuote = 1;
            for (int i = 0; i < 256; i++) {
                if (lettere_non_presenti[i]) {
                    lettere_non_presenti_vuote = 0;
                    break;
                }
            }

            // Al contrario le stampa
            if (!lettere_non_presenti_vuote) {
                // Stampa le lettere non presenti
                printf("Lettere non presenti: ");
                for (int i = 0; i < 256; i++) {
                    if (lettere_non_presenti[i]) {
                        printf("%c ", i);
                    }
                }
                printf("\n");
            }    

            // Input dell'utente per il tentativo 
            printf("\nInserisci il tuo tentativo: ");
            fgets(tentativo, sizeof(tentativo), stdin);

            // Rimozione carattere di newline
            tentativo[strcspn(tentativo, "\n")] = 0;

            // Controllo della lunghezza dell'input, deve essere equivalente alla parola da indovinare
            if (strlen(tentativo) != lunghezza) {
                printf("Lunghezza del tentativo non valida. Deve essere di %d caratteri.\n", lunghezza);
                continue;
            }

            // Controllo se la parola inserita sia effettivamente una parola esistente
            if (!parola_presente_in_file(nome_file, tentativo)) {
                printf("Tentativo non valido. La parola deve essere presente nel file.\n");
                continue;
            }

            // Array per tracciare le lettere usate
            // Per ogni tentativo vengono inizializzate nell'array tutte le lettere utilizzate come errate '-'
            int lettere_usate[256] = {0};
            for (int i = 0; i < lunghezza; i++) {
                // Inizializza tutto a '-'
                indovinato[i] = '-';
            }

            // Array per tenere traccia delle occorrenze di ogni singola lettera
            // Ciò permette di evitare errori relativi a lettere ripetute
            // Es. Parola = "cosa" 
            //     Tentativo = "casa" 
            //     Risultato = "🟩🟥🟨🟩" La prima a non viene presa in considerazione poichè in "cosa" ne è presente solo 1
            int lettere_presente[256] = {0};
            for (int i = 0; i < lunghezza; i++) {
                lettere_presente[(unsigned char)parola[i]]++;
            }

            // Verifica se le lettere nel tentativo corrispondono esattamente alle lettere nella parola
            // Se c'è una corrispondenza esatta, il carattere corrispondente in indovinato viene impostato a corretto '^' 
            // e il contatore in lettere_presente viene decrementato.

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
            for (int i = 0; i < lunghezza; i++) {
                printf(" %c", tentativo[i]);
            }
            printf("\n");
            
            // Stampa il risultato sotto forma di emoji emoji
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
            if (strcmp(tentativo, parola) == 0) {
                printf("Hai indovinato la parola!\n");
                break;
            }

            // Altrimenti decrementa il numero di tentativi
            tentativi--;

            // Se i tentativi sono esauriti stampa la parola e terminerà il loop di gioco
            if (tentativi == 0) {
                printf("Hai esaurito i tentativi. La parola era: %s\n", parola);
            }
        }
    }else{

        // Prompts the user for the length of the word to guess
        do {
            printf("Enter the length of the word (from 4 to 12): ");
            scanf("%d", &lunghezza);
            if (lunghezza < 4 || lunghezza > 12) {
                printf("Invalid length. Try again.\n");
            }
        } while (lunghezza < 4 || lunghezza > 12);

        // The file from which to read the word will be determined by the length chosen by the user
        snprintf(nome_file, sizeof(nome_file), "Parole/words%d.txt", lunghezza);

        // Opening files
        file = fopen(nome_file, "r");
        if (file == NULL) {
            perror("Error opening the file");
            return 1;
        }

        // Counting the lines of the file to choose a random one 
        while (fgets(buffer, sizeof(buffer), file) != NULL) {
            num_righe++;
        }
        srand(time(NULL));
        riga_casuale = rand() % num_righe;

        // Returns to the beginning of the file
        rewind(file);

        // Every line up to the randomly chosen one is read
        // Inefficiente, da rivedere
        for (int i = 0; i <= riga_casuale; i++) {
            fgets(parola, sizeof(parola), file);
        }

        // Print the chosen word
        printf("Word choice: %s", parola);
        
        // Removing newline character
        parola[strcspn(parola, "\n")] = 0; 

        // Clears the input buffer to avoid problems with subsequent reading
        while (getchar() != '\n');

        // Closing file
        fclose(file);

        // User has 6 attempts to guess the word
        int tentativi = 6;
        // Array into which to insert the user's attempt
        char tentativo[100];
        // Array to track the guessed letters
        char indovinato[100];

        // Array to track letters not present in the word
        char lettere_non_presenti[256] = {0}; 

        // Game Loop
        while (tentativi > 0) {
            
            // If the array for letters not present is empty it will not be printed
            int lettere_non_presenti_vuote = 1;
            for (int i = 0; i < 256; i++) {
                if (lettere_non_presenti[i]) {
                    lettere_non_presenti_vuote = 0;
                    break;
                }
            }

            // Instead it prints them
            if (!lettere_non_presenti_vuote) {
                // Print the letters that are not present
                printf("Letters not present: ");
                for (int i = 0; i < 256; i++) {
                    if (lettere_non_presenti[i]) {
                        printf("%c ", i);
                    }
                }
                printf("\n");
            }    

            // User input for the attempt 
            printf("\nEnter your attempt: ");
            fgets(tentativo, sizeof(tentativo), stdin);

            // Enter your attempt:
            tentativo[strcspn(tentativo, "\n")] = 0;

            // Enter your attempt:
            if (strlen(tentativo) != lunghezza) {
                printf("Invalid attempt length. Must be %d characters.\n", lunghezza);
                continue;
            }

            // I check whether the entered word is actually an existing word
            if (!parola_presente_in_file(nome_file, tentativo)) {
                printf("Invalid attempt. The word must be present in the file.\n");
                continue;
            }

            // Array to track the letters used
            // For each attempt, all the letters used as incorrect '-' are initialized in the array
            int lettere_usate[256] = {0};
            for (int i = 0; i < lunghezza; i++) {
                // Initialize everything to '-'
                indovinato[i] = '-';
            }

            // Array to keep track of the occurrences of each individual letter
            // This helps avoid errors related to repeated letters
            // Ex. Word = "home" 
            // Attempt = "holo" 
            // Result = "🟩🟩🟥🟥" The second o is not taken into consideration since only 1 is present in "home"
            int lettere_presente[256] = {0};
            for (int i = 0; i < lunghezza; i++) {
                lettere_presente[(unsigned char)parola[i]]++;
            }

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

            
            // Print the attempt with spaces between the letters to align with the emoji
            for (int i = 0; i < lunghezza; i++) {
                printf(" %c", tentativo[i]);
            }
            printf("\n");
            
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
            
            // If the word has been guessed, you exit the game loop
            if (strcmp(tentativo, parola) == 0) {
                printf("You guessed the word!\n");
                break;
            }

            // Otherwise decrease the number of attempts
            tentativi--;

            // If you run out of attempts, print the word and the game loop will end
            if (tentativi == 0) {
                printf("You've run out of attempts. The word was: %s\n", parola);
            }
        }        
    }
    

    return 0;
}
