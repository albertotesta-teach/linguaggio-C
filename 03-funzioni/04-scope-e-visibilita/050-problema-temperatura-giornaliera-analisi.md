# Analisi – 050-problema-temperatura-giornaliera.c

## 1. Problema
Una stazione meteorologica registra le temperature rilevate ogni due ore
durante una giornata. Il sistema deve calcolare e stampare al termine il
valore minimo, massimo, medio e l'escursione termica. Le variabili globali
conservano lo stato accumulato tra una rilevazione e la successiva, senza
dover passare strutture dati complesse tra le funzioni.

## 2. Analisi

### Input
Nessun input da tastiera: le dodici rilevazioni (ora e temperatura) sono
passate a `stampa_rilevazione` nel `main`.

| Parametro | Tipo | Descrizione |
|---|---|---|
| `ora` | int | Ora della rilevazione (0–22, ogni due ore) |
| `temp` | double | Temperatura rilevata (°C) |

### Output
Una tabella con ora e temperatura di ogni rilevazione (temperatura con segno
e un decimale), poi il report giornaliero: numero di rilevazioni, minima,
massima, media ed escursione termica. Senza rilevazioni il report stampa
"Nessuna rilevazione disponibile."

### Vincoli
- Alla prima rilevazione minimo e massimo valgono la sentinella
  `NESSUNA_RILEVAZIONE`: il confronto con la sentinella viene prima del
  confronto con il valore, così la prima temperatura diventa sia minimo
  sia massimo
- Gli aggiornamenti usano `<` e `>`: in caso di parità si mantiene il valore
  già registrato
- La media si calcola solo se `num_rilevazioni > 0`, per evitare la
  divisione per zero

### Assunzioni
- La sentinella -999.0 è un valore fisicamente impossibile per una
  temperatura terrestre
- Le rilevazioni avvengono ogni due ore nell'arco della giornata

### Variabili di supporto

| Variabile globale | Tipo | Descrizione |
|---|---|---|
| `temp_minima` | double | Minima rilevata finora (sentinella se nessuna) |
| `temp_massima` | double | Massima rilevata finora (sentinella se nessuna) |
| `temp_somma` | double | Somma delle temperature, per la media |
| `num_rilevazioni` | int | Numero di rilevazioni effettuate |

| Variabile locale | Tipo | Descrizione |
|---|---|---|
| `media` | double | Locale a `stampa_report` |

Costante: `NESSUNA_RILEVAZIONE` = -999.0

| Funzione | Firma | Descrizione |
|---|---|---|
| `registra_temperatura` | `void(double)` | Aggiorna min, max, somma e contatore |
| `stampa_rilevazione` | `void(int, double)` | Stampa ora e temperatura, poi chiama `registra_temperatura` |
| `stampa_report` | `void(void)` | Calcola la media e stampa il report finale |

### Algoritmo in linguaggio naturale
Per ogni rilevazione (`stampa_rilevazione`):
1. Stampare ora e temperatura.
2. Chiamare `registra_temperatura`, che:
   a. incrementa `num_rilevazioni` e aggiunge la temperatura a `temp_somma`;
   b. se il minimo vale la sentinella oppure la temperatura è minore del
      minimo, aggiorna il minimo;
   c. lo stesso per il massimo.

Report (`stampa_report`):
1. Se non ci sono rilevazioni stampare il messaggio di assenza dati.
2. Altrimenti calcolare `media = temp_somma / num_rilevazioni` e stampare
   rilevazioni, minima, massima, media ed escursione (`massima − minima`).

## 3. Casi di test

Il programma registra le dodici rilevazioni del `main` e stampa il report:
si esegue una volta e si confronta con l'output atteso.

### Test 1 – Prima rilevazione
- **Cosa si verifica:** il confronto con la sentinella
- **Input:** ora 0, temperatura 4.2
- **Valori intermedi attesi:** dopo la chiamata `temp_minima` e
  `temp_massima` valgono entrambe 4.2

### Test 2 – Report della giornata
- **Input:** 4.2, 3.8, 3.1, 4.5, 7.3, 11.8, 14.2, 15.6, 13.9, 10.4, 7.8, 5.9
- **Valori intermedi attesi:** somma 102.5; minima 3.1 (ore 4); massima 15.6
  (ore 14)
- **Output atteso:**
```
--- Report giornaliero ---
Rilevazioni:   12
Temperatura minima:  +3.1 C
Temperatura massima: +15.6 C
Temperatura media:   +8.5 C
Escursione termica:  12.5 C
```

### Test 3 – Nessuna rilevazione
- **Cosa si verifica:** il ramo che evita la divisione per zero
- **Procedura:** commentare nel `main` tutte le chiamate a
  `stampa_rilevazione`, ricompilare ed eseguire
- **Output atteso:** "Nessuna rilevazione disponibile."
