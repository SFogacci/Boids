cmake_minimum_required(VERSION 3.16)
project(progettopf VERSION 0.1.0)

# abilita il supporto per i test, tra cui l'opzione BUILD_TESTING usata sotto
include(CTest)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# richiedi l'uso di C++17, senza estensioni non-standard offerte dal compilatore usato 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# abilita warning
string(APPEND CMAKE_CXX_FLAGS
      " -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion"
      " -Wshadow -Wimplicit-fallthrough -Wextra-semi -Wold-style-cast")

# abilita asserzioni di debug (in gcc), l'address sanitizer e l'undefined-behaviour sanitizer in debug mode
string(APPEND CMAKE_CXX_FLAGS_DEBUG " -D_GLIBCXX_ASSERTIONS -fsanitize=address,undefined -fno-omit-frame-pointer")
string(APPEND CMAKE_EXE_LINKER_FLAGS_DEBUG " -fsanitize=address,undefined -fno-omit-frame-pointer")

# richiedi il componente graphics della libreria SFML, versione 2.5
#   le dipendenze vengono identificate automaticamente
find_package(SFML 2.5 COMPONENTS graphics REQUIRED)
find_package (ROOT COMPONENTS Core Hist HistPainter Gui)

add_executable(main boid.cpp vectors.cpp main.cpp graphics.cpp input.cpp statistics.cpp)
target_link_libraries(main PRIVATE sfml-graphics)
target_link_libraries (main PRIVATE ROOT::Core ROOT::Hist ROOT::HistPainter ROOT::Gui)

# se il testing e' abilitato...
#   per disabilitare il testing, passare -DBUILD_TESTING=OFF a cmake durante la fase di configurazione
if (BUILD_TESTING)

  # aggiungi l'eseguibile all.t
  add_executable(boid.t boids.test.cpp boid.cpp vectors.cpp)
  target_link_libraries(boid.t PRIVATE sfml-graphics)
  add_executable(stats.t statistics.test.cpp boid.cpp vectors.cpp statistics.cpp)
  target_link_libraries(stats.t PRIVATE sfml-graphics)
  # aggiungi l'eseguibile all.t alla lista dei test
  add_test(NAME boid.t COMMAND boid.t)
  add_test(NAME stats.t COMMAND stats.t)

endif()
