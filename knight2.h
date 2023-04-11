#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

// #define DEBUG

enum ItemType {ANTIDOTE, TEAR_I, TEAR_II, TEAR_III, TEAR_IV};

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

// PROTOTYPES
class BaseItem;
class Events;
class BaseOpponent;

class BaseBag {
public:
    virtual bool insertFirst(BaseItem * item);
    virtual BaseItem * get(ItemType itemType);
    virtual string toString() const;
};

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
    
    // DEBUG
    int phoenixdownI;
    int antidote;
    // DEBUG
    
    bool got_poisioned = false;
    BaseBag * bag;
    KnightType knightType;

public:
    BaseKnight(int id, int maxhp, int level, int phoenixdownI,int gil, int antidote) : 
    id(id), maxhp(maxhp), level(level),phoenixdownI(phoenixdownI) ,gil(gil), bag(nullptr), antidote(antidote) {};

    static BaseKnight * create(int id, int maxhp, int level, int phoenixdownI,int gil, int antidote);
    string toString() const;

    int getHP() const;
    int getMaxHP() const;

    bool poisioned() const;
    void cleanse();
    void healthRestore(const int amount);
    void heal(const int amount);
    void takeDamage(const int damage);
};

class PaladinKnight: public BaseKnight {
  public:
    PaladinKnight(int id,int maxhp, int level,int phoenixdownI,int gil,int antidote):BaseKnight(id, maxhp,level,phoenixdownI,gil, antidote){
      this->hp = maxhp;
      this->knightType = KnightType::PALADIN;
    }
};

class LancelotKnight: public BaseKnight {
  public:
    LancelotKnight(int id,int maxhp, int level,int phoenixdownI,int gil,int antidote):BaseKnight(id, maxhp,level,phoenixdownI,gil, antidote){
      this->hp = maxhp;
      this->knightType = KnightType::LANCELOT;
    }
};

class DragonKnight: public BaseKnight {
  public:
    DragonKnight(int id,int maxhp, int level,int phoenixdownI,int gil,int antidote):BaseKnight(id, maxhp,level,phoenixdownI, gil, antidote){
      this->hp = maxhp;
      this->knightType = KnightType::DRAGON;
    }
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

  bool PalandinShield = false;
  bool LancelotSpear = false;
  bool GuinevereHair = false;
  bool ExcaliburSword = false;

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

    void printInfo() const;
    void printResult(bool win) const;
};

//  _____ _                     
// |_   _| |                    
//   | | | |_ ___ _ __ ___  ___ 
//   | | | __/ _ \ '_ ` _ \/ __|
//  _| |_| ||  __/ | | | | \__ \
//  \___/ \__\___|_| |_| |_|___/

class BaseItem {
public:
    virtual bool canUse ( BaseKnight * knight ) = 0;
    virtual void use ( BaseKnight * knight ) = 0;
};

class Antidote: public BaseItem {
  public:
    ItemType itemType = ItemType::ANTIDOTE;
    bool canUse(BaseKnight* knight) override;
    void use(BaseKnight* knight) override;
};

class phoenixdownI : public BaseItem {
  public:
    ItemType itemType = ItemType::TEAR_I;
    bool canUse(BaseKnight* knight) override;
    void use(BaseKnight* knight) override;
};

class phoenixdownII : public BaseItem {
  public:
    ItemType itemType = ItemType::TEAR_II;
    bool canUse(BaseKnight* knight) override;
    void use(BaseKnight* knight) override;
};

class phoenixdownIII : public BaseItem {
  public:
    ItemType itemType = ItemType::TEAR_III;
    bool canUse(BaseKnight* knight) override;
    void use(BaseKnight* knight) override;
};

class phoenixdownIV : public BaseItem {
  public:
    ItemType itemType = ItemType::TEAR_IV;
    bool canUse(BaseKnight* knight) override;
    void use(BaseKnight* knight) override;
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
