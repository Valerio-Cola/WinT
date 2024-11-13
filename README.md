# WinT 🎮

- [Italiano](#Italiano-)
- [English](#English-)

# Italiano 🇮🇹
# Wordle Nel Tuo Terminale 

Una versione italiana e inglese di Wordle nel proprio terminale scritta interamente in C. Se l'autore di Wordle non approva, la repository verrà rimossa. Non è stato preso codice dal progetto originale.

[![Open in Gitpod](https://gitpod.io/button/open-in-gitpod.svg)](https://gitpod.io/#https://github.com/Valerio-Cola/WinT)
È possibile eseguire il programma online con GitPod. È necessario effettuare il login con github, selezionare come editor Terminal e cliccare su continue. Una volta aperta la shell seseguire i comandi [Come Giocare](#come-giocare-) oppure ```gcc -o Wint WinT.c && ./WinT```


## Indice 📑

- [Parole](#parole-) 📚
- [Funzionamento di WinT.c](#funzionamento-di-wintc-) 🛠️
- [Come Giocare](#come-giocare-) 🎲
- [To-Do List](#to-do-list-) ✅
- [Licenza](#licenza-) 📜


## Parole 📚

Le parole sono state prese da [napolux/paroleitaliane](https://github.com/napolux/paroleitaliane) e successivamente organizzate in base alla lunghezza in vari file dall'algoritmo [`Selettore_Parole.c`](Parole/Selettore_Parole.c).

## Funzionamento di WinT.c 🛠️
**Per una descrizione più dettagliata del codice vedere il file [`WinT.c`](WinT.c)**

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

## Come Giocare 🎲

### Su linux 🐧
1. Scaricare la repository.
2. Compilare il codice.
3. Eseguire il programma.

#### Compila il programma
```sh
gcc -o Wint WinT.c
```

#### Esegui il programma con il seguente comando
```sh
./WinT
```

### Su Windows 🪟
1. Scaricare la repository sotto forma di file .zip
2. Estrarre il contenuto
3. Eseguire il file .bat
4. Windows indicherà che l'eseguibile può essere una minaccia, ovviamente non lo è, poichè
   non è stato firmato. Nel file bat inoltre il comando chcp 65001 all'inizio dello script batch .bat    serve per impostare la codifica su UTF-8 e permettere di mostrare le emoji su terminale


## To-Do List ✅

- [ ] Effettuare scrematura delle parole.
- [ ] Ottimizzare l'algoritmo di selezione delle parole.
- [x] Fornire una copia del README in inglese.
- [x] Fornire una copia del codice commentato in inglese.
- [x] Unire il codice Inglese e Italiano.
- [x] Aggiungere la possibilità di inserire la parola da indovinare.
- [x] Fornire la possibilità di eseguire il gioco su terminale Windows.
- [ ] Integrare il [`Selettore Parole.c`](Selettore_Parole.c) nel codice principale in modo che l'utente possa inserire una propria lista di parole e organizzarle in più file automaticamente.


## Licenza 📜

Questo progetto è distribuito sotto la licenza MIT. Ciò significa che è possibile utilizzare, copiare, modificare, unire, pubblicare, distribuire, concedere in sublicenza e/o vendere copie del software, e permettere alle persone a cui il software è fornito di fare lo stesso.

Il software è fornito "così com'è", senza garanzia di alcun tipo, espressa o implicita, incluse ma non limitate alle garanzie di commerciabilità, idoneità per un particolare scopo e non violazione. In nessun caso gli autori o i detentori del copyright saranno responsabili per qualsiasi reclamo, danno o altra responsabilità, sia in un'azione di contratto, torto o altro, derivante da, fuori o in connessione con il software o l'uso o altre operazioni nel software.



# English 🇬🇧
## Wordle In Your Terminal

An Italian and English version of Wordle in your terminal written entirely in C. If the author of Wordle does not approve, the repository will be removed. No code was taken from the original project.

[![Open in Gitpod](https://gitpod.io/button/open-in-gitpod.svg)](https://gitpod.io/#https://github.com/Valerio-Cola/WinT)
You can run the program online with GitPod. You need to log in with GitHub, select Terminal as editor and click continue. Once the shell is open, follow the commands in [How to Play](#how-to-play-) or run ```gcc -o Wint WinT.c && ./WinT```

## Index 📑

- [Words](#words-) 📚
- [Funzionamento di WinT.c](#funzionamento-di-wintc-) 🛠️
- [Come Giocare](#come-giocare-) 🎲
- [To-Do List](#to-do-list-) ✅
- [Licenza](#licenza-) 📜

## Words 📚

The words were taken from [napolux/paroleitaliane](https://github.com/napolux/paroleitaliane) and subsequently organized based on length in various files by the algorithm [`Selettore_Parole.c`](Parole/Selettore_Parole.c ).

## How WinT.c Works 🛠️
**For a more detailed description of the code see the file [`WinT.c`](WinT.c)**

The main algorithm works as follows:

1. **Word length query**: The user specifies the length of the word to guess.
2. **Word selection**: Opens the relevant file by length and chooses a random word.
3. **Start of the game**: Start the game loop with 6 attempts.
4. **User input**: The user's attempt is requested as input, checks will be carried out regarding the existence and length of the input word.
5. **Verification of letters**: At each attempt, the correctness of the individual letters is kept track of using symbols:
    - Correct but in wrong position: `*`
    - Correct and in the right position: `^`
    - Wrong: `-`
6. **Letters tracking**: An array will be used to keep track of letters that are not present in the word.
    - **Note**: If there is only one 'a' in the word and two are written in the attempt, the letter will be inserted into the array to indicate that there are no other 'a's in the word to be guessed.
7. **Print the result**: The word entered in the input is printed aligned with the emojis indicating correctness: 🟩🟨🟥.
8. **End of the game**:
    - If the word was guessed, you exit the game loop.
    - Otherwise, the number of attempts is decremented.

## How to play 🎲

### On linux 🐧
1. Download the repository.
2. Compile the code.
```sh
gcc -o Wint WinT.c
```
3. Run the executable.
```sh
./WinT
```

### On Windows 🪟
1. Download the repository as a .zip file
2. Extract the contents
3. Run the .bat file
4. Windows will indicate that the executable may be a threat, obviously it is not, since
   it was not signed. Furthermore, in the bat file the chcp 65001 command at the beginning of the .bat batch script is used to set the encoding to UTF-8 and allow you to show the emoji on the terminal


## To-Do List ✅

- [ ] Remove the least used words.
- [ ] Optimize the word selection algorithm.
- [x] Provide a copy of the README in English.
- [x] Provide a copy of the commented code in English.
- [x] Merge English-Italian code.
- [x] Add the ability to enter the word to guess.
- [x] Provide the ability to run the game on Windows terminal.
- [ ] Integrate the [`Words_Selector.c`](Words_Selector.c) into the main code so that the user can insert his own list of words and organize them into multiple files automatically.


## License 📜

This project is distributed under the MIT license. This means that you may use, copy, modify, merge, publish, distribute, sublicense and/or sell copies of the software, and permit persons to whom the software is provided to do the same.

The software is provided "as is", without warranty of any kind, express or implied, including but not limited to the warranties of merchantability, fitness for a particular purpose and non-infringement. In no event shall the authors or copyright holders be liable for any claim, damages or other liability, whether in an action of contract, tort or otherwise, arising out of, out of or in connection with the software or the use or other dealings in the software.
