#pragma once

#include "../ASCII_Engine/ObjetoDeJogo.hpp"
#include "Arma.hpp"

class Prisioneiro : public ObjetoDeJogo
{
public:
    Prisioneiro(const ObjetoDeJogo &obj, int life=100, Arma* arma=nullptr, std::string item="Nenhum", char direcao='d') 
        : ObjetoDeJogo(obj), life(life), direcao(direcao), arma(arma), item(item){}

    virtual ~Prisioneiro() {}

    bool isAlive() const { return life != 0; }
    int getLife() const { return life; }

    void sofrerAtaque(int ataque) { life = (life - ataque >= 0) ? (life - ataque) : 0; }
    int atacar() const { return 5; }

    //Verificando se o prisioneiro tem arma e se a arma tem balas
    bool podeAtirar() { 
        if (arma && arma->usar()) {
            return true;
        }
        return false;
    }

    void pegarArma(Arma *arma) {
        this->arma = arma; 
    }

    void pegarItem(std::string item) {
        this->item = item; 
    }

    void adicionarBalas(int balas) { 
        arma->adicionarBalas(balas);
    }

    Arma* getArma() const {
        return arma;
    }

    std::string getItem() const {
        return item;
    }

    //Métodos para lidar com a direção
    void setDirecao(char novaDirecao) { direcao = novaDirecao; }
    char getDirecao() const { return direcao; }

private:
    int life;
    char direcao;
    Arma *arma;
    std::string item;
};
