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
      current->updateGil(til_full);
      gil_obtained -= til_full;
    }
    else {
      current->updateGil(gil_obtained);
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
//  \____/   \_/   \___||_| |_| \__||___/ @Events

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
//                                           __/ | @BaseBag

void BaseBag::topAppend(BaseItem *item){
  if(this->head == nullptr) {head = item;}
  else{
    item->next = this->head;
    this->head = item;
  }
  this->count++;
}

void BaseBag::drop(){
  BaseItem* cur = head;
  if (head == nullptr) return;

  head = cur->next;
  this->count--;
  delete cur;
}

BaseKnight* BaseBag::owner() const{
  return this->knight;
}

BaseBag::BaseBag(BaseKnight*knight, int phoenixdownI,const int antidote, const int limit){
  this->knight = knight;
  this->head = nullptr;
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
  return true;
}

BaseItem* BaseBag::get(ItemType itemType){
  BaseItem* current = this->head;
  while(current != nullptr){
    // PHOENIX DOWN
    if (itemType == TEAR_ANY){
      if (current->itemType == ANTIDOTE){
        current = current->next;
        continue;
      } //only need em tears
      if (current->canUse(owner())) return current;
    }
    
    //ANTIDOTE
    if (current->itemType == itemType) return current;
    current = current->next;
  }
  return nullptr;
}

void BaseBag::swapAndDel(BaseItem *target){
  if(head == nullptr || target == nullptr) return;

  //SPECIAL CASE
  if(head == target){
    head = head->next;
    this->count--; //IMPORTANT
    delete target;
    return;
  }

  BaseItem* prev = nullptr;
  BaseItem* curr = head;

  while (curr != nullptr && curr != target) {
    prev = curr;
    curr = curr->next;
  }
  if (curr == nullptr) return;

  BaseItem* newHead = head->next;
  head->next = curr->next;
  prev->next = head;
  this->head = newHead;

  delete target;
  this->count--; //IMPORTANT
}

string BaseBag::toString() const{
  string bag_info = "";
  bag_info += "Bag[count=" + to_string(this->count) + ";";
  BaseItem* current = head;
  while(current != nullptr){
    if (current->itemType == ItemType::ANTIDOTE) bag_info += "Antidote";
    else if (current->itemType == ItemType::TEAR_I) bag_info += "PhoenixI";
    else if (current->itemType == ItemType::TEAR_II) bag_info += "PhoenixII";
    else if (current->itemType == ItemType::TEAR_III) bag_info += "PhoenixIII";
    else
    bag_info += "PhoenixdownIV";
    current = current->next;
    if(current!=nullptr) bag_info+=",";
  }
  bag_info += "]";
  return bag_info;
}

BaseBag::~BaseBag(){
  BaseItem* current = this->head;
  BaseItem* next;

  while(current != nullptr){
    next = current->next;
    delete current;
    current  = next;
  }
  head = nullptr;
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
//  \___/ \__\___|_| |_| |_|___/ @Items

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
//  @BaseKnight                                           __/ |            
//    
int BaseKnight::getLevel() const{
  return this->level;
}
void BaseKnight::levelUp(const int& levelPlus){
  this->level += levelPlus;
  this->level = min(10,level);
}

int BaseKnight::getHP() const {return this->hp;}
int BaseKnight::getMaxHP() const {return this->maxhp;}

void BaseKnight::gotPosioned() {this->isPoisioned = true;}
bool BaseKnight::poisioned() const {return this->isPoisioned;}
void BaseKnight::cleanse() {this->isPoisioned=false;}
void BaseKnight::poisionEffect(){
  this->bag->drop();
  this->bag->drop();
  this->bag->drop();
  takeDamage(10);
  cleanse();
}


void BaseKnight::healthRestore(const int& amount){this->hp = amount;}
void BaseKnight::heal(const int& amount){
  this->hp += amount;
  this->hp = min(hp,maxhp);
}
bool BaseKnight::isDead() const {return (hp<=0);}

void BaseKnight::takeDamage(const int& damage){
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

void BaseKnight::updateGil(const int& gil_obtained){
  this->gil += gil_obtained;
}

int BaseKnight::getGil() const{
  return this->gil;
}

void BaseKnight::gilHalved(){
  this->gil /= 2;
}

void BaseKnight::uses(BaseItem *item){
  item->use(this);
  this->bag->swapAndDel(item);
}

bool BaseKnight::aloPhuongHoang() const{
  return (this->getGil()>100);
}

bool BaseKnight::lazarus() {
  BaseItem* any_tear = bag->get(ItemType::TEAR_ANY);

  if(any_tear){
    uses(any_tear);

    if(hp <= 0) return false; // SPECIAL CASE WITH HP BEING 1
    return true;
  }
  else if(aloPhuongHoang()){
    this->updateGil(-100);
    this->healthRestore(maxhp/2);
    return true;
  }
  return false;
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
      knight->bag = new PaladinBag(knight,phoenixdownI,antidote,0);
      break;
    case LANCELOT:
      knight = new LancelotKnight(id, maxhp, level, phoenixdownI, gil, antidote);

      knight->bag = nullptr;
      knight->bag = new LancelotBag(knight,phoenixdownI,antidote,16);
      break;
    case DRAGON:
      knight = new DragonKnight(id, maxhp, level, phoenixdownI, gil, 0);
      knight->bag = new DragonBag(knight,phoenixdownI,0,14);
      break;
    case NORMAL:
      knight = new NormalKnight(id, maxhp, level, phoenixdownI, gil, antidote);
      knight->bag = nullptr;
      knight->bag = new NormalBag(knight,phoenixdownI,antidote,19);
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

bool BaseKnight::fight(BaseOpponent *opponent){ //FOR normal knight only - OMEGAWEAPON and HADES
  int _level = this->getLevel();
  int _levelO = opponent->getLevelO();
  bool outLevel = _level >= _levelO;
  EnemyType kieu = opponent->getType();

  if (kieu == EnemyType::OMEGAWEAPON){
    // ATTACK
    if (!(level == 10 && hp == maxhp)){
      opponent->attack(this);
      return false;
    }

    // REWARD + TRUE
    levelUp(10 - level);
    updateGil(999 - this->gil);
    return true;
  }

  else if (kieu == EnemyType::HADES){
    // ATTACk
    if (!(level == 10)){
      opponent->attack(this);
      return false;
    }

    // REWARD FOR THE ARMY NOT THE KNIGHT
    return true;
  }

  else if (kieu == EnemyType::TORNBERY){
    if (outLevel) levelUp(1);          //REWARD
    else opponent->attack(this);       //ATTACK
    
    // try finding antis
    BaseItem* anti = bag->get(ItemType::ANTIDOTE);
    if(anti) uses(anti);

    if(poisioned()) poisionEffect();
  }

  else if (kieu == EnemyType::QUEENOFCARDS){
    if (outLevel) transferGil(this, this->getGil()); // DOUBLE da GIL
    else opponent->attack(this);
  }

  else if (kieu == EnemyType::NINADERINGS) {
    if ( (hp < maxhp/3) and gil >= 50)
      opponent->trade(this);
  }

  else{
    if(outLevel) transferGil(this, opponent->getGil());
    else
      opponent->attack(this);
  }

  return (!isDead());
}

bool PaladinKnight::fight(BaseOpponent *opponent){
  int _level = this->getLevel();
  int _levelO = opponent->getLevelO();
  bool outLevel = _level >= _levelO;
  EnemyType kieu = opponent->getType();

  if (kieu == EnemyType::OMEGAWEAPON){
    // ATTACK
    if (!(level == 10 && hp == maxhp)){
      opponent->attack(this);
      return false;
    }

    // REWARD + TRUE
    levelUp(10 - level);
    updateGil(999 - this->gil);
    return true;
  }
  else if (kieu == EnemyType::HADES){
    // ATTACk
    if (!(level >= 8)){
      opponent->attack(this);
      return false;
    }

    // REWARD FOR THE ARMY NOT THE KNIGHT
    return true;
  }

  else if (kieu == EnemyType::TORNBERY){
    if (outLevel) levelUp(1);          //REWARD
    else opponent->attack(this);       //ATTACK
    
    // try finding antis
    BaseItem* anti = bag->get(ItemType::ANTIDOTE);
    if(anti) uses(anti);

    if(poisioned()) poisionEffect();
  }

  else if (kieu == EnemyType::QUEENOFCARDS){
    if (outLevel) transferGil(this, this->getGil()); // DOUBLE da GIL
    // NO GIL LOST UPON LOSING
  }

  else if (kieu == EnemyType::NINADERINGS) {
    if ( (hp < maxhp/3) )
      opponent->trade(this);
  }

  else
    transferGil(this, opponent->getGil());
  

  return(!isDead());
}

bool DragonKnight::fight(BaseOpponent *opponent){
  int _level = this->getLevel();
  int _levelO = opponent->getLevelO();
  bool outLevel = _level >= _levelO;
  EnemyType kieu = opponent->getType();

  if (kieu == EnemyType::OMEGAWEAPON){
    // DragonKnight wins those
    levelUp(10 - level);
    updateGil(999 - this->gil);
    return true;
  }
  else if (kieu == EnemyType::HADES){
    // ATTACk
    if (!(level == 10)){
      opponent->attack(this);
      return false;
    }

    // REWARD FOR THE ARMY NOT THE KNIGHT
    return true;
  }

  else if (kieu == EnemyType::TORNBERY){
    if (outLevel) levelUp(1);          // REWARD
                                       // NOT EFFECTED BY POISION
  }

  else if (kieu == EnemyType::QUEENOFCARDS){
    if (outLevel) transferGil(this, this->getGil()); // DOUBLE da GIL
    else opponent->attack(this);
  }

  else if (kieu == EnemyType::NINADERINGS) {
    if ( (hp < maxhp/3) and gil >= 50)
      opponent->trade(this);
  }

  else{
    if(outLevel) transferGil(this, opponent->getGil());
    else
      opponent->attack(this);
  }

  return (!isDead());
}

bool LancelotKnight::fight(BaseOpponent *opponent){ //FOR normal knight only - OMEGAWEAPON and HADES
  int _level = this->getLevel();
  int _levelO = opponent->getLevelO();
  bool outLevel = _level >= _levelO;
  EnemyType kieu = opponent->getType();

  if (kieu == EnemyType::OMEGAWEAPON){
    // ATTACK
    if (!(level == 10 && hp == maxhp)){
      opponent->attack(this);
      return false;
    }

    // REWARD + TRUE
    levelUp(10 - level);
    updateGil(999 - this->gil);
    return true;
  }

  else if (kieu == EnemyType::HADES){
    // ATTACk
    if (!(level == 10)){
      opponent->attack(this);
      return false;
    }

    // REWARD FOR THE ARMY NOT THE KNIGHT
    return true;
  }

  else if (kieu == EnemyType::TORNBERY){
    if (outLevel) levelUp(1);          //REWARD
    else opponent->attack(this);       //ATTACK
    
    // try finding antis
    BaseItem* anti = bag->get(ItemType::ANTIDOTE);
    if(anti) uses(anti);

    if(poisioned()) poisionEffect();
  }

  else if (kieu == EnemyType::QUEENOFCARDS){
    if (outLevel) transferGil(this, this->getGil()); // DOUBLE da GIL
    else opponent->attack(this);
  }

  else if (kieu == EnemyType::NINADERINGS) {
    if ( (hp < maxhp/3) and gil >= 50)
      opponent->trade(this);
  }

  else{
    transferGil(this, opponent->getGil());
  }

  return (!isDead());
}

void BaseKnight::attackUltimecia(Ultimecia *bossCuoi) const{
  int damage = hp*level*baseDamage;
  bossCuoi->takeDamage(damage);
}

//   _____                                
//  |  ___|                               
//  | |__   _ __    ___  _ __ ___   _   _ 
//  |  __| | '_ \  / _ \| '_ ` _ \ | | | |
//  | |___ | | | ||  __/| | | | | || |_| |
//  \____/ |_| |_| \___||_| |_| |_| \__, |
//                                   __/ |
//                                  |___/ @Enemy

BaseOpponent::BaseOpponent(int levelO){
  this->levelO = levelO;
}

EnemyType BaseOpponent::getType() const {
  return this->type;
}

int BaseOpponent::getGil() const{
  return this->gil;
}

int BaseOpponent::getLevelO() const{
  return this->levelO;
}

void BaseOpponent::attack(BaseKnight *knight) const {
  knight->takeDamage(baseDamage*(levelO- knight->getLevel()));
}

void Tornbery::attack(BaseKnight *knight) const{
  knight->gotPosioned();
}

void QoC::attack(BaseKnight *knight) const {
  knight->gilHalved();
}

void Nina::trade(BaseKnight *knight) const{
  if(knight->getType() != KnightType::PALADIN)
    knight->updateGil(-50);
  knight->heal(knight->getMaxHP()/5);
}

void OmegaWeapon::attack(BaseKnight *knight) const{
  knight->takeDamage(knight->getHP());
}

void Hades::attack(BaseKnight *knight) const{
  knight->takeDamage(knight->getHP());
}

bool Ultimecia::isDefeated() const{
  return (this->health <=0);
}

void Ultimecia::annihilate(BaseKnight *knight) const{
  knight->takeDamage(knight->getHP());
}

void Ultimecia::takeDamage(const int &damage){
  this->health -= damage;
}

//    ___                           _   __        _         _          
//   / _ \                         | | / /       (_)       | |         
//  / /_\ \ _ __  _ __ ___   _   _ | |/ /  _ __   _   __ _ | |__   ___ 
//  |  _  || '__|| '_ ` _ \ | | | ||    \ | '_ \ | | / _` || '_ \ / __|
//  | | | || |   | | | | | || |_| || |\  \| | | || || (_| || | | |\__ \
//  \_| |_/|_|   |_| |_| |_| \__, |\_| \_/|_| |_||_| \__, ||_| |_||___/
//                            __/ |                   __/ |            
//                           |___/                   |___/     @Army        

ArmyKnights::ArmyKnights(const string& file_armyknights){
  // Getting those indexes
  ifstream army_file(file_armyknights);
  string line;
  getline(army_file,line);
  stringstream ss(line);

  ss >> this->numKnights;
  this->army = new BaseKnight*[numKnights];
  int maxhp,level,phoenixdownI,gil,antidote;

  // Importing indexes + Create()
  for(int id =1; id <=numKnights;id++){
    getline(army_file,line);
    stringstream lineStream(line);
    lineStream >> maxhp >> level >> phoenixdownI >> gil >> antidote;
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

BaseKnight* ArmyKnights::updateLastKnight() {
  if (lastknight == nullptr) {
    return nullptr;
  }

  BaseKnight* oldLast = lastknight;
  BaseKnight* newLast = lastknight->previous();
  this->numKnights--;
  
  if (newLast == nullptr) {
    lastknight = nullptr;  // Update the lastknight pointer to nullptr
  } else {
    newLast->previous() == nullptr;  // Update the next pointer of the new last knight to nullptr
    lastknight = newLast;  // Update the lastknight pointer to the new last knight
  }

  delete oldLast;
  return lastknight;
}

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
    int eventID = event->get(i);
    int level = this->lastknight->getLevel();
    int levelO = (i+eventID)%10 + 1;


    bool bleed = false;
    KnightType type = lastknight->getType();
    BaseKnight* curKnight = lastknight;

    switch (eventID) {
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
        if(hasPaladinShield() && hasLancelotSpear() && hasGuinevereHair())
          this->ExcaliburSword = true;
        break;
      }

      case MeetDurianGarden:{
        curKnight->healthRestore(curKnight->getMaxHP());
        break;
      }

      case PickedUpPhoenixDown2:{
        PhoenixdownII* tear_2 = new PhoenixdownII;
        transferItem(curKnight, tear_2);
        break;
      }

      case PickedUpPhoenixDown3:{
        PhoenixdownIII* tear_3 = new PhoenixdownIII;
        transferItem(curKnight, tear_3);
        break;
      }

      case PickedUpPhoenixDown4:{
        PhoenixdownIV* tear_4 = new PhoenixdownIV;
        transferItem(curKnight, tear_4);
        break;
      }

      case MeetMadBear:{ //adjust
        MadBear* gau_dien = new MadBear(levelO);

        // COMBAT
        int initialHp = curKnight->getHP();
        bool knightSurvive = curKnight->fight(gau_dien);
        int afterHp = curKnight->getHP();
        bleed = initialHp > afterHp;

        // IN CASE SURVIVE
        if(knightSurvive) break;
		
        // IN CASE DEAD
        bool canRevive = curKnight->lazarus();
        if (canRevive == false){
          curKnight = updateLastKnight();
		  if(curKnight == nullptr) {printInfo();return false;}
          break;
        }

        bleed = false;
        break;

        delete gau_dien;
        break;
      }

      case MeetBandit:{ //adjust
        Bandit* trom = new Bandit(levelO);
          if(curKnight == nullptr) return false;
          // if(curKnight->getLevel() == levelO) break;

          // COMBAT
          int initialHp = curKnight->getHP();
          bool knightSurvive = curKnight->fight(trom);
          int afterHp = curKnight->getHP();
          bleed = initialHp > afterHp;

          // IN CASE SURVIVE
          if(knightSurvive) break;
          
          // IN CASE DEAD
          bool canRevive = curKnight->lazarus();
          if (canRevive == false){
            curKnight = updateLastKnight();
			if(curKnight == nullptr) {printInfo();return false;}
            break;
          }

          // REVIVED
          bleed = false;
          break;


        delete trom;
        break;
      }

      case MeetLordLupin:{ //adjust
        LordLupin* lupin = new LordLupin(levelO);
          if(curKnight == nullptr) return false;
          // if(curKnight->getLevel() == levelO) break;

          // COMBAT
          int initialHp = curKnight->getHP();
          bool knightSurvive = curKnight->fight(lupin);
          int afterHp = curKnight->getHP();
          bleed = initialHp > afterHp;

          // IN CASE SURVIVE
          if(knightSurvive) break;
          
          // IN CASE DEAD
          bool canRevive = curKnight->lazarus();
          if (canRevive == false){
            curKnight = updateLastKnight();
			if(curKnight == nullptr) {printInfo();return false;}
            break;
          }

          // REVIVED
          bleed = false;
          break;

        delete lupin;
        break;
      }

      case MeetElf:{ //adjust
        Elf* eo = new Elf(levelO);
          if(curKnight == nullptr) return false;
          // if(curKnight->getLevel() == levelO) break;

          // COMBAT
          int initialHp = curKnight->getHP();
          bool knightSurvive = curKnight->fight(eo);
          int afterHp = curKnight->getHP();
          bleed = initialHp > afterHp;

          // IN CASE SURVIVE
          if(knightSurvive) break;
          
          // IN CASE DEAD
          bool canRevive = curKnight->lazarus();
          if (canRevive == false){
            curKnight = updateLastKnight();
			if(curKnight == nullptr) {printInfo();return false;}
            break;
          }

          // REVIVED
          bleed = false;
          break;

        delete eo;
        break;
      }

      case MeetTroll:{ //adjust
        Troll* tronlay = new Troll(levelO);
          if(curKnight == nullptr) return false;
          // if(curKnight->getLevel() == levelO) break;

          // COMBAT
          int initialHp = curKnight->getHP();
          bool knightSurvive = curKnight->fight(tronlay);
          int afterHp = curKnight->getHP();
          bleed = initialHp > afterHp;

          // IN CASE SURVIVE
          if(knightSurvive) break;
          
          // IN CASE DEAD
          bool canRevive = curKnight->lazarus();
          if (canRevive == false){
            curKnight = updateLastKnight();
			if(curKnight == nullptr) {printInfo();return false;}
            break;
          }

          // REVIVED
          bleed = false;
          break;

        delete tronlay;
        break;
      }

      case MeetTornbery:{ //adjust
        Tornbery* ghost = new Tornbery(levelO);
          if(curKnight == nullptr) return false;
          // if(curKnight->getLevel() == levelO) break;

          // COMBAT
          int initialHp = curKnight->getHP();
          bool knightSurvive = curKnight->fight(ghost);
          int afterHp = curKnight->getHP();
          bleed = initialHp > afterHp;

          // IN CASE SURVIVE
          if(knightSurvive) break;
          
          // IN CASE DEAD
          bool canRevive = curKnight->lazarus();
          if (canRevive == false){
            curKnight = updateLastKnight();
			if(curKnight == nullptr) {printInfo();return false;}
            break;
          }

          // REVIVED
          bleed = false;
          break;

        delete ghost;
        break;
      }

      case MeetQueenOfCards:{ //adjust
        QoC* queen = new QoC(levelO);
        if(curKnight == nullptr) return false;
        if(curKnight->getLevel() == levelO) break;

        // COMBAT
        bool knightSurvive = curKnight->fight(queen);

        delete queen;
        break;
      }

      case MeetNinaDeRings:{ //adjust
        Nina* funnyMerchant = new Nina(levelO);
        if(curKnight == nullptr) return false;
        // if(curKnight->getLevel() == levelO) break;

        // COMBAT -> TRADE
        bool knightSurvive = curKnight->fight(funnyMerchant);

        delete funnyMerchant;
        break;
      }

      case MeetOmegaWeapon:{ //adjust
        // CHECK IF MET
        if(metOmega) break;

        OmegaWeapon* vuKhiToiThuong = new OmegaWeapon(levelO);
        while(true){
          if(curKnight == nullptr) return false;

          // COMBAT
          int initialHp = curKnight->getHP();

          bool knightSurvive = curKnight->fight(vuKhiToiThuong);
          metOmega = true;

          int afterHp = curKnight->getHP();
          bleed = initialHp > afterHp;

          // IN CASE SURVIVE
          if(knightSurvive) break;
          
          // IN CASE DEAD
          bool canRevive = curKnight->lazarus();
          if (canRevive == false){
            curKnight = updateLastKnight();
			if(curKnight == nullptr) {printInfo();return false;}
            continue;
          }

          // REVIVED
          bleed = false;
          break;
        }

        delete vuKhiToiThuong;
        break;
      }

      case MeetHades:{ //adjust
        if(metHades) break;
        Hades* tuThan = new Hades(levelO);
          if(curKnight == nullptr) return false;

          // COMBAT
          int initialHp = curKnight->getHP();

          bool knightSurvive = curKnight->fight(tuThan);
          metHades = true;

          int afterHp = curKnight->getHP();
          bleed = initialHp > afterHp;

          // IN CASE SURVIVE
          if(knightSurvive){
            this->PalandinShield = true;
            break;
          }
          
          // IN CASE DEAD
          bool canRevive = curKnight->lazarus();
          if(curKnight->getLevel() == levelO) break;
          if (canRevive == false){
            curKnight = updateLastKnight();
			if(curKnight == nullptr) {printInfo();return false;}
            break;
          }

          // REVIVED
          bleed = false;
          break;

        delete tuThan;
        break;
      }

      case MeetUltimecia:{
        if(hasExcaliburSword()) {printInfo();return true;}
        if(!hasLancelotSpear() || !hasPaladinShield() || !hasGuinevereHair()) {printInfo(); return false;}

        Ultimecia* bossCuoi = new Ultimecia;
        BaseKnight* curKnight = lastknight;

        while(curKnight != nullptr){
          // SKIP NORMAL
          if(curKnight->getType() == NORMAL){
            curKnight = updateLastKnight();
            continue;
          }

          // WIN ?
          curKnight->attackUltimecia(bossCuoi);
          if(bossCuoi->isDefeated()){
            printInfo();
            return true;
          }
          
          // Next please
          bossCuoi->annihilate(curKnight);
          curKnight = updateLastKnight();
        }

		curKnight = nullptr;
        printInfo();
        return false;
      }
    }
    
    // DA CHILL HEAL
    if(bleed){
      BaseItem* any_tear = curKnight->bag->get(ItemType::TEAR_ANY);
      if(any_tear) curKnight->uses(any_tear);
    }

    printInfo();
    // CHECK BAG FOR HEAL !!!!!!!!!!!!!!!!!!!
  }
  return false;
}

//
void ArmyKnights::printResult(bool win) const {
    cout << (win ? "WIN" : "LOSE") << endl;
}


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

  bool result = armyKnights->adventure(events);
  this->armyKnights->printResult(result);


  cout << endl << endl;
  // DEBUG
}

KnightAdventure::~KnightAdventure() {
    delete armyKnights;
    delete events;
}

