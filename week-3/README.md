# CPLUS Week 3

## 1. `IntVector`

1. Eenvoudig beginnen

   - Maak voor IntVector de volgende member functions (C++-term voor methods).
     1. Een constructor die als argument de capaciteit van het array meekrijgt.
     2. De destructor.
     3. `size_t capacity()` die de maximale capaciteit van de IntVector terug- geeft.
     4. `void push_back(int value)` die een waarde op de eerste vrije plek in de array zet.
     5. `size_t size()` die het aantal elementen in de array teruggeeft.
     6. `int get(size_t index)` die het element op de meegegeven index terug-
        geeft.
   - Zie [IntVector.hpp](IntVector.hpp) voor de implementatie en [1.1.cpp](1.1.cpp) voor de testcode.

2. Rule of five toepassen
   1. Compileer onderstaand programma en start het programma met een breakpoint op regel 6 en stap over deze regel. Wat gebeurt er met de `_array` member van w wanneer regel 6 wordt uitgevoerd?
      - Zie [1.2.1.cpp](1.2.1.cpp). De `v` `IntVector` wordt gecopieerd naar `w` `IntVector`.
   2. Laat het programma verder draaien. Crasht het programma? Hoe kun je die crash verklaren met wat er op regel 6 gebeurt?
      - Er gebeurt niks.
   3. Implementeer voor de klasse `IntVector` een geschikte `copy` constructoren een `copy` assignment operator.
      - Zie [IntVector.hpp line 14](IntVector.hpp#L14) voor de implementatie.
   4. Implementeer voor de klasse `IntVector` een geschikte `move` constructor en een `move` assignment operator. Pas indien nodig ook de destructor en copy operators aan.
      - Zie [IntVector.hpp line 22](IntVector.hpp#L22) voor de implementatie.
   5. Test je implementaties met de volgende code. Gaat alles goed?
      - Zie [1.2.5.cpp](1.2.5.cpp). Ja, alles gaat goed.

## 2. Exceptions

1. Breid `calc` zodanig uit met exception handling dat de `numbers` pointer niet meer lekt.
   - Zie [2.1.cpp](2.1.cpp) voor de implementatie.
2. Breid `main` zodanig uit met exception handling dat een exception niet maakt dat het programma stopt, maar dat `main` doorgaat met berekeningen printen.
   - Zie [2.2.cpp](2.2.cpp) voor de implementatie.
