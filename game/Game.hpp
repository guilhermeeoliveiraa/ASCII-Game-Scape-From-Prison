#include "Fase0.hpp"
#include "Fase1.hpp"
#include "Fase2.hpp"
#include "FaseEndGame.hpp"
#include "FaseGameOver.hpp"
#include "EstadoJogador.hpp"

// Na criação desse jogo foram realizadas algumas mudanças na Engine:
// No ObjetoDeJogo.hpp foi adicionado o método setSprite()
// No ObjetoDeJogo.hpp foi adicionado o método isActive()
// No Fase.hpp foi adicionado o LEVEL_0

class Game 
{
public:
    Game(){}
    ~Game(){}

    static void run()
    {
        SpriteBuffer buffer(250,65);

        EstadoJogador estado; // Estado compartilhado entre as fases
        
        int ret = Fase::LEVEL_1;

        // Criação dinâmica das fases com os dados do personagem salvo
        while (true){
            
            if (ret == Fase::LEVEL_0) {
                Fase0* fase0 = new Fase0("Fase0", Sprite("rsc/celas.img"), &estado);
                fase0->init();
                ret = fase0->run(buffer);
                buffer.clear();
                delete fase0;
            }
            else if (ret == Fase::LEVEL_1) {
                Fase1* fase1 = new Fase1("Fase1", Sprite("rsc/celas.img"), &estado);
                fase1->init();
                ret = fase1->run(buffer);
                buffer.clear();
                delete fase1;
            }
            else if (ret == Fase::LEVEL_2) {
                Fase2* fase2 = new Fase2("Fase2", Sprite("rsc/celas.img"), &estado);
                fase2->init();
                ret = fase2->run(buffer);
                buffer.clear();
                delete fase2;
            }
            else if (ret == Fase::GAME_OVER) {
                FaseGameOver* fase3 = new FaseGameOver("Fase3", Sprite("rsc/gameover.img"));
                fase3->init();
                ret = fase3->run(buffer);
                buffer.clear();
                delete fase3;
            }
            else if (ret == Fase::END_GAME){
                FaseEndGame* fase4 = new FaseEndGame("Fase4", Sprite("rsc/endgame.img"));
                fase4->init();
                ret = fase4->run(buffer);
                buffer.clear();
                delete fase4;
            }
        }
    }
};