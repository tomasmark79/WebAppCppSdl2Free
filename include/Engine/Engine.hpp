// MIT License
// Copyright (c) 2024-2025 Tomáš Mark

#ifndef __ENGINE_HPP
#define __ENGINE_HPP

#include <Engine/version.h>
#include <filesystem>
#include <string>

#if defined(PLATFORM_WEB)
  #include <emscripten/emscripten.h>
  #include <SDL2/SDL.h>
  #include <SDL2/SDL_image.h>
  #include <SDL2/SDL_ttf.h>
  #include <SDL2/SDL_net.h>
  #include <SDL2/SDL_mixer.h>
#else
  #include <SDL2/SDL.h>
  #include <SDL2/SDL_image.h>
  #include <SDL2/SDL_ttf.h>
  #include <SDL2/SDL_net.h>
  #include <SDL2/SDL_mixer.h>
#endif

// Public API

namespace dotname {
  class Engine {
    const std::string libName_ = std::string ("Engine v.") + ENGINE_VERSION;

  public:
    Engine ();
    Engine (const std::filesystem::path& assetsPath);
    ~Engine ();

  private:
    // Static Sdl2 attributes declaration
    static int screenWidth_;
    static int screenHeight_;
    //static Texture2D textureDotNameLogo_;
    //static Image imageLogo_;
    //static Font fontTopText_;
    static int textSize_;
    static int spacing_;
    //static Camera3D camera_;
    //static Font fontFpsText_;
    static SDL_Window* window_;
    static SDL_Renderer* renderer_;
    static SDL_Surface* textSurface_;
    static SDL_Texture* textTexture_;
    static SDL_Rect textRect_;

    static int initWindowContent();
    static int initSdl2libWindow (int width, int height, const std::string& title);
    static int initSdl2lib ();
    static void loopSdl2lib ();
    static void updateDrawFrame ();
    static bool WindowShouldClose ();
  };

} // namespace dotname

#endif // __ENGINE_HPP