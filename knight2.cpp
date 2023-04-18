#include "knight2.h"

// FUNCTION Programming ROCKS!!
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

void transferGil(BaseKnight* knight,int gil_obtained){
  BaseKnight* current = knight;
  while(current!=nullptr && gil_obtained >0){
    int til_full = 999 - current->getGil();
    if(gil_obtained > til_full){
      current->plusGil(til_full);
      gil_obtained -= til_full;
    }
    else {
      current->plusGil(gil_obtained);
      gil_obtained = 0;
    }
    current = current->previous();
  }
}

void transferItem(BaseKnight* knight, BaseItem* item){
  BaseKnight* current = knight;
  while(current != nullptr){
    if(current->bag->insertFirst(item)){
      current->bag->topAppend(item);
      return;
    }
    current = current->previous();
  }
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

void BaseBag::topAppend(BaseItem *item){
  if(this->head == nullptr) {head = item;}
  else{
      item->next = this->head;
      this->head = item;
    }
  }

BaseBag::BaseBag(const int phoenixdownI,const int antidote, const int limit){
  this->head = nullptr;
  this->count += phoenixdownI + antidote;
  this->limit = limit; 

  for(int a = 0; a <phoenixdownI; a++){
    PhoenixdownI* tear_1 = new PhoenixdownI;
    this->topAppend(tear_1);
  }

  for(int b = 0; b <antidote; b++){
    Antidote* anti = new Antidote;
    this->topAppend(anti);
  }
}

bool BaseBag::insertFirst(BaseItem *item){
  if(this->count == this->limit) return false;
  return false;
}

string BaseBag::toString() const{
  string bag_info = "";
  bag_info += "Bag[count=" + to_string(this->count);
  BaseItem* current = head;
  while(current != nullptr){
    if (current->itemType == ItemType::ANTIDOTE) bag_info += ";Antidote";
    else if (current->itemType == ItemType::TEAR_I) bag_info += ";PhoenixI";
    else if (current->itemType == ItemType::TEAR_II) bag_info += ";PhoenixII";
    else if (current->itemType == ItemType::TEAR_III) bag_info += ";PhoenixIII";
    else
    bag_info += ";PhoenixdownIV";
    current = current->next;
  }
  bag_info += "]";
  return bag_info;
}

// PALADIN BAG
bool PaladinBag::insertFirst(BaseItem *item) {return true;}

// DRAGON BAG
bool DragonBag::insertFirst(BaseItem *item){
  if(item->itemType == ItemType::ANTIDOTE) return false;
  if(this->count == this->limit) return false;
  return true;
}

//  _____ _                     
// |_   _| |                    
//   | | | |_ ___ _ __ ___  ___ 
//   | | | __/ _ \ '_ ` _ \/ __|
//  _| |_| ||  __/ | | | | \__ \
//  \___/ \__\___|_| |_| |_|___/

bool PhoenixdownI::canUse(BaseKnight *knight){
  if(knight->getHP() <=0) return true;
  return false;
}

void PhoenixdownI::use(BaseKnight *knight){
  knight->healthRestore(knight->getMaxHP());
}

bool PhoenixdownII::canUse(BaseKnight *knight){
  if(knight->getHP() < int(knight->getMaxHP()/4)) return true;
  return false;
}

void PhoenixdownII::use(BaseKnight *knight){
  knight->healthRestore(knight->getMaxHP());
}

bool PhoenixdownIII::canUse(BaseKnight *knight){
  if(knight->getHP() < int(knight->getMaxHP()/3)) return true;
  return false;
}

void PhoenixdownIII::use(BaseKnight *knight){
  if(knight->getHP() <=0) knight->healthRestore(int(knight->getMaxHP()/3));
  else
    knight->heal(int(knight->getMaxHP()/4));
}

bool PhoenixdownIV::canUse(BaseKnight *knight){
  if(knight->getHP()< int(knight->getMaxHP()/2)) return true;
  return false;
}

void PhoenixdownIV::use(BaseKnight *knight){
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

void BaseKnight::setPrev(BaseKnight *knight){
  this->prev = knight;
}

BaseKnight* BaseKnight::previous() const{
  return this->prev; 
}

KnightType BaseKnight::getType() const {
  return this->knightType;
}

void BaseKnight::plusGil(const int gil_obtained){
  this->gil += gil_obtained;
}

int BaseKnight::getGil() const{
  return this->gil;
}

BaseKnight* BaseKnight::create(int id, int maxhp, int level, int phoenixdownI, int gil, int antidote){
  // Classify Knights' Types
  KnightType type;
  if(isPrime(maxhp)) type = PALADIN;
  else if(maxhp == 888) type = LANCELOT;
  else if(PythagoreTri(maxhp/100,(maxhp/10)%10 , maxhp%10)) type = DRAGON;
  else type = NORMAL;

  // Initiate Knights' Types
  BaseKnight* knight = nullptr;
    switch (type) {
    case PALADIN:
      knight = new PaladinKnight(id, maxhp, level, phoenixdownI, gil, antidote);

      // DEBUG
      knight->bag = nullptr;
      knight->bag = new PaladinBag(phoenixdownI,antidote,0);
      break;
    case LANCELOT:
      knight = new LancelotKnight(id, maxhp, level, phoenixdownI, gil, antidote);

      knight->bag = nullptr;
      knight->bag = new LancelotBag(phoenixdownI,antidote,16);
      break;
    case DRAGON:
      knight = new DragonKnight(id, maxhp, level, phoenixdownI, gil, antidote);
      knight->bag = new LancelotBag(phoenixdownI,antidote,14);
      break;
    case NORMAL:
      knight = new NormalKnight(id, maxhp, level, phoenixdownI, gil, antidote);
      knight->bag = nullptr;
      knight->bag = new NormalBag(phoenixdownI,antidote,19);
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
        + "," +   bag->toString() 
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
  // Getting those indexes
  ifstream army_file(file_armyknights);
  army_file >> this->numKnights;
  this->army = new BaseKnight*[numKnights];
  int maxhp,level,phoenixdownI,gil,antidote;

  // Importing indexes + Create()
  for(int id =1; id <=numKnights;id++){
    army_file >> maxhp >> level >> phoenixdownI >> gil >> antidote;
    BaseKnight* knight = BaseKnight::create(id, maxhp, level, phoenixdownI, gil, antidote);
    army[id-1] = knight;

    // !!!!!!!!!!!!!!!!!!!!!!!!! UPDATE LASTKNIGHT !!!!!!!!!!!!!!!!!!!!!!!!!
    if(id == 1) lastknight = knight;
    else{
      knight->setPrev(lastknight);
      lastknight = knight;
    }
  }

  //INDEV We're not done yet
  
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
  return this->lastknight;
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
  // transferGil(lastKnight(), 3000);
  PhoenixdownIV tear;
  cout << "Loai item: " << tear.itemType << "; ";
  lastKnight()->takeDamage(200);
  cout << "HP sau khi danh " << lastKnight()->getHP() << endl;
  cout << "Dung tear cho thang cuoi dc ko: " << tear.canUse(lastKnight()) << endl;
  if(tear.canUse(lastKnight())) tear.use(lastKnight());
  cout << "Mau sau khi dung la: " << lastKnight()->getHP() << endl;
  
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

      case MeetDurianGarden:{
        lastKnight()->healthRestore(lastKnight()->getMaxHP());
        break;
      }

      case PickedUpPhoenixDown2:{
        PhoenixdownII* tear_2 = new PhoenixdownII;
        transferItem(this->lastKnight(), tear_2);
        break;
      }

      case PickedUpPhoenixDown3:{
        PhoenixdownIII* tear_3 = new PhoenixdownIII;
        transferItem(this->lastKnight(), tear_3);
        break;
      }

      case PickedUpPhoenixDown4:{
        PhoenixdownIV* tear_4 = new PhoenixdownIV;
        transferItem(this->lastKnight(), tear_4);
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
  cout << "----DEBUG----" << endl;
  cout <<"So event la " << this->events->count() << " << ";
  for(int i =0; i < events->count();i++){
    cout << events->get(i) << " " ;
  }
  cout << endl;
  armyKnights->adventure(events);
  // this->armyKnights->dev_printAll();
  cout << endl;
  this->armyKnights->printInfo();


  cout << endl << endl;
  // DEBUG
}

KnightAdventure::~KnightAdventure() {
    delete armyKnights;
    delete events;
}

