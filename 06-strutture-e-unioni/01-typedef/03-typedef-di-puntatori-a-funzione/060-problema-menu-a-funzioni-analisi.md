# Analisi – 060-problema-menu-a-funzioni.c

## 1. Problema

Il distributore della mensa gestisce il credito della tessera di uno
studente con un menu: ricarica, pagamento del pasto, pagamento della
merenda, saldo. Ogni voce è una funzione con lo stesso prototipo, di tipo
`Azione`; la voce scelta è l'indice della funzione da chiamare nella
tabella `azioni`. Il credito iniziale è 8.30 euro.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `scelta` | `int` | Voce del menu (1-4); 0 esce |
| `euro` | `int` | Importo della ricarica, da 5 a 50 euro |

### Output

- Il menu prima di ogni scelta.
- Per ogni voce: `Ricarica di N euro eseguita.` / `Importo non valido.`,
  `Pagato: pasto 5.20 euro.` / `Credito insufficiente per pasto: servono
  5.20 euro.` (lo stesso per la merenda, 1.50 euro), `Saldo: E.CC euro`.
- `Voce inesistente.` per una scelta non valida.
- All'uscita: `Arrivederci. Credito residuo: E.CC euro`.

### Vincoli

- `typedef void (*Azione)(int *credito);`: tutte le voci ricevono il
  puntatore al credito, anche `mostra_saldo` che lo legge soltanto.
- Il credito è in centesimi (`int`), così non ci sono errori di
  arrotondamento; si stampa come euro e centesimi.
- Un pagamento si esegue solo se il credito basta.
- Una scelta o un importo non numerici vengono scartati (resto della riga)
  e trattati come non validi; a fine input si esce.

### Assunzioni

- La ricarica è in euro interi.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Azione` | `typedef void (*Azione)(int *credito);` | Funzione di una voce del menu |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `voci` | `const char *[4]` | Testi del menu |
| `azioni` | `Azione[4]` | Funzioni delle voci, nello stesso ordine |
| `credito` | `int` | Credito in centesimi, iniziale 830 |
| `letti` | `int` | Valore restituito da `scanf` |
| `PASTO`, `MERENDA` | `#define` | 520 e 150 centesimi |

| Funzione | Compito |
|----------|---------|
| `ricarica`, `paga_pasto`, `paga_merenda`, `mostra_saldo` | Le quattro voci |
| `paga(credito, importo, cosa)` | Scala l'importo se il credito basta |
| `svuota_riga` | Scarta i caratteri rimasti dopo un inserimento non valido |

### Algoritmo in linguaggio naturale

1. Finché la scelta non è 0:
   1. stampare il menu e leggere la scelta (fine input → 0; testo → voce
      inesistente);
   2. se è tra 1 e 4 chiamare `azioni[scelta - 1](&credito)`;
   3. altrimenti, se non è 0, segnalare la voce inesistente.
2. Stampare il credito residuo.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe); il menu, che si
ripete a ogni scelta, è omesso.

### Test 1 – Sessione completa

- **Cosa si verifica:** tutte le voci, il credito insufficiente, gli
  importi e le scelte non validi.
- **Input:** `4`, `2`, `2`, `1` `60`, `1` `abc`, `1` `20`, `3`, `7`, `xyz`,
  `4`, `0`
- **Valori intermedi attesi:** 830 − 520 = 310; 310 < 520 → rifiuto;
  310 + 2000 = 2310; 2310 − 150 = 2160.
- **Output atteso:**
  ```
    Saldo: 8.30 euro
    Pagato: pasto 5.20 euro.
    Credito insufficiente per pasto: servono 5.20 euro.
    Importo in euro (5-50):   Importo non valido.
    Importo in euro (5-50):   Importo non valido.
    Importo in euro (5-50):   Ricarica di 20 euro eseguita.
    Pagato: merenda 1.50 euro.
    Voce inesistente.
    Voce inesistente.
    Saldo: 21.60 euro
  Arrivederci. Credito residuo: 21.60 euro
  ```

### Test 2 – Fine input

- **Cosa si verifica:** la fine dell'input equivale a `0`.
- **Input:** `2`, poi fine input.
- **Output atteso:** `Arrivederci. Credito residuo: 3.10 euro`.
