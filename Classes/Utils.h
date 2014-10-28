//
//  Utils.h
//  TowerDefense_new
//
//  Created by Georgios Floros on 24/08/2014.
//
//

#ifndef TowerDefense_new_Utils_h
#define TowerDefense_new_Utils_h

#include "GameScene.h"
#include <sstream>
#include <fstream>
#include <boost/random/mersenne_twister.hpp>

class Utils
{
    public:
    
    static void WriteLog(std::string log)
    {
        std::stringstream ss1;
        ss1 << cocos2d::CCFileUtils::sharedFileUtils()->getWritablePath();
        ss1 << "/log.txt";
        Utils::WriteToFile(ss1.str());
    }
    
    static void WriteToFile(std::string path)
    {
        std::string input;
        std::cin >> input;
        std::ofstream out(path);
        out << input;
        out.close();
    };
    
};

#endif
