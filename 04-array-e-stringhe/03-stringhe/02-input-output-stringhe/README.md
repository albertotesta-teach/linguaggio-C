# 02 – Input e output di stringhe

## Concetto

Leggere e scrivere stringhe in C richiede la scelta della funzione giusta
in base al contesto. Le funzioni principali sono:

| Funzione          | Direzione | Caratteristica principale                        |
|-------------------|-----------|--------------------------------------------------|
| `printf("%s", s)` | output    | Stampa la stringa senza aggiungere `'\n'`        |
| `puts(s)`         | output    | Stampa la stringa e aggiunge `'\n'` automatico   |
| `putchar(c)`      | output    | Stampa un singolo carattere                      |
| `scanf("%s", s)`  | input     | Legge fino al primo spazio, rischio overflow     |
| `fgets(s, n, f)`  | input     | Legge l'intera riga con spazi, include `'\n'`    |

**Problema del `'\n'` con `fgets`:**
`fgets` include il carattere `'\n'` (invio) nella stringa letta.
Va rimosso manualmente scorrendo la stringa con un ciclo `while`:

```c
fgets(buffer, DIM, stdin);
i = 0;
while (buffer[i] != '\n' && buffer[i] != '\0') {
    i++;
}
buffer[i] = '\0'; /* sostituisce '\n' con '\0' */
```

**Problema del buffer residuo con `scanf`:**
`scanf` lascia `'\n'` nel buffer di input. Se seguito da `fgets`,
il `'\n'` viene letto immediatamente da `fgets` che termina senza
aspettare l'input dell'utente. Soluzione: svuotare il buffer con
un ciclo su `getchar()` prima di chiamare `fgets`.

---

## File dell'esempio

| File | Tipo | Contenuto |
|------|------|-----------|
| `010-output-stringhe.c` | concetto | `printf`, `puts`, `putchar`: differenze e casi d'uso |
| `020-input-con-scanf.c` | concetto | `scanf` con `%s`: limiti, modificatore di larghezza, buffer residuo |
| `030-input-con-fgets.c` | concetto | `fgets`: lettura con spazi, rimozione `'\n'`, confronto con `scanf` |
| `040-input-output-combinati.c` | concetto | Sessione completa: più campi con `fgets` e `scanf` combinati |
| `050-problema-registro-presenze.c` | problema | Registro scolastico: lettura nome con `fgets`, verifica campo vuoto, log formattato |
| `050-problema-registro-presenze-analisi.md` | analisi | Analisi dettagliata del problema registro presenze |
| `060-problema-messaggio-sms.c` | problema | Messaggistica: limite 160 caratteri, conteggio senza `strlen`, barra utilizzo |
| `060-problema-messaggio-sms-analisi.md` | analisi | Analisi dettagliata del problema messaggio SMS |
| `070-problema-inserimento-prodotto.c` | problema | Terminale magazzino: `scanf` e `fgets` combinati, validazione campi obbligatori |
| `070-problema-inserimento-prodotto-analisi.md` | analisi | Analisi dettagliata del problema inserimento prodotto |
| `080-problema-log-sistema.c` | problema | Logging applicativo: input misto `scanf`/`fgets`, composizione riga di log |
| `080-problema-log-sistema-analisi.md` | analisi | Analisi dettagliata del problema log sistema |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-output-stringhe 010-output-stringhe.c
./010-output-stringhe

gcc -Wall -Wextra -o 020-input-con-scanf 020-input-con-scanf.c
./020-input-con-scanf

gcc -Wall -Wextra -o 030-input-con-fgets 030-input-con-fgets.c
./030-input-con-fgets

gcc -Wall -Wextra -o 040-input-output-combinati 040-input-output-combinati.c
./040-input-output-combinati

gcc -Wall -Wextra -o 050-problema-registro-presenze 050-problema-registro-presenze.c
./050-problema-registro-presenze

gcc -Wall -Wextra -o 060-problema-messaggio-sms 060-problema-messaggio-sms.c
./060-problema-messaggio-sms

gcc -Wall -Wextra -o 070-problema-inserimento-prodotto 070-problema-inserimento-prodotto.c
./070-problema-inserimento-prodotto

gcc -Wall -Wextra -o 080-problema-log-sistema 080-problema-log-sistema.c
./080-problema-log-sistema
```

---

## Output atteso

### 010-output-stringhe
```
--- printf con %s ---
Benvenuto nel sistema
Dopo printf: siamo sulla riga successiva grazie a \n esplicito.

--- puts ---
Benvenuto nel sistema
Dopo puts: il ritorno a capo era automatico.

--- printf con larghezza fissa ---
Campo allineato a sinistra:    valore
Benvenuto nel sistema          <-- occupa 30 caratteri

--- putchar su singolo carattere ---
Carattere singolo: A

--- putchar in ciclo (equivalente a printf) ---
Benvenuto nel sistema

--- Confronto: puts aggiunge \n, printf no ---
Con printf: prima seconda
Con puts:   prima
seconda
```

### 050-problema-registro-presenze
*(input: "De Luca Giovanni")*
```
╔════════════════════════════════════════════╗
║     REGISTRO ELETTRONICO PRESENZE          ║
║     Istituto Tecnico G. Marconi            ║
╚════════════════════════════════════════════╝

Data  : 2024-11-15
Ora   : 08:32

Inserisci nome e cognome: De Luca Giovanni

════════════════════════════════════════════════════
  PRESENZA REGISTRATA
════════════════════════════════════════════════════
  N. progressivo : 142
  Data           : 2024-11-15
  Ora            : 08:32
  Studente       : De Luca Giovanni
════════════════════════════════════════════════════

Presenza di De Luca Giovanni registrata correttamente.
```

### 060-problema-messaggio-sms
*(input: "Ciao Anna, ci vediamo domani alle 10?")*
```
Caratteri usati      : 37 / 160
Caratteri rimanenti  : 123

Utilizzo: [##........] 23%

Messaggio pronto per l'invio.
```

### 080-problema-log-sistema
*(input: livello 3, codice "DB_CONN_ERR", descrizione "Connessione al database fallita")*
```
[2024-11-15 08:45:22] [ERROR] GestMagazzino DB_CONN_ERR: Connessione al database fallita
```

---

## Errori comuni da evitare

**`fgets` dopo `scanf` senza svuotare il buffer**
```c
scanf("%d", &n);
fgets(testo, 100, stdin); /* ERRORE: legge il '\n' residuo e termina subito */
```
Soluzione: svuotare il buffer con `getchar()` in un ciclo prima di `fgets`.

**Dimenticare di rimuovere `'\n'` dopo `fgets`**
```c
fgets(nome, 50, stdin);
printf("Ciao %s!\n", nome); /* ERRORE: stampa "Ciao Mario\n!\n" */
```
La stringa contiene `'\n'` prima di `'\0'`: va rimosso con il ciclo `while`.

**`scanf("%s")` senza modificatore di larghezza**
```c
char nome[10];
scanf("%s", nome); /* ERRORE: se l'utente scrive più di 9 caratteri → overflow */
scanf("%9s", nome); /* CORRETTO: legge al massimo 9 caratteri */
```

**`&` con `scanf` su array**
```c
char nome[20];
scanf("%19s", &nome); /* ATTENZIONE: &nome non è sbagliato ma ridondante,
                         il nome dell'array è già un indirizzo.
                         Usa scanf("%19s", nome) senza & */
```

---

## Concetti collegati

- `01-dichiarazione-e-inizializzazione` → come sono strutturate le stringhe in memoria
- `03-lunghezza-e-accesso-ai-caratteri` → conteggio manuale dei caratteri
- `05-puntatori/09-stringhe-e-puntatori` → perché non serve `&` con `scanf` sugli array

---

## Esercizi proposti

1. Modifica `010-output-stringhe.c` per stampare la stringa al contrario
   usando `putchar` e un ciclo `while` che parte dall'ultimo carattere.

2. Modifica `050-problema-registro-presenze.c` per leggere e registrare
   tre studenti consecutivi, numerando le presenze da 1 a 3.

3. Estendi `060-problema-messaggio-sms.c` per leggere anche il nome
   del mittente e del destinatario con `fgets`, e includerli nell'anteprima.

4. Modifica `080-problema-log-sistema.c` per permettere l'inserimento
   di tre eventi consecutivi, stampando le tre righe di log in sequenza.

5. Scrivi un programma che legga un indirizzo completo su una sola riga
   (es. "Via Roma 12, 10100 Torino") con `fgets` e lo stampi separando
   visivamente la via dal CAP e dalla città, assumendo che il separatore
   sia la virgola in posizione fissa (es. posizione 12).
