#include <iostream>
#include "../include/send.h"

int main()
{
    MsgDetails Msg1;
    std::string Hook = "https://discord.com/api/webhooks/1542139799455014992/gfbcDsJ5bE06JlfvMUEHeILe58CNoOcUX-ti4rRFcn7Y1-bJLPm_Qs81bm-d_FHjU6iu";
    WebHook Send(Hook,&Msg1);
    std::string h = "Hello, World!"; 
    std::string* msg = &h; 
    Msg1.SetMessage(msg);
    Send.sendMessage();
    *msg = "Does this work ?";
    Msg1.SetMessage(msg);  
    Send.sendMessage();
    std::string f = "/home/gigu/Photos/spam._maa_1774032281_3857184650632675036_78539813285.heic";  
    Msg1.FilePath = &f; 
    Send.sendFile(); 
    return 0; 
}
