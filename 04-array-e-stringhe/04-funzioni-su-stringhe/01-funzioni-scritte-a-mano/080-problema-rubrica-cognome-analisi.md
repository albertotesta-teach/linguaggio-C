# Analisi – 080-problema-rubrica-cognome.c

## 1. Problema

La rubrica di un ufficio contiene cognomi, nomi e numeri di telefono. Per
trovare un collega basta scrivere l'inizio del cognome, senza badare alle
maiuscole: il programma mostra tutti i contatti il cui cognome comincia con
quel testo e segnala le corrispondenze esatte. Le ricerche si ripetono
finché l'utente non scrive "fine".

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `cognomi` | `char[][]` | 8 × 20 | Cognomi dei contatti |
| `nomi` | `char[][]` | 8 × 20 | Nomi (parallelo) |
| `telefoni` | `char[][]` | 8 × 20 | Numeri come stringhe: contengono uno spazio e lo zero iniziale |
| `ricerca` | `char[]` | 30 | Testo cercato |
| `trovati` | `int` | — | Contatti trovati nella ricerca corrente |

| Funzione | Compito |
|----------|---------|
| `leggi_riga` | Lettura con `fgets` e rimozione del `'\n'` |
| `inizia_con` | 1 se una stringa comincia con un prefisso |
| `uguali_ignorando_maiuscole` | Uguaglianza senza distinguere le maiuscole |
| `minuscola` | Conversione del singolo carattere |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Ricerca per prefisso

**a) Input** – `ross`

**b) Output** – Rossi Mario, Rossetti Paolo, Rossi Anna; "3 contatti"

**c) Variabili di supporto** – `trovati`

**d) Vincoli** – si scorre tutta la rubrica: i contatti trovati possono essere più di uno

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale**
1. Per ogni contatto verificare se il cognome inizia con il testo cercato.
2. In caso affermativo stampare il contatto e incrementare `trovati`.
3. Stampare il numero di contatti trovati.

### Caso d'uso 2 – Corrispondenza esatta

**a) Input** – `Rossi`

**b) Output** – i due Rossi con l'indicazione "(esatto)"

**c) Variabili di supporto** – esito di `uguali_ignorando_maiuscole`

**d) Vincoli** – "Rossetti" non compare perché non inizia con "Rossi"

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – come nel caso 1, aggiungendo
"(esatto)" quando il testo coincide con l'intero cognome.

### Caso d'uso 3 – Nessun risultato o testo vuoto

**a) Input** – `Gialli`; riga vuota

**b) Output** – "Nessun contatto trovato."; "Scrivi almeno una lettera."

**c) Variabili di supporto** – `trovati`, `ricerca[0]`

**d) Vincoli** – un prefisso vuoto sarebbe contenuto in ogni cognome: va escluso

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – se il testo è vuoto si chiede di
riprovare; se dopo lo scorrimento `trovati` vale 0 lo si segnala.

### Caso d'uso 4 – Verifica del prefisso

**a) Input** – una stringa `s` e un `prefisso`

**b) Output** – 1 oppure 0

**c) Variabili di supporto** – indice `i`

**d) Vincoli** – una sola `return`

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale**
1. Avanzare finché il prefisso non è finito e i caratteri (in minuscolo) coincidono.
2. Il prefisso è contenuto all'inizio di `s` se si è arrivati al suo `'\0'`.
