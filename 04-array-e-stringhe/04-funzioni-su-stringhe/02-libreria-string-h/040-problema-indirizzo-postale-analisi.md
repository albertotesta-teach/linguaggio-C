# Analisi – 040-problema-indirizzo-postale.c

## 1. Problema

Un negozio online stampa le etichette dei pacchi. L'operatore inserisce
destinatario, via con numero civico, CAP, comune e sigla della provincia.
Il programma verifica che il CAP abbia 5 cifre e la provincia 2 caratteri,
compone le tre righe dell'etichetta (al massimo 30 caratteri ciascuna) e
avvisa se qualche riga è stata troncata.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `destinatario`, `via`, `cap`, `comune`, `provincia` | `char[]` | 50 | Campi letti con `fgets` |
| `riga` | `char[]` | 31 | Riga dell'etichetta: 30 caratteri + `'\0'` |
| `completa` | `int` | — | 1 se la riga corrente è entrata tutta |
| `troncate` | `int` | — | Righe troncate |

| Funzione | Compito |
|----------|---------|
| `leggi_riga` | `fgets` e rimozione del `'\n'` con `strlen` |
| `solo_cifre` | Verifica che una stringa contenga solo cifre |
| `aggiungi` | `strncat` con il calcolo dello spazio libero; 0 se tronca |
| `stampa_riga` | Stampa la riga dentro il bordo |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Validazione del CAP

**a) Input** – `151`, poi `15020`

**b) Output** – "CAP non valido." e nuova richiesta

**c) Variabili di supporto** – `strlen(cap)`, `solo_cifre(cap)`

**d) Vincoli** – esattamente 5 caratteri, tutti cifre

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – ripetere la lettura (`do-while`)
finché la lunghezza è 5 e i caratteri sono cifre.

### Caso d'uso 2 – Validazione della provincia

**a) Input** – `ALE`, poi `AL`

**b) Output** – "Sigla non valida." e nuova richiesta

**c) Variabili di supporto** – `strlen(provincia)`

**d) Vincoli** – esattamente 2 caratteri

**e) Assunzioni** – l'operatore scrive la sigla in maiuscolo

**f) Algoritmo in linguaggio naturale** – come nel caso 1, con il solo
controllo della lunghezza.

### Caso d'uso 3 – Composizione della terza riga

**a) Input** – `15020`, `San Giorgio Monferrato`, `AL`

**b) Output** – `15020 San Giorgio Monferrato (` e l'avviso "1 riga troppo lunga"

**c) Variabili di supporto** – `riga`, `completa`

**d) Vincoli** – `riga` non deve mai superare 30 caratteri; `aggiungi` va
chiamata anche dopo un troncamento, quindi è scritta a sinistra di `&&`

**e) Assunzioni** – il CAP entra sempre nella riga

**f) Algoritmo in linguaggio naturale**
1. Copiare il CAP in `riga` con `strcpy`.
2. Aggiungere `" "`, comune, `" ("`, provincia, `")"` con `aggiungi`.
3. Se almeno un pezzo è stato troncato, incrementare `troncate`.

### Caso d'uso 4 – Spazio libero per strncat

**a) Input** – `dest`, la sua dimensione `dim`, il testo `sorg`

**b) Output** – `dest` allungata; 1 se `sorg` è entrata tutta

**c) Variabili di supporto** – `spazio_libero`

**d) Vincoli** – il limite di `strncat` è il numero di caratteri ancora
aggiungibili, non la dimensione di `dest`

**e) Assunzioni** – `dest` è già una stringa valida

**f) Algoritmo in linguaggio naturale**
1. `spazio_libero = dim - strlen(dest) - 1`.
2. `strncat(dest, sorg, spazio_libero)`.
3. Restituire `strlen(sorg) <= spazio_libero`.
