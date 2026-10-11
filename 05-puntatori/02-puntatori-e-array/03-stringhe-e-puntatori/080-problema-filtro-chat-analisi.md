# Analisi – 080-problema-filtro-chat.c

## 1. Problema

La chat di classe della piattaforma scolastica deve sostituire con
asterischi le parole di un elenco di parole vietate, senza distinguere
maiuscole e minuscole, prima di pubblicare un messaggio. Per ogni messaggio
si indicano le parole filtrate e alla fine il totale della sessione. Una
riga vuota termina.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `vietate` | `char[][]` | 3 × 12 | Parole vietate, in minuscolo |
| `messaggio` | `char[]` | 120 | Messaggio letto con `fgets` |
| `copia` | `char[]` | 120 | Messaggio in minuscolo, per la ricerca |
| `trovato` | `const char *` | — | Occorrenza trovata da `strstr` nella copia |
| `q`, `fine` | `char *` | — | Caratteri da sostituire nel messaggio originale |

| Funzione | Compito |
|----------|---------|
| `censura(messaggio, parole, n)` | Sostituisce le occorrenze e le conta |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Maiuscole e più occorrenze

**a) Input** – `Sei proprio uno SCEMO, anzi uno scemo stupido`

**b) Output** – `Sei proprio uno *****, anzi uno ***** *******` (3 parole filtrate)

**c) Variabili di supporto** – `copia`, `trovato`

**d) Vincoli** – la posizione `trovato - copia` è la stessa nel messaggio
originale, perché la copia ha la stessa lunghezza

**e) Assunzioni** – le parole vietate sono scritte in minuscolo

**f) Algoritmo in linguaggio naturale**
1. Costruire `copia` con `tolower` carattere per carattere.
2. Per ogni parola vietata cercarla con `strstr(copia, parola)`.
3. Per ogni occorrenza scrivere `'*'` da `messaggio + (trovato - copia)` per
   la lunghezza della parola, poi cercare di nuovo da `trovato + lunghezza`.

### Caso d'uso 2 – Messaggio pulito

**a) Input** – `Domani verifica di matematica`

**b) Output** – messaggio pubblicato senza modifiche

**c) Variabili di supporto** – `sostituite` = 0

**d) Vincoli** – nessuno

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – `strstr` restituisce `NULL` per
tutte le parole: nessuna sostituzione.

### Caso d'uso 3 – Totale della sessione

**a) Input** – quattro messaggi, poi riga vuota

**b) Output** – "Parole filtrate nella sessione: 4"

**c) Variabili di supporto** – `totale`

**d) Vincoli** – singolare e plurale ("1 parola filtrata")

**e) Assunzioni** – il filtro trova la parola anche dentro una parola più
lunga ("scemotto")

**f) Algoritmo in linguaggio naturale** – sommare a `totale` il valore
restituito da `censura` per ogni messaggio.
