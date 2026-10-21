# Analisi – 050-problema-normalizza-nome.c

## 1. Problema

In un modulo di iscrizione i nomi vengono scritti con maiuscole e spazi
irregolari. Prima di salvarli la segreteria vuole un formato unico: niente
spazi iniziali e finali, un solo spazio tra le parole, ogni parola con
l'iniziale maiuscola e il resto minuscolo; dopo un apostrofo o un trattino
la lettera torna maiuscola. Il programma normalizza un nome per riga e si
ferma con una riga vuota.

## 2. Analisi

### Input

| Variabile  | Tipo     | Dimensione | Descrizione                                |
|------------|----------|------------|--------------------------------------------|
| `inserito` | `char[]` | 60         | Nome e cognome; una riga vuota termina     |

### Output
Per ogni nome: il testo inserito e quello normalizzato tra parentesi quadre
(così si vedono gli spazi), con il numero di parole ("parola" al
singolare). Alla fine "Fine inserimento.".

### Vincoli
- Spazi iniziali e finali eliminati, un solo spazio tra le parole
- Iniziale di ogni parola maiuscola, altre lettere minuscole
- Dopo un apostrofo o un trattino la lettera successiva è maiuscola
  (D'Angelo, Anna-Maria)
- La normalizzazione avviene in una sola passata, con un flag
  `inizio_parola` che dice se il prossimo carattere apre una parola
- Il risultato non è mai più lungo dell'originale, quindi basta un array
  della stessa dimensione
- Le parole si contano sul risultato, dove sono separate da un solo spazio;
  una parola con trattino conta come una
- Una riga vuota termina; una riga di soli spazi viene normalizzata in una
  stringa vuota con 0 parole

### Assunzioni
- I nomi non contengono lettere accentate

### Variabili di supporto

| Variabile       | Tipo     | Dimensione | Descrizione                         |
|-----------------|----------|------------|-------------------------------------|
| `corretto`      | `char[]` | 60         | Testo normalizzato                  |
| `parole`        | `int`    | —          | Parole del risultato                |
| `inizio_parola` | `int`    | —          | Locale a `normalizza`               |

| Funzione | Descrizione |
|---|---|
| `int leggi_riga(char s[], int dim)` | `fgets` e rimozione del `'\n'` |
| `void normalizza(char dest[], const char sorg[])` | Testo normalizzato in una passata |
| `int conta_parole(const char s[])` | Parole separate da un solo spazio |
| `char maiuscola(char c)`, `char minuscola(char c)` | Conversione con la differenza `'a' − 'A'` |

### Algoritmo in linguaggio naturale
Normalizzazione (per ogni carattere di `sorg`):
1. Se è uno spazio: copiarlo solo se il risultato non è vuoto e l'ultimo
   carattere copiato non è uno spazio; porre `inizio_parola = 1`.
2. Altrimenti copiarlo in maiuscolo se `inizio_parola` vale 1, in minuscolo
   altrimenti; porre `inizio_parola = 1` solo se il carattere è un
   apostrofo o un trattino.
3. Alla fine togliere un eventuale spazio finale e chiudere con `'\0'`.

Programma principale: leggere un nome per riga finché la riga non è vuota,
normalizzarlo e stamparlo con il numero di parole.

## 3. Casi di test

Si inserisce una sequenza di nomi, una per riga, terminata da una riga
vuota.

### Test 1 – Maiuscole e spazi irregolari
- **Input:** `  mARIO   de  ROSSI ` (con spazi iniziali, multipli e finale)
- **Output atteso:** `archivio : [Mario De Rossi]  (3 parole)`

### Test 2 – Apostrofo e trattino
- **Input:** `anna-maria d'angelo`
- **Output atteso:** `archivio : [Anna-Maria D'Angelo]  (2 parole)`

### Test 3 – Una sola parola
- **Input:** `LUCA`
- **Output atteso:** `archivio : [Luca]  (1 parola)`

### Test 4 – Solo spazi e riga vuota
- **Input:** una riga di soli spazi, poi una riga vuota
- **Output atteso:** `archivio : []  (0 parole)`, poi `Fine inserimento.`
