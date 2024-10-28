#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Funzione per verificare che la parola inserita dall'utente esista
int parola_presente_in_file(const char *nome_file, const char *parola) {

    // Apertura file
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
        int lettere_usate[256] = {0}; // Increased size to 256 to cover all possible ASCII characters
        for (int i = 0; i < lunghezza; i++) {
            // Inizializza tutto a '-'
            indovinato[i] = '-';
        }

        // Array per tenere traccia delle occorrenze di ogni singola lettera
        // Ciò permette di evitare errori relativi a lettere ripetute
        // Es. Parola = "cosa" 
        //     Tentativo = "casa" 
        //     Risultato = "🟩🟥🟨🟩" La prima a non viene presa in considerazione poichè in "cosa" ne è presente solo 1
        int lettere_presente[256] = {0}; // Increased size to 256 to cover all possible ASCII characters
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

    return 0;
}