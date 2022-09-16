//
// Created by Esteban on 8/19/2022.
//

#ifndef UNTITLED26_RAYTRACINGAPP_H
#define UNTITLED26_RAYTRACINGAPP_H

#include <scene/Camera.h>
#include <scene/Scene.h>
#include <tools/IntegerRange.h>

#include <execution>
#include <olcPixelGameEngine.h>


class RayTracingApp : public olc::PixelGameEngine {
public:
    RayTracingApp ();

public:
    bool OnUserCreate () override;
    bool OnUserUpdate (float) override;

private:
    Scene scene;
    Camera camera;
    float ticks = 0;

private:
    void render_scene ();
    void update(float fElapsedTime);
};


#endif //UNTITLED26_RAYTRACINGAPP_H
