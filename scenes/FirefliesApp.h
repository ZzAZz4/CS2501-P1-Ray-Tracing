//
// Created by Esteban on 8/19/2022.
//

#ifndef UNTITLED26_FIREFLIESAPP_H
#define UNTITLED26_FIREFLIESAPP_H

#include <scene/Camera.h>
#include <scene/Scene.h>
#include <tools/IntegerRange.h>

#include <execution>
#include <olcPixelGameEngine.h>

#include "Firefly.h"

class FirefliesApp : public olc::PixelGameEngine {
public:
    FirefliesApp ();

public:
    bool OnUserCreate () override;
    bool OnUserUpdate (float) override;

private:
    Scene scene;
    Camera camera;
    std::vector<Firefly*> fireflies;

    float ticks = 0;

private:
    void render_scene ();
    void update(float fElapsedTime);
};


#endif //UNTITLED26_FIREFLIESAPP_H
