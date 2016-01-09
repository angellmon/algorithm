//==============================================================
#include "ACAutomation.h"
#include <algorithm>
#include <iterator>
#include <list>
//==============================================================
acNode::acNode(void)
{
    m_failed=0;
}
//==============================================================
void acNode::buildFailedPointer(void)
{
    struct tobuildType
    {
        string  key;
        _MyTp   self;
        _MyTp   parent;
    public:
        tobuildType(const string& k, _MyTp s, _MyTp p){key=k;self=s;parent=p;}
    };

    list<tobuildType> tobuild;
    m_failed=this;
    tobuild.push_back(tobuildType("", this->shared_from_this(), this->shared_from_this()));


    for(auto i=tobuild.begin();i!=tobuild.end();++i)
    {
        _MyTp p=i->self;
        p->foreach([&](const string& k, _MyTp& c)
              {
                  tobuild.push_back(tobuildType(k,c,p));
              });
    }

    //print
    cout << "tobuild:" << tobuild.size() << endl;
    for_each(tobuild.begin(), tobuild.end(),
             [&](tobuildType& i)
             {
                 _MyTp      c = i.self;
                 _MyTp      p = i.parent;
                 string&    k = i.key;

                 c->m_failed=p->m_failed;

                 if(this!=p.get())
                 for(;;)
                 {
                     auto t=c->m_failed->get(k);
                     if(false!=t)
                     {
                         c->m_failed=dynamic_pointer_cast<_MyT>(t).get();
                         break;
                     }

                     c->m_failed=c->m_failed->m_failed;
                     if(this==c->m_failed)
                        break;
                 }
                cout <<"   ["<<c.get() << "->" <<c->m_failed << endl;
             }
    );
}
//==============================================================
void acNode::search(const string& str)
{
    _MyTp p=this->shared_from_this();
    for(auto i=str.begin(); i!=str.end(); )
    {
        string ff;ff=(*i);
        _MyTp f=p->get(ff);
        if(false!=f)
        {
            if(false==f->m_pattern.empty())
                cout << "found: " << f->m_pattern << endl;
            p=f;
            ++i;
            continue;
        }

        p=p->m_failed->shared_from_this();
        if(this==p.get())
            ++i;
    }

}
//==============================================================
