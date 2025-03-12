#pragma once

#include "../ASCII_Engine/ObjetoDeJogo.hpp"

class Arma : public ObjetoDeJogo 
{
public:
    Arma(const ObjetoDeJogo &obj, int balas=10) 
        : ObjetoDeJogo(obj), balas(balas) {}

    virtual ~Arma() {}

    virtual bool usar() 
    {
        if (balas > 0){
            balas--;
            return true;
        }
        return false;
    }

    int getBalas() const { return balas; }

    void adicionarBalas(int balas) { this->balas += balas; }

protected:
    int balas;
};