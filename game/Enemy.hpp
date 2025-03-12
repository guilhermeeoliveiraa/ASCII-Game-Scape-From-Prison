#pragma once

#include "../ASCII_Engine/ObjetoDeJogo.hpp"

class Enemy : public ObjetoDeJogo
{
public:
	Enemy(const ObjetoDeJogo &obj, char direcao='d', int life=30, int velAtaque=3, int velTiro=3) : 
			ObjetoDeJogo(obj), life(life), velAtaque(velAtaque), contAtaque(velAtaque), 
			velTiro(velTiro) ,contTiro(velAtaque),direcao(direcao), arma(nullptr) {}
	
	virtual ~Enemy(){}
	
	bool isAlive() const { return life != 0; }
	
	void sofrerAtaque(int ataque) {
		life = (life - ataque >= 0)?(life - ataque):0;
	}

	//Verificando se o inimigo tem arma e se a arma tem balas
    bool podeAtirar() { 
        if (--contTiro == 0 && arma && arma->usar()) {
			contTiro = velTiro;
            return true;
        }
        return false;
    }

	void pegarArma(Arma *arma) {
        this->arma = arma; 
    }

	Arma* getArma() const {
        return arma;
    }

	int atacar() { 
		if (--contAtaque == 0) {
			contAtaque = velAtaque;
			return 10;
		}
		return 0;
	}

	// Métodos para lidar com a direção
    void setDirecao(char novaDirecao) { direcao = novaDirecao; }
    char getDirecao() const { return direcao; }

private:
	int life;
	int velAtaque, velTiro, contAtaque, contTiro;
	char direcao;
	Arma *arma;
};