#!/usr/bin/env bash

# Uso: ./extrae_obmax.sh entrada.txt salida.dat
# salida.dat tendrá: N  OBMaximo

in="$1"
out="$2"

awk -F'|' '
  # líneas de datos (empiezan por "|" pero no son la cabecera)
  /^\|/ && $2 !~ /Tamaño/ && $3 !~ /Time/ {
      # $2 = Tamaño(N), $6 = OBMaximo
      gsub(/^[ \t]+|[ \t]+$/, "", $2);
      gsub(/^[ \t]+|[ \t]+$/, "", $6);
      print $2, $6;
  }
' "$in" > "$out"
