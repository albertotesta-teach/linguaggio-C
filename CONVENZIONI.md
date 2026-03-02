# Convenzioni del progetto linguaggio-C

Questo file definisce le regole e i criteri da seguire nella creazione e
manutenzione di tutti gli esempi didattici del repository. Va letto all'inizio
di ogni sessione di lavoro per garantire coerenza tra i contributi.

---

## 1. Struttura generale del repository

```
linguaggio-C/
├── CONVENZIONI.md               ← questo file
├── 01-introduzione/
├── 02-controllo-del-flusso/
├── 03-funzioni/
├── 04-array-e-stringhe/
│   ├── 01-array-monodimensionali/
│   ├── 02-array-multidimensionali/
│   ├── 03-stringhe/
│   │   ├── 01-dichiarazione-e-inizializzazione/
│   │   │   ├── 010-stringa-base.c
│   │   │   ├── 020-inizializzazione.c
│   │   │   ├── ...
│   │   │   ├── README.md
│   │   │   └── analisi.md        ← solo per esercizi "problema specifico"
│   │   └── 02-input-output-stringhe/
│   └── 04-funzioni-su-stringhe/
├── 05-puntatori/
└── ...
```

Ogni argomento ha la propria cartella numerata. All'interno, ogni esempio
occupa una sottocartella dedicata contenente i file `.c`, il `README.md` e,
dove previsto, il file `analisi.md`.

---

## 2. Nomenclatura dei file

### File sorgente `.c`
- Numerazione a **tre cifre**, multipli di 10: `010-`, `020-`, `030-`, ...
- Il passo di 10 lascia spazio per inserire esempi intermedi in futuro.
- Il nome è descrittivo e in italiano, con parole separate da `-`.

```
010-stringa-base.c
020-inizializzazione.c
030-memoria-e-terminatore.c
040-problema-reale.c
```

### Cartelle degli esempi
- Numerazione a due cifre con passo 1: `01-`, `02-`, `03-`, ...
- Nome descrittivo in italiano, parole separate da `-`.

```
01-dichiarazione-e-inizializzazione/
02-input-output-stringhe/
03-lunghezza-e-accesso-ai-caratteri/
```

---

## 3. Tipologie di esercizi

Gli esercizi si dividono in due categorie (la distinzione non è resa esplicita
allo studente, ma guida la struttura dei file prodotti):

| Tipologia | Descrizione | File richiesti |
|-----------|-------------|----------------|
| **Concetto base** | Illustra un costrutto o meccanismo del linguaggio | `.c`, `README.md` |
| **Problema specifico** | Risolve un problema reale con un contesto applicativo | `.c`, `README.md`, `analisi.md` |

**Criteri per classificare un esercizio come "problema specifico":**
- Ha un contesto applicativo riconoscibile (anagrafica, magazzino, rete, ecc.)
- Richiede la scelta di strutture dati e algoritmi
- Ha casi d'uso distinti e verificabili
- Produce un output significativo oltre la semplice dimostrazione sintattica

---

## 4. Struttura del file `analisi.md`

Presente **solo** per gli esercizi di tipo "problema specifico".

```markdown
# Analisi – <nome-file>.c

## 1. Problema
Descrizione del problema reale da risolvere.

## 2. Analisi generale e struttura dati
Variabili principali con tipo, dimensione e motivazione della scelta.

## 3. Casi d'uso e funzionalità
Per ciascun caso d'uso:

### Caso d'uso N – <titolo>
**a) Input** – dati in ingresso
**b) Output** – risultato atteso
**c) Variabili di supporto** – variabili ausiliarie necessarie
**d) Vincoli** – condizioni che devono essere sempre vere
**e) Assunzioni** – ipotesi fatte sui dati o sul contesto
**f) Algoritmo in linguaggio naturale** – passi della soluzione
```

---

## 5. Struttura del file `README.md`

Obbligatorio per ogni cartella esempio. Sezioni obbligatorie:

```markdown
# <NN> – <Titolo dell'esempio>

## Concetto
Spiegazione teorica del costrutto o problema trattato,
con schema o diagramma ASCII se utile.

## File dell'esempio
Tabella con nome file e breve descrizione del contenuto.
Includere analisi.md nella tabella se presente.

## Compilazione ed esecuzione
Comandi gcc per ogni file, senza Makefile.
Formato: gcc -Wall -o <nome> <nome>.c

## Output atteso
Output esatto per ogni file .c, dentro blocchi di codice.

## Errori comuni da evitare
Esempi di codice sbagliato commentati, con spiegazione dell'errore.

## Concetti collegati
Link ad altri esempi del repository correlati al tema.

## Esercizi proposti
Almeno 3 esercizi graduati per difficoltà, con riferimento
ai concetti dell'esempio.
```

---

## 6. Standard del codice C

### Intestazione obbligatoria
Ogni file `.c` inizia con un blocco commento strutturato:

```c
/*
 * <nome-file>.c
 *
 * <Titolo breve dell'esempio>
 *
 * <Descrizione estesa: cosa fa il file, perché è utile,
 *  quale concetto illustra o quale problema risolve.>
 */
```

### Stile dei commenti
- **Commenti didattici abbondanti**, riga per riga dove necessario.
- Ogni blocco logico è preceduto da un commento che spiega il "perché",
  non solo il "cosa".
- Gli errori comuni vengono mostrati in forma commentata nel codice stesso.
- Lingua: **italiano** per tutti i commenti e i messaggi a schermo.

### Indentazione e formattazione
- Indentazione: **4 spazi** (non tab).
- Apertura delle graffe: stessa riga per `if`, `while`, `for`; riga successiva per `main` e funzioni.
- Una istruzione per riga.
- Variabili dichiarate all'inizio del blocco (compatibilità C89/C90 dove possibile).
- Riga vuota tra blocchi logici distinti.

### Dichiarazioni
- `main` sempre dichiarato come `int main(void)`.
- Variabili con nomi descrittivi in italiano, parole separate da `_`.
- Costanti con `#define` in MAIUSCOLO.

### Regole di struttura del codice
- **Niente `break` nei cicli**: `break` è consentito esclusivamente nelle istruzioni
  `switch/case`. Nei cicli si controlla il flusso tramite la condizione del ciclo
  o variabili booleane di supporto (es. `trovato`, `valido`, `fine`).
- **Niente `continue`**: il flusso all'interno di un ciclo deve essere gestito
  tramite `if/else`, non saltando iterazioni con `continue`.
- **Una sola `return` per funzione**: ogni funzione ha un unico punto di uscita,
  alla fine del corpo. Il risultato viene accumulato in una variabile locale
  e restituito nell'unica `return` finale. Questo migliora la leggibilità
  e facilita il debug e la manutenzione.

```c
/* CORRETTO: una sola return, condizione nel ciclo */
int cerca(char stringa[], char c) {
    int i = 0;
    int trovato = 0;
    while (stringa[i] != '\0' && !trovato) {
        if (stringa[i] == c) {
            trovato = 1;
        }
        i++;
    }
    return trovato;
}

/* ERRATO: return multipli e break nel ciclo */
int cerca(char stringa[], char c) {
    for (int i = 0; stringa[i] != '\0'; i++) {
        if (stringa[i] == c) {
            return 1;   /* return anticipato: vietato */
        }
    }
    return 0;
}
```

### Compilazione
- Tutti gli esempi devono compilare senza warning con:
  ```bash
  gcc -Wall -Wextra -o <nome> <nome>.c
  ```
- Non usare funzioni deprecate o non standard senza esplicita motivazione didattica.

---

## 7. Criteri per la scelta degli esempi e dei problemi reali

### Principi generali
- Ogni esempio deve essere **autonomo e compilabile** senza dipendenze esterne.
- Il problema reale deve essere **riconoscibile e motivante** per uno studente
  di istituto tecnico o primo anno universitario.
- Preferire contesti italiani (codice fiscale, targhe, CAP, ecc.) per
  aumentare la familiarità.

### Progressione della difficoltà
All'interno di ogni cartella esempio, i file seguono una progressione:
- `010-` → concetto minimo, nessuna complessità aggiuntiva
- `020-`, `030-` → varianti e approfondimenti del concetto
- `040-` e oltre → problema reale che integra tutto quanto visto

### Nomenclatura dei file "problema"
I file di tipo "problema specifico" devono avere un nome che identifichi
chiaramente il problema trattato, mai un nome generico come `problema-reale`.
Il nome segue il pattern `NNN-problema-<descrizione-specifica>.c`.

```
✓ 040-problema-codice-fiscale.c
✓ 050-problema-verifica-targa.c
✓ 060-problema-parsing-email.c
✗ 040-problema-reale.c        ← troppo generico
✗ 040-problema.c              ← non descrive nulla
```

### Contesti applicativi preferiti
Per rendere gli esempi concreti si privilegiano questi ambiti:
- **Anagrafica e scuola**: nomi, codici fiscali, voti, classi
- **Magazzino e prodotti**: codici prodotto, prezzi, quantità
- **Sistemi e reti**: indirizzi IP, porte, percorsi file, log
- **Testo e comunicazione**: messaggi, password, validazione input
- **Dati scientifici**: misure, conversioni, elaborazione sequenze

---

## 8. Configurazione CMake per CLion

Il progetto viene sviluppato ed eseguito con **CLion** (JetBrains), che utilizza
**CMake** come sistema di build. Per far apparire il tasto play accanto a ogni
file `.c`, ogni file deve essere registrato come target nel `CMakeLists.txt`.

### Struttura dei file CMake

```
linguaggio-C/
├── CMakeLists.txt                        ← radice: configurazione globale + add_subdirectory
└── 04-array-e-stringhe/
    └── 03-stringhe/
        └── 01-dichiarazione-e-inizializzazione/
            └── CMakeLists.txt            ← esempio: un add_executable per ogni .c
```

### CMakeLists.txt radice
Contiene la configurazione globale del progetto e un `add_subdirectory` per
ogni cartella esempio. Va aggiornato ogni volta che si aggiunge una nuova
cartella esempio.

```cmake
cmake_minimum_required(VERSION 3.20)
project(linguaggio-C C)

set(CMAKE_C_STANDARD 11)
add_compile_options(-Wall -Wextra)

add_subdirectory(04-array-e-stringhe/03-stringhe/01-dichiarazione-e-inizializzazione)
# aggiungere qui le nuove cartelle esempio
```

### CMakeLists.txt per cartella esempio
Un `add_executable` per ogni file `.c`. Il nome del target coincide con il
nome del file senza estensione.

```cmake
cmake_minimum_required(VERSION 3.20)

add_executable(010-stringa-base          010-stringa-base.c)
add_executable(020-inizializzazione      020-inizializzazione.c)
add_executable(030-memoria-e-terminatore 030-memoria-e-terminatore.c)
add_executable(040-problema-reale        040-problema-reale.c)
```

### Aggiornamento dopo ogni nuovo esempio
Ogni volta che si aggiunge una nuova cartella esempio occorre:
1. Creare il `CMakeLists.txt` nella cartella esempio con i target.
2. Aggiungere `add_subdirectory(...)` al `CMakeLists.txt` radice.
3. Ricaricare il progetto CMake in CLion con uno di questi metodi (in ordine di preferenza):
   - CLion mostra automaticamente una notifica in alto nel file: cliccare **Reload**
   - Tasto destro sul `CMakeLists.txt` nel pannello Project → **Load CMake Project**
   - **File → Reload CMake Project**

---

## 9. Lingua

- **Tutto in italiano**: commenti, messaggi a schermo, nomi di variabili,
  testo del README e dell'analisi.
- Eccezione: parole chiave del linguaggio C e nomi di funzioni standard
  restano in inglese (es. `malloc`, `strlen`, `printf`).

---

## 10. Checklist prima di considerare un esempio completo

- [ ] `CMakeLists.txt` della cartella esempio aggiornato con i nuovi target
- [ ] `CMakeLists.txt` radice aggiornato con `add_subdirectory`
- [ ] File `.c` numerati correttamente (tre cifre, multipli di 10)
- [ ] Intestazione presente in ogni file `.c`
- [ ] Commenti didattici presenti e in italiano
- [ ] Compilazione senza warning con `gcc -Wall -Wextra`
- [ ] Nessun `break` fuori da `switch/case`
- [ ] Nessun `continue`
- [ ] Una sola `return` per funzione
- [ ] `README.md` con tutte le sezioni obbligatorie
- [ ] Output atteso verificato ed esatto
- [ ] File `<nome-esercizio>-analisi.md` presente se l'esercizio è di tipo "problema specifico"
- [ ] Almeno 3 esercizi proposti nel README
