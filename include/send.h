#pragma once
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <sstream>

#include "../include/send.h"
#include "../include/curl/curl.h"
#include "../include/curl/easy.h"

 
struct MsgDetails {
  const std::string *Message = nullptr;

  const std::string *FilePath = nullptr;

  const std::string *FileMsg = nullptr;

  const std::string *MsgId = nullptr;

  bool IsEmbed = 0;
};

class WebHook {
private:
  std::string URL_WEBHOOK;
  CURL *curlptr;
  bool IsPtrProvided = false;
  bool IsMimeUsed = false;
  curl_mime *MIME = nullptr;

public:
   WebHook(std::string &URL_WEBHOOK, CURL *curlptr); 

  WebHook(std::string &URL_WEBHOOK); 

  
  void changeWebhook(const std::string& Webhook) noexcept;
   int sendMessage(MsgDetails* MsgProc); 
   int sendFile(const MsgDetails* MsgProc);
  ~WebHook();
};
