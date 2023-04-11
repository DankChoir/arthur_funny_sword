#include "knight2.h"
#include <algorithm>
#include <fstream>

bool isPrime(const int num){
  if (num <=1) return false;
  for(int i =2; i*i <=num;i++){
    if(num%i==0) return false;
  }
  return true;
}

bool PythagoreTri(const int a, const int b, const int c){
  if(a==0) return false;
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

//  _____ _                     
// |_   _| |                    
//   | | | |_ ___ _ __ ___  ___ 
//   | | | __/ _ \ '_ ` _ \/ __|
//  _| |_| ||  __/ | | | | \__ \
//  \___/ \__\___|_| |_| |_|___/

bool phoenixdownI::canUse(BaseKnight *knight){
  if(knight->getHP() <=0) return true;
  return false;
}

void phoenixdownI::use(BaseKnight *knight){
  knight->healthRestore(knight->getMaxHP());
}

bool phoenixdownII::canUse(BaseKnight *knight){
  if(knight->getHP() < int(knight->getMaxHP()/4)) return true;
  return false;
}

void phoenixdownII::use(BaseKnight *knight){
  knight->healthRestore(knight->getMaxHP());
}

bool phoenixdownIII::canUse(BaseKnight *knight){
  if(knight->getHP() < int(knight->getMaxHP()/3)) return true;
  return false;
}

void phoenixdownIII::use(BaseKnight *knight){
  if(knight->getHP() <=0) knight->healthRestore(int(knight->getMaxHP()/3));
  else
    knight->heal(int(knight->getMaxHP()/4));
}

bool phoenixdownIV::canUse(BaseKnight *knight){
  if(knight->getHP()< int(knight->getMaxHP()/2)) return true;
  return false;
}

void phoenixdownIV::use(BaseKnight *knight){
  if(knight->getHP()<=0) knight->healthRestore(int(knight->getMaxHP()/2));
  else
    knight->heal(int(knight->getMaxHP()/5));
}

bool Antidote::canUse(BaseKnight *knight){
  if(knight->poisioned()) return true;
  return false;
}

void Antidote::use(BaseKnight *knight){
  knight->cleanse();
}

//  ______                    _   __        _         _      _   
//  | ___ \                  | | / /       (_)       | |    | |  
//  | |_/ /  __ _  ___   ___ | |/ /  _ __   _   __ _ | |__  | |_ 
//  | ___ \ / _` |/ __| / _ \|    \ | '_ \ | | / _` || '_ \ | __|
//  | |_/ /| (_| |\__ \|  __/| |\  \| | | || || (_| || | | || |_ 
//  \____/  \__,_||___/ \___|\_| \_/|_| |_||_| \__, ||_| |_| \__|
//                                              __/ |            
//    

int BaseKnight::getHP() const {return this->hp;}
int BaseKnight::getMaxHP() const {return this->maxhp;}
bool BaseKnight::poisioned() const {return this->got_poisioned;}

void BaseKnight::cleanse() {this->got_poisioned=false;}

void BaseKnight::healthRestore(const int amount){
  this->hp = amount;
}

void BaseKnight::heal(const int amount){
  this->hp += amount;
  this->hp = min(hp,maxhp);
}

void BaseKnight::takeDamage(const int damage){
  this->hp -= damage;
}

BaseKnight* BaseKnight::create(int id, int maxhp, int level, int phoenixdownI, int gil, int antidote){
  KnightType type;
  if(isPrime(maxhp)) type = PALADIN;
  else if(maxhp == 888) type = LANCELOT;
  else if(PythagoreTri(maxhp/100,(maxhp/10)%10 , maxhp%10)) type = DRAGON;
  else type = NORMAL;

  BaseKnight* knight = nullptr;
    switch (type) {
    case PALADIN:
      knight = new PaladinKnight(id, maxhp, level, phoenixdownI, gil, antidote);
      break;
    case LANCELOT:
      knight = new LancelotKnight(id, maxhp, level, phoenixdownI, gil, antidote);
      break;
    case DRAGON:
      knight = new DragonKnight(id, maxhp, level, phoenixdownI, gil, antidote);
      break;
    case NORMAL:
      knight = new NormalKnight(id, maxhp, level, phoenixdownI, gil, antidote);
      break;
    }
  knight->knightType = type;
  return knight;
}

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
        + "," + "no bag yet sorry " /* bag->toString() */
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

ArmyKnights::ArmyKnights(const string& file_armyknights){
  ifstream army_file(file_armyknights);
  army_file >> this->numKnights;
  this->army = new BaseKnight*[numKnights];
  int maxhp,level,phoenixdownI,gil,antidote;
  for(int id =1; id <=numKnights;id++){
    army_file >> maxhp >> level >> phoenixdownI >> gil >> antidote;
    BaseKnight* knight = BaseKnight::create(id, maxhp, level, phoenixdownI, gil, antidote);
    army[id-1] = knight;
  }
  army_file.close();
}

int ArmyKnights::count()const{
  return this->numKnights;
}

bool ArmyKnights::hasPaladinShield() const {return(this->PalandinShield);}
bool ArmyKnights::hasLancelotSpear() const {return(this->LancelotSpear);}
bool ArmyKnights::hasGuinevereHair() const {return(this->GuinevereHair);}
bool ArmyKnights::hasExcaliburSword() const {return(this->ExcaliburSword);}

BaseKnight* ArmyKnights::lastKnight() const {
  if (this->count()==0) return nullptr;
  BaseKnight* knight_cuoi = this->army[this->count()-1];
  return knight_cuoi;
}

ArmyKnights::~ArmyKnights(){
  for(int i =0; i < numKnights;i++){
    delete this->army[i];
  }
  delete[] this->army;
}

//IN DEV
void ArmyKnights::dev_printAll() const {
  // TEST ITEM
  phoenixdownIV tear;
  army[0]->takeDamage(200);
  cout << army[0]->getHP();
  cout << "Dung tear cho thang dau dc ko: " << tear.canUse(army[0]) << endl;
  if(tear.canUse(army[0])) tear.use(army[0]);
  cout << "Mau sau khi dung la: " << army[0]->getHP() << endl;
  
  //TEST ARMY
  for(int i =0; i < this->numKnights;i++){
    cout << this->army[i]->toString() << endl;
  }
}

void ArmyKnights::printInfo() const {
    cout << "No. knights: " << this->count();
    if (this->count() > 0) {
        BaseKnight * lknight = lastKnight(); // last knight
        cout << ";" << lknight->toString();
    }
    cout << ";PaladinShield:" << this->hasPaladinShield()
        << ";LancelotSpear:" << this->hasLancelotSpear()
        << ";GuinevereHair:" << this->hasGuinevereHair()
        << ";ExcaliburSword:" << this->hasExcaliburSword()
        << endl
        << string(50, '-') << endl;
}

bool ArmyKnights::adventure(Events *event) {
  for(int i =0; i < event->count();i++){
    int ma_su_kien = event->get(i);
    switch (ma_su_kien) {
      case PickedUpPaladinsShield:{
        this->PalandinShield = true;
        break;
      }

      case PickedUpLancelotsSpear:{
        this->LancelotSpear = true;
        break;
      }

      case PickedUpGuineveresHair:{
        this->GuinevereHair = true;
        break;
      }

      case MeetExcaliburSword: {
        if(this->PalandinShield && this->LancelotSpear && this->GuinevereHair)
          this->ExcaliburSword = true;
        break;
      }
    }
  }
  return false;
}

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

void KnightAdventure::loadArmyKnights(const string &file_armyknights){
  this-> armyKnights = new ArmyKnights(file_armyknights);
}

void KnightAdventure::run(){
  // DEBUG
  cout << "----DEBUG----";
  cout <<"So event la " << this->events->count();
  for(int i =0; i < events->count();i++){
    cout << events->get(i) << " " ;
  }
  cout << endl;
  this->armyKnights->dev_printAll();
  cout << endl;
  this->armyKnights->printInfo();

  armyKnights->adventure(events);

  cout << endl << endl;
  // DEBUG
}

KnightAdventure::~KnightAdventure() {
    delete armyKnights;
    delete events;
}

