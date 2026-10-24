# Analisi – 040-problema-unisci-stringhe.c

## 1. Problema

Il laboratorio di informatica crea gli indirizzi email degli studenti
nuovi unendo nome e cognome (`nome.cognome@studenti.scuola.it`), in
minuscolo e senza i caratteri che non sono lettere. Se l'indirizzo esiste
già si aggiunge un numero a partire da 2. La funzione `crea_email` calcola
la lunghezza esatta, alloca il blocco e lo restituisce; il chiamante
conserva i puntatori e alla fine li libera.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `nome`, `cognome` | `char[24]` | Una coppia per riga; `FINE` termina |

### Output

- Per ogni studente: `indirizzo (N caratteri)`, oppure
  `Nome o cognome senza lettere.`, `Memoria insufficiente.`
- Alla fine: `Account da creare: N` e l'elenco degli indirizzi.

### Vincoli

- Lunghezza: lettere del nome + 1 (punto) + lettere del cognome + cifre
  del numero + lunghezza del dominio, più il terminatore; il blocco è
  `malloc((lunghezza + 1) * sizeof *email)`.
- Un indirizzo già presente si scarta (`free`) e si riprova con il numero
  successivo (2, 3, ...).
- Si conservano solo le lettere, in minuscolo (`D'Amico` → `damico`).
- Ogni blocco memorizzato viene liberato alla fine; al massimo 30
  studenti.
- Il resto della riga viene scartato. A fine input il programma termina
  come con `FINE`.

### Assunzioni

- Nome e cognome sono una parola ciascuno (i cognomi composti si scrivono
  uniti o con il trattino).

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `elenco` | `char *[30]` | Indirizzi creati |
| `email` | `char *` | Blocco restituito da `crea_email` |
| `numero` | `int` | Suffisso per gli omonimi (0 = nessuno) |

| Funzione | Compito |
|----------|---------|
| `crea_email(nome, cognome, numero)` | Alloca e compone l'indirizzo; `NULL` se manca memoria |
| `lettere(testo)` | Conta le lettere |
| `cifre(numero)` | Cifre di un numero positivo |
| `presente(elenco, n, email)` | 1 se l'indirizzo esiste già |

### Algoritmo in linguaggio naturale

1. Finché non si termina e c'è posto: leggere nome e cognome (con `FINE` o
   a fine input terminare), scartare il resto della riga; se uno dei due
   non ha lettere segnalarlo; altrimenti creare l'indirizzo e, finché è
   già presente, liberarlo e crearlo con il numero successivo;
   memorizzarlo e stamparlo.
2. Stampare l'elenco liberando ogni blocco.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Omonimi e caratteri non alfabetici

- **Input:** `Mario Rossi`, `mario ROSSI`, `Anna D'Amico`,
  `Mario Rossi extra`, `123 456`, `MARIA DE-LUCA`, `FINE`
- **Output atteso:**
  ```
    mario.rossi@studenti.scuola.it (30 caratteri)
    mario.rossi2@studenti.scuola.it (31 caratteri)
    anna.damico@studenti.scuola.it (30 caratteri)
    mario.rossi3@studenti.scuola.it (31 caratteri)
    Nome o cognome senza lettere.
    maria.deluca@studenti.scuola.it (31 caratteri)

  Account da creare: 5
    mario.rossi@studenti.scuola.it
    mario.rossi2@studenti.scuola.it
    anna.damico@studenti.scuola.it
    mario.rossi3@studenti.scuola.it
    maria.deluca@studenti.scuola.it
  ```
