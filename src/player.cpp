#include "gameobject.hpp"
#include "player.hpp"
#include "components/text.hpp"
#include "components/image.hpp"
#include "log.h"
#include "vector.hpp"
#include "keyword.hpp"
#include "gameglobals.hpp"
#include <sstream>
#include "game.hpp"


#define nframes 4

using namespace engine;

bool Player::init()
{
    engine::GameObject::init();
    active_instrument = instruments[globals::banjo];

    for(auto instrument : instruments){
        instrument.second.init();
    }
    //if(&active_instrument == NULL){

      if(sprites[globals::banjo] != NULL)
        active_sprite = sprites[globals::banjo];
      if(sprites[globals::eletric_guitar] != NULL)
        sprites[globals::eletric_guitar]->setState(Component::State::disabled);
      if(sprites[globals::accordion] != NULL)
        sprites[globals::accordion]->setState(Component::State::disabled);
    //}

    //INFO("x"<<physics.collisionBox.x<<"  y"<<physics.collisionBox.y <<"  w"<<physics.collisionBox.w<< "    h"<< physics.collisionBox.h)
    return true;
}

bool Player::shutdown()
{
    engine::GameObject::shutdown();
    return true;
}

bool Player::draw()
{
    engine::GameObject::draw();
    return true;
}

bool Player::update()
{
    handlePlayer();

    GameObject::update();

    int collisionAdjust = 0;
    physics.collisionBox.x = physics.position.getX() + collisionAdjust;
    physics.collisionBox.y = physics.position.getY() + collisionAdjust;
    physics.collisionBox.w = w - collisionAdjust;
    physics.collisionBox.h = h - collisionAdjust;

    return true;
}
bool Player::moveDown(){
    // Update Velocity
    int componentX = 0;
    int componentY = defaultVel;

    Vector2D move(componentX,componentY);
    physics.velocity = move;
    active_sprite->changeAnimation(globals::moveDown);
    active_sprite->activeAnimation->clock.resumeTimer();
    return true;
}

bool Player::moveUp(){
    // Update Velocity
    int componentX = 0;
    int componentY = -1*defaultVel;

    Vector2D move(componentX,componentY);
    physics.velocity = move;
    active_sprite->changeAnimation(globals::moveUp);
    active_sprite->activeAnimation->clock.resumeTimer();
    return true;
}

bool Player::moveLeft(){
    // Update Velocity
    int componentX = -1*defaultVel;

    int componentY = 0;

    Vector2D move(componentX,componentY);
    physics.velocity = move;
    active_sprite->changeAnimation(globals::moveLeft);
    active_sprite->activeAnimation->clock.resumeTimer();
    return true;
}

bool Player::moveRight(){
    // Update Velocity

    int componentX = defaultVel;
    int componentY = 0;

    Vector2D move(componentX,componentY);
    physics.velocity = move;
    active_sprite->changeAnimation(globals::moveRight);
    active_sprite->activeAnimation->clock.resumeTimer();
    return true;
}

bool Player::changeInstrument(std::string instrument_name){
    INFO("Changing Instrument to " << instrument_name);
    Instrument instrument = instruments[instrument_name];
    bool isInstrumentNull = true;

    active_instrument = instrument;
    changeSprite(instrument_name);

    return isInstrumentNull;
}

bool Player::changeSprite(std::string sprite_name){
    INFO("Changing Sprite to " << sprite_name);
    AnimationControllerComponent* sprite = sprites[sprite_name];

    if(&sprite == &active_sprite){
      INFO("This sprite is active");
      return true;
    }else{

      active_sprite->setState(Component::State::disabled);
      sprite->setState(Component::State::enabled);
      active_sprite = sprite;

      return true;
      }
}

bool Player::handlePlayer(){

    if(Input::keyPressed(Input::ONE))
    {
        changeInstrument(globals::banjo);
    }
    if(Input::keyPressed(Input::TWO))
    {
        changeInstrument(globals::eletric_guitar);
    }
    if(Input::keyPressed(Input::THREE))
    {
        changeInstrument(globals::accordion);
    }
    if(Input::keyPressed(Input::Q))
    {
        active_instrument.useSpellQ();
    }
    if(Input::keyPressed(Input::W))
    {
        active_instrument.useSpellW();
    }
    if(Input::keyPressed(Input::E))
    {
        active_instrument.useSpellE();
    }

    return true;
}

void Player::addInstrument(std::string instrument_name, Instrument instrument){
    instruments[instrument_name] = instrument;
}

void Player::addSprite(std::string instrument_name, AnimationControllerComponent * sprite){
    sprites[instrument_name] = sprite;
}

Instrument Player::getActiveInstrument(){
    return active_instrument;
}

void Player::addFragment(int _id){
    fragments.push_back(_id);
    if(fragments.size() == 4) {
        engine::Game::instance.change_scene("Victory");
        physics.position.setX(getInitialX());
        physics.position.setY(getInitialY());
        life = 100;
        clearFragments();
    }

    std::stringstream ss;
    ss << "Numero de fragmentos: "<<fragments.size();


    nFragments->setText(ss.str());
    nFragments->init();
}
void Player::clearFragments(){
    fragments.clear();

    std::stringstream ss;
    ss << "Numero de fragmentos: "<<fragments.size();

    nFragments->setText(ss.str());
    nFragments->init();


}
