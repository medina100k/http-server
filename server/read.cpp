#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
static string judge(const string &line) {
    size_t check=0;
    size_t check2=0;
    int cont=0;
    if(line.size()<=8) return "400";
    for(int i=0;i<line.size();i=i+1)
      if(line[i]==' ') cont++;
    if(cont!=2) return "400";
    string trailing=line.substr(line.size()-3,3);
    int fir=trailing[0];
    int sec=trailing[1];
    int thrd=trailing[2];
    if(!fir>=48&&fir<=57||sec!=46||!thrd>=48&&thrd<=57) return "400"; 
    // TODO 2: exactly three non-empty fields separated by single spaces -> else "400".
    check=line.find(" ",3);
    if(check==string::npos) return "400";
    check2=line.find(" ",check+1);
    if(check2==string::npos) return "400";
    // TODO 3: method only A-Z; target starts with '/' (or is "*" for OPTIONS) and every byte
    //         is 0x21..0x7e; version is HTTP/<digit>.<digit>  -> any failure is "400".
    for(int i=0;i<check;i=i+1){
      int ln=line[i];
      if(!(ln>=65&&ln<=90)) return "400";
    }
    if((line[check+1])!='/'&&line[check+1]!='*') return "400";
    string mth=line.substr(0,check);
    //cout<<mth<<"\n";
    if(line[check+1]=='*'&&mth!="OPTIONS") return "400";
    for(int i=check+1;i<check2;i=i+1){
        int ln=line[i];
        if(!(ln>=33&&ln<=126)) return "400";
    }
    string ver=line.substr(check2+1,4);
    int dch=line[check2+6],ddot=line[check2+7],dch2=line[check2+8];
    if(ver!="HTTP"||line[check2+5]!='/'||(!(dch>=48&&dch<=57))||(ddot!=46)||(!(dch2>=48&&dch2<=57))) return "400";
    // TODO 4: method not in GET HEAD POST PUT DELETE OPTIONS PATCH -> "501".
    string mthc=line.substr(0,check);
    if(mthc!="GET"&&mthc!="HEAD"&&mthc!="POST"&&mthc!="PUT"&&mthc!="DELETE"&&mthc!="OPTIONS"&&mthc!="PATCH") return "501";
    // TODO 5: version not HTTP/1.0 or HTTP/1.1 -> "505".
    int nm=line.size();
    int num=abs(nm-((int)(check2+1)));
    string verc=line.substr(check2+1,num);
    if(verc!="HTTP/1.0"&&verc!="HTTP/1.1") return "505";
    return "OK " + line;
}

int main() {

    istreambuf_iterator<char> begin(cin), end;
    string data(begin,end);
    size_t start=0;
    while (true) {
        size_t p = data.find("\r\n", start);
        if (p == string::npos) break;
        cout << judge(data.substr(start,p-start)) << "\n";
        start = p + 2;
    }
    if (start < data.size()) cout << "400\n";
    return 0;
}