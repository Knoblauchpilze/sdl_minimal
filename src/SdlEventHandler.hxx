#ifndef    SDLEVENTHANDLER_HXX
# define   SDLEVENTHANDLER_HXX

# include <sdl_core/SdlException.hh>
# include "SdlEventHandler.hh"

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
        // No need to do anything, process not started.
        unlock();
        return;
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
    SdlEventHandler::addListener(SdlEventListener* listener) {
      if (listener == nullptr) {
        throw SdlException(std::string("Cannot add null event listener"));
      }
      std::lock_guard<std::mutex> guard(m_listenersLocker);
      m_listeners.push_back(listener);
    }

    inline
    void
    SdlEventHandler::removeListener(SdlEventListener* listener) {
      if (listener == nullptr) {
        throw SdlException(std::string("Cannot remove null event listener"));
      }
      std::lock_guard<std::mutex> guard(m_listenersLocker);
      std::remove_if(m_listeners.begin(), m_listeners.end(),
        [&listener](SdlEventListener* internalListener) {
          return &*(listener) == &(*internalListener);
        }
      );
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
    SdlEventHandler::processKeyPressedEvent(const SDL_KeyboardEvent& event) {
      for (std::vector<SdlEventListener*>::iterator listener = m_listeners.begin() ;
           listener != m_listeners.end() ;
           ++listener)
      {
        (*listener)->onKeyPressedEvent(event);
      }
    }

    inline
    void
    SdlEventHandler::processKeyReleasedEvent(const SDL_KeyboardEvent& event) {
      for (std::vector<SdlEventListener*>::iterator listener = m_listeners.begin() ;
           listener != m_listeners.end() ;
           ++listener)
      {
        (*listener)->onKeyReleasedEvent(event);
      }
    }

    inline
    void
    SdlEventHandler::processMouseMotionEvent(const SDL_MouseMotionEvent& event) {
      for (std::vector<SdlEventListener*>::iterator listener = m_listeners.begin() ;
           listener != m_listeners.end() ;
           ++listener)
      {
        (*listener)->onMouseMotionEvent(event);
      }
    }

    inline
    void
    SdlEventHandler::processMouseButtonPressedEvent(const SDL_MouseButtonEvent& event) {
      for (std::vector<SdlEventListener*>::iterator listener = m_listeners.begin() ;
           listener != m_listeners.end() ;
           ++listener)
      {
        (*listener)->onMouseButtonPressedEvent(event);
      }
    }

    inline
    void
    SdlEventHandler::processMouseButtonReleasedEvent(const SDL_MouseButtonEvent& event) {
      for (std::vector<SdlEventListener*>::iterator listener = m_listeners.begin() ;
           listener != m_listeners.end() ;
           ++listener)
      {
        (*listener)->onMouseButtonReleasedEvent(event);
      }
    }

    inline
    void
    SdlEventHandler::processMouseWheelEvent(const SDL_MouseWheelEvent& event) {
      for (std::vector<SdlEventListener*>::iterator listener = m_listeners.begin() ;
           listener != m_listeners.end() ;
           ++listener)
      {
        (*listener)->onMouseWheelEvent(event);
      }
    }

    inline
    void
    SdlEventHandler::processQuitEvent(const SDL_QuitEvent& event) {
      for (std::vector<SdlEventListener*>::iterator listener = m_listeners.begin() ;
           listener != m_listeners.end() ;
           ++listener)
      {
        (*listener)->onQuitEvent(event);
      }
    }

  }
}

#endif    /* SDLEVENTHANDLER_HXX */
