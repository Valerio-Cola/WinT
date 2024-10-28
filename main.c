#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int parola_presente_in_file(const char *nome_file, const char *parola) {
    FILE *file = fopen(nome_file, "r");
    if (file == NULL) {
        perror("Errore nell'apertura del file");
        return 0;
    }
    char buffer[100];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        buffer[strcspn(buffer, "\n")] = 0; // Rimuovi il carattere di newline
        if (strcmp(buffer, parola) == 0) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

int main() {
    int lunghezza;
    char nome_file[50];
    FILE *file;
    char parola[100];
    int num_righe = 0;
    int riga_casuale;
    char buffer[100];

    // Richiedi la lunghezza della parola
    do {
        printf("Inserisci la lunghezza della parola (da 4 a 12): ");
        scanf("%d", &lunghezza);
        if (lunghezza < 4 || lunghezza > 12) {
            printf("Lunghezza non valida. Riprova.\n");
        }
    } while (lunghezza < 4 || lunghezza > 12);

    // Costruisci il nome del file
    snprintf(nome_file, sizeof(nome_file), "Parole/parole%d.txt", lunghezza);

    // Apri il file
    file = fopen(nome_file, "r");
    if (file == NULL) {
        perror("Errore nell'apertura del file");
        return 1;
    }

    // Conta il numero di righe nel file
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        num_righe++;
    }

    // Scegli una riga casuale
    srand(time(NULL));
    riga_casuale = rand() % num_righe;

    // Torna all'inizio del file
    rewind(file);

    // Leggi la riga casuale
    for (int i = 0; i <= riga_casuale; i++) {
        fgets(parola, sizeof(parola), file);
    }

    // Stampa la parola scelta
    printf("Parola scelta: %s", parola);
    parola[strcspn(parola, "\n")] = 0; // Rimuovi il carattere di newline

    // Svuota il buffer di input
    while (getchar() != '\n');

    // Chiudi il file
    fclose(file);

    int tentativi = 6;
    char tentativo[100];
    char indovinato[100];
    char lettere_non_presenti[256] = {0}; // Array per tracciare le lettere non presenti

    while (tentativi > 0) {
        

        int lettere_non_presenti_vuote = 1;
        for (int i = 0; i < 256; i++) {
            if (lettere_non_presenti[i]) {
                lettere_non_presenti_vuote = 0;
                break;
            }
        }

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

        printf("\nInserisci il tuo tentativo: ");
        fgets(tentativo, sizeof(tentativo), stdin);
        // Rimuovi il carattere di newline
        tentativo[strcspn(tentativo, "\n")] = 0;

        if (strlen(tentativo) != lunghezza) {
            printf("Lunghezza del tentativo non valida. Deve essere di %d caratteri.\n", lunghezza);
            continue;
        }

        if (!parola_presente_in_file(nome_file, tentativo)) {
            printf("Tentativo non valido. La parola deve essere presente nel file.\n");
            continue;
        }

        // Array per tracciare le lettere usate
        int lettere_usate[256] = {0};
        for (int i = 0; i < lunghezza; i++) {
            // Inizializza tutto a '-'
            indovinato[i] = '-';
        }

        int lettere_presente[256] = {0};
        for (int i = 0; i < lunghezza; i++) {
            lettere_presente[(unsigned char)parola[i]]++;
        }

        for (int i = 0; i < lunghezza; i++) {
            if (tentativo[i] == parola[i]) {
                indovinato[i] = '^';
                lettere_presente[(unsigned char)tentativo[i]]--;
            }
        }

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

        
        // Stampa il tentativo con spazi tra le lettere
        for (int i = 0; i < lunghezza; i++) {
            printf(" %c", tentativo[i]);
        }
        printf("\n");
        
        // Stampa il risultato con le emoji
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
        
        if (strcmp(tentativo, parola) == 0) {
            // Esci dal loop se la parola è indovinata
            printf("Hai indovinato la parola!\n");
            break;
        }

        tentativi--;
        if (tentativi == 0) {
            printf("Hai esaurito i tentativi. La parola era: %s\n", parola);
        }
    }

    return 0;
}