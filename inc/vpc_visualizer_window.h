#ifndef AWS_DESKTOP_VPC_VISUALIZER_WINDOW_H
#define AWS_DESKTOP_VPC_VISUALIZER_WINDOW_H

#include <vector>
#include <string>

#include <aws/EC2/EC2Client.h>

#include "window.h"

using namespace std;
using namespace Aws::EC2;
using namespace Aws::EC2::Model;

class VpcVisualizerWindow : public Window
{
private:

  EC2Client* m_client;

public:

  /**
   * Constructor
   */
  VpcVisualizerWindow();

  /**
   * Destructor.
   */
  ~VpcVisualizerWindow();

  /**
   * Shows the window.
   */
  void showWindow();

private:

};

#endif
