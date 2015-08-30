#include <string>

class PathFind
{
public:
    /*for accessing files. will assume that the directory is based eithe on the project root (for assets)*/
   static inline std::string getAsset(const char* relativePath)
    {
        std::string srcPath;
        #ifdef __unix__
            srcPath = __FILE__;
            srcPath = srcPath.substr(0, srcPath.rfind('/') + 1);
            srcPath += relativePath;
        #elif defined(_WIN32)
             srcPath = std::string(relativePath);
        #endif

        return srcPath;
    }


};