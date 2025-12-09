#!/usr/bin/env bash

# Uso: ./extrae_time.sh entrada.txt salida.dat
# salida.dat tendrá: N  Time

in="$1"
out="$2"

awk -F'|' '
  # líneas de datos (empiezan por "|" pero no son la cabecera)
  /^\|/ && $2 !~ /Tamaño/ && $3 !~ /Time/ {
      # $2 = Tamaño(N), $3 = Time
      gsub(/^[ \t]+|[ \t]+$/, "", $2);
      gsub(/^[ \t]+|[ \t]+$/, "", $3);
      print $2, $3;
  }
' "$in" > "$out"
