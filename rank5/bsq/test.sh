#!/bin/bash

BIN=./bsq   # change si ton exécutable a un autre nom

echo "=== TEST BSQ ==="

run_test() {
    NAME="$1"
    FILE="$2"

    echo -e "\n--- $NAME ---"
    echo "Input:"
    cat "$FILE"
    echo -e "\nOutput:"
    $BIN "$FILE"
}

mkdir -p tests

###############################################
# 1) MAP VALIDE (celle de l'exemple)
###############################################
cat > tests/valid1.txt << EOF
9 . o x
...........................
....o......................
............o..............
...........................
....o......................
...............o...........
...........................
......o..............o.....
..o.......o................
EOF

###############################################
# 2) MAP AVEC HEADER INVALIDE
###############################################
cat > tests/bad_header1.txt << EOF
9 . o
.......
EOF

cat > tests/bad_header2.txt << EOF
9 . o x y
.......
EOF

cat > tests/bad_header3.txt << EOF
9 . . x
.......
EOF

cat > tests/bad_header4.txt << EOF
9 . o x   truc
.......
EOF

###############################################
# 3) MAP AVEC LIGNES DE LONGUEURS DIFFÉRENTES
###############################################
cat > tests/bad_lines1.txt << EOF
3 . o x
.....
....
.....
EOF

###############################################
# 4) MAP AVEC CARACTÈRES INVALIDES
###############################################
cat > tests/bad_chars1.txt << EOF
3 . o x
..a..
.....
.....
EOF

###############################################
# 5) MAP AVEC TROP DE LIGNES
###############################################
cat > tests/bad_extra_lines.txt << EOF
2 . o x
.....
.....
.....
EOF

###############################################
# 6) MAP AVEC PAS ASSEZ DE LIGNES
###############################################
cat > tests/bad_missing_lines.txt << EOF
4 . o x
.....
.....
EOF

###############################################
# 7) MAP VIDE APRÈS HEADER
###############################################
cat > tests/bad_empty_after_header.txt << EOF
3 . o x

.....
.....
EOF

###############################################
# 8) MAP AVEC SEULEMENT DES OBSTACLES
###############################################
cat > tests/only_obstacles.txt << EOF
4 . o x
oooo
oooo
oooo
oooo
EOF

###############################################
# 9) MAP AVEC UNE SEULE CASE
###############################################
cat > tests/one_cell.txt << EOF
1 . o x
.
EOF

###############################################
# LANCEMENT DES TESTS
###############################################

run_test "VALID MAP" tests/valid1.txt
run_test "HEADER MANQUANT" tests/bad_header1.txt
run_test "HEADER TROP LONG" tests/bad_header2.txt
run_test "HEADER CARACTÈRES IDENTIQUES" tests/bad_header3.txt
run_test "HEADER AVEC MOTS EN PLUS" tests/bad_header4.txt
run_test "LIGNES DE LONGUEURS DIFFÉRENTES" tests/bad_lines1.txt
run_test "CARACTÈRES INVALIDES" tests/bad_chars1.txt
run_test "TROP DE LIGNES" tests/bad_extra_lines.txt
run_test "PAS ASSEZ DE LIGNES" tests/bad_missing_lines.txt
run_test "LIGNE VIDE APRÈS HEADER" tests/bad_empty_after_header.txt
run_test "QUE DES OBSTACLES" tests/only_obstacles.txt
run_test "UNE SEULE CASE" tests/one_cell.txt

echo -e "\n=== FIN DES TESTS ==="
