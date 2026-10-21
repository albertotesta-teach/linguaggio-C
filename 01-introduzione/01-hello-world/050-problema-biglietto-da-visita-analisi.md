# Analisi – 050-problema-biglietto-da-visita.c

## 1. Problema
Il programma acquisisce i dati numerici di un professionista (prefisso e
numero di telefono, anno di fondazione dell'azienda, numero civico e CAP
della sede) e li inserisce in un biglietto da visita testuale con bordo ASCII.
I dati non numerici (nome, ruolo, via, città) sono testo fisso, nel rispetto
dei vincoli del capitolo 01-introduzione.

## 2. Analisi

### Input

| Variabile          | Tipo  | Significato                              |
|--------------------|-------|------------------------------------------|
| `prefisso`         | `int` | Prefisso telefonico (es. 02, 06)         |
| `numero`           | `int` | Numero di telefono principale            |
| `anno_fondazione`  | `int` | Anno di fondazione dell'azienda          |
| `numero_civico`    | `int` | Numero civico della sede                 |
| `cap`              | `int` | Codice di avviamento postale             |

### Output
Un biglietto da visita racchiuso in un bordo ASCII, con il testo fisso
(nome, ruolo, ragione sociale, via, città) e i valori inseriti nei campi
corrispondenti. Il prefisso è stampato sempre su tre cifre (`%03d`).

### Vincoli
- Il prefisso ha al massimo 3 cifre
- Tutti i valori sono interi positivi
- I vincoli non vengono verificati dal programma

### Assunzioni
- I dati inseriti sono validi e realistici (nessuna validazione)
- Il testo fisso (nome, ruolo, via, città) non cambia tra un'esecuzione
  e l'altra
- Il bordo ha larghezza fissa: con valori lunghi l'allineamento del bordo
  destro può variare, comportamento accettabile in un esempio introduttivo

### Variabili di supporto
Nessuna: i valori letti sono stampati direttamente. Non si usano array
né stringhe.

### Algoritmo in linguaggio naturale
1. Acquisire prefisso, numero di telefono, anno di fondazione, numero
   civico e CAP.
2. Stampare riga per riga il biglietto, inserendo i valori nei campi
   corretti con gli specificatori di formato.

## 3. Casi di test

Per ogni caso si esegue il programma con l'input indicato e si confronta
quanto stampato con l'output atteso.

### Test 1 – Biglietto completo (caso tipico)
- **Input:** prefisso = 2, numero = 1234567, anno_fondazione = 1985,
  numero_civico = 10, cap = 20121
- **Output atteso:**
```
+--------------------------------------+
|                                      |
|   MARIO ROSSI                        |
|   Sviluppatore Software              |
|                                      |
|   ACME S.r.l.  (dal 1985)          |
|   Via Roma, 10                      |
|   20121  Milano                     |
|                                      |
|   Tel: 002 / 1234567          |
|                                      |
+--------------------------------------+
```

### Test 2 – Prefisso a due cifre
- **Cosa si verifica:** `%03d` completa il prefisso con lo zero iniziale
- **Input:** prefisso = 11, numero = 9876543, anno_fondazione = 2010,
  numero_civico = 5, cap = 10100
- **Output atteso (riga del telefono):**
```
|   Tel: 011 / 9876543          |
```

### Test 3 – Valori più lunghi (numero civico a tre cifre, telefono a otto cifre)
- **Cosa si verifica:** il comportamento del bordo destro con valori lunghi
- **Input:** prefisso = 6, numero = 55512300, anno_fondazione = 2022,
  numero_civico = 128, cap = 40127
- **Output atteso (righe che cambiano):**
```
|   ACME S.r.l.  (dal 2022)          |
|   Via Roma, 128                      |
|   40127  Milano                     |
|   Tel: 006 / 55512300          |
```
