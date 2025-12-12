# Nome do executável
TARGET = ted

ALUNO = Vitor Kenji Yakushijin Taniguti

# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -std=c99 -fstack-protector-all -Wall -Wextra -O0 -g -ggdb

# Diretórios
SRC_DIR = .
BUILD_DIR = ./build

# 1. Pega TODOS os arquivos .c
ALL_SRCS = $(wildcard $(SRC_DIR)/*.c)

# 2. Identifica os arquivos de teste (que têm main duplicada)
TEST_SRCS = $(wildcard $(SRC_DIR)/teste_visibilidade_*.c)

# 3. Cria a lista final removendo os testes da lista total
SRCS = $(filter-out $(TEST_SRCS), $(ALL_SRCS))

# Gera a lista de objetos baseada apenas nos arquivos filtrados
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

# Regra padrão
all: $(TARGET)

# Regra de compilação dos arquivos de objeto
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	@echo "Compilando $< -> $@"
	$(CC) $(CFLAGS) -c $< -o $@

# Regra de compilação do executável
$(TARGET): $(OBJS)
	@echo "Linkando $(TARGET)..."
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) -lm

# Limpeza de arquivos intermediários e o executável
clean:
	@echo "Limpando arquivos gerados..."
	rm -f $(BUILD_DIR)/*.o $(TARGET)

.PHONY: all clean