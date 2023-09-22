# CPLUS Week 5

## 1. Een alpaca- en lamaboerderij

1. Implementeer hierin de functies `add_llama` en `add_alpaca`. Zorg ervoor dat jouw code werkt met onderstaande main functie, die je toevoegt aan bovenstaande file:

    ```cpp
    int main() {
        Farm f{}; 
        f.add_llama(std::make_unique<Llama>(10)); 
        f.add_alpaca(std::make_unique<Alpaca>(false));
    }
    ```

    - Zie [1/alpacallama.cpp line 47](1/alpacallama.cpp#47) voor de implementatie.

2. Implementeer in Farm.cpp de functie inspect. Deze loopt alle dieren in volgorde van toevoegen af en roept de functie make_noise aan. Je mag hierbij GEEN gebruik maken van indicies, of de subscriptoperator van `std::vector`. Onderstaande implementatie is *verboden*:

    ```cpp
    void Farm::inspect() const {
        for (std::size_t i = 0; i < animals_.size(); ++i) {
            animals_[i]->make_noise();
        }
    }
    ```

    - Zie [1/alpacallama.cpp line 51](1/alpacallama.cpp#51) voor de implementatie.
3. Implementeer nu de functie reverse_inspect. Deze functie doet hetzelfde als inspect maar loopt de dieren in omgekeerde volgorde af.
    - Zie [1/alpacallama.cpp line 56](1/alpacallama.cpp#56) voor de implementatie.
4. Voor gevorderden. Voeg volgende functie toe aan `Farm`:

    ```cpp
    template <typename T, typename... Args> void add_animal(Args &&... args);
    ```

    Deze functie krijgt als eerste templateargument een subklasse van `Animal`. De overige templateparameters worden gebruikt om de constructor van die sub- klasse aan te roepen middels perfect forwarding.
    - Zie [1/alpacallama.cpp line 61](1/alpacallama.cpp#61) voor de implementatie.

## 2. Iterators en templates

1. Schrijf een functietemplate `print_big` dat twee iterators accepteert. Deze functie print de naam van elke vijand met een aantal hp groter dan of gelijk aan 30 in het bereik van die twee iterators.
    - Zie [2/template_iterators_begin.cpp line 16](2/template_iterators_begin.cpp#16) voor de implementatie.
