#include <aws/EC2/EC2Client.h>
#include <imgui.h>

#include "vpc_visualizer_window.h"
#include "settings.h"

using namespace std;

VpcVisualizerWindow::VpcVisualizerWindow()
{
  m_popen = true;
  m_client = new EC2Client(SETTINGS->getActiveAwsCredentials(),
                           SETTINGS->getClientConfiguration());

  m_windowTitle = "Vpc Visualizer";
  m_windowTitle.append(SETTINGS->getStringDescription());
}

VpcVisualizerWindow::~VpcVisualizerWindow()
{
  delete m_client;
}

void VpcVisualizerWindow::showWindow()
{
  ImGui::Begin(m_windowTitle.c_str(), &m_popen);

  ImGui::Button("Refresh VPCs");
    
  ImGui::End();
}
