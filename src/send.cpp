#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <sstream>

#include "../include/send.h"
#include "../include/curl/curl.h"
#include "../include/curl/easy.h"


    
// UPDATE
// ONLY GOD KNOWS HOW THIS WORKS 
// after 1 week without writing this 
// file, idk how tf this works anymore 

//----------------------------------------|
// NON AI PROJECT                         |
// DONE BY REAL HUMAN BEING               |
// TEENAGER (16)                          |
// CODE WILL ALWAYS BE WRITTEN BY HUMANS  |
// F YOU, IF YOU DO VIBE CODING           |
//----------------------------------------|




  /*
      ;@ Constructors
      -With And Without CURL Pointer Object
      -required URL_WEBHOOK
  */

  /*
      -This constructor used when the developer already has a CURL Pointer
     Object. -Best For Latency And Raw Speed. -Does Not Clean The Curl Object.
      -Cleans The Header Object Only.
  */
  WebHook::WebHook(std::string &URL_WEBHOOK, CURL *curlptr)
      : URL_WEBHOOK(URL_WEBHOOK), curlptr(curlptr), IsPtrProvided(true) {}

  /*
      -This Constructor Is Used When The Developer Needs a Clean Request To
     Discord. -Creates New Curl Pointer Object. -Both Header And Curl Object Are
     Cleared In The Functions.
  */
  WebHook::WebHook(std::string &URL_WEBHOOK) : URL_WEBHOOK(URL_WEBHOOK), curlptr(nullptr) {}

  
  /*
    -Setter Function.
    -Changes The Webhook.
    -Rvalue Reference type.
  */
  void WebHook::changeWebhook(const std::string& Webhook) noexcept
  {
    this->URL_WEBHOOK = Webhook; 
    std::cout << "Webhook Changed To " << Webhook << std::endl; 
    return;
  }

  /*
      -For: This Function Sends Message Via Webhook to discord
      -CAUTION: THIS FUNCTION DOES NOT CLEANUP THE  CURL POINTER OBJECT
      -THE CURL POINTER OBJECT IS CLEANED AT THE DESTRUCTOR
  */
  int WebHook::sendMessage(MsgDetails* MsgProc) {
    // exception handling
    try {
      if (this->curlptr == nullptr) {
        
        // if the curlptr is not provided
        // it is made in this scope
        // it is cleaned up in the destructor
        this->curlptr = curl_easy_init();
        // not a local variable 
        // this is a global variable 
      } else {

        // if the curlptr is given in the construtor
        // it is reseted for clearning the header's and all
        curl_easy_reset(curlptr);
      }

      if (this->curlptr) {
        struct curl_slist *headers = nullptr;
        headers = curl_slist_append(headers, "Content-Type: application/json");

        // code explains
        curl_easy_setopt(this->curlptr, CURLOPT_URL, URL_WEBHOOK.c_str());
        curl_easy_setopt(this->curlptr, CURLOPT_POST, 1L);
        curl_easy_setopt(this->curlptr, CURLOPT_HTTPHEADER, headers);
        // local variable 
        // for json_data for sending the json formated message to discord
        
        std::string json_data; 

        // code explains 
        if(!MsgProc->IsEmbed)
        {
          // for combing the content and MsgProc->Message 
          std::ostringstream ss; 
          ss << R"({"content": ")" << *MsgProc->Message << R"("})";
          // the ss makes it into the string 
          json_data = ss.str(); 
        }
        else
        {
          // the embed message is directly into the postfields
          // WARNING: THE EMBED MESSAGE SHOULD BE FORMATED 
          curl_easy_setopt(curlptr, CURLOPT_POSTFIELDS, MsgProc->Message->data());
        }
        
        curl_easy_setopt(curlptr,CURLOPT_POSTFIELDS,json_data.data()); 
        CURLcode res = curl_easy_perform(curlptr);
        
        if (res != CURLE_OK) {
          curl_slist_free_all(headers);
          std::cout << "Error Code: " << res << std::endl;
          std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
          throw std::runtime_error("Cannot Send Message To The Webhook.");
        }
        // free's the headers
        curl_slist_free_all(headers);
        return 1;
      } else {
        throw std::runtime_error("Cannot Initialize Curl Object");
      }
    } catch (const std::exception &e) {
      std::cout << e.what() << std::endl;
      return 1;
    }
  }

    /*
        -The function is used for sending File's to the specified channel 
        -The FileMsg variable can be Null, the variable is used for Sending Custom Message To the file Sented
    */
  int WebHook::sendFile(const MsgDetails* MsgProc)
  { // 156 - 214 
        if(this->curlptr == nullptr)
        {
            this->curlptr = curl_easy_init(); 
        }
        else
        {
            curl_easy_reset(curlptr); 
        }
    try
    {
        if(!this->curlptr)
        {
            throw std::runtime_error("Cannot Initialize CurlPointer Object"); 
        }    
        curl_mime* Mime = curl_mime_init(curlptr); 
        curl_mimepart* Part = nullptr;
        if(this->MIME != nullptr)
        {
            curl_mime_free(MIME);
        }
        this->MIME = Mime; 
        std::string json_data; 
        if(MsgProc->FileMsg != nullptr)
        {
            std::ostringstream ss; 
            ss << R"({"content": ")" << *MsgProc->FileMsg << R"("})";
            Part = curl_mime_addpart(Mime);
            curl_mime_name(Part,"payload_json"); 
            curl_mime_data(Part,json_data.data(),CURL_ZERO_TERMINATED); 
        }
        Part = curl_mime_addpart(Mime); 
        curl_mime_name(Part,"file"); 
        curl_mime_filedata(Part,MsgProc->FilePath->data()); 
        curl_easy_setopt(curlptr,CURLOPT_URL,URL_WEBHOOK.c_str());
        curl_easy_setopt(curlptr,CURLOPT_MIMEPOST,Mime);
        CURLcode res = curl_easy_perform(curlptr); 
        if(res != CURLE_OK)
        {
            throw std::runtime_error("Function Curl Easy Perform Failed."); 
        }

    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return 1; 
    }
    return 0;
  } // 214 
   // destructor
  WebHook::~WebHook() {
    if (IsPtrProvided == false && this->curlptr != nullptr) {
      curl_easy_cleanup(this->curlptr);
      this->curlptr = nullptr;
    }
    if(this->MIME != nullptr)
    {
        curl_mime_free(this->MIME);
        this->MIME = nullptr;
    }
  }


