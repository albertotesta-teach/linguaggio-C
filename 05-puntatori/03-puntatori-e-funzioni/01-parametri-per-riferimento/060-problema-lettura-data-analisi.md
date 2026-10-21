# Analisi – 060-problema-lettura-data.c

## 1. Problema

Per prenotare la palestra comunale si inserisce una data `gg/mm/aaaa`. Il
programma controlla che la data esista, compresi i mesi da 30 giorni e
febbraio negli anni bisestili, e per una data valida indica il giorno
successivo, quando la prenotazione scade. Una riga vuota termina.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `riga` | `char[40]` | Data `gg/mm/aaaa` letta con `fgets` dentro `leggi_data`; riga vuota per finire |

### Output

- Per una data valida: `Prenotazione per il gg/mm/aaaa, scade il gg/mm/aaaa`
  (giorno successivo).
- Per una data non valida: `Data non valida.`

### Vincoli

- `leggi_data` ha tre esiti: 1 data valida, 0 data non valida, -1 riga
  vuota o fine dell'input. Le variabili del chiamante (`*g`, `*m`, `*a`) si
  scrivono solo se la data è valida: prima si usano variabili provvisorie.
- Data valida: anno ≥ 1900, mese 1-12, giorno da 1 al numero di giorni del
  mese.
- Bisestile se divisibile per 4 e non per 100, oppure divisibile per 400.
- `giorno_dopo` modifica insieme giorno, mese e anno, con i cambi di mese e
  di anno.
- Una riga più lunga del buffer viene troncata e il resto si scarta.

### Assunzioni

- Una riga che inizia con `'\n'` è vuota.
- Testo dopo la data sulla stessa riga viene ignorato.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `giorno`, `mese`, `anno` | `int` | Data letta, poi spostata al giorno dopo |
| `esito` | `int` | 1 valida, 0 non valida, -1 fine |
| `gg`, `mm`, `aa` | `int` | In `leggi_data`: valori provvisori prima del controllo |
| `n`, `c` | `int` | In `leggi_data`: ricerca del `'\n'` e scarto del resto della riga |

| Funzione | Compito |
|----------|---------|
| `leggi_data(&g, &m, &a)` | Legge e controlla una data; tre esiti possibili |
| `giorni_del_mese(m, a)` | 28, 29, 30 o 31 |
| `giorno_dopo(&g, &m, &a)` | Porta la data al giorno successivo |

### Algoritmo in linguaggio naturale

1. Finché l'esito non è -1:
   1. chiamare `leggi_data`, che legge la riga (se manca o è vuota
      restituisce -1), scarta l'eventuale resto, converte con `sscanf` e
      controlla la data; solo se valida la scrive nelle variabili del
      chiamante;
   2. esito 0 → `Data non valida.`; esito 1 → stampare la data, portarla al
      giorno dopo con `giorno_dopo` e stamparla.
2. In `giorno_dopo`: incrementare il giorno; se supera i giorni del mese
   ripartire da 1 e incrementare il mese; se il mese supera 12 ripartire da
   1 e incrementare l'anno.

## 3. Casi di test

Nell'output le date inserite non compaiono (input da pipe).

### Test 1 – Cambio di anno

- **Input:** `31/12/2026`
- **Output atteso:** `  Prenotazione per il 31/12/2026, scade il 01/01/2027`

### Test 2 – Anni bisestili

- **Input:** `29/02/2026`, `28/02/2028`, `29/02/2028`
- **Output atteso:**
  ```
    Data non valida.
    Prenotazione per il 28/02/2028, scade il 29/02/2028
    Prenotazione per il 29/02/2028, scade il 01/03/2028
  ```

### Test 3 – Mesi da 30 giorni e anno minimo

- **Input:** `31/04/2026`, `30/04/2026`, `01/01/1899`
- **Output atteso:**
  ```
    Data non valida.
    Prenotazione per il 30/04/2026, scade il 01/05/2026
    Data non valida.
  ```

### Test 4 – Testo non valido e fine

- **Input:** `ciao`, riga vuota
- **Output atteso:** `  Data non valida.`, poi il programma termina.

### Test 5 – Riga più lunga del buffer

- **Cosa si verifica:** il resto della riga non viene letto come un'altra data.
- **Input:** `12/03/2026` seguita da 50 spazi e una `x`; poi `13/03/2026`
- **Output atteso:**
  ```
    Prenotazione per il 12/03/2026, scade il 13/03/2026
    Prenotazione per il 13/03/2026, scade il 14/03/2026
  ```
