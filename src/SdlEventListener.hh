#ifndef    SDLEVENTLISTENER_HH
# define   SDLEVENTLISTENER_HH

# include <SDL2/SDL.h>

namespace sdl {
  namespace core {

    class SdlEventListener {
      public:

        struct Interaction {
          using Mask = unsigned char;

          static constexpr Mask NoInteraction = 0x00;

          static constexpr Mask KeyPressed = 0x01;
          static constexpr Mask KeyReleased = 0x02;
          static constexpr Mask Key = KeyPressed | KeyReleased;

          static constexpr Mask MouseButtonPressed = 0x04;
          static constexpr Mask MouseButtonReleased = 0x08;
          static constexpr Mask MouseButton = MouseButtonPressed | MouseButtonReleased;

          static constexpr Mask MouseMotion = 0x10;

          static constexpr Mask MouseWheelDown = 0x20;
          static constexpr Mask MouseWheelUp = 0x40;
          static constexpr Mask MouseWheel = MouseWheelDown | MouseWheelUp;

          static constexpr Mask Mouse = MouseButton | MouseMotion | MouseWheel;

          static constexpr Mask Quit = 0x80;

          static constexpr Mask FullInteraction = Key | Mouse | Quit;

        };

      public:

        SdlEventListener(const Interaction::Mask& mask);

        virtual ~SdlEventListener();

        const Interaction::Mask&
        getInteractionMask() const noexcept;

        virtual void
        onExitEvent(const SDL_Event& exitEvent);

        virtual void
        onKeyPressedEvent(const SDL_KeyboardEvent& keyEvent);

        virtual void
        onKeyReleasedEvent(const SDL_KeyboardEvent& keyEvent);

        virtual void
        onMouseMotionEvent(const SDL_MouseMotionEvent& mouseMotionEvent);

        virtual void
        onMouseButtonPressedEvent(const SDL_MouseButtonEvent& mouseButtonEvent);

        virtual void
        onMouseButtonReleasedEvent(const SDL_MouseButtonEvent& mouseButtonEvent);

        virtual void
        onMouseWheelEvent(const SDL_MouseWheelEvent& event);

        virtual void
        onQuitEvent(const SDL_QuitEvent& event);

      protected:

        bool
        isRelevant(const Interaction::Mask& event) const noexcept;

      private:

        Interaction::Mask m_mask;

    };

  }
}

# include "SdlEventListener.hxx"

#endif    /* SDLEVENTLISTENER_HH */
