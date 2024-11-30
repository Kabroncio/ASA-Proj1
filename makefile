# Nome do executável
EXEC = a.out

# Comando de compilação
CXX = g++
CXXFLAGS = -std=c++11 -O3 -Wall

# Arquivo fonte
SRC = proj.cpp

# Regra padrão
all: $(EXEC)

# Regra para compilar o programa
$(EXEC): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -lm

# Regra para executar o programa
run: $(EXEC)
	./$(EXEC) < input1.txt

# Regra para limpar os arquivos gerados
clean:
	rm -f $(EXEC)
