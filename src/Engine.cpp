// MIT License
// Copyright (c) 2024-2025 Tomáš Mark

#include <Engine/Engine.hpp>
#include <Assets/AssetContext.hpp>
#include <Logger/Logger.hpp>
#include <Utils/Utils.hpp>

// https://wiki.libsdl.org/SDL2/README-emscripten

#if defined(PLATFORM_WEB)
  #include <emscripten/emscripten.h>
#endif

namespace dotname {

  Engine::Engine () {
    LOG_D_STREAM << libName_ << " constructed ..." << std::endl;
    AssetContext::clearAssetsPath ();
  }

  Engine::Engine (const std::filesystem::path& assetsPath) : Engine () {
    if (!assetsPath.empty ()) {
      AssetContext::setAssetsPath (assetsPath);
      LOG_D_STREAM << "Assets path given to the library\n"
                   << "╰➤ " << AssetContext::getAssetsPath () << std::endl;
      auto logo = std::ifstream (AssetContext::getAssetsPath () / "logo.png");

      int screenWidth = 640 * 2;
      int screenHeight = 480 * 2;
      if (createSdl2Window ("WebAppCppSdl2 Demo App by DotName", screenWidth, screenHeight) == 0) {
        ;
      }
    }
  }

  Engine::~Engine () {
    LOG_D_STREAM << libName_ << " ... destructed" << std::endl;
  }

  int Engine::createSdl2Window (const std::string& title, int width, int height) {
    
    if (SDL_Init (SDL_INIT_VIDEO) < 0) {
      std::cout << "Failed to initialize the SDL2 library\n";
      return -1;
    }

    SDL_Window* window = SDL_CreateWindow (title.c_str (), SDL_WINDOWPOS_CENTERED,
                                           SDL_WINDOWPOS_CENTERED, width, height, 0);

    if (!window) {
      std::cout << "Failed to create window\n";
      return -1;
    }

    // SDL_Surface* window_surface = SDL_GetWindowSurface (window);

    // if (!window_surface) {
    //   std::cout << "Failed to get the surface from the window\n";
    //   return -1;
    // }

    // SDL_UpdateWindowSurface (window);

    renderer = SDL_CreateRenderer (window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
      std::cout << "Failed to create renderer\n";
      return -1;
    }
    SDL_SetRenderDrawColor (renderer, 142, 142, 242, 255);

    // write text to the window

    SDL_RenderClear (renderer);
    SDL_RenderPresent (renderer);

    // SDL_Color textColor = { 255, 255, 255, 255 };
    // TTF_Init ();
    // TTF_Font* font = TTF_OpenFont (AssetContext::getAssetsPath () / "fonts" / "arial.ttf", 24);
    // if (!font) {
    //   std::cout << "Failed to load font\n";
    //   return -1;
    // }
    // SDL_Surface* textSurface = TTF_RenderText_Solid (font, "Hello, SDL2!", textColor);
    // if (!textSurface) {
    //   std::cout << "Failed to create text surface\n";
    //   return -1;
    // }
    // SDL_Texture* textTexture = SDL_CreateTextureFromSurface (renderer, textSurface);
    // if (!textTexture) {
    //   std::cout << "Failed to create text texture\n";
    //   return -1;
    // }
    

    SDL_Delay (5000);

    return 0;
  }
  bool game_is_still_running = true;
  static void mainLoop (void) /* this will run often, possibly at the monitor's refresh rate */
  {
    if (!game_is_still_running) {
      //  deinitialize_the_game ();
#ifdef __EMSCRIPTEN__
      emscripten_cancel_main_loop (); /* this should "kill" the app. */
#else
      exit (0);
#endif
    }
    
    //check_for_new_input ();
    //think_about_stuff ();
    //draw_the_next_frame ();
  }

  bool WindowShouldClose () {
    return false;
  } // Placeholder for actual window close check

  void loopSdl2 () {

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop (mainLoop, 0, 1);
#else
    // SetTargetFPS (120);        // Set our game to run at 60 frames-per-second
    while (!WindowShouldClose ()) // Detect window close button or ESC key
    {
      mainLoop ();
    }
#endif
  }

} // namespace dotname