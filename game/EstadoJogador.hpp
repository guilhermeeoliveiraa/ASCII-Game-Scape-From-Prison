#pragma once

#include "Arma.hpp"
#include "List.hpp"

// struct EstadoJogador para manter informações entre as fases
struct EstadoJogador {
    int vida;
    int balas;
    std::string arma;
    std::string item;
    char direcao;
    int posY;
    int posX;
    List<std::string> inimigosMortos;
    bool portaoAberto;

    EstadoJogador() : vida(100), balas(3), arma("Nenhuma"), item("Nenhum"), direcao('s'), posY(12), posX(109), portaoAberto(false) {}
};