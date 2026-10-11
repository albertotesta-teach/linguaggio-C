# Analisi – 060-problema-login.c

## 1. Problema

Il gestionale di un laboratorio ha quattro account. A ogni tentativo di
accesso l'utente scrive nome e password; dopo 3 password errate consecutive
l'account viene bloccato. Per non aiutare chi prova a indovinare, il
messaggio di errore è lo stesso sia per un utente inesistente sia per una
password sbagliata. Si continua finché come nome si scrive "fine"; alla fine
si stampa lo stato degli account.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `utenti` | `char[][]` | 4 × 20 | Nomi degli account |
| `password` | `char[][]` | 4 × 20 | Password (parallelo) |
| `errori` | `int[]` | 4 | Errori consecutivi per account (parallelo) |
| `nome`, `chiave` | `char[]` | 40 | Dati inseriti |
| `accessi` | `int` | — | Accessi riusciti |

| Funzione | Compito |
|----------|---------|
| `leggi_riga` | Lettura con `fgets`; a fine input scrive "fine" |
| `cerca_utente` | Indice dell'account con `strcmp`, oppure -1 |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Accesso riuscito

**a) Input** – `mrossi`, `Rossi#77`

**b) Output** – "Benvenuto, mrossi!"

**c) Variabili di supporto** – `k`, `accessi`

**d) Vincoli** – l'accesso riuscito azzera `errori[k]`

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale**
1. Cercare il nome con `cerca_utente`.
2. Se l'account esiste, non è bloccato e `strcmp(chiave, password[k]) == 0`:
   azzerare gli errori, contare l'accesso, salutare.

### Caso d'uso 2 – Utente inesistente o password errata

**a) Input** – `pippo` / `x`; `lbianchi` / `bianchi99`

**b) Output** – "Credenziali non valide." in entrambi i casi

**c) Variabili di supporto** – `errori[k]`

**d) Vincoli** – per un utente inesistente non c'è un contatore da aggiornare

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – se `k == -1` stampare il messaggio;
se la password è sbagliata incrementare `errori[k]` e stampare lo stesso messaggio.

### Caso d'uso 3 – Blocco dell'account

**a) Input** – terza password errata per `lbianchi`, poi la password corretta

**b) Output** – "l'account lbianchi è stato bloccato"; poi "Account bloccato…"

**c) Variabili di supporto** – `errori[k]`

**d) Vincoli** – un account bloccato non accetta nemmeno la password corretta

**e) Assunzioni** – lo sblocco è fatto dal tecnico, fuori dal programma

**f) Algoritmo in linguaggio naturale** – quando `errori[k]` raggiunge 3 si
segnala il blocco; ai tentativi successivi si controlla il blocco prima
della password.

### Caso d'uso 4 – Riepilogo finale

**a) Input** – `fine`

**b) Output** – accessi riusciti e stato di ogni account

**c) Variabili di supporto** – `errori[]`

**d) Vincoli** – nessuno

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – scorrere gli array paralleli e
stampare "BLOCCATO" quando `errori[k] >= 3`.
