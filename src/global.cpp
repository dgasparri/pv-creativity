#include "global.h"


pure std::filesystem::path global::workdir_path(std::string filename)
{
    std::filesystem::path basepath(DATA_PIPE_DIRECTORY); 
    if(!std::filesystem::exists(basepath)) {
        std::filesystem::create_directory(basepath);
    }
    basepath.append(filename);
    return basepath;
}