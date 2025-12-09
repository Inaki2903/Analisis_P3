#!/usr/bin/env bash

# Uso: ./extrae_obmin.sh entrada.txt salida.dat
# salida.dat tendrá: N  OBMinimo

in="$1"
out="$2"

awk -F'|' '
  # líneas de datos (empiezan por "|" pero no son la cabecera)
  /^\|/ && $2 !~ /Tamaño/ && $3 !~ /Time/ {
      # $2 = Tamaño(N), $5 = OBMinimo
      gsub(/^[ \t]+|[ \t]+$/, "", $2);
      gsub(/^[ \t]+|[ \t]+$/, "", $5);
      print $2, $5;
  }
' "$in" > "$out"
