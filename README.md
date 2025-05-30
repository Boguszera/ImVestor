===========================================================
                       ImVestor
                 Wersja: 1.0.0
          Opis: Symulator giełdowy
===========================================================

## Opis projektu
--------------
ImVestor to interaktywna aplikacja desktopowa stworzona w C++ z wykorzystaniem biblioteki SFML 3.0,
która symuluje rynek akcji. Użytkownik może kupować i sprzedawać akcje różnych firm,
a także śledzić zmiany cen w czasie rzeczywistym za pomocą wizualnego wykresu.

## Funkcjonalności:
- **Symulacja rynku akcji** - dynamicznie zmieniające się ceny akcji
- **System transakcji** - możliwość kupna i sprzedaży akcji
- **Portfel inwestycyjny** - śledzenie posiadanych aktywów
- **Interaktywne GUI** - przyjazny interfejs użytkownika
- **Wizualizacja danych** - wykresy cen akcji w czasie rzeczywistym

-----------------------------------------------------------
## Wymagania systemowe
--------------------
- Kompilator C++ obsługujący standard C++20 (np. GCC 10+, Clang 12+, MSVC 2019+)
- CMake w wersji 3.20 lub nowszej
- SFML 3.0.0 (biblioteka graficzna)
- System operacyjny: Windows / Linux / macOS

-----------------------------------------------------------
## Struktura projektu
------------------
ImVestor/
├── src/                    # Katalog ze wszystkimi plikami źródłowymi (.h i .cpp)
│   ├── Company.h           # Klasa reprezentująca firmę na giełdzie, zarządzająca ceną akcji, trendami i historią cen
│   ├── Company.cpp
│   ├── Portfolio.h         # Zarządza portfelem użytkownika — przechowuje pozycje akcji, umożliwia dodawanie i usuwanie
│   ├── Portfolio.cpp
│   ├── StockHolding.h      # Reprezentuje pojedynczą pozycję w portfelu użytkownika (np. 100 akcji danej firmy)
│   ├── StockHolding.cpp
│   ├── TransactionManager.h # Obsługuje logikę kupna i sprzedaży akcji, aktualizując portfel i saldo użytkownika
│   ├── TransactionManager.cpp
│   ├── User.h             # Przechowuje dane użytkownika: nazwę, saldo oraz portfel inwestycyjny
│   ├── User.cpp
│   └── main.cpp           Punkt startowy aplikacji
│
├── gui/                    # Interfejs użytkownika
│   ├── Button.h            # Deklaracja klasy przycisku GUI
│   └── Button.cpp          # Implementacja klasy przycisku GUI
│
├── assets/                 # Zasoby (czcionki, obrazy, ikony itp.)
│   └── ARIAL.ttf           # Czcionka wykorzystywana w aplikacji
│
├── README.md               # Dokumentacja projektu i instrukcje użytkowania
├── .gitignore              # Pliki i foldery ignorowane przez Git

-----------------------------------------------------------
## Budowanie projektu
-------------------
1. Sklonuj repozytorium:
   git clone <adres_repozytorium>

2. Przejdź do folderu projektu:
   cd ImVestor

3. Utwórz katalog build i przejdź do niego:
   mkdir build && cd build

4. Skonfiguruj projekt za pomocą CMake:
   cmake ..

   - Domyślnie używany jest systemowy SFML 3.0.0.
   - Możesz wyłączyć używanie systemowej biblioteki SFML ustawiając
     USE_SYSTEM_SFML=OFF podczas konfiguracji:
     cmake -DUSE_SYSTEM_SFML=OFF ..

5. Zbuduj projekt:
   cmake --build .

6. Uruchom aplikację:
   ./ImVestor  (Linux/macOS)
   ImVestor.exe (Windows)

-----------------------------------------------------------
## Użycie
-------
1. Po uruchomieniu aplikacji wyświetlana jest lista dostępnych spółek z aktualnymi cenami akcji.

2. Użyj przycisków "Buy" i "Sell" do dokonywania transakcji.

3. Kliknij na nazwę spółki, aby wyświetlić wykres jej cen.

4. Śledź swój portfel i saldo w prawym panelu.

===========================================================
