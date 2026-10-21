# Analisi – 070-problema-selezione-sicura.c

## 1. Problema

Il pannello di una lavatrice permette di cambiare temperatura, centrifuga
e durata scrivendo un codice e un valore ("T 40", "C 1200"). Ogni
impostazione ha un intervallo ammesso. Le richieste con codice sconosciuto
o senza valore sono scartate, i valori fuori intervallo rifiutati. Una riga
vuota avvia il lavaggio con le impostazioni finali.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `riga` | `char[40]` | Richiesta `codice valore`: `T` gradi, `C` giri, `D` minuti; riga vuota per avviare |
| impostazioni iniziali | `int` | 30 gradi, 800 giri, 60 minuti (nel sorgente) |
| `limiti_temp`, `limiti_centr`, `limiti_durata` | `const int[2]` | 20-90, 400-1400, 15-180 (nel sorgente) |

### Output

- Per ogni richiesta: `impostato N`, `valore fuori dai limiti min-max`
  oppure `richiesta non valida`.
- Alla fine: `Avvio: T gradi, C giri, D minuti`.

### Vincoli

- La richiesta si scompone con `sscanf(riga, " %c %d", ...)`: se non
  vengono letti codice e valore la richiesta non è valida.
- Secondo il codice, `valore` punta all'impostazione e `minimo`/`massimo`
  agli elementi del suo array di limiti; con un codice sconosciuto restano
  `NULL`.
- `&limiti_temp[0]` è l'indirizzo di un elemento `const`: si assegna a un
  `const int *`.
- `imposta` controlla che nessuno dei tre puntatori sia `NULL` prima di
  usarli; un valore fuori intervallo non modifica l'impostazione.
- Riga vuota o fine dell'input avviano il lavaggio.

### Assunzioni

- I codici sono in maiuscolo; una minuscola è un codice sconosciuto.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `codice`, `nuovo` | `char`, `int` | Parti della richiesta |
| `valore` | `int *` | Impostazione da modificare |
| `minimo`, `massimo` | `const int *` | Limiti, di sola lettura |
| `esito` | `int` | `ACCETTATO`, `NON_VALIDO` o `FUORI_LIMITI` |

| Funzione | Compito |
|----------|---------|
| `imposta(valore, minimo, massimo, nuovo)` | Controlla i puntatori e i limiti, poi scrive; restituisce l'esito |

### Algoritmo in linguaggio naturale

1. Finché si legge una riga non vuota:
   1. porre i tre puntatori a `NULL`;
   2. se `sscanf` legge codice e valore, secondo il codice far puntare
      `valore`, `minimo` e `massimo`;
   3. chiamare `imposta`: se un puntatore è `NULL` → `NON_VALIDO`; se il
      valore è fuori da `*minimo`-`*massimo` → `FUORI_LIMITI`; altrimenti
      scrivere `*valore = nuovo` → `ACCETTATO`;
   4. stampare l'esito.
2. Stampare le impostazioni di avvio.

## 3. Casi di test

Nell'output le richieste non compaiono (input da pipe).

### Test 1 – Sessione completa

- **Input:** `T 40`, `C 1200`, `D 90`, `C 1600`, `Z 5`, `D`, `t 50`,
  `T 20`, `T 91`, riga vuota
- **Output atteso** (risposte nell'ordine):
  ```
    impostato 40
    impostato 1200
    impostato 90
    valore fuori dai limiti 400-1400
    richiesta non valida
    richiesta non valida
    richiesta non valida
    impostato 20
    valore fuori dai limiti 20-90

  Avvio: 20 gradi, 1200 giri, 90 minuti
  ```

### Test 2 – Fine dell'input

- **Cosa si verifica:** senza riga vuota il lavaggio parte comunque.
- **Input:** `T 40`, poi fine dell'input (Ctrl+D, o input da pipe)
- **Output atteso** (ultima riga): `Avvio: 40 gradi, 800 giri, 60 minuti`
