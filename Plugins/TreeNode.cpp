#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

namespace NSMLFWJKFUNCS
{
    typedef map<string, string> AttriNameAndValueDic;

    struct NodeInfo
    {
        AttriNameAndValueDic attriNameAndValueDic;
    };

    typedef vector<NodeInfo> NodeInfoSeq;

    struct TreeNodeInfo;

    typedef vector<TreeNodeInfo> ListTree;

    struct TreeNodeInfo
    {
      NodeInfo nodeInfo;
      ListTree childTreeNode;
    };
}

using namespace NSMLFWJKFUNCS;

void showAllTreeNodeInfosIter(TreeNodeInfo& xs, int& count)
{
    count += 2;

    for(int i=0; i<xs.childTreeNode.size(); i++)
    {
        for(auto iter = xs.childTreeNode[i].nodeInfo.attriNameAndValueDic.begin();
            iter != xs.childTreeNode[i].nodeInfo.attriNameAndValueDic.end(); iter++)
        {
            for(int i=0; i<count; i++)
            {
                cout << "--";
            }
            cout << iter->first << " : " << iter->second << endl;
        }

        showAllTreeNodeInfosIter(xs.childTreeNode[i], count);
    }
}

void setAttriNameAndAttriValueToNodeInfo(NodeInfo& nodeInfo)
{
    nodeInfo.attriNameAndValueDic.insert(pair<string, string>("Name", "laowang"));
    nodeInfo.attriNameAndValueDic.insert(pair<string, string>("age", "24"));
    nodeInfo.attriNameAndValueDic.insert(pair<string, string>("sex", "man"));
}

void setAllNodeInfos(TreeNodeInfo& xs, int& sum)
{
    if(sum < 5)
    {
        TreeNodeInfo temp;
        setAttriNameAndAttriValueToNodeInfo(temp.nodeInfo);
        sum++;
        setAllNodeInfos(temp, sum);
        xs.childTreeNode.push_back(temp);
    }
}


int TreeNode()
{
    cout << "-------start----------" << endl;

    TreeNodeInfo xs;

    int sum = 1;

    setAllNodeInfos(xs, sum);

    int count = 1;

    showAllTreeNodeInfosIter(xs, count);


    return 0;
}












