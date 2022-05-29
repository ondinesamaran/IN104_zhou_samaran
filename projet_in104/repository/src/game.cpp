#include "game.h"
#include "checkpoint.h"
#include "utils.h"
#include "pod.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <cmath>
#include <stdexcept>

Game::Game() : finalCP_({0,0})
{}

Game::Game(std::vector<sf::Vector2f> checkpointsPositions) : finalCP_(checkpointsPositions[0])
{
    unsigned long taille = checkpointsPositions.size();
    otherCPs_.reserve(taille-1);
    for (unsigned long i=1;i<taille;i++)
    {
        otherCPs_.emplace_back(checkpointsPositions[i],i);
    }
    backgroundTexture_.loadFromFile("/home/ensta/projet_in104/repository/Images/background.png");  
    backgroundSprite_.setTexture(backgroundTexture_);
    auto rec = backgroundSprite_.getGlobalBounds();
    backgroundSprite_.scale(sf::Vector2f(16000/rec.width, 9000/rec.height));
    cpPositions_ = checkpointsPositions;
}

void Game::addPod(int j1, int j2)
{
    int nombre_pod = 2;

    pods_.reserve(nombre_pod);
    podsTextures_.reserve(nombre_pod);
    podsSprites_.reserve(nombre_pod);

    Pod pod = Pod({600,600},0.f);
    Pod pod2 = Pod({600,600},0.f);

    sf::Texture podTexture;
    sf::Sprite podSprite;

    podsTextures_.emplace_back(); //création d'une Texture à la fin du vecteur podsTextures_sans argument d'entrée
    podsTextures_[0].loadFromFile("../repository/Images/NMSFighterY.png");  //appelle la fonction load sur le premier élément du vecteur
    // podsTextures_.back().loadFromFile("../repository/Images/NMSFighterY.png");
     //appelle la fonction load sur le dernier élément du vecteur (pour info)
    podsSprites_.emplace_back(podsTextures_[0]); //création d'une Sprite à la fin du vecteur podsSprites_ avec la première Texture du vecteur podsTextures_ en argument d'entrée, tu crées directement une sf::Sprite(podsTextures_[0]) dans le vecteur
    pod.mode = j1;

    pods_.emplace_back(pod);

    sf::Texture podTexture2;
    sf::Sprite podSprite2;

    //podTexture2.loadFromFile("../repository/Images/NMSFighterG.png"); 
    //podsTextures_.emplace_back(podTexture2);
    //podsSprites_.emplace_back(podSprite2);



    podsTextures_.emplace_back(); //création d'une Texture à la fin du vecteur podsTextures_sans argument d'entrée
    podsTextures_[1].loadFromFile("../repository/Images/NMSFighterG.png");  //appelle la fonction load sur le premier élément du vecteur
    // podsTextures_.back().loadFromFile("../repository/Images/NMSFighterY.png");
     //appelle la fonction load sur le dernier élément du vecteur (pour info)
    podsSprites_.emplace_back(podsTextures_[1]); //création d'une Sprite à la fin du vecteur podsSprites_ avec la première Texture du vecteur podsTextures_ en argument d'entrée, tu crées directement une sf::Sprite(podsTextures_[0]) dans le vecteur
    pod2.mode = j2;
    pods_.emplace_back(pod2);
    




    for (int i=0;i<nombre_pod;++i)
    {
    podsSprites_[i].setTexture(podsTextures_[i]);
    scaleToMaxSize(podsSprites_[i],800,800);
    setOriginToCenter(podsSprites_[i]);

    pods_[i].nextCP_=1;
    pods_[i].lapCount_ = 1; // nombre de tours effectués

    }

    

}




void Game::updatePhysics()
{
    
    std::vector<Pod> PodsSnapshot = pods_;
    int taille = size(cpPositions_);
    for (Pod &pod : pods_)
    {
        if (pod.mode==1){
            if(pod.lapCount_ <= NUMBER_OF_LAPS)
            {
                Decision d = pod.getDecision({pods_, cpPositions_});

                float c= 0.85;
            

                if (pod.vel_.x !=0){
                    if (pod.vel_.x <0 &&pod.vel_.y>=0)
                    { 
                    pod.angle_ = M_PI + std::atan(pod.vel_.y/pod.vel_.x) ;
                    }
                    else if (pod.vel_.x <0 &&pod.vel_.y<0)
                    { 
                    pod.angle_ = -M_PI + std::atan(pod.vel_.y/pod.vel_.x) ;
                    }
                    else {pod.angle_ = std::atan(pod.vel_.y/pod.vel_.x);}
                }
                else if (pod.vel_.x ==0)
                {pod.angle_ = std::atan(pod.vel_.y/abs(pod.vel_.y))*M_PI/2;}

                if(norme(pod.pos_ , d.target_)!=0){
                    pod.vel_ = c*(pod.vel_ + d.power_*(d.target_-pod.pos_)/norme(d.target_,pod.pos_));
                    pod.pos_ = pod.pos_ + pod.vel_;
                    }
                else{
                    pod.vel_=c*pod.vel_;
                    pod.pos_=pod.pos_+pod.vel_;
                }
                if (norme(pod.pos_ , d.target_)<500) //Le pod a atteint le CP
                    { 
                        if (pod.nextCP_ == 0 && pod.lapCount_<= NUMBER_OF_LAPS){
                        pod.nextCP_ = 1;
                        pod.lapCount_ += 1;
                        }
                    
                        else if (0 < pod.nextCP_ && pod.nextCP_ < taille) 
                            {
                            pod.nextCP_ += 1;
                            }
                        else {
                            pod.nextCP_ = 0; //FinalCP*
                        }
                    }
                if (norme(pod.pos_ ,{5000,5000})<700)
                { 
                    pod.vel_={0,0};
                }

            }
        }
        else{           // le comptage de tour pour les pods en manuel fait tout beuguer
             Decision d = pod.getDecision({pods_, cpPositions_});

                float c= 0.85;
            
                // on fait une disjonction de cas pour calculer l'angle et qui'il ny ait pas de demi tour ou d'irrégularité
                if (pod.vel_.x !=0){
                    if (pod.vel_.x <0 &&pod.vel_.y>=0)
                    { 
                    pod.angle_ = M_PI + std::atan(pod.vel_.y/pod.vel_.x) ;
                    }
                    else if (pod.vel_.x <0 &&pod.vel_.y<0)
                    { 
                    pod.angle_ = -M_PI + std::atan(pod.vel_.y/pod.vel_.x) ;
                    }
                    else {pod.angle_ = std::atan(pod.vel_.y/pod.vel_.x);}
                }
                else if (pod.vel_.x ==0)
                {pod.angle_ = std::atan(pod.vel_.y/abs(pod.vel_.y))*M_PI/2;}


                // on met a jour position et vitesse
                if(norme(pod.pos_ , d.target_)!=0){
                    pod.vel_ = c*(pod.vel_ + d.power_*(d.target_-pod.pos_)/norme(d.target_,pod.pos_));
                    pod.pos_ = pod.pos_ + pod.vel_;
                    }
                else{
                    pod.vel_=c*pod.vel_;
                    pod.pos_=pod.pos_+pod.vel_;
                }


                if (norme(pod.pos_ , d.target_)<500) //Le pod a atteint le CP test pas top si pod rapide
                    { 
                        if (pod.nextCP_ == 0 && pod.lapCount_<= NUMBER_OF_LAPS){
                        pod.nextCP_ = 1;
                        }
                    
                        else if (0 < pod.nextCP_ && pod.nextCP_ < taille) 
                            {
                            pod.nextCP_ += 1;
                            }
                        else {
                            pod.nextCP_ = 0; //FinalCP
                        }
                    }

                if (norme(pod.pos_ ,{5000,5000})<700) //si le pod passe par la banane il s'arrête
                { 
                    pod.vel_={0,0};
                }
        }
        
        // on aimerait dessiner le nombre de tour de chaque pod en temps réel
        /*
        sf::Text text1;
            sf::Font font;
            if(!font.loadFromFile("/home/ensta/projet_in104/repository/Fredoka-Bold.ttf")){
                printf("error");
            }
            text1.setFont(font);
            text1.setCharacterSize(500);
            text1.setFillColor(sf::Color(255,255,255,200));
            text1.setOutlineThickness(10);
            setTextCenterPosition(text1, 12000, 700);
            int tour = pod.lapCount_;
            sf::String txt = std::to_string(tour);
            text1.setString("tour" + txt + "/3");
       */

    }

    physicsTime += PHYSICS_TIME_STEP;
    
    
}

void Game::updateGraphics(sf::Time frameTime)
{
  //utiliser la position de la podSprite (ancienne position graphique) et la position du pod
  //(prochaine position rÃ©elle), physicsTime_, lastFrameTime_ et frameTime pour Ã©valuer la nouvelle position graphique
    float c = (physicsTime - frameTime)/(frameTime - lastFrameTime);

    float sec1  = physicsTime.asSeconds();
    float sec2 = frameTime.asSeconds();
    float sec3 = lastFrameTime.asSeconds();
    printf("c = %f\n", c);
    printf("physicsTime = %f, frameTime = %f, lastFrameTime = %f\n", sec1, sec2, sec3);
    
    int nb_pods = podsSprites_.size();
    for (int i=0; i<nb_pods; ++i){
        sf::Vector2f pos_sprite = podsSprites_[i].getPosition();

        // mettre une image entre deux update de la physique sinon saccadé
        if (c>1)  {
            podsSprites_[i].setPosition( pos_sprite + (pods_[i].pos_ - pos_sprite)/c ); 
            }   
        else {
            podsSprites_[i].setPosition(pods_[i].pos_);
        }
        
        podsSprites_[i].setRotation(pods_[i].angle_*180.f/M_PI);
    }

    lastFrameTime = frameTime;


    
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(backgroundSprite_, states);
    target.draw(finalCP_, states);

    sf::Text text1;
    sf::Font font;
    if(!font.loadFromFile("/home/ensta/projet_in104/repository/Fredoka-Bold.ttf")){
        printf("error");
    }
    text1.setFont(font);
    text1.setCharacterSize(500);
    text1.setFillColor(sf::Color(255,255,255,200));
    text1.setOutlineThickness(10);
    setTextCenterPosition(text1, 12000, 300);
    int tour = pods_[0].lapCount_;
    sf::String txt = std::to_string(tour);
    text1.setString("tour : " + txt + "/3");
    target.draw(text1);

    for (const auto &cp : otherCPs_)
    {
        target.draw(cp, states);
    }

     for (const auto &podSprite : podsSprites_)
    {
        target.draw(podSprite, states);
    } 
}