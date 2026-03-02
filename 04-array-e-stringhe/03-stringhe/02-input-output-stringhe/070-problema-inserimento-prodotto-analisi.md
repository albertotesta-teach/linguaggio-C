# Analisi – 070-problema-inserimento-prodotto.c

## 1. Problema

Un operatore di magazzino usa un terminale per inserire nuovi prodotti
nell'archivio. Il programma legge codice, nome (con possibili spazi),
categoria, prezzo e quantità, verifica che i campi obbligatori non siano
vuoti e stampa la scheda prodotto pronta per l'archiviazione.

---

## 2. Analisi generale e struttura dati

| Variabile         | Tipo     | Dimensione | Motivazione                                           |
|-------------------|----------|------------|-------------------------------------------------------|
| `nome_prodotto`   | `char[]` | 81         | Nome con spazi, max 80 caratteri + `'\0'`             |
| `categoria`       | `char[]` | 21         | Categoria con spazi, max 20 caratteri + `'\0'`        |
| `codice`          | `char[]` | 10         | Formato XXX-NNN, senza spazi, max 9 caratteri + `'\0'`|
| `prezzo`          | `char[]` | 10         | Prezzo come stringa (es. "12.50"), max 9 + `'\0'`     |
| `quantita`        | `int`    | —          | Numero intero di unità disponibili                    |
| `i`               | `int`    | —          | Indice per rimozione `'\n'` da fgets                  |
| `nome_valido`     | `int`    | —          | Flag: 1 = nome non vuoto, 0 = vuoto                   |
| `categoria_valida`| `int`    | —          | Flag: 1 = categoria non vuota, 0 = vuota              |

---

## 3. Casi d'uso e funzionalità

---

### Caso d'uso 1 – Lettura dei campi del prodotto

**a) Input**
Dati inseriti dall'operatore da tastiera: codice (senza spazi),
nome (con spazi), categoria (con spazi), prezzo (senza spazi), quantità.

**b) Output**
Nessun output diretto: i valori sono memorizzati nelle variabili.

**c) Variabili di supporto**
- `i` (`int`): indice per rimozione `'\n'` dopo ogni `fgets`.
- Blocco locale `c` (`int`): usato per svuotare il buffer dopo `scanf`.

**d) Vincoli**
- Dopo ogni `scanf` che precede una `fgets`, il buffer deve essere svuotato
  consumando il `'\n'` residuo con un ciclo `while` su `getchar()`.
- Ogni `fgets` deve essere seguita dalla rimozione del `'\n'`.

**e) Assunzioni**
- Il prezzo viene letto come stringa per evitare problemi con il separatore
  decimale (punto vs virgola a seconda del locale di sistema).
- La quantità è sempre un intero non negativo.

**f) Algoritmo in linguaggio naturale**
```
1. Leggere codice con scanf("%9s", codice).
2. Svuotare il buffer: leggere con getchar() fino a '\n' o EOF.
3. Leggere nome_prodotto con fgets; rimuovere '\n'.
4. Leggere categoria con fgets; rimuovere '\n'.
5. Leggere prezzo con scanf("%9s", prezzo).
6. Leggere quantita con scanf("%d", &quantita).
```

---

### Caso d'uso 2 – Validazione dei campi obbligatori

**a) Input**
`nome_prodotto[0]` e `categoria[0]` dopo la rimozione del `'\n'`.

**b) Output**
Nessun output diretto: imposta `nome_valido` e `categoria_valida`.

**c) Variabili di supporto**
- `nome_valido` e `categoria_valida` (`int`): flags di risultato.

**d) Vincoli**
- Una stringa vuota ha il primo carattere uguale a `'\0'` dopo
  la rimozione del `'\n'`.

**e) Assunzioni**
- Codice, prezzo e quantità non sono validati (semplificazione didattica).

**f) Algoritmo in linguaggio naturale**
```
1. Se nome_prodotto[0] è '\0': nome_valido = 0. Altrimenti: nome_valido = 1.
2. Se categoria[0] è '\0': categoria_valida = 0. Altrimenti: categoria_valida = 1.
```

---

### Caso d'uso 3 – Output scheda prodotto o messaggio di errore

**a) Input**
`nome_valido`, `categoria_valida` e tutti i campi del prodotto.

**b) Output**
Se valido:
```
════════════════════════════════════════════════
  SCHEDA PRODOTTO - PRONTA PER L'ARCHIVIAZIONE
════════════════════════════════════════════════
  Codice      : ELE-042
  Nome        : Cavo HDMI 2m
  Categoria   : Elettronica Consumer
  Prezzo      : 12.50 EUR
  Disponibile : 25 pz
════════════════════════════════════════════════

Prodotto inserito correttamente nell'archivio.
```
Se non valido, messaggio con indicazione dei campi mancanti.

**c) Variabili di supporto**
Nessuna variabile aggiuntiva.

**d) Vincoli**
- La scheda viene stampata solo se entrambi i flag sono 1.
- I messaggi di errore indicano specificatamente quale campo è mancante.

**e) Assunzioni**
- Il salvataggio nell'archivio è simulato (non viene scritto alcun file).

**f) Algoritmo in linguaggio naturale**
```
1. Se nome_valido è 1 E categoria_valida è 1:
   a. Stampare la scheda prodotto con tutti i campi.
   b. Stampare conferma di inserimento.
2. Altrimenti:
   a. Stampare messaggio di errore generale.
   b. Se nome_valido è 0: segnalare il campo nome.
   c. Se categoria_valida è 0: segnalare il campo categoria.
   d. Stampare "Inserimento annullato".
```
