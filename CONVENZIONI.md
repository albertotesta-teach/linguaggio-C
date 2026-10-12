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
│   ├── 01-logica-booleana/
│   ├── 02-if-else/
│   ├── 03-switch/
│   ├── 04-while-do-while/
│   ├── 05-for/
│   └── 06-break-continue/
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
│   │   │   └── <nome-esercizio>-analisi.md  ← solo per esercizi "problema specifico"
│   │   └── 02-input-output-stringhe/
│   └── 04-funzioni-su-stringhe/
│       ├── 01-funzioni-scritte-a-mano/
│       ├── 02-libreria-string-h/
│       ├── 03-ricerca-nelle-stringhe/
│       ├── 04-caratteri-e-conversioni/
│       └── 05-array-di-stringhe/
├── 05-puntatori/
│   ├── 01-introduzione-ai-puntatori/
│   │   ├── 01-indirizzi-e-memoria/
│   │   ├── 02-dichiarazione-e-dereferenziazione/
│   │   └── 03-errori-e-puntatori-sicuri/
│   ├── 02-puntatori-e-array/
│   │   ├── 01-aritmetica-dei-puntatori/
│   │   ├── 02-array-come-puntatori/
│   │   └── 03-stringhe-e-puntatori/
│   ├── 03-puntatori-e-funzioni/
│   │   ├── 01-parametri-per-riferimento/
│   │   ├── 02-funzioni-che-restituiscono-puntatori/
│   │   └── 03-puntatori-a-funzione/
│   └── 04-puntatori-a-puntatori/
│       ├── 01-doppio-puntatore/
│       ├── 02-array-di-puntatori/
│       └── 03-matrici-e-puntatori/
├── 06-strutture-e-unioni/
│   ├── 01-typedef/
│   │   ├── 01-alias-di-tipi-base/
│   │   ├── 02-typedef-di-array/
│   │   └── 03-typedef-di-puntatori-a-funzione/
│   ├── 02-struct/
│   │   ├── 01-dichiarazione-e-accesso/
│   │   ├── 02-assegnamento-e-confronto/
│   │   └── 03-array-di-struct/
│   ├── 03-struct-e-funzioni/
│   │   ├── 01-struct-per-valore/
│   │   ├── 02-puntatori-a-struct/
│   │   └── 03-array-di-struct-e-funzioni/
│   └── 04-struct-annidate/
│       ├── 01-struct-dentro-struct/
│       ├── 02-funzioni-e-struct-annidate/
│       └── 03-array-e-struct-annidate/
└── ...
```

Ogni argomento ha la propria cartella numerata. All'interno, ogni esempio
occupa una sottocartella dedicata contenente i file `.c`, il `README.md` e,
dove previsto, i file `<nome-esercizio>-analisi.md`.

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
040-problema-codice-fiscale.c
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
Il file si chiama `<nome-esercizio>-analisi.md` (stesso nome del sorgente,
senza `.c`, seguito da `-analisi.md`) e sta nella stessa cartella del `.c`:

```
040-problema-codice-fiscale.c
040-problema-codice-fiscale-analisi.md
```

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
- Tipi definiti con `typedef` (dal capitolo `06-strutture-e-unioni`): nome in
  italiano con **iniziale maiuscola**, senza suffisso `_t` (riservato da POSIX):
  `typedef int Voto;`, `typedef struct { ... } Studente;`. Le variabili restano
  in minuscolo: `Studente studente;`.

### Regole di struttura del codice
- **Niente `break` nei cicli**: `break` è consentito esclusivamente nelle istruzioni
  `switch/case`. Nei cicli si controlla il flusso tramite la condizione del ciclo
  o variabili booleane di supporto (es. `trovato`, `valido`, `fine`).
- **Niente `continue`**: il flusso all'interno di un ciclo deve essere gestito
  tramite `if/else`, non saltando iterazioni con `continue`.
- **Unica eccezione dichiarata**: `02-controllo-del-flusso/06-break-continue/010-break-e-continue.c`
  mostra `break` nei cicli e `continue` nel codice eseguibile per spiegarne il
  funzionamento; ogni uso è marcato nei commenti come "DA NON IMITARE".
  Negli altri file della sezione le versioni con `break`/`continue` compaiono
  solo nei commenti, a confronto con quelle corrette.
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

## 7. Vincoli per capitolo

Ogni capitolo introduce solo i costrutti già trattati nei capitoli precedenti.
I vincoli seguenti definiscono cosa **non** è ancora disponibile in ciascun
capitolo e devono essere rispettati in tutti i file `.c` e nei problemi specifici.

| Capitolo | Costrutti NON ancora disponibili |
|----------|----------------------------------|
| `01-introduzione` | array, stringhe (char[]), puntatori, funzioni definite dall'utente, struct |
| `02-controllo-del-flusso` | array, stringhe, puntatori, funzioni definite dall'utente, struct; inoltre ogni sezione usa solo i costrutti delle sezioni precedenti (`01-logica-booleana` senza `if` né cicli, `02-if-else` senza `switch` né cicli, `03-switch` senza cicli, `04-while-do-while` senza `for`) |
| `03-funzioni` | array, stringhe, struct; puntatori ammessi **solo** dalla sezione `03-passaggio-per-riferimento` in poi, limitati a `&`, `*` e parametri per riferimento |
| `04-array-e-stringhe` | puntatori oltre al passaggio per riferimento (aritmetica dei puntatori, puntatori e array), struct, allocazione dinamica; `<string.h>` e `<ctype.h>` solo da `04-funzioni-su-stringhe` in poi. In quel sottocapitolo il puntatore restituito da `strchr`, `strrchr` e `strstr` si usa solo nel confronto con `NULL` (la posizione si ottiene con funzioni scritte a mano che restituiscono l'indice); `strtok` escluso |
| `05-puntatori` | struct, allocazione dinamica; `void *` solo come conversione per stampare indirizzi con `%p`; l'aritmetica dei puntatori solo da `02-puntatori-e-array` in poi; in `02-puntatori-e-array` niente funzioni che restituiscono puntatori, doppi puntatori e array di puntatori (sottocapitoli 03 e 04); in `03-puntatori-e-funzioni` niente doppi puntatori, array di puntatori (anche di puntatori a funzione), `typedef`, `qsort` e `void *`; in `04-puntatori-a-puntatori` niente `main(int argc, char *argv[])` (capitolo 12) e niente algoritmi di ordinamento completi (capitolo 11) |
| `06-strutture-e-unioni` | allocazione dinamica (`malloc`, `calloc`, `realloc`, `free`), liste concatenate e altre strutture autoreferenziali; ogni sottocapitolo usa solo quelli precedenti, nell'ordine `01-typedef` (senza struct, enum e union), `02-struct` (senza struct come parametri o valori restituiti, senza `->` e senza struct annidate; in `01-dichiarazione-e-accesso` niente assegnamento tra struct intere, in `01` e `02` niente array di struct), `03-struct-e-funzioni` (senza struct annidate, enum, union e `qsort`; in `01-struct-per-valore` niente `->`), `04-struct-annidate` (senza enum, union e struct che contengono un puntatore al proprio tipo), `05-enum` (senza union), `06-union` |
| `07-memoria-dinamica` | liste concatenate, pile, code e alberi (capitolo 10) |

**Principio generale:** se un costrutto non è ancora stato introdotto nel
percorso didattico, non deve comparire negli esempi del capitolo corrente,
nemmeno in forma implicita o semplificata.

---

## 8. Criteri per la scelta degli esempi e dei problemi reali

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

## 9. Configurazione CMake per CLion

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
Un `add_executable` per ogni file `.c`. I nomi dei target devono essere
**unici in tutto il progetto**: dal capitolo 02 in poi il nome è formato dal
prefisso `<capitolo>-<sezione>-` seguito dal nome del file senza estensione
(es. `02-05-010-for-base`). Se un file usa `<math.h>` si aggiunge
`target_link_libraries(<target> m)`, necessario su Linux.

```cmake
cmake_minimum_required(VERSION 3.20)

add_executable(010-stringa-base          010-stringa-base.c)
add_executable(020-inizializzazione      020-inizializzazione.c)
add_executable(030-memoria-e-terminatore 030-memoria-e-terminatore.c)
add_executable(040-problema-codice-fiscale 040-problema-codice-fiscale.c)
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

## 10. Lingua

- **Tutto in italiano**: commenti, messaggi a schermo, nomi di variabili,
  testo del README e dell'analisi.
- Eccezione: parole chiave del linguaggio C e nomi di funzioni standard
  restano in inglese (es. `malloc`, `strlen`, `printf`).

---

## 11. Checklist prima di considerare un esempio completo

- [ ] `CMakeLists.txt` della cartella esempio aggiornato con i nuovi target
- [ ] `CMakeLists.txt` radice aggiornato con `add_subdirectory`
- [ ] File `.c` numerati correttamente (tre cifre, multipli di 10)
- [ ] Intestazione presente in ogni file `.c`
- [ ] Commenti didattici presenti e in italiano
- [ ] Compilazione senza warning con `gcc -Wall -Wextra`
- [ ] Nessun `break` fuori da `switch/case`
- [ ] Nessun `continue`
- [ ] Una sola `return` per funzione
- [ ] Rispettati i vincoli per capitolo (sezione 7)
- [ ] `README.md` con tutte le sezioni obbligatorie
- [ ] Output atteso verificato ed esatto
- [ ] File `<nome-esercizio>-analisi.md` presente se l'esercizio è di tipo "problema specifico"
- [ ] Almeno 3 problemi specifici per sezione
- [ ] Nessun eseguibile compilato aggiunto al repository (`git status` pulito)

---

## 12. Presentazioni

### Flusso di lavoro
- Le presentazioni si generano in **Gamma**, direttamente da Claude tramite il
  collegamento a Gamma, con il tema personalizzato **"Modello T"**.
- La presentazione viene poi esportata in `.pptx` e `.pdf` e salvata nella
  cartella `00-Documentazione/` alla radice del repository.
- Il `GAMMA-PROMPT.md` del capitolo 01 resta come archivio del vecchio flusso
  (prompt copiato a mano in Gamma).
- Nome del file: `Linguaggio-C-<codice>-<Titolo-Con-Trattini>.pptx`, dove il
  codice è il numero del capitolo (`01`) oppure capitolo + sezione (`0401`).

```
00-Documentazione/
├── Linguaggio-C-01-Introduzione.pptx
├── Linguaggio-C-01-Introduzione.pdf
├── Linguaggio-C-0401-Gli-Array-Monodimensionali-in-C.pptx
└── Linguaggio-C-0401-Gli-Array-Monodimensionali-in-C.pdf
```

### Stile grafico (uguale alle presentazioni già realizzate)
- Tema Gamma "Modello T": sfondo chiaro, riquadri di evidenza verdi.
- Titoli in Verdana grassetto, testo in Verdana, codice in Consolas.
- Tutto il testo allineato a sinistra; impostazioni identiche su tutte le slide.
- Contenuto delle slide allineato in alto (allineamento verticale "inizio"),
  così il titolo è sempre nella stessa posizione; fa eccezione la copertina,
  che resta centrata.
- Nessuna immagine decorativa o di sfondo: solo elementi visivi utili alla
  comprensione (tabelle a celle per gli array, schemi di memoria, codice).
  Fa eccezione l'immagine della slide di copertina.
- Schemi di memoria, frecce dei puntatori e disposizioni di array non si
  disegnano con caratteri ASCII né con tabelle o riquadri di Gamma: si
  generano come immagini PNG con uno script Python (matplotlib) nei colori del
  tema e si salvano in `00-Documentazione/immagini/` insieme allo script
  (`diagrammi-<codice>.py`, immagini `<codice>-<nome>.png`). Dopo il push
  vengono inserite nella slide dall'URL `raw.githubusercontent.com` del
  repository.
- Gli indirizzi di memoria si scrivono in esadecimale come li stampa `%p`
  (`0x7ffd5e8a2eec`); se abbreviati alle ultime cifre (`...eec`), lo schema
  lo spiega in una legenda.

### Struttura della presentazione
1. **Copertina**: titolo, sottotitolo con gli argomenti, etichette di tema.
2. **Slide teoriche**, una per concetto, nell'ordine delle sezioni del
   capitolo: spiegazione, schema o tabella, frammento di codice, riquadro verde
   con la regola chiave o l'errore tipico.
3. **Errori comuni da evitare**: schede numerate.
4. **Riepilogo concetti**: tabella Operazione / Tecnica / Note.
5. **Esempi pratici**, per ogni sezione due slide:
   - file concetto base (010, 020, 030) in tre colonne numerate, ciascuna con
     nome del file, *Problema* e *Tecnica*;
   - file problema (040 e successivi) come schede affiancate con numero, titolo
     e descrizione breve; l'ultimo problema su una barra a tutta larghezza.
