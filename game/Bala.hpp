#pragma once

#include "../ASCII_Engine/ObjetoDeJogo.hpp"

class Bala : public ObjetoDeJogo {
public:
    Bala(const ObjetoDeJogo &obj, char direcao, int velocidade) 
        : ObjetoDeJogo(obj), direcao(direcao), velocidade(velocidade), dano(10) {}

    void mover() {
        switch (direcao) {
            case 'w': moveUp(velocidade); break;
            case 's': moveDown(velocidade); break;
            case 'a': moveLeft(velocidade); break;
            case 'd': moveRight(velocidade); break;
        }
    }

    char getDirecao() const { return direcao; }
    
    int getDano() const {return dano; }

private:
    char direcao;
    int velocidade;
    int dano;
};