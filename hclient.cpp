#include "TFile.h"
#include "TSocket.h"
#include "TMessage.h"
#include "TROOT.h"
#include <iostream>
using namespace std;

void hclient()
{ 
  gROOT->ProcessLine(".L this2.so");
  
  //Open connection to server
  TSocket *sock=new TSocket("localhost",51400);
  
  //wait till we get the start message
  char str[32];
  sock->Recv(str,32);
  
  //server tells us who we are
  int idx;
  if(strcmp(str,"go 0") == 0){
        idx = 0;
  }
  
  if(idx == 0){
    printf("this is the first client:\n");
    
    //select which file to transfer
    std::cout<<"please input file name:"<<std::endl;
    char a[32];
    std::cin>>a;
    
    //open the file and get the object
    if(strcmp(a,"1.dst") == 0){
       TFile f1("1.dst");
       TObject* obj1=f1.Get("Event");
       //create TMessage to save the object
       TMessage mess(kMESS_OBJECT);
       mess.WriteObject(obj1);
       obj1->Print();
       
       //send message
       sock->Send(mess);
    }
    
    sock->Send("the first client:\n");
  }
  
    //Close the socket
    sock->Close();
}

int main(int argc,char **argv){
        hclient();
        return 0;
}
