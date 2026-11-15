#!/bin/sh
# install.sh - compila e instala Neutron en /usr/local/bin
set -e

SRC="neutrontui.c"
BIN="bin/neutron"
DEST="/usr/local/bin/neutron"

# Dependencias
command -v gcc >/dev/null 2>&1 || { echo "falta gcc"; exit 1; }

# Compilar
echo "compilando $SRC..."
mkdir -p bin
gcc -Wall -Wextra -O2 "$SRC" -o "$BIN"

# Instalar
echo "instalando en $DEST..."
install -Dm755 "$BIN" "$DEST"

echo "listo. prueba con: sudo neutron"