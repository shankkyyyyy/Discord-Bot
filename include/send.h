#pragma once
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <sstream>

#include "../include/send.h"
#include "../include/curl/curl.h"
#include "../include/curl/easy.h"

 
// THIS STURCT IN THE VERSION 0.1 IS USELESS
// BETTER TO USE CLASS METHODS ONLY 
// this struct is usefull in the case for getting message id, used for deleting and updating message's
// via webhook 
struct MsgDetails {
   std::string *Message = nullptr;

  const std::string *FilePath = nullptr;

  const std::string *FileMsg = nullptr;

  const std::string *MsgId = nullptr;

  bool IsEmbed = 0;

  // methods 

  // function for setting the variable Message 
  // testing stage
  // making a new unit case for this 
  void SetMessage(std::string *msg); 
};

class WebHook {
private:
  std::string URL_WEBHOOK = nullptr;
  
  CURL *curlptr = nullptr;
  
  MsgDetails *Msg = nullptr; 
  
  bool IsPtrProvided = false;
  
  bool IsMimeUsed = false;
  
  curl_mime *MIME = nullptr;

public:

  //constructor
  WebHook(std::string &URL_WEBHOOK, CURL *curlptr,MsgDetails* Msg); 
  WebHook(std::string &URL_WEBHOOK,MsgDetails* Msg); 

  //methods
  void changeWebhook(const std::string& Webhook) noexcept;
  int sendMessage(); 
  int sendFile();
  ~WebHook();
};
