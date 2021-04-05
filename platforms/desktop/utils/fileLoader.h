#ifndef PLATFORMS_DESKTOP_UTILS_FILELOADER_H
#define PLATFORMS_DESKTOP_UTILS_FILELOADER_H
#include <string>
#include <fstream>
#include <platforms/desktop/common.h>

#include <platforms/platform.h>


inline std::string LoadTextFile(const char* filename){
    std::string content;
    #ifdef RESOURCE_DESKTOP_DIR
    std::ifstream ShaderStream(PATH(filename), std::ios::in);
    #else
    std::ifstream ShaderStream(filename, std::ios::in);
    #endif

       if(ShaderStream.is_open()){
           std::string Line = "";
           while(getline(ShaderStream, Line)) content += "\n" + Line;
           ShaderStream.close();
       }else{
           LOGE("====Failed to load file: %s", filename);
       }
       return content;
}
#endif 
