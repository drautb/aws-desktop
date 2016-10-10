#include <vector>

#include "window.h"

using namespace std;

#define WM WindowManager::getInstance()

class WindowManager
{
private:

  /**
   * Vector of active windows.
   */
  vector<Window*> m_activeWindows;

private:

  /**
   * Private constructor for singleton.
   */
  WindowManager();

public:

  /**
   * Destructor.
   */
  ~WindowManager();

  /**
   * Static getInstance method.
   */
  static WindowManager* getInstance();

  /**
   * Add a new window to management/rendering.
   */
  void addWindow(Window* w);

  /**
   * Delete the windows that have been closed.
   */
  void updateWindows();

  /**
   * Call `showWindow` on each window in the manager.
   */
  void showWindows();

};
