#ifndef WINDOW_H
#define WINDOW_H

#include <string>

using namespace std;

class Window
{
protected:

  /**
   * Flag for keeping track of when the window is closed.
   */
  bool m_popen;

  string m_windowTitle;

public:

  virtual ~Window(){};

  virtual void showWindow()=0;

  bool isOpen()const{return m_popen == true;}

};

#endif
