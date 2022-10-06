#include <aws/cloudformation/model/ListStacksRequest.h>
#include <aws/cloudformation/CloudFormationClient.h>
#include <imgui.h>

#include "cloudformation_window.h"
#include "settings.h"

using namespace std;

CloudFormationWindow::CloudFormationWindow()
{
  m_popen = true;
  m_client = new CloudFormationClient(SETTINGS->getActiveAwsCredentials(),
                                      SETTINGS->getClientConfiguration());

  m_windowTitle = "CloudFormation - ";
  m_windowTitle.append(SETTINGS->getStringDescription());

  loadStackList();
}


CloudFormationWindow::~CloudFormationWindow()
{
  delete m_client;
}

void CloudFormationWindow::showWindow()
{
  ImGui::Begin(m_windowTitle.c_str(), &m_popen);

  if (ImGui::Button("Refresh Stack List"))
    loadStackList();

  ImGui::SameLine();
  ImGui::Text("Stack Count: %lu", m_stackList.size());

  m_stackListFilter.Draw();

  ImGui::Columns(4, "cfncolumns");
  ImGui::Separator();
  ImGui::Text("Name"); ImGui::NextColumn();
  ImGui::Text("Status"); ImGui::NextColumn();
  ImGui::Text("Created"); ImGui::NextColumn();
  ImGui::Text("Updated"); ImGui::NextColumn();
  ImGui::Separator();

  for (StackSummary s : m_stackList)
  {
    if (m_stackListFilter.PassFilter(s.GetStackName().c_str()))
    {
      ImGui::TextUnformatted(s.GetStackName().c_str()); ImGui::NextColumn();
      ImGui::TextUnformatted(""); ImGui::NextColumn();
      ImGui::TextUnformatted(s.GetCreationTime().ToLocalTimeString("%Y-%m-%dT%H:%M:%SZ").c_str()); ImGui::NextColumn();
      ImGui::TextUnformatted(s.GetLastUpdatedTime().ToLocalTimeString("%Y-%m-%dT%H:%M:%SZ").c_str()); ImGui::NextColumn();
    }
  }

  ImGui::Columns(1);
  ImGui::Separator();

  ImGui::End();
}

void CloudFormationWindow::loadStackList()
{
  m_stackList.clear();
  m_stackList.reserve(20000);

  ListStacksRequest request;
  ListStacksResult result;

  do
  {
    if (result.GetNextToken() != "")
    {
      request.SetNextToken(result.GetNextToken());
    }

    result = m_client->ListStacks(request).GetResult();

    Aws::Vector<StackSummary> stacks = result.GetStackSummaries();
    m_stackList.insert(m_stackList.begin(), stacks.begin(), stacks.end());
  }
  while (result.GetNextToken() != "");
}
