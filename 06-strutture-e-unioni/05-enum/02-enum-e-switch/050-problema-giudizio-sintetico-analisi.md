# Analisi – 050-problema-giudizio-sintetico.c

## 1. Problema

Dopo la verifica di storia il docente scrive accanto a ogni voto il
giudizio sintetico. `da_voto` trasforma il voto in un `Giudizio` con una
catena di `if`; `nome` restituisce il testo con uno `switch`. Alla fine un
istogramma mostra quanti studenti hanno ogni giudizio.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `voto` | `double` | Voto da 1 a 10, anche con decimali; −1 termina |

### Output

- Per ogni voto: `V: giudizio` (voto con un decimale), oppure
  `Voto non valido.`
- `Giudizi della classe (N studenti)` e una riga per giudizio con tanti
  asterischi quanti studenti e il numero.

### Vincoli

- Fasce: meno di 5 gravemente insufficiente, da 5 a meno di 6
  insufficiente, poi sufficiente (6), discreto (7), buono (8), ottimo (da
  9 a 10).
- I conteggi usano il `Giudizio` come indice; il ciclo dell'istogramma va
  da `GRAV_INSUFFICIENTE` a `NUM_GIUDIZI`.
- Un voto non numerico viene scartato con il resto della riga; a fine
  input il programma termina come con −1.

### Assunzioni

- Nessuna.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Giudizio` | `typedef enum { GRAV_INSUFFICIENTE, INSUFFICIENTE, SUFFICIENTE, DISCRETO, BUONO, OTTIMO, NUM_GIUDIZI } Giudizio;` | Giudizio sintetico |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `conteggi` | `int[6]` | Studenti per giudizio |
| `studenti` | `int` | Voti validi |
| `letti` | `int` | Valore restituito da `scanf` |

| Funzione | Compito |
|----------|---------|
| `da_voto(voto)` | Fascia del voto |
| `nome(g)` | Testo del giudizio |
| `svuota_riga` | Scarta i caratteri rimasti dopo un inserimento non valido |

### Algoritmo in linguaggio naturale

1. Finché il voto non è −1:
   1. leggere il voto (fine input → −1; testo → non valido);
   2. se fuori da 1-10 segnalarlo;
   3. altrimenti trovare il giudizio, contarlo e stamparlo.
2. Stampare l'istogramma.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Una verifica

- **Cosa si verifica:** i confini delle fasce e i voti non validi.
- **Input:** `4.5`, `5`, `6.5`, `7`, `8`, `9`, `10`, `11`, `sei`, `7.5`,
  `-1`
- **Output atteso:**
  ```
    4.5: gravemente insufficiente
    5.0: insufficiente
    6.5: sufficiente
    7.0: discreto
    8.0: buono
    9.0: ottimo
    10.0: ottimo
    Voto non valido.
    Voto non valido.
    7.5: discreto

  Giudizi della classe (8 studenti)
    gravemente insufficiente   * 1
    insufficiente              * 1
    sufficiente                * 1
    discreto                   ** 2
    buono                      * 1
    ottimo                     ** 2
  ```

### Test 2 – Nessun voto

- **Input:** `-1`
- **Output atteso:** `Giudizi della classe (0 studenti)` e tutti i
  giudizi con 0.
