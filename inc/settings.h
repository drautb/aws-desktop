#ifndef AWS_DESKTOP_SETTINGS_H
#define AWS_DESKTOP_SETTINGS_H

#include <string>
#include <vector>

#include <aws/core/Region.h>
#include <aws/core/client/ClientConfiguration.h>
#include <aws/core/auth/AWSCredentialsProvider.h>

using namespace std;
using namespace Aws;
using namespace Aws::Client;
using namespace Aws::Auth;

#define SETTINGS Settings::getInstance()

class Settings
{
private:

  const int MIN_RETRIES = 3;
  const int MAX_RETRIES = 50;

  /**
   * The number of retries to make on all AWS API calls.
   */
  int m_numRetries;

  /**
   * The name of the profile to use for credentials.
   */
  int m_profileIdx;
  vector<string> m_availableProfiles;

  /**
   * Selected region
   */
  int m_regionIdx;
  vector<string> m_availableRegions;

  /**
   * Config summary for window titles
   */
  string m_configDescription;

private:

  /**
   * Private constructor for Singleton.
   */
  Settings();

public:

  ~Settings();

  static Settings* getInstance();

  void showMenu();

  ClientConfiguration getClientConfiguration();

  AWSCredentials getAwsCredentials();

  const char* getStringDescription();

private:

  void loadAvailableProfiles(vector<string>* profiles);

  Region getCurrentRegion();

};

#endif

