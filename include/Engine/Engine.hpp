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
    SDL_Renderer* renderer;
    int createSdl2Window (const std::string& title, int width, int height);
  };

} // namespace dotname

#endif // __ENGINE_HPP