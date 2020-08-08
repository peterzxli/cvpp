
#include <cvpp/auxiliar/definitions.h>
#include <cvpp/auxiliar/macros.h>

#include <curl/curl.h>

namespace cvpp
{

struct StructMemory
{
    char* memory;
    unsigned size;
};

class Downloader
{

protected:

    String url,file;
    String user,pass;

    bool verbose;

public:

    // Constructor
    Downloader()
    {
        verbose = false;
    }

    // Destructor
    ~Downloader()
    {
    }

    // Set Values

    Downloader& setURL(  const String& str ) { url  = str; return *this; }
    Downloader& setFile( const String& str ) { file = str; return *this; }

    Downloader& setUsername( const String& str ) { user = str; return *this; }
    Downloader& setPassword( const String& str ) { pass = str; return *this; }

    Downloader& setUserPass( const String& str1 , const String& str2 )
    { user = str1 ; pass = str2 ; return *this; }

    // Options
    Downloader& setVerbose( const bool& verb ) { verbose = verb; return *this; }

    // Write File
    static unsigned write_file( void* ptr , unsigned size ,
                                unsigned nmemb , void* stream )
    {
        return fwrite( ptr , size , nmemb , (FILE*)stream );
    }

    // Write Memory
    static unsigned write_memory( void* ptr , unsigned size ,
                                  unsigned nmemb , void* stream )
    {
        unsigned realsize = size * nmemb;
        StructMemory* mem = (StructMemory*)stream;

        mem->memory = (char*)realloc( mem->memory , mem->size + realsize + 1 );
        memcpy( &( mem->memory[mem->size] ) , ptr , realsize );

        mem->size += realsize;
        mem->memory[mem->size] = 0;

        return realsize;
    }

    // TO FILE

    bool toFile() { return toFile( url , file ); }
    bool toFile( const String& url ) { return toFile( url , file ); }

    bool toFile( const String& url , const String& file )
    {
        CURL* curl_handle;

        curl_global_init(CURL_GLOBAL_ALL);
        curl_handle = curl_easy_init();

        if( user != "" && pass != "" )
            curl_easy_setopt( curl_handle , CURLOPT_USERPWD , ( user + ":" + pass ).c_str() );

        curl_easy_setopt( curl_handle , CURLOPT_URL , url.c_str() );
        curl_easy_setopt( curl_handle , CURLOPT_NOPROGRESS , 1L );
        curl_easy_setopt( curl_handle , CURLOPT_WRITEFUNCTION , write_file );

        if( verbose )
             curl_easy_setopt( curl_handle , CURLOPT_VERBOSE , 1L );
        else curl_easy_setopt( curl_handle , CURLOPT_VERBOSE , 0L );

        bool success = false;

        FILE* pagefile = fopen( file.c_str() , "wb" );
        if( pagefile )
        {
            curl_easy_setopt( curl_handle , CURLOPT_WRITEDATA , pagefile );
            success = !curl_easy_perform( curl_handle );
            fclose( pagefile );
        }

        curl_easy_cleanup( curl_handle );
        return success;
    }

    // TO STRING

    String toString() { String str; toString( url , str ); return str; }
    String toString( const String& url ) { String str; toString( url , str ); return str; }

    bool toString( const String& url , String& str )
    {
        CURL* curl_handle;
        StructMemory chunk;

        chunk.memory = (char*)malloc(1);
        chunk.size = 0;

        curl_global_init( CURL_GLOBAL_ALL );
        curl_handle = curl_easy_init();

        curl_easy_setopt( curl_handle , CURLOPT_URL , url.c_str() );
        curl_easy_setopt( curl_handle , CURLOPT_WRITEFUNCTION , write_memory );
        curl_easy_setopt( curl_handle , CURLOPT_WRITEDATA , (void*)&chunk );
        curl_easy_setopt( curl_handle , CURLOPT_USERAGENT , "libcurl-agent/1.0" );

        bool success = !curl_easy_perform( curl_handle );

        str = chunk.memory;
        free( chunk.memory );

        curl_easy_cleanup( curl_handle );
        curl_global_cleanup();

        return success;
    }

};

}



