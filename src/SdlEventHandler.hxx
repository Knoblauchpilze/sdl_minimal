#ifndef    SDLEVENTHANDLER_HXX
# define   SDLEVENTHANDLER_HXX

# include "SdlException.hh"
# include "SdlEventHandler.hh"

# include <iostream>

namespace sdl {
  namespace core {

    inline
    void
    SdlEventHandler::run() {
      std::lock_guard<std::mutex> guard(m_locker);
      if (m_executionThread != nullptr) {
        throw SdlException(std::string("Cannot start event handling, process already running"));
      }

      m_executionThread = std::make_shared<std::thread>(
        &SdlEventHandler::handleEvents,
        this
      );
    }

    inline
    void
    SdlEventHandler::stop() {
      lock();
      if (m_executionThread == nullptr) {
        unlock();
        throw SdlException(std::string("Cannot stop event handling, process not yet started"));
      }

      m_eventsRunning = false;
      unlock();
      m_executionThread->join();

      lock();
      m_executionThread.reset();
      unlock();
    }

    inline
    bool
    SdlEventHandler::isRunning() {
      std::lock_guard<std::mutex> guard(m_locker);
      return m_eventsRunning;
    }

    inline
    void
    SdlEventHandler::lock() {
      m_locker.lock();
    }

    inline
    void
    SdlEventHandler::unlock() {
      m_locker.unlock();
    }

    inline
    void
    SdlEventHandler::processKeyPressedEvent(const SDL_KeyboardEvent& event) {}

    inline
    void
    SdlEventHandler::processKeyReleasedEvent(const SDL_KeyboardEvent& event) {}

    inline
    void
    SdlEventHandler::processMouseMotionEvent(const SDL_MouseMotionEvent& event) {}

    inline
    void
    SdlEventHandler::processMouseButtonPressedEvent(const SDL_MouseButtonEvent& event) {}

    inline
    void
    SdlEventHandler::processMouseButtonReleasedEvent(const SDL_MouseButtonEvent& event) {}

    inline
    void
    SdlEventHandler::processMouseWheelEvent(const SDL_MouseWheelEvent& event) {}

    inline
    void
    SdlEventHandler::processQuitEvent(const SDL_QuitEvent& event) {
      std::cout << "[EVN] Quit" << std::endl;
    }

  }
}

#endif    /* SDLEVENTHANDLER_HXX */
