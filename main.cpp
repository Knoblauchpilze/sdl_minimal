
# include <iostream>
# include <SDL/SDL_ttf.h>

# include "FontException.hh"
# include "SdlException.hh"

int main(int argc, char* argv[])
{
  // Run the application.
  try {
  }
  catch (const sdl::core::FontException& e) {
    std::cerr << "[MAIN] Caught exception:" << std::endl << e.what() << std::endl;
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
  return 0;
}
