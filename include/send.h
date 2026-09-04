#pragma once

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
}
