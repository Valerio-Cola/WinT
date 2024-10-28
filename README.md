# WinT
# Wordle Nel Tuo Terminale 

Una versione italiana di Wordle nel proprio terminale scritta interamente in C. Se l'autore di Wordle non approva, la repository verrà rimossa. Non è stato preso codice dal progetto originale.

## Indice

- [Parole](#parole)
- [Funzionamento di WinT.c](#funzionamento-di-wintc)
- [Come Giocare](#come-giocare)
- [To-Do List](#to-do-list)
- [Licenza](#licenza)


## Parole

Le parole sono state prese da [napolux/paroleitaliane](https://github.com/napolux/paroleitaliane) e successivamente organizzate in base alla lunghezza in vari file dall'algoritmo [`Selettore_Parole.c`](Parole/Selettore_Parole.c).

## Funzionamento di WinT.c

L'algoritmo principale opera nel seguente modo:

1. **Richiesta della lunghezza della parola**: L'utente specifica la lunghezza della parola da indovinare.
2. **Selezione della parola**: Apre il relativo file in base alla lunghezza e sceglie una parola casuale.
3. **Inizio del gioco**: Inizia il loop di gioco con 6 tentativi.
4. **Input dell'utente**: Viene richiesto in input il tentativo all'utente, verranno effettuate delle verifiche riguardo l'esistenza e la lunghezza della parola in input.
5. **Verifica delle lettere**: Ad ogni tentativo si tiene traccia della correttezza delle singole lettere mediante i simboli:
    - Corretta ma in posizione errata: `*`
    - Corretta e in posizione giusta: `^`
    - Errata: `-`
6. **Tracciamento delle lettere**: Verrà utilizzato un array per tenere traccia delle lettere che non sono presenti nella parola.
    - **Nota**: Se nella parola è presente una sola 'a' e nel tentativo ne vengono scritte due, la lettera verrà inserita nell'array per indicare che non ci sono altre 'a' nella parola da indovinare.
7. **Stampa del risultato**: Viene stampata la parola inserita in input allineata con le emoji che indicano la correttezza: 🟩🟨🟥.
8. **Fine del gioco**:
    - Se la parola è stata indovinata, si esce dal loop di gioco.
    - Altrimenti, viene decrementato il numero di tentativi.

## Come Giocare

### Su linux
1. Scaricare la repository.
2. Compilare il codice.
3. Eseguire il programma.
```sh
# Compila il programma
gcc -o Wint WinT.c

# Esegui il programma con il seguente comando
./WinT
```

### Su Windows
1. Scaricare la repository sotto forma di file .zip
2. Estrarre il contenuto
3. Eseguire il file .bat
4. Windows indicherà che l'eseguibile può essere una minaccia, ovviamente non lo è, poichè
   non è stato firmato. Nel file bat inoltre il comando chcp 65001 all'inizio dello script batch .bat    serve per impostare la codifica su UTF-8 e permettere di mostrare le emoji su terminale


## To-Do List

- [ ] Effettuare scrematura delle parole.
- [ ] Ottimizzare l'algoritmo di selezione delle parole.
- [ ] Fornire una copia integrale in inglese.
- [ ] Aggiungere la possibilità di inserire la parola da indovinare.
- [x] Fornire la possibilità di eseguire il gioco su terminale Windows


## Licenza

Questo progetto è distribuito sotto la licenza MIT. Ciò significa che è possibile utilizzare, copiare, modificare, unire, pubblicare, distribuire, concedere in sublicenza e/o vendere copie del software, e permettere alle persone a cui il software è fornito di fare lo stesso.

Il software è fornito "così com'è", senza garanzia di alcun tipo, espressa o implicita, incluse ma non limitate alle garanzie di commerciabilità, idoneità per un particolare scopo e non violazione. In nessun caso gli autori o i detentori del copyright saranno responsabili per qualsiasi reclamo, danno o altra responsabilità, sia in un'azione di contratto, torto o altro, derivante da, fuori o in connessione con il software o l'uso o altre operazioni nel software.

