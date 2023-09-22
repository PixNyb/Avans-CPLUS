# CPLUS Week 4

## 1. RAII gebruiken met een C library

1. Breid het programma uit door boven de `main`-functie een simpele eigengemaakte RAII class te definiëren die een instantie van `Dinges` kan beheren.
    - Zie [1/program.cpp](1/program.cpp) voor de implementatie.
2. Gebruik die RAII class vervolgens op de juiste manier door één regel aan de `main` toe te voegen, en er ook eentje te verwijderen... Test je oplossing.
    - Zie [1/program.cpp](1/program.cpp) voor de implementatie.
        - De toegevoegde regel is `DingesRaii dinges_raii(dinges);` (regel 15)
        - De verwijderde regel is `destroy_dinges(dinges);` (regel 22)
3. Maak nu een tweede oplossing door jouw eigengemaakte RAII class te verwijderen en te vervangen door std::unique_ptr. Wat moet je doen om te zorgen dat std::unique_ptr bij het opruimen geen delete gebruikt, maar destroy_dinges?
    - Zie [1/program_unique_ptr.cpp](1/program_unique_ptr.cpp) voor de implementatie.
        - De `std::unique_ptr` moet een custom deleter krijgen die `destroy_dinges` aanroept.

## 2. C-strings versus std::string

1. Moet de C-string in dit voorbeeld nog opgeruimd worden?
    - Nee, de C-string wordt na het aanroepen van `std::string` overgenomen door de `std::string` en wordt dus automatisch opgeruimd.
2. Om de lengte van een C-string te bepalen heb je de functie `strlen` nodig (en de header `<string.h>`). Deze functie is niet erg efficiënt: hij loopt door de chars heen totdat hij het afsluitende NUL-byte tegenkomt. Zoek op: hoe bepaal je de lengte van een `std::string`?
    - De lengte van een `std::string` kan bepaald worden met de functie `std::string::length()`.
3. Is die aanpak efficiënter? Leg uit.
    - Ja, de lengte van een `std::string` wordt bijgehouden in een variabele en hoeft dus niet berekend te worden.

## 3. Byte-buffers

1. In welk van de drie geheugengebieden (global memory, de stack, de heap) staat dit blok van 1024 bytes?
    - de array `char buf[1024]` staat op de stack.
2. Wat is het type van de variabele buf? Twee antwoorden mogelijk.
    - `char*` of `char[]`
3. In welk van de drie geheugengebieden alloceert `std::vector` zijn interne buffer?
    - De interne buffer van `std::vector` staat op de heap.
4. Schrijf een stukje code dat een `std::string` initialiseert met een stuk tekst, en dat vervolgens kopiëert naar een buffer die je met een `std::vector` maakt. Dat kopiëren kan op twee manieren: via indexering, waarbij je dus de tekst als `char` array gebruikt; of met pointers die door de data lopen. Na het kopiëren schrijf je de inhoud van de `std::vector` naar de standard output (`std::cout`).
    - Zie [3.cpp](3.cpp) voor de implementatie.

## 4. Smart pointers correct gebruiken

1. `std::unique_ptr` doorgeven
    1. Wat is het type van de variabele `w` in main?
        - Het type van `w` is `std::unique_ptr<Widget>`.
    2. Wat voor compile-error krijg je?
        - Ik krijg de volgende compile-errors:

        ```console
        /home/pixnyb/Projects/Avans/CPLUS/week-4/4.cpp: In function ‘int main()’:
        /home/pixnyb/Projects/Avans/CPLUS/week-4/4.cpp:22:7: error: cannot bind rvalue reference of type ‘std::unique_ptr<Widget>&&’ to lvalue of type ‘std::unique_ptr<Widget>’
        22 |   fun(w);
           |       ^
        /home/pixnyb/Projects/Avans/CPLUS/week-4/4.cpp:18:36: note:   initializing argument 1 of ‘void fun(std::unique_ptr<Widget>&&)’
        18 | void fun(std::unique_ptr<Widget> &&p) { std::cout << p->message() << '\n'; }
           |          ~~~~~~~~~~~~~~~~~~~~~~~~~~^
        ```

        De compiler geeft aan dat de `rvalue` reference niet gebonden kan worden aan de `lvalue` reference.
    3. Wijzig de aanroep van `fun` in `main` zodat het wel werkt.
        - Zie [4.1.cpp](4.1.cpp) voor de implementatie. De aanroep van `fun` is nu `fun(std::move(w));`. Dit werkt omdat `std::move` de `lvalue` reference omzet naar een `rvalue` reference.
    4. Blijkbaar kan een `std::unique_ptr` niet gekopieerd worden. Daar is bewust voor gekozen. Waarom?
        - Een `std::unique_ptr` kan niet gekopieerd worden omdat er maar één eigenaar van een `std::unique_ptr` mag zijn. Als je een `std::unique_ptr` kopieert, dan zijn er twee eigenaren en dat is niet toegestaan.
    5. Hoe geef je in een class declaration aan dat je een object van dat type niet kunt kopiëren?
        - Je kan een class niet kopiëren door de copy constructor en de copy assignment operator te verwijderen. Dit kan je doen door de volgende regels toe te voegen aan de class declaration:

        ```cpp
        Widget(const Widget&) = delete;
        Widget& operator=(const Widget&) = delete;
        ```

    6. Waarom staan er achter de parameter van fun twee ampersands (“&”)?
        - De twee ampersands achter de parameter van `fun` geven aan dat het een `rvalue` reference is. Dit betekent dat de parameter een tijdelijke waarde kan zijn en dat de parameter dus niet gekopieerd mag worden.
    7. Check de waarde van de geëncapsuleerde Widget-pointer in `w` nadat `fun` is aangeroepen. Gebruik een debugger of voeg regel toe waarin je iets naar `std::cout` schrijft. Wat is hier gebeurd?
        - De waarde van de geëncapsuleerde `Widget` pointer is `nullptr` nadat `fun` is aangeroepen. Dit komt omdat de `std::unique_ptr` in `fun` de `Widget` pointer heeft overgenomen en de `std::unique_ptr` in `main` dus geen `Widget` pointer meer heeft.

2. `std::shared_ptr` doorgeven
    1. Wat is het type van de variabele `w` in `main`?
        - Het type van `w` is `std::shared_ptr<Widget>`.
    2. Verklaar de output.
        - De functie `fun` geeft de waarde van de geëncapsuleerde `Widget` pointer weer (in dit geval `Nice weather today.`). Daarnaast wordt het aantal referenties van de `std::shared_ptr` weergegeven. Doordat de functie `fun` en `main` dezelfde `std::shared_ptr` delen, wordt de waarde van het aantal referenties in beide functies hetzelfde weergegeven. In dit geval is het aantal referenties 2. Nadat `fun` klaar is met uitvoeren wordt het aantal referenties weer weergegeven. Doordat `fun` klaar is met uitvoeren, wordt de `std::shared_ptr` in `fun` opgeruimd en wordt het aantal referenties weer 1.
    3. We hebben eerder geleerd dat we objecten bij voorkeur als reference doorgeven, liefst ook nog `const`. Maar de `std::shared_ptr` wordt in dit voorbeeld by value doorgegeven aan `fun`. Waarom is dat?
        - De `std::shared_ptr` wordt by value doorgegeven omdat de `std::shared_ptr` in `fun` een kopie van de `std::shared_ptr` in `main` moet zijn. Als de `std::shared_ptr` in `fun` een reference zou zijn, dan zouden de `std::shared_ptr` in `fun` en `main` dezelfde `std::shared_ptr` zijn. Dit zou betekenen dat de `std::shared_ptr` in `fun` en `main` dezelfde referenties zouden hebben en dat is niet de bedoeling.
    4. Verander `fun` zodat je een `const std::shared_ptr<Widget>&` doorgeeft. Bouw en run opnieuw. Verklaar de output.
        - De output is grotendeels hetzelfde als bij de vorige vraag. Het enige verschil is dat de `std::shared_ptr` in `fun` nu een reference is. Dit betekent dat de `std::shared_ptr` in `fun` en `main` dezelfde `std::shared_ptr` zijn. Hierdoor is het aantal referenties in `fun` en `main` hetzelfde en wordt het aantal referenties in `fun` niet gereset nadat `fun` klaar is met uitvoeren. Dit blijft dus 1.
3. `std::unique_ptr` omzetten in `std::shared_ptr`
    1. Het type van de variabele `w` in `main` is hier: `std::unique_ptr<Widget>`. De functie `fun` verwacht echter een `std::shared_ptr<Widget>`. Toch bouwt en runt dit prima. Leg uit wat hier gebeurt.
        - De `std::unique_ptr` in `main` wordt omgezet naar een `std::shared_ptr` door de functie `std::shared_ptr::unique`. Hierdoor kan de `std::unique_ptr` in `main` doorgegeven worden aan `fun`.
    2. Kun je nu ook de output verklaren?
        - De output is hetzelfde als bij de vorige vragen. Alleen omdat in de functie `fun` de `std::unique_ptr` wordt omgezet naar een `std::shared_ptr`, is het aantal referenties 1. Dit komt omdat de `std::shared_ptr` in `fun` een kopie is van de `std::shared_ptr` in `main` en dus niet naar dezelfde waarde wijst.
4. Smart pointers als instantievariabelen
    1. In main wordt een `Graph` object gedefinieerd. Wat is het nut van dit object?
        - Het `Graph` object wordt gebruikt om een collectie `Node` objecten en hun buren bij te houden.
    2. De `Node` objecten houden hun buren bij met een `std::vector` waarin `std::weak_ptrs` worden gezet. Als je een andere `Node` als buur toevoegt met de `add_neighbor` method, krijgt die de `Node` verpakt in een `std::shared_ptr`. De omzetting naar een `std::weak_ptr` gebeurt tijdens het plaatsen in de `std::vector`. We komen daar in week 5 op terug. Waarom heeft de ontwerper gekozen voor `std::weak_ptrs`, en niet gewoon `std::shared_ptrs` in `_neighbors` gezet?
        - De ontwerper heeft gekozen voor `std::weak_ptrs` omdat de `Node` objecten elkaar niet mogen bezitten. Als de `Node` objecten elkaar zouden bezitten, dan zou er een circulaire referentie ontstaan en zouden de `Node` objecten nooit opgeruimd worden.
    3. Stel dat we in main het `Graph` object al opruimen voordat er iets naar `std::cout` wordt geschreven, wat zal dan het gedrag van programma zijn? Probeer stap voor stap te beschrijven wat er gebeurt.
        1. Het `Graph` object wordt opgeruimd. Hierdoor wordt de destructor van elk `Node` object in de `_nodes` vector aangeroepen.
        2. De `std::shared_ptr` objecten welke de `Node` objecten bezitten worden opgeruimd. Hierdoor zal de referentie count van de `std::shared_ptr` objecten 0 worden.
        3. Omdat alle `Node` objecten nogsteeds een `std::weak_ptr` naar elkaar hebben, worden de `Node` objecten niet opgeruimd.
        4. Het programma zal proberen om de `name` van de `Node` objecten weer te geven met behulp van de `neighbor_with_name` functie. Omdat de `Node` objecten al opgeruimd zijn, zal het programma een `std::bad_weak_ptr` exception gooien.
