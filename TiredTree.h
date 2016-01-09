#ifndef _TiredTreeH
#define _TiredTreeH
//==============================================================
#include <memory>
#include <map>
#include <string>
#include <iostream>
#include <utility>
using namespace std;
//==============================================================
template<typename T>
class tiredTreeNode
{
protected:
    typedef tiredTreeNode<T>        _MyT;
    typedef shared_ptr<T>           _TTNode;
    typedef map<string, _TTNode>    _TTNodes;

protected:
    _TTNodes    m_children;
    string      m_pattern;

public:
    _TTNode insert(const string& key)
    {
        auto tFind=m_children.find(key);
        if(m_children.end()!=tFind)
            return tFind->second;

        try
        {
            _TTNode tNew=make_shared<T>();
            m_children.insert(make_pair(key, tNew));
            return tNew;
        }
        catch(const exception& e)
        {
            return _TTNode();
        }
    }
    //========================================
    _TTNode get(const string& key)
    {
        auto tFind=m_children.find(key);
        if(m_children.end()!=tFind)
            return tFind->second;

        return _TTNode();
    }
    //========================================
    template<typename F>
    void foreach(F func)
    {
        auto tIter=m_children.begin();
        for(; m_children.end()!=tIter; ++tIter)
            func(tIter->first, tIter->second);
    }
        //========================================
    void Print(const string& parent="")
    {
        if(0 == m_children.size())
        {
            cout << parent << endl;
            return;
        }

        for(auto i=m_children.begin(); m_children.end()!=i; ++i)
        {
            string sub = parent+i->first;
            i->second->Print(sub);
        }
    }
    //========================================
    void Print(const wstring& parent=L"")
    {
        if(0 == m_children.size())
        {
            wcout << parent << endl;
            return;
        }

        for(auto i=m_children.begin(); m_children.end()!=i; ++i)
        {
            string sub = parent+i->first;
            i->second->Print(sub);
        }
    }
    //========================================
    bool Build(const string& s)
    {
        _MyT* p = this;
        for(size_t i=0; i<s.size(); i++)
        {
            _TTNode n=p->insert(s.substr(i,1));
            if(false==n)
                return false;
            p=n.get();
        }
        p->m_pattern=s;

        return true;
    }
};
//==============================================================
#endif
