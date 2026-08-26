#include <string>
#include "../include/curl/curl.h"
#include "../include/curl/easy.h" 
#include <iostream>
#include <stdexcept>

#include <vector>


//----------------------------------------|
// NON AI PROJECT                         |
// DONE BY REAL HUMAN BEING               |
// TEENAGER (16)                          |
// CODE WILL ALWAYS BE WRITTEN BY HUMANS  |
// F YOU, IF YOU DO VIBE CODING           |
//----------------------------------------|


class Send
{ 
    private:
        /*
            -
        */
        const std::string URL_WEBHOOK; 
        CURL* curlptr; 
        bool IsPtrProvided = false;
    public:
        /*
            ;@ Constructors
            -With And Without CURL Pointer Object 
            -required URL_WEBHOOK
        */
           
        /*
            -This constructor used when the developer already has a CURL Pointer Object.
            -Best For Latency And Raw Speed.
            -Does Not Clean The Curl Object.
            -Cleans The Header Object Only.
        */
            Send(std::string& URL_WEBHOOK,CURL* curlptr): URL_WEBHOOK(URL_WEBHOOK),curlptr(curlptr),IsPtrProvided(true){}
        

        /*
            -This Constructor Is Used When The Developer Needs a Clean Request To Discord.
            -Creates New Curl Pointer Object. 
            -Both Header And Curl Object Are Cleared In The Functions. 
        */
            Send(std::string& URL_WEBHOOK) : URL_WEBHOOK(URL_WEBHOOK),curlptr(nullptr){}
        
        /*
            -Sends The Message to Discord Via URL_WEBHOOK Provided At The Initialize Of The Constructor.
            -Returns 0 If the function succeed, Returns 1 If The Function Failed. 
        */
        int sendMessage(std::string Message)
        {
                try
                {
                    if(this->curlptr == nullptr)
                    {
                        this->curlptr  = curl_easy_init(); 
                    }
                    else
                    {
                        curl_easy_reset(curlptr); 
                    }
                    if(this->curlptr)
                    {
                        
                        struct curl_slist* headers = nullptr;
                        headers = curl_slist_append(headers,"Content-Type: application/json"); 
                        
                        // 
                        curl_easy_setopt(this->curlptr,CURLOPT_URL,URL_WEBHOOK.c_str()); 
                        curl_easy_setopt(this->curlptr, CURLOPT_POST, 1L);
                        curl_easy_setopt(this->curlptr, CURLOPT_HTTPHEADER, headers);
                        
                        //
                        
                        std::vector<char> Msg(Message.length() + 30);   
                        int returnVal = std::snprintf(Msg.data(), Msg.size(), "{\"content\": \"%s\"}", Message.c_str());
         
                        if(returnVal < 0)
                        {
                            curl_slist_free_all(headers);
                            throw std::runtime_error("Function Snprintf Failed To Produce");
                        }
                        curl_easy_setopt(curlptr, CURLOPT_POSTFIELDS,Msg.data());
                        
                        //
                        CURLcode res = curl_easy_perform(curlptr);
                        if(res != CURLE_OK)
                        {
                           curl_slist_free_all(headers);
                           throw std::runtime_error("Cannot Send Message To The Webhook."); 
                        }
                        curl_slist_free_all(headers);

                        return 0;
                    }
                    else
                    {
                        throw std::runtime_error("Cannot Initialize Curl Object");
                    }
                }
                catch(const std::exception& e)
                {
                    std::cout << e.what() << std::endl; 
                    return 1;
                }
                
            }
            
    ~Send()
    {
        if(IsPtrProvided == false && this->curlptr != nullptr)
        {
            curl_easy_cleanup(this->curlptr); 
            this->curlptr = nullptr;
        }
    }
};

int main()
{
    CURL* ptr = curl_easy_init();
    std::string webhook = "https://discord.com/api/webhooks/1542139799455014992/gfbcDsJ5bE06JlfvMUEHeILe58CNoOcUX-ti4rRFcn7Y1-bJLPm_Qs81bm-d_FHjU6iu";
    Send silly(webhook); 
    std::string msg = "new 3 times okay lets see"; 
    int b = silly.sendMessage(msg);
    silly.sendMessage(msg); 
    silly.sendMessage(msg); 
    return 0; 
}