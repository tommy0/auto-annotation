#include <iostream>
#include <fstream>
#include <map>
#include <iterator>
#include <cmath>
#include <cstdio>
#include <boost\regex.hpp>

boost::regex PUNCTSIGN("[^à-ÿ]");
boost::regex E("(¸|¨)");

using namespace std;

string tolow(string s) //function translate word to lower case
{
    const int temp='à'-'À';
    for(int i=0; i<s.length(); ++i)
    {
        if((s[i]>='À') && (s[i]<='ß')) s[i]+=temp;
    }
    return s;
}

string normalization(string s)
{
    s=tolow(s);
    s=regex_replace(s,E,"e");
    s=regex_replace(s,PUNCTSIGN,"");
    return s;
}

void input(map<string,int> &words, string &name) //input text with add to map of words
{
    ifstream in;
    string s;
    cin>>name;
    in.open(name);
    while(in>>s)
    {
        s=normalization(s);
        if(s.length()<7) continue;
        if (words.count(s)>0)
            words[s]++;
        else
            words.insert(pair<string,int>(s,1));
    }
    in.close();
}

void weighting(map<string,int> &file1,vector<int> &weight,string name)
{
    ifstream in;
    string s;
    in.open(name);
    int currectWieght=0;
	while(in>>s)
    {
        if(s.length()<7) continue;
        if(s[s.length()-1]=='.' || s[s.length()-1]=='?' || s[s.length()-1]=='!')
        {
            s=normalization(s);
            currectWieght+=file1[s];
            weight.push_back(currectWieght);
            currectWieght==0;
        }
        s=normalization(s);
        currectWieght+=file1[s];
    }
}

void output(vector<int> weight, string name)
{
    vector<int> number;
    for(int i=0;i<5;++i)
    {
        auto it=max_element(begin(weight),end(weight));
        number.push_back(it-weight.begin());
        weight.erase(it);
    }
    ifstream in;
    string s;
    in.open(name);
    int num=0;
	while(in>>s)
    {

            if(s[s.length()-1]=='.' || s[s.length()-1]=='?' || s[s.length()-1]=='!')
            {
            if(find(number.begin(), number.end(), num) != number.end())
            {
                cout<<s<<endl;
            }
                num++;
                continue;
            }
            if(find(number.begin(), number.end(), num) != number.end())
            {
                cout<<s<<" ";
            }
    }

}

int main()
{
    setlocale(LC_ALL, "rus");
    map<string,int> mapFile1;
    vector<int> weight;
    string name;
    cout<<"Please, enter first file name"<<endl;
    input(mapFile1,name);
    weighting(mapFile1,weight,name);
    output(weight,name);
    map <string,int>::iterator cur;
	for (cur=mapFile1.begin();cur!=mapFile1.end();cur++)
	{
		cout<<(*cur).first<<": "<<(*cur).second<<endl;
	}
    return 0;
}
