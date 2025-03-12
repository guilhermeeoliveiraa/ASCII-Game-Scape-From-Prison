#include "../ASCII_Engine/Fase.hpp"

class FaseGameOver : public Fase
{
public:
    FaseGameOver(std::string name, const Sprite &bkg) : Fase(name,bkg) {}
    FaseGameOver(std::string name, const SpriteAnimado &bkg) : Fase(name,bkg) {}
    virtual ~FaseGameOver(){}

    void init() {}

    unsigned run(SpriteBuffer &screen)
    {
        std::string ent;

        //padrão
        draw(screen);
        system("clear");
        show(screen);

        while (true)
        {
            //lendo entrada
            getline(std::cin, ent);

            // Padrão
            update(); //Atualiza as animações
            draw(screen); //Desenha os elementos da screen
            system("clear"); //Limpa a tela do terminal
            show(screen); //Imprime na tela os elementos
        }
    }

private:

};