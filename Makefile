# Nom de l'exécutable
EXEC = mon_programme
TEST_EXEC = run_tests

# Compilateur C++
CXX = g++

# Options de compilation
CXXFLAGS = -std=c++17 -Wall -Wextra -g

# Fichiers source
SOURCES = main.cpp 

# Fichiers objets générés à partir des fichiers source
OBJECTS = $(SOURCES:.cpp=.o)

# Règle par défaut
all: $(EXEC)

# Règle pour générer l'exécutable
$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJECTS)

# Règle pour générer les fichiers objets
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Règle pour nettoyer les fichiers générés
clean:
	rm -f $(OBJECTS) $(TEST_OBJECTS) $(EXEC) $(TEST_EXEC)
