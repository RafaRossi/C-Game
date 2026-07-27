//
// Created by rossi on 26/07/2026.
//

#ifndef SDLPROJECT_GAMECONTACTLISTENER_H
#define SDLPROJECT_GAMECONTACTLISTENER_H

#include "box2d/b2_world.h"
#include "box2d/b2_contact.h"

class GameContactListener : public b2ContactListener {
public:
    void BeginContact(b2Contact* contact) override;

    void EndContact(b2Contact* contact) override;
};


#endif //SDLPROJECT_GAMECONTACTLISTENER_H
