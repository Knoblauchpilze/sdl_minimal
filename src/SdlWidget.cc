
# include "SdlWidget.hh"

namespace sdl {
  namespace core {

    SdlWidget::SdlWidget(const std::string& name,
                         const Boxf& area,
                         const bool transparent,
                         SdlWidget* parent):
      m_name(name),
      m_parent(parent),
      m_area(area),
      m_drawingLocker()
    {}

  }
}
