//
//  SessionProfiler.h
//  TowerDefense_new
//
//  Created by Georgios Floros on 24/08/2014.
//
//

#ifndef __TowerDefense_new__SessionStats__
#define __TowerDefense_new__SessionStats__

#include <iostream>

enum TypeOfActivity { UpgradeTowerAttack = 0, UpgradeTowerElement = 1, UpgradeTowerSpeed = 2, PlaceTower = 3, SellTower = 4 };


struct RoundStats
{
    ////////////////////////
    int successfulAttackers; // how many creeps made it to the end
    int totalCreeps; // out of
    ////////////////////////
    
    ////////////////////////
    int playerHealthPointsRemaining; // how much hp the player has
    std::vector<TypeOfActivity> playerActivity; // e.g: 1 activity = upgrade tower
    int playerUsedCurrency; // money used for this round
    ////////////////////////
    
    ////////////////////////
    ElementalAffinity creepsEle;
    ElementalAffinity specialCreepsEle;
    ////////////////////////
    
    ////////////////////////
    std::vector<Tower*> towerStats;
    ////////////////////////
    
    
};

class SessionStats
{
    public:
    
    std::string profileId;
    int playerHealthPointsTotal;
    int playerStartingCurrency;
    std::vector< RoundStats > sessionStats;
    
    SessionStats()
    {
        ////////////////////////////////////////////////
        //updates the sessionstats
        RoundStats p;
        this->sessionStats.push_back(p);
        ////////////////////////////////////////////////
    }
    
    ~SessionStats()
    {
        this->sessionStats.clear();
    }
    
    void OpenBrowser()
    {
        std::stringstream s1;
        s1 << "http://www.gflweb.gr/mscproject/questionnaire.php?profilestats=" << this->profileId << "@" << this->playerHealthPointsTotal << "@" << this->playerStartingCurrency << "@";
        
        
        for( int i = 0; i < this->sessionStats.size(); i++ )
        {
            
            s1 << i+1 << "!" << this->sessionStats.at(i).successfulAttackers << "!" << this->sessionStats.at(i).totalCreeps << "!" <<
            this->sessionStats.at(i).playerHealthPointsRemaining << "!" << this->sessionStats.at(i).playerUsedCurrency
            << "!" << this->sessionStats.at(i).creepsEle << "!" << this->sessionStats.at(i).specialCreepsEle << "!";
            
            for ( int k = 0; k < this->sessionStats.at(i).playerActivity.size(); k++ )
            {
                s1 << (int)this->sessionStats.at(i).playerActivity.at(k);
                
                if( this->sessionStats.at(i).playerActivity.size() > 1  )
                {
                    if(k != this->sessionStats.at(i).playerActivity.size()-1)
                    {
                        s1 << ".";
                    }
                }
            }
            
            if(this->sessionStats.at(i).playerActivity.size() > 0)
            {
                s1 << "!";
            }
            
            for ( int j = 0; j < this->sessionStats.at(i).towerStats.size(); j++ )
            {
                s1 << this->sessionStats.at(i).towerStats.at(j)->getPosition().x << "," << this->sessionStats.at(i).towerStats.at(j)->getPosition().y << "," << this->sessionStats.at(i).towerStats.at(j)->GetElement();
                
                if( this->sessionStats.at(i).towerStats.size() > 1 )
                {
                    if(j != this->sessionStats.at(i).towerStats.size()-1)
                    {
                        s1 << "*";
                    }
                }
            }
            
            if( i < this->sessionStats.size()-1 )
            {
                s1 << ":";
            }
            
            
        }
        
        std::cout << "\n\n test: " << s1.str().c_str() << " \n\n";
        
        
        #ifdef defined(_WIN32) || defined(WIN32)
        
        ShellExecute(NULL, "open", s1.str().c_str(),
                     NULL, NULL, SW_SHOWNORMAL);
        
        #else
        
        std::string s = "open ";
        s.append(s1.str().c_str());
        
        system(s.c_str());
        
        #endif
        
    }
    
    void AddCurrency(int round, int currency)
    {
        int s = 0;
        if( round == 0 ) {
            s = 0;
        }
        else {
            s = round-1;
        }
        this->sessionStats.at(s).playerUsedCurrency = this->sessionStats.at(s).playerUsedCurrency + currency;
    }
    
    void RemoveCurrency(int round, int currency)
    {
        int s = 0;
        if( round == 0 ) {
            s = 0;
        }
        else {
            s = round-1;
        }
        this->sessionStats.at(s).playerUsedCurrency = this->sessionStats.at(s).playerUsedCurrency - currency;
    }
    
    void AddTower(int round, Tower* tower)
    {
       
        int s = 0;
        if( round == 0 ) {
            s = 0;
        }
        else {
            s = round-1;
        
            this->sessionStats.at(s).playerActivity.push_back(TypeOfActivity::PlaceTower);
            this->sessionStats.at(s).towerStats.push_back(tower);
        }
        
    }
    
    void AddAllTowers(int round, std::list<Tower*> tlist)
    {
        int s = 0;
        if(tlist.size() > 0)
        {
            if( round == 0 || round == 1) {
                s = 0;
            }
            else {
                s = round-1;
                if( this->sessionStats.size() >= s  )
                {
                    for (std::list<Tower*>::iterator it = tlist.begin(); it != tlist.end(); ++it)
                    {
                        this->sessionStats.at(s).towerStats.push_back(*it);
                    }
                }
            }
        }
        
    }
 
    void WaveStats(int round, Creep* first, Creep* last, int size, int healthpoints, int currency)
    {
        //updates the sessionstats
        if( round > 1 && first && last )
        {
            RoundStats p;
            //session stats
            p.totalCreeps = size;
            p.creepsEle = first->element;
            p.specialCreepsEle = last->element;
            p.playerHealthPointsRemaining = healthpoints;
            p.playerUsedCurrency = currency;
            p.successfulAttackers = 0;
            this->sessionStats.push_back(p);
        }
        else
        {
            if(round-1 <= this->sessionStats.size()-1 && first && last)
            {
                RoundStats &p = this->sessionStats.at(round-1);
                //session stats
                p.totalCreeps = size;
            
                p.creepsEle = first->element;
                p.specialCreepsEle = last->element;
                p.playerHealthPointsRemaining = healthpoints;
                p.playerUsedCurrency = currency;
                p.successfulAttackers = 0;
            }
        }

    }
    
    
    void TowerUpgradesStats(TypeOfActivity toa, int round)
    {
        /////////////////////////
        //update the sessionstats
       
        int s = 0;
        if( round == 0 ) {
            s = 0;
        }
        else {
            s = round-1;
        }
        
        this->sessionStats.at(s).playerActivity.push_back(toa);
        /////////////////////////
    }
    
    //for debugging purposes mostly
    void PrintSession()
    {
        std::cout << "\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
        
        for( int i = 0; i < sessionStats.size(); i++ )
        {
            RoundStats rs = sessionStats.at(i);
            std::cout << "\n Round: " << i+1 << " \nHP: " <<  rs.playerHealthPointsRemaining << "/" << this->playerHealthPointsTotal << " \nUsed: " << rs.playerUsedCurrency << " \nSuccessful Attackers/Total: " << rs.successfulAttackers << "/" << rs.totalCreeps << " \nCreeps Element: " << (int)rs.creepsEle << " \nSpecial Creeps Element: " << (int)rs.specialCreepsEle << " \n\nActivities: \n" ;
            for( int i = 0; i < rs.playerActivity.size(); i++ )
            {
                std::cout << "\n activity: " << (int)rs.playerActivity.at(i) << " ";
            }
            std::cout << "\n Towers: \n";
            for( int k = 0; k < this->sessionStats.at(i).towerStats.size(); k++ )
            {
                std::cout << "\n tower: positions: " << this->sessionStats.at(i).towerStats.at(k)->getPosition().x << " " << this->sessionStats.at(i).towerStats.at(k)->getPosition().y << " | eleaffinity:" << (int)this->sessionStats.at(i).towerStats.at(k)->GetElement();
            }
            std::cout << "\n\n**********\n";
        }
        std::cout << "\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
    }
    
};

#endif
