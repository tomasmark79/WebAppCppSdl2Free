# MIT License Copyright (c) 2024-2025 Tomáš Mark
function(emscripten target isRequiredHtml)
    if(CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
        message(STATUS "Emscripten detected")

        # define PLATFORM_WEB
        target_compile_definitions(${target} PRIVATE PLATFORM_WEB)

        if(isRequiredHtml EQUAL 1)
            message(STATUS "html target requested")
            set_target_properties(${target} PROPERTIES SUFFIX ".html")
        endif()

        set(_optimalisation "-O3")

        set(_activate_sdl2_sdl2 "-s USE_SDL=2")
        set(_activate_sdl2_image "-s USE_SDL_IMAGE=2")
        set(_activate_sdl2_ttf "-s USE_SDL_TTF=2")
        set(_activate_sdl2_net "-s USE_SDL_NET=2")
        set(_activate_sdl2_mixer "-s USE_SDL_MIXER=2")

        set(_pthread_flags "-s USE_PTHREADS=1 -pthread")

        # combine compiler flags
        set(_compiler_flags
            "-s WASM=1 ${_optimalisation} ${_activate_sdl2_sdl2} ${_activate_sdl2_image} ${_activate_sdl2_ttf} ${_activate_sdl2_net} ${_activate_sdl2_mixer}"
        )
        set_target_properties(${target} PROPERTIES COMPILE_FLAGS "${_compiler_flags}")

        # combine linker flags
        set(_link_flags_sdl2 "-s USE_SDL=2")

        # pthread?
        if(ENABLE_EMSCRIPTEN_PTHREAD)
            message(STATUS "Emscripten pthread enabled")
            set(_compiler_flags "${_compiler_flags} ${_pthread_flags}")
            set(_link_flags_sdl2 "${_link_flags_sdl2} ${_pthread_flags}")
        endif()

        # set both
        set_target_properties(${target} PROPERTIES COMPILE_FLAGS "${_compiler_flags}"
                                                   LINK_FLAGS "${_link_flags_sdl2}")
    endif()

    # Checks if OSX and links appropriate frameworks (Only required on MacOS)
    if(APPLE)
        target_link_libraries(${target} PRIVATE "-framework IOKit")
        target_link_libraries(${target} PRIVATE "-framework Cocoa")
        target_link_libraries(${target} PRIVATE "-framework OpenGL")
    endif()

endfunction()
