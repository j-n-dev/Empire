#include <iostream>
#include <fstream>
#include <thread>

#include "Util/Random.h"
#include "Util/Config.h"
#include "Application.h"
#include "Native/Native.h"

void parseConfig    (std::ifstream& inFile, Config& configFile);

int main()
{
    Config configFile;


    std::ifstream inFile("config.txt");
    if (!inFile.is_open())
    {
        configFile.image.loadFromFile("Res/Maps/world_map_large.png");
    }
    else
    {
        parseConfig(inFile, configFile);
    }

    
    configFile.width    = configFile.image.getSize().x;
    configFile.height   = configFile.image.getSize().y;

    Application app(configFile);
    app.run();
}

void parseConfig(std::ifstream& inFile, Config& configFile)
{

    std::string str;
    while (std::getline(inFile, str))
    {
        if (str == "IMAGE")
        {
            inFile >> str;
            if (!configFile.image.loadFromFile("Res/Maps/" + str))
            {
                configFile.image.loadFromFile("Res/Maps/world_map_large.png");
            }
            else
            {
                configFile.imageName = str.substr(0, str.length() - 4);
            }
        }
        else if (str == "CUSTOM_START")
        {
            inFile >> configFile.customStart;
        }
        else if (str == "REPRODUCTION")
        {
            inFile >> configFile.reproductionThreshold;
        }
        else if (str == "COLONIES")
        {
            inFile >> configFile.colonies;

            if (configFile.colonies <= 2)
            {
                configFile.colonies = 3;
            }
            else if (configFile.colonies > 400)
            {
                configFile.colonies = 400;
            }
        }
    }
}
