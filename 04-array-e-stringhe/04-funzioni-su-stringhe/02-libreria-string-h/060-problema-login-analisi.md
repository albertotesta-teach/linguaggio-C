# Analisi – 060-problema-login.c

## 1. Problema

Il gestionale di un laboratorio ha quattro account. A ogni tentativo di
accesso l'utente scrive nome e password; dopo 3 password errate consecutive
l'account viene bloccato. Per non aiutare chi prova a indovinare, il
messaggio di errore è lo stesso sia per un utente inesistente sia per una
password sbagliata. Si continua finché come nome si scrive "fine"; alla fine
si stampa lo stato degli account.

## 2. Analisi

### Input

| Variabile | Tipo     | Dimensione | Descrizione                         |
|-----------|----------|------------|-------------------------------------|
| `nome`    | `char[]` | 40         | Nome utente; "fine" termina         |
| `chiave`  | `char[]` | 40         | Password inserita                   |

Gli account (nomi e password) sono inizializzati nel codice.

### Output
- Per ogni tentativo: "Benvenuto, nome!", "Credenziali non valide." oppure
  "Account bloccato: rivolgersi al tecnico."; al terzo errore consecutivo
  anche "Troppi errori: l'account … e' stato bloccato.";
- alla fine il numero di accessi riusciti e, per ogni account, lo stato
  (attivo o BLOCCATO) e gli errori.

### Vincoli
- Utente inesistente e password sbagliata danno **lo stesso** messaggio
- Gli errori si contano per account e sono **consecutivi**: un accesso
  riuscito li azzera
- Al terzo errore l'account è bloccato; un account bloccato rifiuta anche
  la password corretta
- La password viene chiesta anche per un utente inesistente, così chi prova
  non capisce se il nome esiste
- I confronti usano `strcmp` e distinguono le maiuscole
- La ricerca dell'utente si ferma al primo trovato (flag, niente `break`)
- A fine input `leggi_riga` scrive "fine" nel nome, così il ciclo termina

### Assunzioni
- I nomi utente sono univoci

### Variabili di supporto

| Variabile  | Tipo       | Dimensione | Descrizione                              |
|------------|------------|------------|------------------------------------------|
| `utenti`   | `char[][]` | 4 × 20     | Nomi degli account                       |
| `password` | `char[][]` | 4 × 20     | Password, parallelo a `utenti`           |
| `errori`   | `int[]`    | 4          | Errori consecutivi, parallelo            |
| `k`        | `int`      | —          | Indice dell'account (-1 se inesistente)  |
| `accessi`  | `int`      | —          | Accessi riusciti                         |
| `MAX_ERRORI` | `#define`| 3          | Errori prima del blocco                  |

| Funzione | Descrizione |
|---|---|
| `int leggi_riga(char s[], int dim)` | `fgets`; a fine input scrive "fine" |
| `int cerca_utente(const char nome[], const char utenti[][LUNG], int n)` | Indice o -1 |

### Algoritmo in linguaggio naturale
1. Leggere il nome.
2. Finché il nome non è "fine":
   a. leggere la password e cercare l'utente;
   b. se non esiste: messaggio generico;
   c. altrimenti, se è bloccato: messaggio di blocco;
   d. altrimenti, se la password è giusta: azzerare gli errori, contare
      l'accesso e salutare;
   e. altrimenti incrementare gli errori, dare il messaggio generico e, se
      gli errori sono arrivati a 3, segnalare il blocco;
   f. leggere il nome successivo.
3. Stampare gli accessi e lo stato degli account.

## 3. Casi di test

Si inseriscono coppie nome/password, terminate da `fine`.

### Test 1 – Sessione con blocco
- **Input:** `mrossi`/`Rossi#77`, `pippo`/`x`, poi tre volte `gverdi` con
  password sbagliate (`a`, `b`, `c`), `gverdi`/`Verdi_2010`,
  `ADMIN`/`Lab!2024`, `fine`
- **Output atteso:**
  - `Benvenuto, mrossi!`
  - `pippo` e i primi due errori di gverdi → `Credenziali non valide.`
  - terzo errore → `Credenziali non valide.` e
    `Troppi errori: l'account gverdi e' stato bloccato.`
  - gverdi con la password giusta → `Account bloccato: rivolgersi al
    tecnico.`
  - `ADMIN` (maiuscolo) → `Credenziali non valide.`
- **Riepilogo atteso:**
```
Accessi riusciti: 1
Stato degli account:
  admin     attivo   (errori: 0)
  mrossi    attivo   (errori: 0)
  lbianchi  attivo   (errori: 0)
  gverdi    BLOCCATO (errori: 3)
```

### Test 2 – Errori azzerati da un accesso riuscito
- **Cosa si verifica:** gli errori sono consecutivi
- **Input:** `admin`/`x`, `admin`/`y`, `admin`/`Lab!2024`, `admin`/`z`,
  `fine`
- **Output atteso:** l'accesso riesce al terzo tentativo; nel riepilogo
  `admin     attivo   (errori: 1)`
