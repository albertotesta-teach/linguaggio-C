# Analisi – 050-problema-normalizza-nome.c

## 1. Problema

In un modulo di iscrizione i nomi vengono scritti con maiuscole e spazi
irregolari. Prima di salvarli la segreteria vuole un formato unico: niente
spazi iniziali e finali, un solo spazio tra le parole, ogni parola con
l'iniziale maiuscola e il resto minuscolo; dopo un apostrofo o un trattino
la lettera torna maiuscola. Il programma normalizza un nome per riga e si
ferma con una riga vuota.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `inserito` | `char[]` | 60 | Testo scritto dall'utente |
| `corretto` | `char[]` | 60 | Testo normalizzato (mai più lungo dell'originale) |
| `parole` | `int` | — | Numero di parole del risultato |

| Funzione | Compito |
|----------|---------|
| `leggi_riga` | Lettura con `fgets` e rimozione del `'\n'` |
| `normalizza` | Costruisce il testo normalizzato in una sola passata |
| `conta_parole` | Conta le parole separate da un solo spazio |
| `maiuscola`, `minuscola` | Conversione di un carattere con la differenza `'a' - 'A'` |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Spazi e maiuscole irregolari

**a) Input** – `  mARIO   de  ROSSI `

**b) Output** – `Mario De Rossi  (3 parole)`

**c) Variabili di supporto** – `i` (lettura), `j` (scrittura), `inizio_parola`

**d) Vincoli** – uno spazio si scrive solo se il carattere precedente in
`dest` non è uno spazio e `dest` non è vuota

**e) Assunzioni** – lettere senza accenti

**f) Algoritmo in linguaggio naturale**
1. Scorrere la stringa con l'indice `i`; `j` indica la prossima cella libera di `dest`.
2. Se il carattere è uno spazio: copiarlo solo se separa due parole e segnare
   che il prossimo carattere apre una parola.
3. Altrimenti scrivere la maiuscola se apre una parola, la minuscola se no.
4. Al termine togliere un eventuale spazio finale e aggiungere `'\0'`.

### Caso d'uso 2 – Apostrofi e trattini

**a) Input** – `anna-maria d'angelo`

**b) Output** – `Anna-Maria D'Angelo  (2 parole)`

**c) Variabili di supporto** – `inizio_parola`

**d) Vincoli** – dopo `'` e `-` `inizio_parola` torna a 1

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – come nel caso 1: dopo aver scritto un
apostrofo o un trattino il carattere successivo è trattato come iniziale.

### Caso d'uso 3 – Fine dell'inserimento

**a) Input** – riga vuota

**b) Output** – "Fine inserimento."

**c) Variabili di supporto** – `inserito[0]`

**d) Vincoli** – una riga vuota contiene solo `'\0'` dopo la rimozione del `'\n'`

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – il ciclo continua finché la lettura
riesce e il primo carattere non è `'\0'`.
