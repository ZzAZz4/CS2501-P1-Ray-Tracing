//
// Created by Esteban on 8/19/2022.
//

#include "RayTracingApp.h"
#include <object/Sphere.h>
#include <object/Cylinder.h>
#include <object/Plane.h>
#include <random>

#define OLC_PGE_APPLICATION

#include <olcPixelGameEngine.h>


RayTracingApp::RayTracingApp ()
    : scene{}, camera{} {
    sAppName = "Ray Tracing";
    camera = Camera::pointing(
        { 0, 1, 0 },
        { 0, 0, 3 },
        2 * Math::atan(1.f),
        1.0f,
        1.0f
    );
}


bool RayTracingApp::OnUserCreate () {
    scene.background_color = { 0.8f, 0.8f, 1.f };
//    scene.ambient_light.intensity_value = Math::vec3(0.2f);

    const auto mid_light = scene.create_light<PointLight>(Math::vec3(0.f, -0.25f, 2.f), Math::vec3(3.f, 3.f, 2.f));
    scene.create_light<DirectionalLight>(Math::vec3(1, 1, 1), Math::vec3(0.02f));

    const auto mate_white = Material{ .color={ 1.f, 1.f, 1.f }};
    const auto shiny_green = Material{ .color={ 0.f, 0.8f, 0.f }, .specular=glm::vec3{ 0.1 }, .specular_exp=500, .reflection=0.1 };
    const auto shiny_wood = Material{ .color={ 0.45f, 0.2f, 0.02f }, .specular=glm::vec3{ 0.4f }, .specular_exp=1, .reflection=0.02f };
    const auto yellow_luminal = Material{ .color={ 0.8f, 0.8f, 0.8f }, .diffuse=glm::vec3(0.5f), .emission={ 0.9f, 1.f, 0.2f }};
    const auto glass = Material{ .color={ 1.f, 1.f, 1.f }, .specular=glm::vec3{ 0.8f }, .specular_exp=9, .index_of_refraction=1.5f, .transmittance=1.f };

    scene.create_object<Cylinder>(Math::vec3{ 0, -0.5, 2 }, Math::vec3{ 0, 0, 2 }, -0.5, mate_white)->light = mid_light;
    scene.create_object<Sphere>(Math::vec3{ -2.f, 1.f, 4.f }, 1.f, shiny_green);
    scene.create_object<Sphere>(Math::vec3{ 2.f, 1.f, 4.f }, 0.05f, yellow_luminal);
    scene.create_object<Sphere>(Math::vec3{ 2.f, 1.f, 4.f, }, 1.f, glass);
//    scene.create_object<Cylinder>(Math::vec3{ 2.f, 0.f, 4.f }, Math::vec3{ 2.f, 2.f, 4.f }, 1.f, glass);
//    scene.create_object<Cylinder>(Math::vec3{ 2.f, 0.1f, 4.f }, Math::vec3{ 2.f, 1.9f, 4.f }, -0.9f, glass);

    scene.create_object<Plane>(Math::vec4{ 0.f, 1.f, 0.f, 1.f }, shiny_wood);
    return true;
}


bool RayTracingApp::OnUserUpdate (float fElapsedTime) {
    if (GetKey(olc::Key::ESCAPE).bPressed) {
        return false;
    }
    update(fElapsedTime);
    render_scene();

    return true;
}


void RayTracingApp::render_scene () {
    const auto range = IntegerRange{ 0, ScreenWidth() * ScreenHeight() };

    std::for_each(
        std::execution::par_unseq,
        std::cbegin(range), std::cend(range), [&] (auto index) {
            const auto x = index % ScreenWidth();
            const auto y = index / ScreenWidth();

            const auto x_conv = (float) x / (float) ScreenWidth();
            const auto y_conv = (float) y / (float) ScreenHeight();
            const auto color = camera.pixel_color(scene, x_conv, y_conv, 7);
            const auto pixel = olc::PixelF(color.x, color.y, color.z);

            Draw(x, y, pixel);
        }
    );
}

void RayTracingApp::update (float fElapsedTime [[maybe_unused]]) {
    const float speed = GetKey(olc::Key::CTRL).bHeld ? 1.f : 0.5f;
    if (GetKey(olc::Key::W).bHeld) camera.move_forward(speed * fElapsedTime);
    if (GetKey(olc::Key::S).bHeld) camera.move_forward(-speed * fElapsedTime);
    if (GetKey(olc::Key::A).bHeld) camera.move_right(speed * fElapsedTime);
    if (GetKey(olc::Key::D).bHeld) camera.move_right(-speed * fElapsedTime);
    if (GetKey(olc::Key::SPACE).bHeld) camera.move_up(speed * fElapsedTime);
    if (GetKey(olc::Key::SHIFT).bHeld) camera.move_up(-speed * fElapsedTime);

    ticks += fElapsedTime;
}
