#include <iostream>
#include "../include/send.h"

int main()
{
    MsgDetails Msg1;
    const std::string Msg = "Hello, World Discord";  
    Msg1.Message = &Msg;
    std::string Hook = "https://discord.com/api/webhooks/1542139799455014992/gfbcDsJ5bE06JlfvMUEHeILe58CNoOcUX-ti4rRFcn7Y1-bJLPm_Qs81bm-d_FHjU6iu";
    WebHook Send(Hook);
    Send.sendMessage(&Msg1);
    return 0; 
}
