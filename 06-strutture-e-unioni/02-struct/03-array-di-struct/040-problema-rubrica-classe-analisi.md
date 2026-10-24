# Analisi – 040-problema-rubrica-classe.c

## 1. Problema

Il rappresentante di classe cerca nella rubrica i contatti per inizio del
cognome o per ruolo (studente, docente, genitore), oppure stampa l'elenco
completo. Ogni ricerca indica quanti contatti ha trovato. La rubrica è un
array di 8 struct `Contatto`.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `comando` | `char` | `C testo` cerca per cognome, `R ruolo` per ruolo, `E` elenco, `Q` fine (anche minuscoli) |
| `testo` | `char[20]` | Inizio del cognome o ruolo cercato |
| `rubrica` | `Contatto[8]` | Contatti (nel sorgente) |

### Output

- Per una ricerca: i contatti trovati (cognome, nome, telefono, ruolo) e
  `Trovati: N`.
- Per `E`: l'elenco numerato di tutti i contatti.
- `Comando sconosciuto.` per un comando non previsto.

### Vincoli

- Ricerca per cognome: i contatti il cui cognome inizia con il testo
  (`strncmp` sulla lunghezza del testo).
- Ricerca per ruolo: uguaglianza completa (`strcmp`).
- Maiuscole e minuscole contano nel testo cercato.
- A ogni elemento dell'array si accede con `rubrica[i].campo`.
- Un comando per riga: il resto della riga viene scartato. A fine input il
  programma termina come con `Q`.

### Assunzioni

- La rubrica non è ordinata: la ricerca scorre tutti i contatti.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Contatto` | `typedef struct { char cognome[20]; char nome[16]; char telefono[16]; char ruolo[10]; } Contatto;` | Un contatto della rubrica |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `rubrica` | `Contatto[8]` | Array di struct |
| `comando` | `char` | Comando letto, in maiuscolo |
| `trovati` | `int` | Contatti trovati da una ricerca |

| Funzione | Compito |
|----------|---------|
| `svuota_riga` | Scarta i caratteri rimasti sulla riga |

### Algoritmo in linguaggio naturale

1. Finché il comando non è `Q`:
   1. leggere il comando (fine input → `Q`) e convertirlo in maiuscolo;
   2. `C` o `R`: leggere il testo e scorrere la rubrica stampando e
      contando i contatti che corrispondono; stampare il totale;
   3. `E`: stampare l'elenco numerato;
   4. altro diverso da `Q`: comando sconosciuto;
   5. scartare il resto della riga.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Ricerche

- **Cosa si verifica:** ricerca per prefisso e per ruolo, ricerche senza
  risultati, comando minuscolo e sconosciuto.
- **Input:** `C Bas`, `r docente`, `C Z`, `R preside`, `C B`, `X`, `Q`
- **Output atteso:**
  ```
    Bassi      Andrea   333 5566778  studente
    Bassi      Paola    335 1212121  genitore
    Trovati: 2
    Benedetti  Laura    0131 222333  docente
    Fontana    Diego    0131 444555  docente
    Trovati: 2
    Trovati: 0
    Trovati: 0
    Barbieri   Giorgia  347 1122334  studente
    Bassi      Andrea   333 5566778  studente
    Benedetti  Laura    0131 222333  docente
    Bassi      Paola    335 1212121  genitore
    Trovati: 4
    Comando sconosciuto.
  ```

### Test 2 – Elenco

- **Input:** `E`, `Q`
- **Output atteso:**
  ```
    1. Barbieri   Giorgia  347 1122334  studente
    2. Bassi      Andrea   333 5566778  studente
    3. Benedetti  Laura    0131 222333  docente
    4. Caruso     Matteo   349 9988776  studente
    5. Caputo     Rosa     340 4455667  genitore
    6. Fontana    Diego    0131 444555  docente
    7. Lombardi   Noemi    338 7766554  studente
    8. Bassi      Paola    335 1212121  genitore
  ```

### Test 3 – Maiuscole nel testo

- **Input:** `C bas`, `Q`
- **Output atteso:** `Trovati: 0`.
