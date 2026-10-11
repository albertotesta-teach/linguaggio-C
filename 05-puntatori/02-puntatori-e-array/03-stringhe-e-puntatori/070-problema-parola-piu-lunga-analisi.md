# Analisi – 070-problema-parola-piu-lunga.c

## 1. Problema

La redazione del giornalino scolastico vuole controllare che i titoli
stiano nelle colonne: per ogni titolo il programma conta le parole, trova
la parola più lunga con la sua posizione e segnala quelle che superano 12
lettere.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `titoli` | `char[][]` | 4 × 80 | Titoli da controllare |
| `migliore` | `const char *` | — | Inizio della parola più lunga nel titolo |
| `lunghezza` | `int` | — | Lettere della parola più lunga |
| `parola` | `const char *` | — | Inizio della parola esaminata |

| Funzione | Compito |
|----------|---------|
| `parola_piu_lunga(testo, &lunghezza)` | Posizione della parola più lunga, lunghezza come parametro OUT |
| `conta_parole(testo)` | Numero di parole |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Parola più lunga

**a) Input** – `Torneo di pallavolo: vince la 4B`

**b) Output** – 6 parole, la più lunga "pallavolo" (9 lettere, posizione 10)

**c) Variabili di supporto** – `parola`, `p`, `migliore`

**d) Vincoli** – la parola non si copia: si stampa con
`printf("%.*s", lunghezza, migliore)`

**e) Assunzioni** – a parità di lunghezza vale la prima

**f) Algoritmo in linguaggio naturale**
1. All'inizio di una parola salvare `parola = p` e avanzare fino alla prima
   non-lettera.
2. Se `p - parola` supera la lunghezza migliore, aggiornare lunghezza e
   `migliore`.
3. Restituire `migliore - testo`; il main calcola `titoli[t] + posizione`.

### Caso d'uso 2 – Parola oltre il limite

**a) Input** – `Laboratorio di elettrotecnica aperto al pomeriggio`

**b) Output** – "elettrotecnica" (14 lettere) e l'avviso "troppo lunga per
la colonna"

**c) Variabili di supporto** – `lunghezza`

**d) Vincoli** – limite 12 lettere

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – confrontare la lunghezza trovata con
`LIMITE`.

### Caso d'uso 3 – Conteggio delle parole

**a) Input** – `Gita a Torino, si parte lunedi`

**b) Output** – 6 parole

**c) Variabili di supporto** – `p`, `*(p - 1)`

**d) Vincoli** – `*(p - 1)` si legge solo se `p` non è il primo carattere

**e) Assunzioni** – le cifre non sono lettere ("4B" conta come la parola "B")

**f) Algoritmo in linguaggio naturale** – una parola inizia dove c'è una
lettera preceduta da una non-lettera o dall'inizio del testo.
