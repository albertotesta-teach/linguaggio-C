# Analisi – 070-problema-email-istituzionale.c

## 1. Problema

La scuola assegna a studenti e docenti un indirizzo email della forma
`nome.cognome@dominio`, tutto in minuscolo e senza spazi né apostrofi. Il
dominio dipende dal ruolo (`studenti.scuola.edu.it` oppure `scuola.edu.it`).
Se la parte prima della `@` supera 25 caratteri, il nome viene ridotto
all'iniziale. Il programma stampa gli indirizzi e le liste di distribuzione
di docenti e studenti.

## 2. Analisi

### Input
Nessun input da tastiera: i dati sono inizializzati nel codice in tre array
paralleli.

| Variabile | Tipo       | Dimensione | Descrizione                                 |
|-----------|------------|------------|---------------------------------------------|
| `nomi`    | `char[][]` | 7 × 30     | Nomi, anche composti                        |
| `cognomi` | `char[][]` | 7 × 30     | Cognomi                                     |
| `ruoli`   | `char[]`   | 7          | `'S'` studente, `'D'` docente               |

### Output
- L'elenco con nome, cognome, ruolo e indirizzo email di ogni persona;
- la lista dei docenti e quella degli studenti, nell'ordine dell'elenco.

### Vincoli
- Di nome e cognome si tengono solo le lettere, in minuscolo: spazi e
  apostrofi spariscono ("Maria Grazia" "D'Angelo" → mariagrazia.dangelo)
- Parte locale = nome + `.` + cognome; se supera `MAX_LOCALE` (25)
  caratteri, del nome resta solo l'iniziale
- Dominio: `@scuola.edu.it` per i docenti, `@studenti.scuola.edu.it` per
  ogni altro ruolo
- L'indirizzo si costruisce con `copia` e `concatena`, scritte a mano
- Il buffer dell'email (60) contiene la parte locale più lunga ammessa più
  il dominio più lungo

### Assunzioni
- I nomi non contengono lettere accentate
- Nome e cognome hanno almeno una lettera

### Variabili di supporto

| Variabile | Tipo       | Dimensione | Descrizione                          |
|-----------|------------|------------|--------------------------------------|
| `email`   | `char[][]` | 7 × 60     | Indirizzi costruiti, parallelo       |
| `parte_nome`, `parte_cognome` | `char[]` | 30 | Locali a `crea_email`    |
| `MAX_LOCALE` | `#define` | 25      | Lunghezza massima della parte locale |

| Funzione | Descrizione |
|---|---|
| `void crea_email(char email[], const char nome[], const char cognome[], char ruolo)` | Applica le regole |
| `void solo_lettere(char dest[], const char sorg[])` | Solo lettere, in minuscolo |
| `void copia(...)`, `void concatena(...)`, `int lunghezza(...)` | Funzioni di base |

### Algoritmo in linguaggio naturale
1. Per ogni persona costruire l'indirizzo:
   a. ricavare nome e cognome con le sole lettere minuscole;
   b. se nome + 1 + cognome supera 25 caratteri, troncare il nome dopo
      l'iniziale;
   c. copiare il nome, aggiungere il punto, il cognome e il dominio del
      ruolo.
2. Stampare l'elenco.
3. Stampare gli indirizzi dei docenti, poi quelli degli studenti.

## 3. Casi di test

Il programma non legge dati: si esegue una volta e si confronta con l'output
atteso.

### Test 1 – Indirizzi
- **Cosa si verifica:** nomi composti, apostrofi, cognomi con spazio e
  riduzione all'iniziale ("mariavittoria.dellacquabianchi" avrebbe 30
  caratteri)
- **Output atteso:**
```
  Luca            Ferrari             S  luca.ferrari@studenti.scuola.edu.it
  Maria Grazia    D'Angelo            D  mariagrazia.dangelo@scuola.edu.it
  Paolo           Esposito            S  paolo.esposito@studenti.scuola.edu.it
  Maria Vittoria  Dell'Acqua Bianchi  S  m.dellacquabianchi@studenti.scuola.edu.it
  Sara            Colombo             D  sara.colombo@scuola.edu.it
  Giovanni        La Rosa             S  giovanni.larosa@studenti.scuola.edu.it
  Elena           Ricci               D  elena.ricci@scuola.edu.it
```

### Test 2 – Liste di distribuzione
- **Output atteso:**
```
Lista docenti:
  mariagrazia.dangelo@scuola.edu.it
  sara.colombo@scuola.edu.it
  elena.ricci@scuola.edu.it
Lista studenti:
  luca.ferrari@studenti.scuola.edu.it
  paolo.esposito@studenti.scuola.edu.it
  m.dellacquabianchi@studenti.scuola.edu.it
  giovanni.larosa@studenti.scuola.edu.it
```
