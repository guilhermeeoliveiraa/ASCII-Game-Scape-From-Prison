#include "../ASCII_Engine/Fase.hpp"
#include <algorithm>

#include "Prisioneiro.hpp"
#include "Enemy.hpp"
#include "Arma.hpp"
#include "Bala.hpp"
#include "EstadoJogador.hpp"
#include "List.hpp"

class Fase1 : public Fase
{
public:
    Fase1(std::string name, const Sprite &bkg, EstadoJogador* estado) : Fase(name,bkg), estado(estado) {}
    Fase1(std::string name, const SpriteAnimado &bkg, EstadoJogador* estado) : Fase(name,bkg), estado(estado) {}
    virtual ~Fase1(){}

    void init()
    {
        // Criando primeiro os itens do cenário que passar por trás do prisioneiro quando colididos 

        beliche = new ObjetoDeJogo("Beliche2", Sprite("rsc/beliche.img"), 7, 82);
        objs.push_back(beliche);

        vaso = new ObjetoDeJogo("Vaso2", Sprite("rsc/vaso.img"), 8, 136);
        objs.push_back(vaso);

        // Criando prisioneiro
        criarPrisioneiro();

        // Criando inventário
        criarInventario();

        // Criando armas para os guardas
        
        Arma* arma1 = new Arma(ObjetoDeJogo("Arma1", Sprite("rsc/arma.img"), 35 , 90));
        armas.push_back(arma1);
        objs.push_back(armas.back());

        // Criando guardas

        guardaDormindo = new Enemy(ObjetoDeJogo("Guarda1",SpriteAnimado("rsc/guarda.anm",3),31,85));
        guardas.push_back(guardaDormindo);
        objs.push_back(guardas.back());
        
        guardaAcordado = new Enemy(ObjetoDeJogo("Guarda2",SpriteAnimado("rsc/guardaArmadoD.anm",3),32,87),'d',30,3,6);
        guardas.push_back(guardaAcordado);
        objs.push_back(guardas.back());

        // Equipando as armas nos guardas e ocultando elas para o jogador

        guardaAcordado->pegarArma(arma1);
        arma1->desativarObj();

        // Cenário

        objs.push_back(new ObjetoDeJogo("Beliche1", Sprite("rsc/beliche.img"), 7, 11));
        objs.push_back(new ObjetoDeJogo("Beliche3", Sprite("rsc/beliche.img"), 7, 153));

        objs.push_back(new ObjetoDeJogo("Vaso1", Sprite("rsc/vaso.img"), 8, 65));
        objs.push_back(new ObjetoDeJogo("Vaso3", Sprite("rsc/vaso.img"), 8, 207));

        saidaE = new ObjetoDeJogo("SE", Sprite("rsc/saidaEsquerda.img"), 48, 0);
        objs.push_back(saidaE);

        saidaD = new ObjetoDeJogo("SD", Sprite("rsc/saidaDireita.img"), 48, 225);
        objs.push_back(saidaD);

        portaoInteracao = new ObjetoDeJogo("PortaoInteracao", Sprite("rsc/portao.img"), 27, 105);
        objs.push_back(portaoInteracao);


        //Colisões

        objs.push_back(new ObjetoDeJogo("PV1", Sprite("rsc/paredeVertical.img"), 6, 74));
        colisoes.push_back(objs.back());

        objs.push_back(new ObjetoDeJogo("PV2", Sprite("rsc/paredeVertical.img"), 6, 145));
        colisoes.push_back(objs.back());

        objs.push_back(new ObjetoDeJogo("PE", Sprite("rsc/paredeEsquerda.img"), 27, 10));
        colisoes.push_back(objs.back());

        objs.push_back(new ObjetoDeJogo("PD", Sprite("rsc/paredeDireita.img"), 27, 192));
        colisoes.push_back(objs.back());

        objs.push_back(new ObjetoDeJogo("PM1", Sprite("rsc/paredeMeio.img"), 27, 50));
        colisoes.push_back(objs.back());

        objs.push_back(new ObjetoDeJogo("PM2", Sprite("rsc/paredeMeio.img"), 27, 121));
        colisoes.push_back(objs.back());

        objs.push_back(new ObjetoDeJogo("PT1", Sprite("rsc/portao.img"), 27, 34));
        colisoes.push_back(objs.back());

        objs.push_back(new ObjetoDeJogo("PT2", Sprite("rsc/portao.img"), 27, 176));
        colisoes.push_back(objs.back());

        objs.push_back(new ObjetoDeJogo("PFE", Sprite("rsc/paredeFundoPassagem.img"), 6, 0));
        colisoes.push_back(objs.back());

        objs.push_back(new ObjetoDeJogo("PFD", Sprite("rsc/paredeFundoPassagem.img"), 6, 216));
        colisoes.push_back(objs.back());

        portaoColisao = new ObjetoDeJogo("PortaoColisao", Sprite("rsc/portaoCurto.img"), 28, 105);
        objs.push_back(portaoColisao);
        colisoes.push_back(objs.back());

        if (estado->portaoAberto){
            portaoInteracao->desativarObj();
            portaoColisao->desativarObj();
        } 
        else {
            guardaAcordado->desativarObj();
        }
    }

    unsigned run(SpriteBuffer &screen)
    {
        std::string ent;

        // Atualizar inventario
        atualizarInventario();
        // Verificar mortes
        verificarMortes();

        //padrão
        draw(screen);
        system("clear");
        show(screen);

        while (true)
        {
            //lendo entrada
            getline(std::cin, ent);

            //processando entradas
            int posL = prisioneiro->getPosL(), posC = prisioneiro->getPosC();

            if (ent == "w" && prisioneiro->getPosL() > 8) {
                prisioneiro->moveUp(4);
            }
            else if (ent == "s" && prisioneiro->getPosL() < screen.getAltura() - 18) {
                prisioneiro->moveDown(4);
            }
            else if (ent == "a") {
                prisioneiro->moveLeft(6);
                prisioneiro->setDirecao('a');
            }
            else if (ent == "d") {
                prisioneiro->moveRight(6);
                prisioneiro->setDirecao('d');
            }
            else if (ent == "x") {
                // Verificando se o prisioneiro consegue atirar
                if (prisioneiro->podeAtirar()) {
                    // Criando distancia pro jogador não se atingir com a própria bala
                    int distanciaY;
                    int distanciaX;
                    char direcao = prisioneiro->getDirecao();
                    if (direcao == 'a'){
                        distanciaY = 3;
                        distanciaX = -4;
                    }
                    else if (direcao == 'd'){
                        distanciaY = 3;
                        distanciaX = 14;
                    }
                    balas.push_back(new Bala(ObjetoDeJogo("Bala", Sprite("rsc/bala.img"), 
                                                prisioneiro->getPosL() + distanciaY, 
                                                prisioneiro->getPosC() + distanciaX), 
                                                prisioneiro->getDirecao(), 5));
                    objs.push_back(balas.back());
                }
            }
            else if (ent == "e") {
                if (prisioneiro->getItem() == "Canivete"){
                    for (auto guarda : guardas) {
                        if (prisioneiro->colideCom(*guarda)) {
                            guarda->sofrerAtaque(10);
                        }
                    }
                    if (prisioneiro->colideCom(*portaoInteracao)) {
                        portaoInteracao->desativarObj();
                        portaoColisao->desativarObj();
                        guardaDormindo->sofrerAtaque(30);
                        guardaDormindo->desativarObj();
                        guardaAcordado->ativarObj();
                        estado->portaoAberto = true;
                    }
                }
            }
            else if (ent == "f") {
                if (prisioneiro->colideCom(*vaso)) {
                    prisioneiro->pegarItem("Canivete");
                    estado->item = "Canivete";
                }
            }

            // Verificando se o prisioneiro colide com blocos
            if (colideComBloco()) 
            prisioneiro->moveTo(posL, posC);

            // Verificando se o priseiro está morto
            if (!prisioneiro->isAlive())
                return Fase::GAME_OVER;

            // Verificando se o priseiro matou todos os inimigos
            std::vector<std::string> procurados = {"Guarda2", "Guarda3", "Guarda4", "Guarda5", "Guarda6", "Guarda7", "Guarda8"};
            int encontrados = 0;
            for (const std::string& elemento : procurados) {
                if (std::find(estado->inimigosMortos.begin(), estado->inimigosMortos.end(), elemento) != estado->inimigosMortos.end()) {
                    encontrados++;
                }
            }
            if (encontrados == 7) {
                return Fase::END_GAME;
            }

            // Verificando se entrou em uma das portas
            if (prisioneiro->colideCom(*saidaE)) {
                estado->posY = 48;
                estado->posX = 213;
                return Fase::LEVEL_0;
            } 
            else if (prisioneiro->colideCom(*saidaD)) {
                estado->posY = 48;
                estado->posX = 4;
                return Fase::LEVEL_2;
            }

            // Atualizar armas
            atualizarArmas();
            // Atualizar inventario
            atualizarInventario();
            // Atualizar balas
            atualizarBalas();
            // Verificar ataques
            verificarAtaques();
            // Verificar mortes
            verificarMortes();

            // Padrão
            update(); //Atualiza as animações
            draw(screen); //Desenha os elementos da screen
            system("clear"); //Limpa a tela do terminal
            show(screen); //Imprime na tela os elementos
        }
    }

    bool colideComBloco() const
    {
        for (auto it = colisoes.begin(); it != colisoes.end(); ++it) {
            if (prisioneiro->colideCom(**it)) {
                return true;
            }
        }
        return false;
    }

    void atualizarBalas()
    {
        for (auto it = balas.begin(); it != balas.end();) {
            (*it)->mover();
            // Verificando se a bala colide com o jogador
            if ((*it)->colideCom(*prisioneiro)){
                prisioneiro->sofrerAtaque((*it)->getDano());
                estado->vida = prisioneiro->getLife();
                (*it)->desativarObj();
                break; // Continua com a próxima bala
            }
            // Verificando se a bala colide com o cenario
            for (auto objColisao : colisoes) {
                if ((*it)->colideCom(*objColisao)) {
                    (*it)->desativarObj();
                    break; // Continua com a próxima bala
                }
            }
            // Verificando se a bala colide com inimigo
            for (auto guarda : guardas) {
                if (guarda->isAlive() && (*it)->colideCom(*guarda)) {
                    guarda->sofrerAtaque((*it)->getDano());
                    (*it)->desativarObj();
                    break; // Continua com a próxima bala
                }
            }
            ++it;
        }
    }

    void atualizarArmas()
    {
        // Verificar se o personagem colide com armas no chão
        for (auto it = armas.begin(); it != armas.end(); ) {
            auto arma = *it;
            if (prisioneiro->colideCom(*arma)) {
                if (prisioneiro->getArma()) {
                    prisioneiro->adicionarBalas(arma->getBalas());
                } else {
                    prisioneiro->pegarArma(arma);
                }
                // Salvando as balas e a arma do personagem quando ele mudar de level
                estado->balas = prisioneiro->getArma()->getBalas();
                estado->arma = "Pistola";

                // Removendo da lista objs
                auto itObjs = std::find(objs.begin(), objs.end(), arma);
                if (itObjs != objs.end()) {
                    objs.erase(itObjs);
                }
                // Removendo da lista armas
                it = armas.erase(it);
            } else {
                ++it;
            }
        }
    }

    void verificarMortes()
    {
        // Verificando quais guardas ja foram mortos para não surgirem novamente entre as fases
        for (auto guarda : guardas) {
            for (std::string nomeGuarda : estado->inimigosMortos) {
                if (guarda->getName() == nomeGuarda){
                    guarda->desativarObj();
                }
            }
        }

        // Verificar quando um guarda morre, salvando sua morte e dropando sua arma
        for (auto guarda : guardas) {
            if (!guarda->isAlive()){
                estado->inimigosMortos.push_back(guarda->getName()); //Salvando nome do guarda que foi morto
                if(guarda->getArma()){
                    guarda->getArma()->ativarObj();
                }
                guarda->desativarObj();
            }
        }
    }

    void verificarAtaques()
    {
        for (auto guarda : guardas) {
            if (prisioneiro->colideCom(*guarda)) {
                prisioneiro->sofrerAtaque(guarda->atacar());
                estado->vida = prisioneiro->getLife();
            }
            if (guarda->isActive() && guarda->podeAtirar()) {
                balas.push_back(new Bala(ObjetoDeJogo("Bala", Sprite("rsc/bala.img"), guarda->getPosL() + 3, guarda->getPosC() + 14), guarda->getDirecao(), 5));
                objs.push_back(balas.back());
            }
        }
    }

    void atualizarInventario()
    {
        // Verificando como deve estar a barra de vida e a munição
        std::string tamanhoVida = std::string(prisioneiro->getLife()*41/100,'#');
        barraVida1->setText(tamanhoVida);
        barraVida2->setText(tamanhoVida);
        if (prisioneiro->getArma())
            numeroMunicao->setText("Balas: " + std::to_string(prisioneiro->getArma()->getBalas()));
        else
            numeroMunicao->setText("");

        // Verificando quais itens são mostrados no inventário
        if (prisioneiro->getItem() == "Canivete") {
            chaveInventario->desativarObj();
            caniveteInventario->ativarObj();
        } 
        else if (prisioneiro->getItem() == "Chave") {
            caniveteInventario->desativarObj();
            chaveInventario->ativarObj();
        }
        // Verificar qual arma é mostrada no inventário e qual sprite o personagem deve usar
        if (prisioneiro->getArma()) {
            armaInventario->ativarObj();
            if (prisioneiro->getDirecao() == 'a')
                prisioneiro->setSprite(SpriteAnimado("rsc/prisioneiroArmadoE.anm", 2));
            if (prisioneiro->getDirecao() == 'd')
                prisioneiro->setSprite(SpriteAnimado("rsc/prisioneiroArmadoD.anm", 2));
        } 
        else {
            prisioneiro->setSprite(SpriteAnimado("rsc/prisioneiro.anm", 2));
            armaInventario->desativarObj();
        }
    }

    void criarInventario()
    {
        caniveteInventario = new ObjetoDeJogo("CaniveteInventario", Sprite("rsc/caniveteInventario.img"), 58, 186);
        objs.push_back(caniveteInventario);
        caniveteInventario->desativarObj();

        chaveInventario = new ObjetoDeJogo("ChaveInventario", Sprite("rsc/chaveInventario.img"), 59, 186);
        objs.push_back(chaveInventario);
        chaveInventario->desativarObj();

        armaInventario = new ObjetoDeJogo("ArmaInventario", Sprite("rsc/armaInventario.img"), 58, 125);
        objs.push_back(armaInventario);
        armaInventario->desativarObj();

        std::string tamanhoVida = std::string(estado->vida*41/100,'#');
        objs.push_back(new ObjetoDeJogo("BarraVida1",TextSprite(tamanhoVida),60,40));
	    SpriteBase *tmp1 = const_cast<SpriteBase*> (objs.back()->getSprite());
	    barraVida1 = dynamic_cast<TextSprite*> (tmp1);
        objs.push_back(new ObjetoDeJogo("BarraVida2",TextSprite(tamanhoVida),61,40));
	    SpriteBase *tmp2 = const_cast<SpriteBase*> (objs.back()->getSprite());
	    barraVida2 = dynamic_cast<TextSprite*> (tmp2);

        objs.push_back(new ObjetoDeJogo("NumeroMunicao",TextSprite(""),62,136));
        SpriteBase *tmp3 = const_cast<SpriteBase*> (objs.back()->getSprite());
	    numeroMunicao = dynamic_cast<TextSprite*> (tmp3);
    }

    void criarPrisioneiro()
    {
        //criando prisioneiro usando os dados de outras fases
        prisioneiro = new Prisioneiro(ObjetoDeJogo("Prisioneiro", SpriteAnimado("rsc/prisioneiro.anm", 2), estado->posY, estado->posX), 
            estado->vida,
            nullptr,
            estado->item,
            estado->direcao);
        objs.push_back(prisioneiro);

        //criando arma do prisioneiro se ele trouxer de outra fase
        if (estado->arma == "Pistola"){
            prisioneiro->pegarArma(new Arma(ObjetoDeJogo("Arma1", Sprite("rsc/arma.img"), 34 , 108), estado->balas));
        }
    }

private:
    Prisioneiro* prisioneiro;  // O personagem principal controlado pelo jogador
    ObjetoDeJogo* caniveteInventario; // Canivete mostrado no inventário
    ObjetoDeJogo* chaveInventario; // Chave mostrada no inventário
    ObjetoDeJogo* armaInventario; // Arma mostrada no inventário
    TextSprite* barraVida1; // Parte superior da barra de vida
    TextSprite* barraVida2; // Parte inferior da barra de vida
    TextSprite* numeroMunicao; // Numero de munição no inventário
    List<Enemy*> guardas;  // Lista de inimigos na fase
    List<ObjetoDeJogo*> colisoes;  // Objetos que bloqueiam movimento
    List<Arma*> armas;  // Lista de armas da fase
    List<Bala*> balas;  // Lista de balas que estão ativas na fase
    EstadoJogador* estado; // Estado do jogador que vai ser passado entre as fases

    ObjetoDeJogo* portaoColisao; // Portão com colisão que bloqueia o prisioneiro
    ObjetoDeJogo* portaoInteracao; // Portão sem colisão que o prisioneiro pode interagir
    ObjetoDeJogo* beliche; // Beliche que o prisioneiro pode interagir
    ObjetoDeJogo* vaso; // Vaso que o prisioneiro pode interagir
    ObjetoDeJogo* saidaE; // Saída da esquerda
    ObjetoDeJogo* saidaD; // Saída da direita
    Enemy* guardaDormindo; // Guarda quando ainda está dormindo
    Enemy* guardaAcordado; // GUarda quando acordar
};