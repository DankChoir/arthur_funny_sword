#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

// #define DEBUG

enum ItemType {/* TODO: */};

// PROTOTYPES
class BaseItem;
class Events;

class BaseBag {
public:
    virtual bool insertFirst(BaseItem * item);
    virtual BaseItem * get(ItemType itemType);
    virtual string toString() const;
};

class BaseOpponent;

enum KnightType { PALADIN = 0, LANCELOT, DRAGON, NORMAL };

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

    BaseBag * bag;
    KnightType knightType;

public:
    BaseKnight(int id, int maxhp, int level, int phoenixdownI,int gil, int antidote) : id(id), maxhp(maxhp), level(level),phoenixdownI(phoenixdownI) ,gil(gil), bag(nullptr), antidote(antidote) {};
    static BaseKnight * create(int id, int maxhp, int level, int phoenixdownI,int gil, int antidote);
    string toString() const;
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
public:
    int numKnights;
    BaseKnight** army;
    ArmyKnights (const string & file_armyknights);
    ~ArmyKnights();
    bool fight(BaseOpponent * opponent);
    bool adventure (Events * events);
    int count() const;
    BaseKnight * lastKnight() const;

    // bool hasPaladinShield() const;
    // bool hasLancelotSpear() const;
    // bool hasGuinevereHair() const;
    // bool hasExcaliburSword() const;

    void printInfo() const;
    void printResult(bool win) const;
};

class BaseItem {
public:
    virtual bool canUse ( BaseKnight * knight ) = 0;
    virtual void use ( BaseKnight * knight ) = 0;
};

class Events {
private:
    int* eventCodes;  // events array
    int numEvents;    // number of events
public:
    Events(const string& file_events);
    int count() const;
    int get(int i) const;
    ~Events();
};

class KnightAdventure {
private:
    ArmyKnights * armyKnights;
    Events * events;

public:
    KnightAdventure();
    ~KnightAdventure(); // TODO:

    void loadArmyKnights(const string &);
    void loadEvents(const string &);
    void run();
};

#endif // __KNIGHT2_H__
