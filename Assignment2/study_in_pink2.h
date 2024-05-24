/*
* Ho Chi Minh City University of Technology
* Faculty of Computer Science and Engineering
* Initial code for Assignment 1
* Programming Fundamentals Spring 2023
* Author: Vu Van Tien
* Date: 02.02.2023
*/

//The library here is concretely set, students are not allowed to include any other libraries.
#ifndef _H_STUDY_IN_PINK_2_H_
#define _H_STUDY_IN_PINK_2_H_

#include "main.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

// Forward declaration
// class MovingObject;
// class Position;
// class Configuration;
// class Map;

// class Criminal;
// class RobotS;
// class RobotW;
// class RobotSW;
// class RobotC;

// class ArrayMovingObject;
// class StudyPinkProgram;

// class BaseItem;
// class BaseBag;
// class SherlockBag;
// class WatsonBag;

class TestStudyInPink;

enum ItemType {
    MAGIC_BOOK, ENERGY_DRINK, FIRST_AID, EXCEMPTION_CARD, PASSING_CARD
};
enum ElementType {
    PATH, WALL, FAKE_WALL
};
enum RobotType {
    C = 0, S, W, SW
};

//class MapElement {
//protected:
//    ElementType type;
//public:
//    MapElement(ElementType in_type);
//
//    virtual ~MapElement();
//
//    virtual ElementType getType() const;
//};

// Class MAP ELEMENTS
class MapElement {
protected:
    ElementType type;
public:
    explicit MapElement(ElementType in_type);

    virtual ~MapElement() = default;

    virtual ElementType getType() const = 0;
};

class Path : public MapElement {
public:
    Path() : MapElement(PATH) {}

    ElementType getType() const override;
};

class Wall : public MapElement {
public:
    Wall() : MapElement(WALL) {}

    ElementType getType() const override;
};

class FakeWall : public MapElement {
private:
    int req_exp;
public:
    explicit FakeWall(int in_req_exp);

    ElementType getType() const override;

    int getReqExp() const;
};

// Class POSITION
class Position {
private:
    int r, c;

    static void extract_numbers(const string &str_pos, int &num_1, int &num_2);

public:
    static const Position npos;

    explicit Position(int r = 0, int c = 0);

    explicit Position(const string &str_pos);

    int getRow() const;

    int getCol() const;

    void setRow(int r);

    void setCol(int c);

    string str() const;

    bool isEqual(int in_r, int in_c) const;
};

// Class MOVING OBJECT
class Map; // Early declaration

class MovingObject {
protected:
    int index;
    Position pos;
    Map *map;
    string name;

    static void verified_HP(int &HP);

    static void verified_EXP(int &EXP);

    static char processMovingRule(string &movRule);

public:
    MovingObject(int index, const Position pos, Map *map, const string &name = "");

    virtual ~MovingObject() = default;

    virtual Position getNextPosition() = 0;

    Position getCurrentPosition() const;

    virtual void move() = 0;

    virtual string str() const = 0;

    string getName();
};

class Sherlock : public MovingObject {
private:
    // TODO
    int hp, exp;
    string orgMovRule; // original moving rule
    string movRule;

public:
    explicit Sherlock(int index, const string &moving_rule, const Position &init_pos, Map *map, int init_hp,
                      int init_exp);

    // getNextPosition
    Position getNextPosition() override;

    // move
    void move() override;

    // str
    string str() const override;

    // ...
    int getHP() const;

    int getEXP() const;
};

class Watson : public MovingObject {
private:
    // TODO
    int hp, exp;
    string orgMovRule; // original moving rule
    string movRule;

public:
    explicit Watson(int index, const string &moving_rule, const Position &init_pos, Map *map, int init_hp,
                    int init_exp);

    // getNextPosition
    Position getNextPosition() override;

    // move
    void move() override;

    // str
    string str() const override;

    // ...
    int getHP() const;

    int getEXP() const;
};

class Criminal : public MovingObject {
private:
    // TODO

public:
    Criminal(int index, const Position &init_pos, Map *map, Sherlock *sherlock, Watson *watson);
    // getNextPosition
    // move
    // str
    // ...
};

// Class ARRAY_MOVING_OBJECT
class ArrayMovingObject {
private:
    // TODO

public:
    ArrayMovingObject(int capacity);

    ~ArrayMovingObject();

    bool isFull() const;

    bool add(MovingObject *mv_obj);

    MovingObject *get(int index) const;

    int size() const; // return current number of elements in the array
    string str() const;
};

// Class MAP
class Map {
private:
    int num_rows, num_cols;
    MapElement ***map;

public:
    Map(int num_rows, int num_cols, int num_walls, Position *array_walls, int num_fake_walls,
        Position *array_fake_walls);

    ~Map();

    int getNumRows() const;

    int getNumCols() const;

    ElementType getElementType(int i, int j) const;

    bool isValid(const Position &pos, MovingObject *mv_obj) const;
};

// Class Configuration
class Configuration {
    friend class StudyPinkProgram;

private:
    // TODO
    int map_num_rows, map_num_cols;
    int max_num_moving_objects;
    int num_walls;
    Position *arr_walls;
    int num_fake_walls;
    Position *arr_fake_walls;
    string sherlock_moving_rule;
    Position sherlock_init_pos;
    int sherlock_init_hp;
    int sherlock_init_exp;
    string watson_moving_rule;
    Position watson_init_pos;
    int watson_init_hp;
    int watson_init_exp;
    Position criminal_init_pos;
    int num_steps;

    static int countPairs(const string &data);

public:
    explicit Configuration(const string &filepath);

    ~Configuration();

    string str() const;
};

// Robot, BaseItem, BaseBag,...
class StudyPinkProgram {
private:
    // Sample attributes
    Configuration *config;

    Sherlock *sherlock;
    Watson *watson;
    Criminal *criminal;

    Map *map;
    ArrayMovingObject *arr_mv_objs;


public:
    StudyPinkProgram(const string &config_file_path);

    bool isStop() const;

    void printResult() const {
        if (sherlock->getCurrentPosition().isEqual(criminal->getCurrentPosition())) {
            cout << "Sherlock caught the criminal" << endl;
        } else if (watson->getCurrentPosition().isEqual(criminal->getCurrentPosition())) {
            cout << "Watson caught the criminal" << endl;
        } else {
            cout << "The criminal escaped" << endl;
        }
    }

    void printStep(int si) const {
        cout << "Step: " << setw(4) << setfill('0') << si
             << "--"
             << sherlock->str() << "--|--" << watson->str() << "--|--" << criminal->str() << endl;
    }

    void run(bool verbose) {
        // Note: This is a sample code. You can change the implementation as you like.
        // TODO
        for (int istep = 0; istep < config->num_steps; ++istep) {
            for (int i = 0; i < arr_mv_objs->size(); ++i) {
                arr_mv_objs->get(i)->move();
                if (isStop()) {
                    printStep(istep);
                    break;
                }
                if (verbose) {
                    printStep(istep);
                }
            }
        }
        printResult();
    }

    ~StudyPinkProgram();
};

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////
#endif /* _H_STUDY_IN_PINK_2_H_ */
