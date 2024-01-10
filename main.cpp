
# include <core_utils/log/StdLogger.hh>
# include <core_utils/log/PrefixedLogger.hh>
# include <core_utils/log/Locator.hh>

# include <sdl_app_core/SdlApplication.hh>
# include <core_utils/CoreException.hh>
# include "Content.hh"

namespace {
constexpr auto APP_NAME = "sdl_minimal";
constexpr auto APP_TITLE = "Yes you're doing some serious hacking mate";
constexpr auto APP_ICON_PATH = "data/img/65px-Stop_hand.BMP";
}

int main(int /*argc*/, char** /*argv*/) {
  // Create the logger.
  utils::log::StdLogger raw;
  raw.setLevel(utils::log::Severity::DEBUG);
  utils::log::PrefixedLogger logger("minimal", "main");
  utils::log::Locator::provide(&raw);

  try {
    auto app = std::make_shared<sdl::app::SdlApplication>(
      APP_NAME,
      APP_TITLE,
      APP_ICON_PATH,
      utils::Sizei(640, 480),
      true,
      utils::Sizef(0.7f, 0.5f),
      50.0f,
      60.0f
    );

    // `root_widget`
    sdl::minimal::Content* root_widget = new sdl::minimal::Content(std::string("root_widget"));
    app->setCentralWidget(root_widget);

    // Run it.
    app->run();

    app.reset();
  }
  catch (const utils::CoreException& e) {
    logger.error("Caught internal exception while setting up application", e.what());
    return EXIT_FAILURE;
  }
  catch (const std::exception& e) {
    logger.error("Caught internal exception while setting up application", e.what());
    return EXIT_FAILURE;
  }
  catch (...) {
    logger.error("Unexpected error while setting up application");
    return EXIT_FAILURE;
  }

  // All is good.
  return EXIT_SUCCESS;
}
