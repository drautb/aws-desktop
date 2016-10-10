#include <vector>
#include <fstream>

#include <aws/core/auth/AWSCredentialsProvider.h>
#include <aws/core/client/DefaultRetryStrategy.h>

#include <imgui.h>
#include <imgui-SFML.h>

#include "settings.h"
#include "imgui_shim.h"

using namespace std;
using namespace Aws::Client;
using namespace Aws::Auth;

Settings::Settings()
{
  m_numRetries = 30;

  loadAvailableProfiles(&m_availableProfiles);

  // Select 'default' profile if it exists
  auto it = std::find(m_availableProfiles.begin(), m_availableProfiles.end(), "default");
  if (it == m_availableProfiles.end())
    m_profileIdx = 0;
  else
    m_profileIdx = std::distance(m_availableProfiles.begin(), it);

  m_regionIdx = 0;
  m_availableRegions = {
    "us-east-1",
    "us-west-1",
    "us-west-2",
    "eu-west-1",
    "eu-central-1"
  };

  m_configDescription = "";
}

Settings::~Settings()
{

}

Settings* Settings::getInstance()
{
  static Settings instance;
  return &instance;
}

void Settings::showMenu()
{
  if (ImGui::BeginMenu("Settings"))
  {
    ImGui::Combo("Profile", &m_profileIdx, m_availableProfiles);
    ImGui::Combo("Region", &m_regionIdx, m_availableRegions);
    ImGui::SliderInt("Retries", &m_numRetries, MIN_RETRIES, MAX_RETRIES);
    ImGui::EndMenu();
  }
}

ClientConfiguration Settings::getClientConfiguration()
{
  ClientConfiguration configuration;

  shared_ptr<DefaultRetryStrategy> retryStrategy(new DefaultRetryStrategy(m_numRetries));
  configuration.retryStrategy = retryStrategy;

  configuration.region = getCurrentRegion();

  return configuration;
}

AWSCredentials Settings::getAwsCredentials()
{
  ProfileConfigFileAWSCredentialsProvider* provider = new ProfileConfigFileAWSCredentialsProvider(m_availableProfiles[m_profileIdx].c_str());

  return provider->GetAWSCredentials();
}

const char* Settings::getStringDescription()
{
  m_configDescription.clear();
  m_configDescription.append(m_availableProfiles[m_profileIdx]);
  m_configDescription.append(" - ");
  m_configDescription.append(RegionMapper::GetRegionName(getCurrentRegion()));

  return m_configDescription.c_str();
}

void Settings::loadAvailableProfiles(vector<string>* profiles)
{
  profiles->clear();
  Aws::String credFile = Aws::Auth::ProfileConfigFileAWSCredentialsProvider::GetCredentialsProfileFilename();
  ifstream inputFile(credFile.c_str());

  string line;
  while (getline(inputFile, line))
  {
    if (line[0] == '[')
    {
      profiles->push_back(line.substr(1, line.find(']') - 1));
    }
  }
}

Region Settings::getCurrentRegion()
{
  switch (m_regionIdx)
  {
    case 0: return Region::US_EAST_1;
    case 1: return Region::US_WEST_1;
    case 2: return Region::US_WEST_2;
    case 3: return Region::EU_WEST_1;
    case 4: return Region::EU_CENTRAL_1;
    default:
      return Region::US_EAST_1;
  }
}
