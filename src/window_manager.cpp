#include <vector>

#include "window.h"
#include "window_manager.h"

static bool windowIsClosed(const Window* w)
{
  bool isClosed = !w->isOpen();

  if (isClosed)
    delete w;

  return isClosed;
}

WindowManager::WindowManager()
{
  m_activeWindows.clear();
}

WindowManager::~WindowManager()
{
  for (int w=0; w<m_activeWindows.size(); w++)
  {
    if (m_activeWindows[w] != NULL)
      delete m_activeWindows[w];
  }

  m_activeWindows.clear();
}

WindowManager* WindowManager::getInstance()
{
  static WindowManager wm;

  return &wm;
}

void WindowManager::addWindow(Window* w)
{
  m_activeWindows.push_back(w);
}

void WindowManager::updateWindows()
{
  m_activeWindows.erase(std::remove_if(m_activeWindows.begin(), m_activeWindows.end(), windowIsClosed),
                        m_activeWindows.end());
}

void WindowManager::showWindows()
{
  for (Window* w : m_activeWindows)
  {
    w->showWindow();
  }
}
