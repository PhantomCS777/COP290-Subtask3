#include "stock_data.h"
std::string reverse(std::string str){
    std::string ans=str.substr(str.length() - 4); 
    ans+=str.substr(3,2);
    ans+=str.substr(0,2);
    return ans;
}
std::string replace_hyphens(std::string str){
    std::string ans="";
    for(auto c:str){
        if(c=='-') ans+='/';
        else ans+=c;
    }
    return ans;
}
