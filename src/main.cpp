#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include <aws/core/Aws.h>

#include <imgui.h>
#include <imgui-SFML.h>

#include "settings.h"
#include "window_manager.h"
#include "cloudformation_window.h"

using namespace std;

void showMenuBar()
{
  if (ImGui::BeginMainMenuBar())
  {
   if (ImGui::BeginMenu("Services"))
   {
     if (ImGui::MenuItem("CloudFormation")) WM->addWindow(new CloudFormationWindow());
     ImGui::EndMenu();
   }

    SETTINGS->showMenu();
    ImGui::EndMainMenuBar();
  }
}

int main()
{
  sf::RenderWindow window(sf::VideoMode(1024, 768), "AWS Desktop");
  window.setVerticalSyncEnabled(true);
  ImGui::SFML::Init(window);

  Aws::SDKOptions options;
  Aws::InitAPI(options);

  sf::Color bgColor(20.0f, 20.0f, 20.0f);

  sf::Clock deltaClock;
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      ImGui::SFML::ProcessEvent(event);

      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    ImGui::SFML::Update(deltaClock.restart());

    showMenuBar();

    WM->updateWindows();
    WM->showWindows();

    window.clear(bgColor);
    ImGui::Render();
    window.display();
  }

  Aws::ShutdownAPI(options);

  ImGui::SFML::Shutdown();
}

