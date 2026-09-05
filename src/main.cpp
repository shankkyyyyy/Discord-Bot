#include <iostream>
#include "../include/send.h"

// this project is made by shankkkyyy
// this code need's heavy refacotring because this is written by a 16 year old 
// this code is not good for concurrency other things
// this is just a project to learn about libcurl 


/*
    EXAMPLE CODE:
    1, Replace strings with your WebHook,Message,Filepath 
    and see the magic

*/

int main()
{
    MsgDetails Msg1;
    std::string Hook = "Your Discord WebHook"; 
    WebHook Send(Hook,&Msg1);
    std::string h = "Your Message"; 
    std::string* msg = &h; 
    Msg1.SetMessage(msg);
    Send.sendMessage();
    std::string f = "/File/Path/To/Your/File";  
    Msg1.FilePath = &f; 
    Send.sendFile(); 
    return 0; 
}
