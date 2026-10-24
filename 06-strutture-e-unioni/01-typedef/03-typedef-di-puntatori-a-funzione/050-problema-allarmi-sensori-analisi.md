# Analisi – 050-problema-allarmi-sensori.c

## 1. Problema

Il laboratorio di chimica ha quattro sensori (temperatura, umidità, CO2,
rumore), letti ogni ora dalle 8 alle 13. Ogni sensore ha la propria regola
di allarme, scritta come funzione. Il programma stampa ora per ora i
sensori in allarme e, per ogni sensore, quante volte è scattato l'allarme.
Le regole hanno il tipo `Regola`, un puntatore a funzione.

## 2. Analisi

### Input

Nessun input da tastiera: le letture sono nel sorgente.

| Sensore | Letture dalle 8 alle 13 |
|---------|-------------------------|
| temperatura | 15.2, 18.5, 21.0, 23.4, 26.1, 28.6 |
| umidità | 58, 61, 64, 72, 75, 69 |
| CO2 | 620, 840, 1080, 1240, 760, 1050 |
| rumore | 45, 82, 67, 71, 88, 60 |

### Output

- `=== ORA PER ORA ===`: per ogni ora i sensori in allarme con il valore,
  oppure `tutto regolare`.
- `=== ALLARMI PER SENSORE ===`: per ogni sensore `N su 6 letture`.

### Vincoli

- `typedef int (*Regola)(double valore);`
- Regole: temperatura fuori da 16-28 gradi (estremi esclusi dall'allarme),
  umidità oltre 70%, CO2 oltre 1000 ppm, rumore oltre 80 dB.
- Ogni sensore usa la regola nella stessa posizione dell'array `regole`.

### Assunzioni

- Le letture sono già acquisite e valide.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Regola` | `typedef int (*Regola)(double valore);` | Funzione che decide se un valore è un allarme |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `letture` | `double[4][6]` | Una riga per sensore, una colonna per ora |
| `regole` | `Regola[4]` | Regola di ogni sensore |
| `nomi` | `const char *[4]` | Nomi dei sensori |
| `in_allarme` | `int` | Almeno un allarme nell'ora |

| Funzione | Compito |
|----------|---------|
| `temperatura_fuori`, `umidita_alta`, `co2_alta`, `rumore_alto` | 1 se il valore è in allarme |
| `conta_allarmi(serie, n, r)` | Quante letture della serie fanno scattare la regola `r` |

### Algoritmo in linguaggio naturale

1. Per ogni ora: per ogni sensore, se `regole[s]` applicata alla lettura
   restituisce 1, stampare nome e valore; se nessun sensore è in allarme
   stampare `tutto regolare`.
2. Per ogni sensore stampare il risultato di `conta_allarmi` sulla sua
   riga di letture con la sua regola.

## 3. Casi di test

### Test 1 – Dati del sorgente

- **Cosa si verifica:** applicazione delle regole tramite la tabella e
  conteggio.
- **Input:** nessuno.
- **Output atteso:**
  ```
  === ORA PER ORA ===
    ore  8:  temperatura (15.2)
    ore  9:  rumore (82)
    ore 10:  CO2 (1080)
    ore 11:  umidita' (72)  CO2 (1240)
    ore 12:  umidita' (75)  rumore (88)
    ore 13:  temperatura (28.6)  CO2 (1050)

  === ALLARMI PER SENSORE ===
    temperatura  2 su 6 letture
    umidita'     2 su 6 letture
    CO2          3 su 6 letture
    rumore       2 su 6 letture
  ```

### Test 2 – Ora senza allarmi

- **Cosa si verifica:** il messaggio `tutto regolare`.
- **Procedura:** cambiare la prima temperatura in `17.0`.
- **Output atteso:** `ore  8:  tutto regolare` e
  `temperatura  1 su 6 letture`.

### Test 3 – Valore sulla soglia

- **Cosa si verifica:** la soglia stessa non è un allarme.
- **Procedura:** cambiare la prima lettura di CO2 in `1000`.
- **Output atteso:** l'ora 8 resta con il solo allarme di temperatura; CO2
  resta `3 su 6 letture`.
