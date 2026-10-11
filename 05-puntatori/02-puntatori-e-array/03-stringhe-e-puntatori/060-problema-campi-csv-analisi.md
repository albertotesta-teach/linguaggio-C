# Analisi – 060-problema-campi-csv.c

## 1. Problema

Il registro elettronico esporta i voti come righe CSV
`cognome;nome;classe;voto`. Il programma scompone ogni riga nei campi,
scarta le righe con un numero di campi diverso da 4 o con un voto non
valido, stampa una tabella dei voti importati e ne calcola la media.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `righe` | `char[][]` | 6 × 60 | Righe CSV da importare |
| `campi` | `char[][]` | 4 × 16 | Campi della riga corrente |
| `p` | `const char *` | — | Carattere esaminato della riga |
| `dest` | `char *` | — | Prossima posizione libera nel campo corrente |
| `voto`, `somma` | `double` | — | Voto convertito, somma per la media |

| Funzione | Compito |
|----------|---------|
| `dividi_riga(riga, campi)` | Copia i campi e restituisce quanti sono |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Riga corretta

**a) Input** – `Rossi;Mario;4B;7.5`

**b) Output** – `Rossi  Mario  4B  7.50`

**c) Variabili di supporto** – `p`, `dest`, `numero`

**d) Vincoli** – ogni campo si termina con `'\0'`; i caratteri oltre 15 si
ignorano

**e) Assunzioni** – il separatore è sempre `;`

**f) Algoritmo in linguaggio naturale**
1. `dest` punta all'inizio di `campi[0]`.
2. Ogni carattere diverso da `;` si copia in `*dest` e `dest` avanza.
3. Con `;` si termina il campo, si incrementa `numero` e `dest` passa
   all'inizio del campo successivo.

### Caso d'uso 2 – Numero di campi sbagliato

**a) Input** – `Verdi;Paolo;4B`; `Gallo;Anna;4B;9;assente`

**b) Output** – "3 campi invece di 4"; "5 campi invece di 4"

**c) Variabili di supporto** – `numero`

**d) Vincoli** – oltre il quarto campo si conta ma non si copia: l'array
`campi` non viene mai superato

**e) Assunzioni** – i campi sono uno in più dei `;`

**f) Algoritmo in linguaggio naturale** – la funzione restituisce
`numero + 1`; il main scarta la riga se il risultato è diverso da 4.

### Caso d'uso 3 – Voto non numerico

**a) Input** – `Neri;Sara;4B;sei`

**b) Output** – `voto non valido "sei"`; media finale 7.25 sulle 3 righe
importate

**c) Variabili di supporto** – `voto`, `importate`

**d) Vincoli** – il voto deve essere tra 1 e 10

**e) Assunzioni** – il voto usa il punto decimale

**f) Algoritmo in linguaggio naturale** – convertire con `sscanf("%lf")`;
se la conversione fallisce o il valore è fuori intervallo, scartare la riga.
