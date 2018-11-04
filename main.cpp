
# include <iostream>
# include <SDL2/SDL_ttf.h>

# include <sdl_app_core/SdlApplication.hh>
# include <sdl_core/SdlException.hh>
# include "GenericWidget.hh"

int main(int argc, char* argv[]) {
  // Run the application.
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cerr << "[MAIN] Could not initialize sdl video mode (err: \"" << SDL_GetError() << "\")" << std::endl;
    return EXIT_FAILURE;
  }

  try {
    sdl::core::BasicSdlWindowShPtr app = std::make_shared<sdl::core::SdlApplication>(
      std::string("This is SPARTA !"),
      std::string("data/img/65px-Stop_hand.BMP"),
      640,
      480,
      60.0f,
      30.0f
    );

    sdl::minimal::GenericWidgetShPtr widget = std::make_shared<sdl::minimal::GenericWidget>(
      std::string("Best widget in da place"),
      sdl::core::Boxf(320.0f, 240.0f, 200.0f, 200.0f),
      SDL_Color{0, 128, 0, SDL_ALPHA_OPAQUE}
    );

    app->addWidget(widget);

    app->run();

    std::cout << "[MAIN] App stopped" << std::endl;
  }
  catch (const sdl::core::SdlException& e) {
    std::cerr << "[MAIN] Caught internal exception:" << std::endl << e.what() << std::endl;
  }

  // Unload the sdl and the ttf libs if needed.
  if (TTF_WasInit()) {
    TTF_Quit();
  }
  if (SDL_WasInit(0u)) {
    SDL_Quit();
  }

  // All is good.
  return EXIT_SUCCESS;
}
