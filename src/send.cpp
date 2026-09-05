#include "../include/send.h"

    
//----------------------------------------|
// NON AI PROJECT                         |
// DONE BY REAL HUMAN BEING               |
// TEENAGER (16)                          |
// CODE WILL ALWAYS BE WRITTEN BY HUMANS  |
// F YOU, IF YOU DO VIBE CODING           |
//----------------------------------------|



// struct MsgDetials methods


// Set's message to the scope of the variable; 
// don't give parameter an rvalue leads to unexpected errors  
  void MsgDetails::SetMessage(std::string* msg)
  {
    std::cout << &msg << std::endl; 
    this->Message = nullptr;
    this->Message = msg;
    return; 
  }

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
  WebHook::WebHook(std::string &URL_WEBHOOK, CURL *curlptr,MsgDetails* Msg)
      : URL_WEBHOOK(URL_WEBHOOK), curlptr(curlptr), IsPtrProvided(true), Msg(Msg) {}

  /*
      -This Constructor Is Used When The Developer Needs a Clean Request To
     Discord. -Creates New Curl Pointer Object. -Both Header And Curl Object Are
     Cleared In The Functions.
  */
  WebHook::WebHook(std::string &URL_WEBHOOK,MsgDetails* Msg) : URL_WEBHOOK(URL_WEBHOOK), curlptr(nullptr), Msg(Msg) {}

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
  int WebHook::sendMessage() {
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
        if(!Msg->IsEmbed)
        {
          // for combing the content and Msg->Message 
          std::ostringstream ss;
          ss << R"({"content": ")" << *Msg->Message << R"("})";
          // the ss makes it into the string 
          
          json_data = ss.str(); 
        }
        else
        {
          // the embed message is directly into the postfields
          // WARNING: THE EMBED MESSAGE SHOULD BE FORMATED 
          curl_easy_setopt(curlptr, CURLOPT_POSTFIELDS, Msg->Message->data());
        }
        // the problem is that json data variable does not have anything inside it ? 
        // what is the problem with this code ?? 
        // let me check this code out 
        std::cout << json_data << std::endl;    
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
  int WebHook::sendFile()
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
        if(Msg->FileMsg != nullptr)
        {
            std::ostringstream ss; 
            ss << R"({"content": ")" << *Msg->FileMsg << R"("})";
            Part = curl_mime_addpart(Mime);
            curl_mime_name(Part,"payload_json"); 
            curl_mime_data(Part,json_data.data(),CURL_ZERO_TERMINATED); 
        }
        Part = curl_mime_addpart(Mime); 
        curl_mime_name(Part,"file"); 
        curl_mime_filedata(Part,Msg->FilePath->data()); 
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


