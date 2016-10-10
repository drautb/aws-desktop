#ifndef AWS_DESKTOP_CLOUDFORMATION_WINDOW_H
#define AWS_DESKTOP_CLOUDFORMATION_WINDOW_H

#include <vector>
#include <string>

#include <aws/cloudformation/CloudFormationClient.h>
#include <aws/cloudformation/model/StackSummary.h>

#include "window.h"

using namespace std;
using namespace Aws::CloudFormation;
using namespace Aws::CloudFormation::Model;

class CloudFormationWindow : public Window
{
private:

  CloudFormationClient* m_client;

  vector<StackSummary> m_stackList;

  ImGuiTextFilter m_stackListFilter;

public:

  /**
   * Constructor
   */
  CloudFormationWindow();

  /**
   * Destructor.
   */
  ~CloudFormationWindow();

  /**
   * Shows the CFN console window.
   */
  void showWindow();

private:

  void loadStackList();

};

#endif
