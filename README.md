# 2048start
2048 in C

1. Funcționalități principale
    • Interfață grafică modernă, bazată pe SDL2, pentru afișarea tablei de joc și a numerelor.
    • Mecanica jocului 2048 standard: 
        ◦ Mutarea plăcilor prin săgeți.
        ◦ Combinarea numerelor identice.
        ◦ Generarea de noi plăci după fiecare mutare.
    • Sistem de scor: 
        ◦ Calcularea și afișarea scorului curent.
        ◦ Salvarea și afișarea celui mai mare scor.
        ◦ Animații fluide pentru mișcările și combinațiile plăcilor.
    • Ecran de start și meniuri interactive: 
        ◦ Opțiuni: Start, Instrucțiuni, Ieșire.
        ◦ Salvarea și încărcarea jocului pentru a continua progresul.
        ◦ Efecte sonore și muzică de fundal pentru îmbunătățirea experienței utilizatorului.
    • Detectarea stării jocului (victorie, înfrângere, posibilitatea de a continua după 2048).
    • Mod multiplayer: 
        ◦ Jocul se desfășoară în paralel, fiecare jucător având propria tablă de joc.
        ◦ Mutările se efectuează alternativ, similar principiului jocului de șah cu cronometru.
        ◦ Runda are un timp limitat de 1 minut.
        ◦ Câștigătorul este jucătorul cu scorul cel mai mare la finalul intervalului de timp.
Mod de joc pe nivele:
Nivel ușor: tablă de 5x5 casete, oferind mai mult spațiu pentru mutări.
Nivel mediu: tablă de 4x4 casete, similar versiunii clasice.
Nivel dificil: tablă de 3x3 casete, unde mutările sunt mai limitate.
Nivel expert: tablă de 2x2 casete, provocând jucătorul să obțină scor maxim într-un spațiu extrem de restrâns.

3. Librării necesare
Pentru implementarea acestui proiect, voi folosi următoarele librării:
SDL2 – pentru interfața grafică și gestionarea evenimentelor utilizatorului.
SDL2_ttf – pentru afișarea textului (scor, mesaje informative).
SDL2_mixer – pentru efecte sonore și muzică de fundal.
stdlib.h, stdio.h – pentru alocare de memorie și operații standard.
time.h – pentru generarea numerelor aleatoare necesare plăcilor de joc.

5. Structura proiectului
main.c – Inițializarea jocului, bucla principală.
game_logic.c / game_logic.h – Implementarea regulilor jocului.
render.c / render.h – Funcții pentru desenarea graficii și animațiilor.
input.c / input.h – Gestionarea comenzilor utilizatorului.
save_load.c / save_load.h – Funcții pentru salvarea și încărcarea progresului.
