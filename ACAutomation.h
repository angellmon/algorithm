#ifndef ACAutomationH
#define ACAutomationH
//==============================================================
#include <memory>
#include <map>
#include <string>
#include <vector>
using namespace std;

#include "TiredTree.h"

//==============================================================
class acNode;
class acNode : public tiredTreeNode<acNode>, public enable_shared_from_this<acNode>
{
public:
    typedef tiredTreeNode<acNode>   _Supper;
    typedef acNode                  _MyT;
    typedef shared_ptr<acNode>      _MyTp;

private:
    _MyT*  m_failed;

public:
    acNode(void);

    void buildFailedPointer (void);
    void search             (const string& str);
};
//==============================================================
#endif

