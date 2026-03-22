# Analisi – 070-problema-sensori-industriali.c

## 1. Problema

Un impianto industriale dispone di 8 sensori di temperatura. Il sistema deve
acquisire le letture, mostrarle in una dashboard con indicatore di stato,
segnalare i sensori fuori dalla soglia operativa e calcolare la temperatura
media dell'impianto.

---

## 2. Analisi generale e struttura dati

| Variabile      | Tipo       | Dimensione | Motivazione                                    |
|----------------|------------|------------|------------------------------------------------|
| `letture`      | `double[]` | 8          | Temperature in °C con decimali                 |
| `somma`        | `double`   | —          | Accumulatore per la media                      |
| `num_allarmi`  | `int`      | —          | Contatore sensori fuori soglia                 |
| `stato`        | `char[]`   | 10         | Stringa "OK" o "ALLARME" costruita manualmente |
| `SOGLIA_MIN`   | `#define`  | 10.0       | Limite inferiore accettabile                   |
| `SOGLIA_MAX`   | `#define`  | 80.0       | Limite superiore accettabile                   |
| `NUM_SENSORI`  | `#define`  | 8          | Dimensione array e limite cicli                |

---

## 3. Casi d'uso e funzionalità

---

### Caso d'uso 1 – Acquisizione letture

**a) Input** — Valori double da tastiera, uno per sensore.
**b) Output** — Prompt per ogni sensore.
**d) Vincoli** — `scanf` usa `%lf` per `double`. Nessuna validazione del range in input.
**f) Algoritmo**
```
Per i da 0 a NUM_SENSORI - 1: leggere letture[i].
```

---

### Caso d'uso 2 – Dashboard con stato per sensore

**a) Input** — Array `letture`, costanti `SOGLIA_MIN` e `SOGLIA_MAX`.
**b) Output**
```
--- DASHBOARD IMPIANTO ---
  Sensore    | Temp (°C)  | Stato
  S01        |     65.0 °C | OK
  S02        |      5.0 °C | ALLARME
```
**c) Variabili di supporto** — `stato` (`char[]`): costruita manualmente senza `strcpy`.
**d) Vincoli** — Valori esattamente uguali alle soglie sono considerati OK (operatori `<` e `>`).
**f) Algoritmo**
```
Per i da 0 a NUM_SENSORI - 1:
  Se letture[i] fuori [SOGLIA_MIN, SOGLIA_MAX]: stato = "ALLARME".
  Altrimenti: stato = "OK".
  Stampare riga.
```

---

### Caso d'uso 3 – Elenco allarmi e media

**a) Input** — Array `letture`.
**b) Output**
```
Temperatura media impianto: 48.3°C
Sensori in allarme: 2 su 8
```
**d) Vincoli** — Messaggi distinti per temperatura troppo bassa e troppo alta. Media calcolata su tutti i sensori.
**f) Algoritmo**
```
Per i da 0 a NUM_SENSORI - 1:
  Se letture[i] < SOGLIA_MIN: segnalare e incrementare num_allarmi.
  Altrimenti se letture[i] > SOGLIA_MAX: segnalare e incrementare.
Calcolare somma e stampare media e num_allarmi.
```
