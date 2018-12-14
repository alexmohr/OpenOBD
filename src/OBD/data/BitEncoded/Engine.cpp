//
// Created by me on 13/12/18.
//

#include "Engine.h"

void Engine::fromFrame(byte *frame) {
    engineSystem1->fromFrame(frame);
    engineSystem2->fromFrame(frame);
    engineSystem3->fromFrame(frame);
    engineSystem4->fromFrame(frame);
    engineSystem5->fromFrame(frame);
    engineSystem6->fromFrame(frame);
    engineSystem7->fromFrame(frame);
    engineSystem8->fromFrame(frame);

}

byte *Engine::toFrame() {
    return nullptr;
}
