
#include <cvpp/auxiliar/definitions.h>
#include <curl/curl.h>

namespace cvpp
{

static char* email_text[6];

class Emailer
{

protected:

    String user,pass,url;
    String to,from,subj,body;

    bool verbose;

public:

    Emailer()
    {
        email_text[0] = new char[1000];
        email_text[1] = new char[1000];
        email_text[2] = new char[1000];
        email_text[3] = new char[1000];
        email_text[4] = new char[1000];

        verbose = false;
    }

    ~Emailer()
    {
    }

    Emailer& setUsername( const String& str ) { user = str ; from = str ; return *this; }
    Emailer& setPassword( const String& str ) { pass = str; return *this; }
    Emailer& setURL(      const String& str ) { url  = str; return *this; }
    Emailer& setTo(       const String& str ) { to   = str; return *this; }
    Emailer& setFrom(     const String& str ) { from = str; return *this; }
    Emailer& setSubject(  const String& str ) { subj = str; return *this; }
    Emailer& setBody(     const String& str ) { body = str; return *this; }

    const String& getUsername() const { return user; }
    const String& getPassword() const { return pass; }
    const String& getURL()      const { return url;  }
    const String& getTo()       const { return to;   }
    const String& getFrom()     const { return from; }
    const String& getSubject()  const { return subj; }
    const String& getBody()     const { return body; }

    Emailer& setVerbose( const bool& verb ) { verbose = verb; return *this; }

    const void assembleText()
    {
        strcpy( email_text[0] , ( "To: <" + to + ">\r\n" ).c_str() );
        strcpy( email_text[1] , ( "From: <" + from + ">\r\n" ).c_str() );
        strcpy( email_text[2] , ( "Subject: " + subj + "\r\n" ).c_str() );
        strcpy( email_text[3] , "\r\n" );
        strcpy( email_text[4] , ( body + "\r\n" ).c_str() );

        email_text[5] = NULL;
    }

    bool send()
    {
        CURL* curl;
        struct curl_slist* recipients;

        int upload_ctx = 0;
        curl = curl_easy_init();

        bool success;
        if( curl )
        {
          assembleText();

          curl_easy_setopt( curl , CURLOPT_USERNAME , user.c_str() );
          curl_easy_setopt( curl , CURLOPT_PASSWORD , pass.c_str() );
          curl_easy_setopt( curl , CURLOPT_URL      ,  url.c_str() );
          curl_easy_setopt( curl , CURLOPT_USE_SSL  , (long)CURLUSESSL_ALL );

          curl_easy_setopt( curl , CURLOPT_MAIL_FROM , from.c_str() );
          recipients = curl_slist_append( recipients ,   to.c_str() );

          curl_easy_setopt( curl , CURLOPT_MAIL_RCPT    , recipients );
          curl_easy_setopt( curl , CURLOPT_READFUNCTION , payload_source );
          curl_easy_setopt( curl , CURLOPT_READDATA     , &upload_ctx );
          curl_easy_setopt( curl , CURLOPT_UPLOAD  , 1L );

          if( verbose )
               curl_easy_setopt( curl , CURLOPT_VERBOSE , 1L );
          else curl_easy_setopt( curl , CURLOPT_VERBOSE , 0L );

          success = !curl_easy_perform( curl );
        }

        curl_slist_free_all( recipients );
        curl_easy_cleanup( curl );
        return success;
    }

    static unsigned payload_source( void* ptr , unsigned size , unsigned nmemb , void* userp )
    {
      int* upload_ctx = (int*)userp;

      if( ( size == 0 ) || ( nmemb == 0 ) || ( ( size * nmemb ) < 1 ) )
        return 0;

      const char* data;
      data = email_text[ *upload_ctx ];

      if( data )
      {
        unsigned len = strlen( data );
        memcpy( ptr , data , len );
        ( *upload_ctx )++;

        return len;
      }

      return 0;
    }

};

}



