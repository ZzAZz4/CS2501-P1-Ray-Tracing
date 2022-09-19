
#define OLC_PGE_APPLICATION

#include <olcPixelGameEngine.h>

#include "FirefliesApp.h"
#include <object/Sphere.h>
#include <object/Cylinder.h>
#include <object/Plane.h>


FirefliesApp::FirefliesApp ()
    : scene{}, camera{} {
    sAppName = "Ray Tracing";
    camera = Camera::pointing(
        { 0, 1, 0 },
        { 0, 0, -3 },
        2 * Math::atan(1.f),
        1.0f,
        1.0f
    );
}


bool FirefliesApp::OnUserCreate () {
    scene.background_color = { 0.2f, 0.1f, 0.2f };

    const auto mid_light = scene.create_light<PointLight>(Math::vec3(0.f, 0.25f, -2.f), Math::vec3(3.f, 3.f, 2.f));

    const auto mate_white = Material{ .color={ 1.f, 1.f, 1.f }};
    const auto shiny_green = Material{ .color={ 0.f, 0.8f, 0.f }, .specular=glm::vec3{ 0.5 }, .specular_exp=500, .reflection=0.2 };
    const auto shiny_wood = Material{ .color={ 0.45f, 0.2f, 0.02f }, .specular=glm::vec3{ 0.4f }, .reflection=0.02f };
    const auto yellow_luminal = Material{ .emission={ 0.9f, 1.f, 0.6f }};
    const auto glass = Material{ .color={ 0.f, 0.f, 0.f }, .index_of_refraction=1.5f, .transmittance=0.9f };

    scene.create_object<Cylinder>(Math::vec3{ 0, 0, -2 }, Math::vec3{ 0, 0.5, -2 }, -0.5, mate_white)
         ->light = mid_light;
    scene.create_object<Cylinder>(Math::vec3{ 0.f, 0.f, -4.f }, Math::vec3{ 0.f, 2.f, -4.f }, 1.f, glass);
    scene.create_object<Cylinder>(Math::vec3{ 0.f, 0.05f, -4.f }, Math::vec3{ 0.f, 1.95f, -4.f }, -0.95f, glass);
    scene.create_object<Sphere>(Math::vec3{ -2.f, 0.7f, -2.f }, 0.72f, shiny_green);

    for (int i = 0; i < 10; ++i) {
        auto firefly = scene.create_object<Firefly>(Math::vec3{ 0.f, 1.f, -4.f }, 0.01f, yellow_luminal, 0.75f);
        fireflies.push_back(firefly);
    }

    scene.create_object<Plane>(Math::vec4{ 0.f, 1.f, 0.f, 0.01f }, shiny_wood);
    return true;
}


bool FirefliesApp::OnUserUpdate (float fElapsedTime) {
    if (GetKey(olc::Key::ESCAPE).bPressed) {
        return false;
    }
    update(fElapsedTime);
    render_scene();

    return true;
}


void FirefliesApp::render_scene () {
    const auto range = IntegerRange{ 0, ScreenWidth() * ScreenHeight() };

    std::for_each(
        std::execution::par_unseq,
        range.cbegin(), range.cend(), [&] (auto index) {
            const auto x = index % ScreenWidth();
            const auto y = index / ScreenWidth();

            const auto x_conv = (float) x / (float) ScreenWidth();
            const auto y_conv = (float) y / (float) ScreenHeight();
            const auto color = camera.pixel_color(scene, x_conv, y_conv, 4);
            const auto pixel = olc::PixelF(color.x, color.y, color.z);

            Draw(x, y, pixel);
        }
    );
}

void FirefliesApp::update (float fElapsedTime [[maybe_unused]]) {
    const float speed = GetKey(olc::Key::CTRL).bHeld ? 1.f : 0.5f;
    if (GetKey(olc::Key::W).bHeld) camera.move_forward(speed * fElapsedTime);
    if (GetKey(olc::Key::S).bHeld) camera.move_forward(-speed * fElapsedTime);
    if (GetKey(olc::Key::A).bHeld) camera.move_right(speed * fElapsedTime);
    if (GetKey(olc::Key::D).bHeld) camera.move_right(-speed * fElapsedTime);
    if (GetKey(olc::Key::SPACE).bHeld) camera.move_up(speed * fElapsedTime);
    if (GetKey(olc::Key::SHIFT).bHeld) camera.move_up(-speed * fElapsedTime);
    if (GetKey(olc::Key::UP).bHeld) camera.rotate_up(speed * fElapsedTime);
    if (GetKey(olc::Key::DOWN).bHeld) camera.rotate_up(-speed * fElapsedTime);
    if (GetKey(olc::Key::LEFT).bHeld) camera.rotate_right(speed * fElapsedTime);
    if (GetKey(olc::Key::RIGHT).bHeld) camera.rotate_right(-speed * fElapsedTime);

    for (auto firefly: fireflies) {
        firefly->update(fElapsedTime);
    }

    ticks += fElapsedTime;
}
