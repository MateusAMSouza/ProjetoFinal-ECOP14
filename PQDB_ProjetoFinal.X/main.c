//UNIFEI - 2021.2
//Disciplina: ECOP14
//Nome: Mateus Alexandre Martins de Souza
//Matrícula: 2021004023

#include <proc/pic18f4520.h>
#include "lcd.h"
#include "keypad.h"
#include "config.h"
#include "ssd.h"
#include "bits.h"

void Start(void) {
    float t;
    lcdCommand(0x80);
    lcdString("Bem-vindo!");
    lcdCommand(0xC0);
    lcdString("Como jogar:");
    for (t = 0; t < 5000; t++);
    lcdCommand(0x80);
    lcdString("Pedra(P): ");
    lcdCommand(0xC0);
    lcdString("Vence de T e L  ");
    for (t = 0; t < 7000; t++);
    lcdCommand(0xC0);
    lcdString("Perde para p e S");
    for (t = 0; t < 7000; t++);
    lcdCommand(0x80);
    lcdString("Papel(p): ");
    lcdCommand(0xC0);
    lcdString("Vence de P e S  ");
    for (t = 0; t < 7000; t++);
    lcdCommand(0xC0);
    lcdString("Perde para T e L");
    for (t = 0; t < 7000; t++);
    lcdCommand(0x80);
    lcdString("Tesoura(T): ");
    lcdCommand(0xC0);
    lcdString("Vence de p e L  ");
    for (t = 0; t < 7000; t++);
    lcdCommand(0xC0);
    lcdString("Perde para P e S");
    for (t = 0; t < 7000; t++);
    lcdCommand(0x80);
    lcdString("Spock(S):  ");
    lcdCommand(0xC0);
    lcdString("Vence de P e T  ");
    for (t = 0; t < 7000; t++);
    lcdCommand(0xC0);
    lcdString("Perde para p e L");
    for (t = 0; t < 7000; t++);
    lcdCommand(0x80);
    lcdString("Lagarto(L): ");
    lcdCommand(0xC0);
    lcdString("Vence de p e S  ");
    for (t = 0; t < 7000; t++);
    lcdCommand(0xC0);
    lcdString("Perde para P e T");
    for (t = 0; t < 7000; t++);
    lcdInit();
    lcdString("Num. de jogos:  ");
    lcdCommand(0xC0);
    lcdString("Y=1|X=3|A=7|B=99");
}

unsigned int NumJogos(void) {
    unsigned char fim;
    unsigned int at = 0, ant = 0, tec;
    volatile float t;
    for (t = 0; t < 5000; t++) {
        kpDebounce();
        at = kpRead();
        if (at != ant) {
            for (tec = 5; tec < 10; tec++) {
                if (bitTst(at, tec)) {
                    fim = kpReadKey();
                    kpDebounce();
                    t = 5000;
                }
            }
        }
    }
    switch (fim) {
        case 'X':
            return 3;
            break;
        case 'Y':
            return 1;
            break;
        case 'B':
            return 99;
            break;
        case 'A':
            return 7;
            break;
    }
}

void Jogador1(void) {
    float t;
    lcdCommand(0x80);
    lcdString("Jogador 1       ");
    lcdCommand(0xC0);
    lcdString("Escolha:        ");
    for (t = 0; t < 3500; t++);
    lcdCommand(0x80);
    lcdString("L=P, U=p, R=T");
    lcdCommand(0xC0);
    lcdString("D=L ou S=S ");
}

void Jogador2(void) {
    float t;
    lcdCommand(0x80);
    lcdString("Jogador 2       ");
    lcdCommand(0xC0);
    lcdString("Escolha:        ");
    for (t = 0; t < 3500; t++);
    lcdCommand(0x80);
    lcdString("Y=P, X=p, A=T");
    lcdCommand(0xC0);
    lcdString("B=L ou s=S ");
}

char Jogada(unsigned char j) {
    switch (j) {
        case 'U':
            return 'p';
            break;
        case 'L':
            return 'P';
            break;
        case 'D':
            return 'L';
            break;
        case 'R':
            return 'T';
            break;
        case 'S':
            return 'S';
            break;
        case 'X':
            return 'p';
            break;
        case 'A':
            return 'T';
            break;
        case 'B':
            return 'L';
            break;
        case 'Y':
            return 'P';
            break;
        case 's':
            return 'S';
            break;
    }
}

char Versus(unsigned char j1, unsigned char j2) {
    char v1, v2;
    float t;
    v1 = Jogada(j1);
    v2 = Jogada(j2);
    lcdInit();
    lcdCommand(0x80);
    lcdString("J1: ");
    lcdChar(v1);
    lcdString("  ||  J2: ");
    lcdChar(v2);
    if (v1 == v2) {
        lcdCommand(0xC0);
        lcdString("Empate!");
        return '0';
    } else {
        lcdCommand(0xC0);
        switch (v1) {
            case 'P':
                if (v2 == 'T' || v2 == 'L') {
                    lcdString("J1 venceu!");
                    return '1';
                } else {
                    lcdString("J2 venceu!");
                    return '2';
                }
                break;
            case 'p':
                if (v2 == 'P' || v2 == 'S') {
                    lcdString("J1 venceu!");
                    return '1';
                } else {
                    lcdString("J2 venceu!");
                    return '2';
                }
                break;
            case 'T':
                if (v2 == 'p' || v2 == 'L') {
                    lcdString("J1 venceu!");
                    return '1';
                } else {
                    lcdString("J2 venceu!");
                    return '2';
                }
                break;
            case 'S':
                if (v2 == 'P' || v2 == 'T') {
                    lcdString("J1 venceu!");
                    return '1';
                } else {
                    lcdString("J2 venceu!");
                    return '2';
                }
                break;
            case 'L':
                if (v2 == 'p' || v2 == 'S') {
                    lcdString("J1 venceu!");
                    return '1';
                } else {
                    lcdString("J2 venceu!");
                    return '2';
                }
                break;
        }
    }
}

void Placar(unsigned int c1, unsigned int c2) {
    ssdDigit(((c1 / 10) % 10), 0);
    ssdDigit((c1 % 10), 1);
    ssdDigit(((c2 / 10) % 10), 2);
    ssdDigit((c2 % 10), 3);
    ssdUpdate();
}

void FimDeJogo(unsigned int c1, unsigned int c2) {
    float t;
    lcdInit();
    lcdCommand(0xC0);
    lcdString("Placar Final:");
    lcdCommand(0x80);
    if (c1 > c2) {
        lcdString("J1 Venceu!  ");
    } else {
        lcdString("J2 Venceu!  ");
    }
    for (t = 0; t < 1000; t++) {
        Placar(c1, c2);
    }
}

void main(void) {
    unsigned char slot, j1 = 0, j2 = 0, cont;
    unsigned int atual = 0, ant = 0, tecla, c1 = 0, c2 = 0, partida = 0, final;
    volatile float t;
    lcdInit();
    kpInit();
    ssdInit();
    TRISD = 0x00;
    Start();
    final = NumJogos();
    lcdInit();
    lcdString("Partida:");
    lcdCommand(0xC0);
    lcdString("Melhor de ");
    lcdChar((final % 100) + 48);
    for (t = 0; t < 5000; t++);
    PORTD = partida;
    for (;;) {
        switch (slot) {
            case 0:
                lcdInit();
                atual = 0;
                ant = 0;
                Jogador1();
                for (t = 0; t < 5000; t++) {
                    kpDebounce();
                    atual = kpRead();
                    if (atual != ant) {
                        for (tecla = 0; tecla < 5; tecla++) {
                            if (bitTst(atual, tecla)) {
                                j1 = kpReadKey();
                                lcdInit();
                                lcdString("J1 escolhido!");
                                t = 4750;
                                slot = 1;
                            }
                        }
                    }
                }
                break;
            case 1:
                lcdInit();
                atual = 0;
                ant = 0;
                Jogador2();
                for (t = 0; t < 5000; t++) {
                    kpDebounce();
                    atual = kpRead();
                    if (atual != ant) {
                        for (tecla = 5; tecla < 10; tecla++) {
                            if (bitTst(atual, tecla)) {
                                j2 = kpReadKey();
                                lcdInit();
                                lcdString("J2 escolhido!");
                                t = 4750;
                                slot = 2;
                            }
                        }
                    }
                }
                break;
            case 2:
                cont = Versus(j1, j2);
                if (cont == '1') {
                    c1++;
                } else if (cont == '2') {
                    c2++;
                }
                for (t = 0; t < 7000; t++);
                slot = 3;
                break;
            case 3:
                partida++;
                lcdInit();
                lcdString("Placar (Jogo: ");
                lcdChar((partida % 100) + 48);
                lcdString(") ");
                lcdCommand(0xC0);
                lcdString("[J1]x[J2]:");
                for (t = 0; t < 500; t++) {
                    Placar(c1, c2);
                }
                slot = 4;
                break;
            case 4:
                PORTD = partida;
                slot = 5;
                break;
            case 5:
                if (partida >= final) {
                    FimDeJogo(c1, c2);
                } else {
                    slot = 6;
                }
                break;
            default:
                slot = 0;
                break;
        }
    }
}