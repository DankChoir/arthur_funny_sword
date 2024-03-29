#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

// #define DEBUG

enum ItemType {ANTIDOTE, TEAR_I, TEAR_II, TEAR_III, TEAR_IV, TEAR_ANY};

enum EventCode {
    MeetMadBear = 1,
    MeetBandit,
    MeetLordLupin,
    MeetElf,
    MeetTroll,
    MeetTornbery,
    MeetQueenOfCards,
    MeetNinaDeRings,
    MeetDurianGarden,
    MeetOmegaWeapon,
    MeetHades,
    PickedUpPhoenixDown2 = 112,
    PickedUpPhoenixDown3,
    PickedUpPhoenixDown4,
    PickedUpPaladinsShield = 95,
    PickedUpLancelotsSpear,
    PickedUpGuineveresHair,
    MeetExcaliburSword = 98,
    MeetUltimecia
};

enum KnightType { PALADIN = 0, LANCELOT, DRAGON, NORMAL };

enum EnemyType {MADBEAR = 1, BANDIT, LORDLUPIN, ELF, TROLL, TORNBERY, QUEENOFCARDS, NINADERINGS, OMEGAWEAPON, HADES};

// PROTOTYPES
class BaseItem;
class Events;
class BaseOpponent;
class BaseBag;
class Ultimecia;

 // _   __      _       _     _   
// | | / /     (_)     | |   | |  
// | |/ / _ __  _  __ _| |__ | |_ 
// |    \| '_ \| |/ _` | '_ \| __|
// | |\  \ | | | | (_| | | | | |_ 
// \_| \_/_| |_|_|\__, |_| |_|\__|
//                 __/ |          
//                |___/           
//
class BaseKnight {
protected:
  int id;
  int hp;
  int maxhp;
  int level;
  int gil;
  
  int phoenixdownI;
  int antidote;

  float baseDamage;
  
  bool isPoisioned = false;
  BaseKnight* prev = nullptr;
  KnightType knightType;

public:
  BaseBag * bag;
  BaseKnight(int id, int maxhp, int level, int phoenixdownI,int gil, int antidote) : 
  id(id), maxhp(maxhp), level(level),phoenixdownI(phoenixdownI) ,gil(gil), bag(nullptr), antidote(antidote) {};

  static BaseKnight * create(int id, int maxhp, int level, int phoenixdownI,int gil, int antidote);
  string toString() const;

  int getLevel() const;
  void levelUp(const int& levelPlus);

  int getHP() const;
  int getMaxHP() const;
  void healthRestore(const int& amount);
  void heal(const int& amount);
  bool isDead() const;
  
  void gotPosioned();
  bool poisioned() const;
  void poisionEffect();
  void cleanse();

  void takeDamage(const int& damage);

  int getGil() const;
  void updateGil(const int& gil_obtained);
  void gilHalved();
  KnightType getType() const;

  void setPrev(BaseKnight* knight);
  BaseKnight* previous() const;

  virtual bool fight(BaseOpponent* opponent);
  bool lazarus();
  bool aloPhuongHoang() const;
  void uses(BaseItem* item);

  void attackUltimecia(Ultimecia* bossCuoi) const;
};

class PaladinKnight: public BaseKnight {
  public:
    PaladinKnight(int id,int maxhp, int level,int phoenixdownI,int gil,int antidote):BaseKnight(id, maxhp,level,phoenixdownI,gil, antidote){
      this->hp = maxhp;
      this->knightType = KnightType::PALADIN;
      this->baseDamage = 0.06;
  }
    bool fight(BaseOpponent* opponent) override;
};

class LancelotKnight: public BaseKnight {
  public:
    LancelotKnight(int id,int maxhp, int level,int phoenixdownI,int gil,int antidote):BaseKnight(id, maxhp,level,phoenixdownI,gil, antidote){
      this->hp = maxhp;
      this->knightType = KnightType::LANCELOT;
      this->baseDamage = 0.05;
    }
    bool fight(BaseOpponent* opponent) override;
};

class DragonKnight: public BaseKnight {
  public:
    DragonKnight(int id,int maxhp, int level,int phoenixdownI,int gil,int antidote):BaseKnight(id, maxhp,level,phoenixdownI, gil, antidote){
      this->hp = maxhp;
      this->knightType = KnightType::DRAGON;
      this->baseDamage = 0.075;
    }
    bool fight(BaseOpponent* opponent) override;
};

class NormalKnight: public BaseKnight {
  public:
    NormalKnight(int id,int maxhp, int level,int phoenixdownI,int gil,int antidote):BaseKnight(id, maxhp,level,phoenixdownI, gil, antidote){
      this->hp = maxhp;
      this->knightType = KnightType::NORMAL;
    }
};

class ArmyKnights {
private:
  int numKnights;
  BaseKnight** army;
  BaseKnight* lastknight= nullptr;

  bool PalandinShield = false;
  bool LancelotSpear = false;
  bool GuinevereHair = false;
  bool ExcaliburSword = false;

  bool beatedOmega = false;
  bool beatedHades = false;

public:
    ArmyKnights (const string & file_armyknights); // MAMA
    ~ArmyKnights();
    bool fight(BaseOpponent * opponent);
    bool adventure (Events * events);
    int count() const; //OK
    BaseKnight * lastKnight() const; //OK

    void dev_printAll() const;

    bool hasPaladinShield() const; //OK
    bool hasLancelotSpear() const; //OK
    bool hasGuinevereHair() const; //OK
    bool hasExcaliburSword() const; //OK
    
    BaseKnight* updateLastKnight();
    void printInfo() const;
    void printResult(bool win) const;
};

//   _____                                
//  |  ___|                               
//  | |__   _ __    ___  _ __ ___   _   _ 
//  |  __| | '_ \  / _ \| '_ ` _ \ | | | |
//  | |___ | | | ||  __/| | | | | || |_| |
//  \____/ |_| |_| \___||_| |_| |_| \__, |
//                                   __/ |
//                                  |___/

class BaseOpponent{
protected:
  int baseDamage;
  int levelO;
  int gil;
  EnemyType type;
public:
  BaseOpponent(int levelO);

  int getGil() const;
  int getLevelO()const;
  EnemyType getType() const;

  virtual void attack(BaseKnight* knight) const;
  virtual void trade(BaseKnight* knight) const {};

  virtual ~BaseOpponent() {};
};

class MadBear: public BaseOpponent{
  public:
  MadBear(int levelO): BaseOpponent(levelO){
    this->baseDamage =10;
    this->gil = 100;
    this->type = EnemyType::MADBEAR;
  };
};

class Bandit: public BaseOpponent{
  public:
  Bandit(int levelO): BaseOpponent(levelO){
    this->baseDamage =15;
    this->gil = 150;
    this->type = EnemyType::BANDIT;
  };
};

class LordLupin: public BaseOpponent{
  public:
  LordLupin(int levelO): BaseOpponent(levelO){
    this->baseDamage =45;
    this->gil = 450;
    this->type = EnemyType::LORDLUPIN;
  };
};

class Elf: public BaseOpponent{
  public:
  Elf(int levelO): BaseOpponent(levelO){
    this->baseDamage =75;
    this->gil = 750;
    this->type = EnemyType::ELF;
  };
};

class Troll: public BaseOpponent{
  public:
  Troll(int levelO): BaseOpponent(levelO){
    this->baseDamage =95;
    this->gil = 800;
    this->type = EnemyType::TROLL;
  };
};

class Tornbery: public BaseOpponent{
  public:
  Tornbery(int levelO): BaseOpponent(levelO){
    this->type = EnemyType::TORNBERY;
  };
  void attack(BaseKnight* knight) const override;
};

class QoC: public BaseOpponent{
  public:
  QoC(int levelO): BaseOpponent(levelO){
    this->type = EnemyType::QUEENOFCARDS;
  };
  void attack(BaseKnight* knight) const override;
};

class Nina: public BaseOpponent{
  public:
  Nina(int levelO): BaseOpponent(levelO){
    this->type = EnemyType::NINADERINGS;
  };
  using BaseOpponent::trade;
  void trade(BaseKnight* knight) const override;
};

class OmegaWeapon: public BaseOpponent{
  public:
  OmegaWeapon(int levelO): BaseOpponent(levelO){
    this->type = EnemyType::OMEGAWEAPON;
  };
  void attack(BaseKnight* knight) const override;
};

class Hades: public BaseOpponent{
  public:
  Hades(int levelO): BaseOpponent(levelO){
    this->type = EnemyType::HADES;
  };
  void attack(BaseKnight* knight) const override;
};


// ZA BOSS
class Ultimecia{
private:
  int health;
public:
  Ultimecia(){
    this->health = 5000;
  }

  bool isDefeated() const;
  void annihilate(BaseKnight* knight) const; // knight just cant
  void takeDamage(const int& damage);
};



//  _____ _                     
// |_   _| |                    
//   | | | |_ ___ _ __ ___  ___ 
//   | | | __/ _ \ '_ ` _ \/ __|
//  _| |_| ||  __/ | | | | \__ \
//  \___/ \__\___|_| |_| |_|___/

class BaseItem {
public:
    ItemType itemType;
    BaseItem* next = nullptr;
    BaseItem() {}
    virtual bool canUse ( BaseKnight * knight ) = 0;
    virtual void use ( BaseKnight * knight ) = 0;

    virtual ~BaseItem(){};
};

class Antidote: public BaseItem {
  public:
    Antidote(){ itemType = ItemType::ANTIDOTE;}
    bool canUse(BaseKnight* knight) override;
    void use(BaseKnight* knight) override;
};

class PhoenixdownI : public BaseItem {
  public:
    PhoenixdownI(){ itemType = ItemType::TEAR_I;}
    bool canUse(BaseKnight* knight) override;
    void use(BaseKnight* knight) override;
};

class PhoenixdownII : public BaseItem {
  public:
    PhoenixdownII(){ itemType = ItemType::TEAR_II;}
    bool canUse(BaseKnight* knight) override;
    void use(BaseKnight* knight) override;
};

class PhoenixdownIII : public BaseItem {
  public:
    PhoenixdownIII(){ itemType = ItemType::TEAR_III;}
    bool canUse(BaseKnight* knight) override;
    void use(BaseKnight* knight) override;
};

class PhoenixdownIV : public BaseItem {
  public:
    PhoenixdownIV(){ itemType = ItemType::TEAR_IV;}
    bool canUse(BaseKnight* knight) override;
    void use(BaseKnight* knight) override;
};

//  ______   ___   _____ 
//  | ___ \ / _ \ |  __ \
//  | |_/ // /_\ \| |  \/
//  | ___ \|  _  || | __ 
//  | |_/ /| | | || |_\ \
//  \____/ \_| |_/ \____/
//                       

class BaseBag {
  protected:
    int count=0;
    int limit;
    BaseKnight* knight;
  public:
    BaseBag(BaseKnight* knight, int phoenixdownI, const int antidote, const int limit);
    ~BaseBag();
    BaseItem* head = nullptr;

    void topAppend(BaseItem* item);
    void swapAndDel(BaseItem* item);
    void drop();
    BaseKnight* owner() const;

    virtual bool insertFirst(BaseItem * item);
    virtual BaseItem * get(ItemType itemType);
    virtual string toString() const;
};

class PaladinBag : public BaseBag{
  public:
    using BaseBag::BaseBag;
    bool insertFirst(BaseItem *item) override;
};

class LancelotBag : public BaseBag{
  public:
    using BaseBag::BaseBag;
};

class NormalBag : public BaseBag{
  public:
    using BaseBag::BaseBag;
};

class DragonBag : public BaseBag{
  public:
    using BaseBag::BaseBag;
    bool insertFirst(BaseItem* item) override;
};

//  _____                _       
// |  ___|              | |      
// | |____   _____ _ __ | |_ ___ 
// |  __\ \ / / _ \ '_ \| __/ __|
// | |___\ V /  __/ | | | |_\__ \
// \____/ \_/ \___|_| |_|\__|___/

class Events {
private:
    int* eventCodes;  // events array
    int numEvents;    // number of events
public:
    Events(const string& file_events);
    int count() const; //OK
    int get(int i) const; //OK
    ~Events(); //OK
};

class KnightAdventure {
private:
    ArmyKnights * armyKnights;
    Events * events;

public:
    KnightAdventure();  // OK
    ~KnightAdventure(); // TODO:

    void loadArmyKnights(const string &); //OK
    void loadEvents(const string &); //OK
    void run(); // MA - MA
};

#endif // __KNIGHT2_H__
