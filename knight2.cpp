#include "knight2.h"

bool isPrime(const int num){
  if (num <=1) return false;
  for(int i =2; i*i <=num;i++){
    if(num%i==0) return false;
  }
  return true;
}

bool PythagoreTri(const int a, const int b, const int c){
  return (a*a + b*b == c*c || c*c + b*b == a*a || a*a + c*c == b*b);
}

//   _____                      _        
//  |  ___|                    | |       
//  | |__  __   __  ___  _ __  | |_  ___ 
//  |  __| \ \ / / / _ \| '_ \ | __|/ __|
//  | |___  \ V / |  __/| | | || |_ \__ \
//  \____/   \_/   \___||_| |_| \__||___/

Events::Events(const string& file_events){
  ifstream events_file(file_events);
  if(!events_file) cout << "dummy";
  events_file >> this->numEvents;
  eventCodes = new int[numEvents];
  for(int i =0; i < numEvents;i++){
    events_file >> this->eventCodes[i];
  }
  events_file.close();
}

int Events::count() const{
  return this->numEvents;
}

int Events::get(int i) const {
  return this->eventCodes[i];
}

Events::~Events(){
  delete [] this->eventCodes;
}

//  ______                   ______               
//  | ___ \                  | ___ \
//  | |_/ /  __ _  ___   ___ | |_/ /  __ _   __ _ 
//  | ___ \ / _` |/ __| / _ \| ___ \ / _` | / _` |
//  | |_/ /| (_| |\__ \|  __/| |_/ /| (_| || (_| |
//  \____/  \__,_||___/ \___|\____/  \__,_| \__, |
//                                           __/ |


//  ______                    _   __        _         _      _   
//  | ___ \                  | | / /       (_)       | |    | |  
//  | |_/ /  __ _  ___   ___ | |/ /  _ __   _   __ _ | |__  | |_ 
//  | ___ \ / _` |/ __| / _ \|    \ | '_ \ | | / _` || '_ \ | __|
//  | |_/ /| (_| |\__ \|  __/| |\  \| | | || || (_| || | | || |_ 
//  \____/  \__,_||___/ \___|\_| \_/|_| |_||_| \__, ||_| |_| \__|
//                                              __/ |            
//    

string BaseKnight::toString() const {
    string typeString[4] = {"PALADIN", "LANCELOT", "DRAGON", "NORMAL"};
    // inefficient version, students can change these code
    //      but the format output must be the same
    string s("");
    s += "[Knight:id:" + to_string(id) 
        + ",hp:" + to_string(hp) 
        + ",maxhp:" + to_string(maxhp)
        + ",level:" + to_string(level)
        + ",gil:" + to_string(gil)
        + "," + bag->toString()
        + ",knight_type:" + typeString[knightType]
        + "]";
    return s;
}

//    ___                           _   __        _         _          
//   / _ \                         | | / /       (_)       | |         
//  / /_\ \ _ __  _ __ ___   _   _ | |/ /  _ __   _   __ _ | |__   ___ 
//  |  _  || '__|| '_ ` _ \ | | | ||    \ | '_ \ | | / _` || '_ \ / __|
//  | | | || |   | | | | | || |_| || |\  \| | | || || (_| || | | |\__ \
//  \_| |_/|_|   |_| |_| |_| \__, |\_| \_/|_| |_||_| \__, ||_| |_||___/
//                            __/ |                   __/ |            
//                           |___/                   |___/             

// void ArmyKnights::printInfo() const {
//     cout << "No. knights: " << this->count();
//     if (this->count() > 0) {
//         BaseKnight * lknight = lastKnight(); // last knight
//         cout << ";" << lknight->toString();
//     }
//     cout << ";PaladinShield:" << this->hasPaladinShield()
//         << ";LancelotSpear:" << this->hasLancelotSpear()
//         << ";GuinevereHair:" << this->hasGuinevereHair()
//         << ";ExcaliburSword:" << this->hasExcaliburSword()
//         << endl
//         << string(50, '-') << endl;
// }
//
// void ArmyKnights::printResult(bool win) const {
//     cout << (win ? "WIN" : "LOSE") << endl;
// }


//   _     _         _         _              _______      _                                                 
//  (_)   | |       (_)       | |      _     (_______)    | |                       _                        
//   _____| | ____   _   ____ | |__  _| |_    _______   __| | _   _  _____  ____  _| |_  _   _   ____  _____ 
//  |  _   _)|  _ \ | | / _  ||  _ \(_   _)  |  ___  | / _  || | | || ___ ||  _ \(_   _)| | | | / ___)| ___ |
//  | |  \ \ | | | || |( (_| || | | | | |_   | |   | |( (_| | \ V / | ____|| | | | | |_ | |_| || |    | ____|
//  |_|   \_)|_| |_||_| \___ ||_| |_|  \__)  |_|   |_| \____|  \_/  |_____)|_| |_|  \__)|____/ |_|    |_____)
//                     (_____|                                                                               
KnightAdventure::KnightAdventure() {
    this->armyKnights = nullptr;
    this->events = nullptr;
}

void KnightAdventure::loadEvents(const string &file_events){
  this->events = new Events(file_events);
}

void KnightAdventure::run(){
  // DEBUG
  cout <<"So event la " << this->events->count();
  for(int i =0; i < events->count();i++){
    cout << events->get(i) << " ";
  }
  // DEBUG
}

KnightAdventure::~KnightAdventure() {
    // delete armyKnights;
    delete events;
}

