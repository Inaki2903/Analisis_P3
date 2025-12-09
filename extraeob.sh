#!/usr/bin/env bash

# Uso: ./extrae_ob.sh entrada.txt salida.dat
# salida.dat tendrá: N  OBPromedio

in="$1"
out="$2"

awk -F'|' '
  # líneas que empiezan por "|" y no son la cabecera
  /^\|/ && $2 !~ /Tamaño/ && $3 !~ /Time/ {
      # $2 = Tamaño(N), $4 = OBPromedio
      gsub(/^[ \t]+|[ \t]+$/, "", $2);
      gsub(/^[ \t]+|[ \t]+$/, "", $4);
      print $2, $4;
  }
' "$in" > "$out"
