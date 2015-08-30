#include "ini_parser.h"
#include "fstream"

namespace qh
{
    INIParser::INIParser(){

    }

    INIParser::~INIParser(){
    
    }

    bool INIParser::Parse(const std::string& ini_file_path){
        std::ifstream file(ini_file_path.c_str());
        if(!file)
            return false;
        file.seekg(0, std::ios::end);
        size_t size = file.tellg();
        file.seekg(0);
        char* pData = new char(size);
        if(NULL == pData)
            return false;
        file.read(pData, size);
        Parse(pData, size);
        return true;
    }

    void INIParser::lineProcess(const std::string& line, const std::string& key_value_seperator, std::string& section){
        size_t pos = line.find(key_value_seperator);
        if(pos == std::string::npos){ 
            //update section
            size_t secStart = line.find('[');
            if(secStart != std::string::npos){
                secStart++;
                size_t secEnd = line.find(']', secStart);
                if(secEnd != std::string::npos && secEnd > secStart + 1)
                    section = line.substr(secStart, secEnd - secStart);
            }
        }else{
            sectionMap[section][line.substr(0, pos)] = line.substr(pos + 1);
        }
    }

    bool INIParser::Parse(const char* ini_data, 
        size_t ini_data_len, 
        const std::string& line_seperator, 
        const std::string& key_value_seperator)
    {
        std::string section("default");
        std::string data(ini_data);
        size_t posStart = 0;
        while(1){
            size_t posEnd = data.find(line_seperator, posStart);
            if(posEnd != std::string::npos){
                if(posEnd > posStart)
                    lineProcess(data.substr(posStart, posEnd - posStart), key_value_seperator, section);
                posStart = posEnd + line_seperator.size();
            }else{
                if(data.size() > posStart)
                    lineProcess(data.substr(posStart, data.size() - posStart), key_value_seperator, section);
                break; 
            }
        }//end while(1)
        return true;
    }

    const std::string& INIParser::Get(const std::string& key, bool* found){
        return Get(std::string("default"), key, found);
    }

    const std::string& INIParser::Get(const std::string& section, const std::string& key, bool* found){
        SectionMap::iterator sectionIter = sectionMap.find(section);
        if(sectionIter != sectionMap.end()){
            KeyMap::iterator keyIter = sectionIter->second.find(key);
            if(keyIter != sectionIter->second.end()){
                if(found != NULL)
                    *found = true;
                return keyIter->second;
            }
        }
        if(found != NULL)
            *found = false;
        return "";
    }
}
