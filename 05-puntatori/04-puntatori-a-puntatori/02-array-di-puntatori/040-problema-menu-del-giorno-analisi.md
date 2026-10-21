# Analisi – 040-problema-menu-del-giorno.c

## 1. Problema

Il menu settimanale della mensa ha primo, secondo e contorno per ogni
giorno da lunedì a venerdì, con nomi di lunghezza molto diversa. Lo
studente sceglie il giorno e il programma stampa il menu; alla fine indica
il nome di piatto più lungo, per il tabellone.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `g` | `int` | Giorno scelto (1-5); 0 per finire |
| `giorni`, `primi`, `secondi`, `contorni` | `const char *[5]` | Menu della settimana (nel sorgente) |

### Output

- Per ogni giorno valido: nome del giorno, primo, secondo e contorno.
- `Giorno non valido.` per un numero fuori da 0-5 o un testo.
- Alla fine il nome di piatto più lungo con il numero di caratteri.

### Vincoli

- I menu sono array di puntatori a stringhe costanti: ogni elemento punta a
  un testo della lunghezza che serve, senza spreco di spazio.
- I quattro array sono paralleli: lo stesso indice indica lo stesso giorno.
- L'indice usato è sempre tra 0 e 4 (`g − 1` con `g` da 1 a 5).
- Per il nome più lungo si conserva il puntatore, non una copia del testo;
  a parità vale il primo trovato (confronto con `>`).
- Un testo non numerico è un giorno non valido (la riga si scarta); a fine
  input il programma termina come con 0.

### Assunzioni

- Giorni numerati da 1 (lunedì) a 5 (venerdì).

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `piu_lungo` | `const char *` | Puntatore al nome più lungo |
| `letti` | `int` | Valore restituito da `scanf` |
| `i` | `int` | Indice dei giorni |

| Funzione | Compito |
|----------|---------|
| `stampa_menu(g, giorni, primi, secondi, contorni)` | Stampa il menu del giorno di indice `g` |
| `svuota_riga` | Scarta i caratteri rimasti dopo un inserimento non valido |

### Algoritmo in linguaggio naturale

1. Finché il giorno non è 0: leggerlo (a fine input 0; testo → non
   valido); se fuori da 0-5 segnalarlo, altrimenti, se non è 0, stampare il
   menu del giorno `g − 1`.
2. Scorrere i tre array dei piatti e conservare in `piu_lungo` il puntatore
   al nome con `strlen` maggiore.
3. Stampare il nome più lungo e la sua lunghezza.

## 3. Casi di test

Nell'output i giorni inseriti non compaiono (input da pipe).

### Test 1 – Sessione completa

- **Input:** `3`, `7`, `abc`, `1`, `0`
- **Output atteso:**
  ```
    --- Mercoledi ---
    Primo:    Minestrone di verdure
    Secondo:  Merluzzo al forno
    Contorno: Patate al forno
    Giorno non valido.
    Giorno non valido.
    --- Lunedi ---
    Primo:    Pasta al pomodoro e basilico
    Secondo:  Pollo arrosto
    Contorno: Insalata
  Nome piu' lungo per il tabellone: "Pasta al pomodoro e basilico" (28 caratteri)
  ```
