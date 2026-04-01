# Analisi – 050-problema-biglietto-da-visita.c

## 1. Problema
Il programma acquisisce i dati numerici di un professionista (prefisso e
numero di telefono, anno di fondazione dell'azienda, numero civico e CAP
della sede) e li inserisce in un biglietto da visita testuale con bordo ASCII.
I dati non numerici (nome, ruolo, via, città) sono testo fisso, nel rispetto
dei vincoli del capitolo 01-introduzione.

## 2. Analisi generale e struttura dati

| Variabile          | Tipo  | Significato                              |
|--------------------|-------|------------------------------------------|
| `prefisso`         | `int` | Prefisso telefonico (es. 02, 06)         |
| `numero`           | `int` | Numero di telefono principale            |
| `anno_fondazione`  | `int` | Anno di fondazione dell'azienda          |
| `numero_civico`    | `int` | Numero civico della sede                 |
| `cap`              | `int` | Codice di avviamento postale             |

Non si usano array né stringhe.

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Azienda storica, numero breve

**a) Input**
- prefisso = 2, numero = 1234567, anno_fondazione = 1985
- numero_civico = 10, cap = 20121

**b) Output**
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

**c) Variabili di supporto**
- Nessuna: i valori sono stampati direttamente

**d) Vincoli**
- Il bordo ha larghezza fissa; valori molto grandi possono sforare il bordo

**e) Assunzioni**
- I dati inseriti sono validi e ragionevoli
- Il testo fisso (nome, ruolo, via, città) non cambia tra un'esecuzione e l'altra

**f) Algoritmo in linguaggio naturale**
1. Acquisire prefisso, numero, anno fondazione, numero civico, CAP
2. Stampare riga per riga il biglietto con i valori inseriti nei campi corretti

---

### Caso d'uso 2 – Prefisso con tre cifre

**a) Input**
- prefisso = 11, numero = 9876543, anno_fondazione = 2010
- numero_civico = 5, cap = 10100

**b) Output**
```
|   Tel: 011 / 9876543          |
```

**c) Variabili di supporto**
- Nessuna

**d) Vincoli**
- `%03d` garantisce sempre tre cifre per il prefisso

**e) Assunzioni**
- Il prefisso è al massimo 3 cifre

**f) Algoritmo in linguaggio naturale**
- Identico al caso d'uso 1

---

### Caso d'uso 3 – Azienda recente, numero civico alto

**a) Input**
- prefisso = 6, numero = 55512300, anno_fondazione = 2022
- numero_civico = 128, cap = 40127

**b) Output**
```
|   ACME S.r.l.  (dal 2022)          |
|   Via Roma, 128                      |
|   40127  Milano                     |
|   Tel: 006 / 55512300          |
```

**c) Variabili di supporto**
- Nessuna

**d) Vincoli**
- Con numero civico a 3 cifre l'allineamento del bordo destro può variare;
  questo comportamento è accettabile in un esempio introduttivo

**e) Assunzioni**
- Valori inseriti coerenti con la realtà (no validazione)

**f) Algoritmo in linguaggio naturale**
- Identico al caso d'uso 1
