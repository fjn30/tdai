//
//  Settings.cpp
//  TD1
//
//  Created by Georgios Floros on 28/08/2014.
//
//

#include "GameScene.h"

MapType Settings::mapType = MapType::TraditionalWithRoads;
bool Settings::imEnabled = false;
WaveRules* Settings::waveRules = nullptr;

bool Settings::fullyInitialized = false;

int Settings::numberOfRounds = 10;
int Settings::playerStartingHealthPoints= 20;
int Settings::playerStartingCurrency = 800;

double Settings::towerAttackRange = 6.0f;
int Settings::towerAttackPoints = 45;
double Settings::towerInbetweenAttacksPeriod = 1000.0f;
int Settings::towerCost = 50;

std::string Settings::towerTexture = "1_towers_1.png";