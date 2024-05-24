#include "study_in_pink2.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

// Class MAP ELEMENTS
MapElement::MapElement(ElementType in_type) { this->type = in_type; }

ElementType Path::getType() const { return this->type; }

ElementType Wall::getType() const { return this->type; }

FakeWall::FakeWall(int in_req_exp) : MapElement(FAKE_WALL) { this->req_exp = in_req_exp; }

ElementType FakeWall::getType() const { return this->type; }

int FakeWall::getReqExp() const { return this->req_exp; }

// Class POSITION
void Position::extract_numbers(const std::string &str_pos, int &num_1, int &num_2) {
    size_t start = str_pos.find_first_of("0123456789");
    if (start != string::npos) {
        size_t ptr = start;
        while (isdigit(str_pos[ptr])) { ptr++; }
        if (ptr != string::npos) {
            num_1 = stoi(str_pos.substr(start, ptr - 1));
            size_t comma_pos = str_pos.find(',', start);
            if (comma_pos != string::npos) {
                size_t end = str_pos.find_first_of("0123456789", comma_pos);
                if (end != string::npos) {
                    ptr = end;
                    while (isdigit(str_pos[ptr])) { ptr++; }
                    num_2 = stoi(str_pos.substr(end, ptr - end));
                    return;
                } else { return; }
            } else { return; }
        } else { return; }
    } else { return; }
}

bool Position::isEqual(int in_r, int in_c) const {
    if (in_r == this->r && in_c == this->c) {
        return true;
    } else { return false; }
}

const Position Position::npos = Position(-1, -1); // npos value

Position::Position(int r, int c) {
    this->r = r;
    this->c = c;
}

Position::Position(const std::string &str_pos) {
    int row = 0, col = 0;
    extract_numbers(str_pos, row, col);
    this->r = row;
    this->c = col;
}

string Position::str() const { return "(" + to_string(this->r) + "," + to_string(this->c) + ")"; }

int Position::getCol() const { return this->c; }

int Position::getRow() const { return this->r; }

void Position::setCol(int c) { this->c = c; }

void Position::setRow(int r) { this->r = r; }

// Class MAP
Map::Map(int num_rows, int num_cols, int num_walls, Position *array_walls, int num_fake_walls,
         Position *array_fake_walls) {
    this->num_rows = num_rows;
    this->num_cols = num_cols;
    this->map = new MapElement **[num_rows];
    // Create Map 2D matrix with size [num_rows x num_cols]
    for (int i = 0; i < num_rows; i++) {
        this->map[i] = new MapElement *[num_cols];
        for (int j = 0; j < num_cols; ++j) {
            this->map[i][j] = new Path();
        }
    }
    // Assign Walls
    for (int i = 0; i < num_walls; i++) {
        int row = array_walls[i].getRow();
        int col = array_walls[i].getCol();
        if ((row >= 0 && row < num_rows) && (col >= 0 && col < num_cols)) {
            this->map[row][col] = new Wall();
        }
    }
    // Assign FakeWalls
    for (int i = 0; i < num_fake_walls; i++) {
        int row = array_fake_walls[i].getRow();
        int col = array_fake_walls[i].getCol();
        int in_req_exp = (row * 257 + col * 139 + 89) % 900 + 1;
        if ((row >= 0 && row < num_rows) && (col >= 0 && col < num_cols)) {
            this->map[row][col] = new FakeWall(in_req_exp);
        }
    }
}

Map::~Map() {
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            delete map[i][j];
        }
        delete[] map[i];
    }
    delete[] map;
}

int Map::getNumRows() const { return this->num_rows; }

int Map::getNumCols() const { return this->num_cols; }

ElementType Map::getElementType(int i, int j) const { return this->map[i][j]->getType(); }

bool Map::isValid(const Position &pos, MovingObject *mv_obj) const {
    ElementType position_type = getElementType(pos.getRow(), pos.getCol());
    if (position_type == ElementType::PATH) { return true; }
    else if (position_type == ElementType::WALL) { return false; }
    else {
        // position is FakeWall, needs to check moving object is who
        if (mv_obj->getName() == "Watson") {
            auto *pWatson = dynamic_cast<Watson *>(mv_obj);
            auto *pFW = dynamic_cast<FakeWall *>(this->map[pos.getRow()][pos.getCol()]);
            if (pWatson->getEXP() > pFW->getReqExp()) { return true; }
            else { return false; }
        } else { return true; }
    }
}

// Class MOVING OBJECT
MovingObject::MovingObject(int index, const Position pos, Map *map, const std::string &name) {
    this->index = index;
    this->pos = pos;
    this->map = map;
    this->name = name;
}

Position MovingObject::getCurrentPosition() const { return this->pos; }

void MovingObject::verified_HP(int &HP) {
    if (HP > 500) { HP = 500; }
    else if (HP < 0) { HP = 0; }
}

void MovingObject::verified_EXP(int &EXP) {
    if (EXP > 900) { EXP = 900; }
    else if (EXP < 0) { EXP = 0; }
}

string MovingObject::getName() { return this->name; }

char MovingObject::processMovingRule(std::string &movRule) {
    char firstChar = movRule[0];
    movRule.erase(0, 1);
    movRule += firstChar;
    return firstChar;
}

// Class SHERLOCK
Sherlock::Sherlock(int index, const std::string &moving_rule, const Position &init_pos, Map *map, int init_hp,
                   int init_exp) : MovingObject(index, init_pos, map, "Sherlock") {
    verified_HP(init_hp);
    verified_EXP(init_exp);
    this->hp = init_hp;
    this->exp = init_exp;
    this->movRule = moving_rule;
    this->orgMovRule = moving_rule;
}

int Sherlock::getHP() const { return this->hp; }

int Sherlock::getEXP() const { return this->exp; }

Position Sherlock::getNextPosition() {
    char mov = processMovingRule(this->movRule);
    Position curPos = this->getCurrentPosition();
    int x = curPos.getRow(), y = curPos.getCol();
    switch (mov) {
        case 'L':
            y -= 1;
            break;
        case 'R':
            y += 1;
            break;
        case 'U':
            x -= 1;
            break;
        case 'D':
            x += 1;
            break;
        default:
            break;
    }
    if (x < 0 || y < 0 || x >= this->map->getNumRows() || y >= this->map->getNumCols()) { return Position::npos; }
    else {
        if (this->map->isValid(Position(x, y), this)) {
            return Position(x, y);
        } else { return Position::npos; }
    }
}

void Sherlock::move() {
    Position nxtPos = this->getNextPosition();
    if (this->hp == 0 || this->exp == 0 ||
        (nxtPos.getRow() == Position::npos.getRow() && nxtPos.getCol() == Position::npos.getCol())) { return; }
    else {
        this->pos.setRow(nxtPos.getRow());
        this->pos.setCol(nxtPos.getCol());
    }
}

string Sherlock::str() const {
    stringstream ss;
    ss << "Sherlock[index=" << to_string(this->index) << ";pos=" << this->getCurrentPosition().str() << ";moving_rule="
       << this->orgMovRule << "]";
    return ss.str();
}

// Class Watson
Watson::Watson(int index, const std::string &moving_rule, const Position &init_pos, Map *map, int init_hp,
               int init_exp) : MovingObject(index, init_pos, map, "Watson") {
    verified_HP(init_hp);
    verified_EXP(init_exp);
    this->hp = init_hp;
    this->exp = init_exp;
    this->movRule = moving_rule;
    this->orgMovRule = moving_rule;
}

int Watson::getHP() const { return this->hp; }

int Watson::getEXP() const { return this->exp; }

Position Watson::getNextPosition() {
    char mov = processMovingRule(this->movRule);
    Position curPos = this->getCurrentPosition();
    int x = curPos.getRow(), y = curPos.getCol();
    switch (mov) {
        case 'L':
            y -= 1;
            break;
        case 'R':
            y += 1;
            break;
        case 'U':
            x -= 1;
            break;
        case 'D':
            x += 1;
            break;
        default:
            break;
    }
    if (x < 0 || y < 0 || x >= this->map->getNumRows() || y >= this->map->getNumCols()) { return Position::npos; }
    else {
        if (this->map->isValid(Position(x, y), this)) {
            return Position(x, y);
        } else { return Position::npos; }
    }
}

void Watson::move() {
    Position nxtPos = this->getNextPosition();
    if (this->hp == 0 || this->exp == 0 ||
        (nxtPos.getRow() == Position::npos.getRow() && nxtPos.getCol() == Position::npos.getCol())) { return; }
    else {
        this->pos.setRow(nxtPos.getRow());
        this->pos.setCol(nxtPos.getCol());
    }
}

string Watson::str() const {
    stringstream ss;
    ss << "Watson[index=" << to_string(this->index) << ";pos=" << this->getCurrentPosition().str() << ";moving_rule="
       << this->orgMovRule << "]";
    return ss.str();
}

// Class Configuration
int Configuration::countPairs(const std::string &data) {
    int pairs_count = 1;
    if (data.find('(') == string::npos || data.find(')') == string::npos) {
        return 0;
    }
    for (char i: data) {
        if (i == ';') { pairs_count++; }
    }
    return pairs_count;
}

Configuration::Configuration(const std::string &filepath) {
    ifstream ifs(filepath);
    string myText;
    while (getline(ifs, myText)) {
        // Split the input line into variables
        size_t space = myText.find('=');
        string str_1 = myText.substr(0, space);
        string str_2 = myText.substr(space + 1);

        // Store the value into private variables
        if (str_1 == "MAP_NUM_ROWS") { this->map_num_rows = stoi(str_2); }
        else if (str_1 == "MAP_NUM_COLS") { this->map_num_cols = stoi(str_2); }
        else if (str_1 == "MAX_NUM_MOVING_OBJECTS") { this->max_num_moving_objects = stoi(str_2); }
        else if (str_1 == "ARRAY_WALLS") {
            int pairs_count = countPairs(str_2);
            this->arr_walls = new Position[pairs_count];
            this->num_walls = pairs_count;
            if (pairs_count == 0) { continue; } // Early return when there are no pair in input

            size_t pos = 0;
            int pair_index = 0;
            while ((pos = str_2.find('(', pos)) != string::npos) {
                size_t close_bracket = str_2.find(')', pos);
                string pair = str_2.substr(pos, close_bracket - pos + 1);
                this->arr_walls[pair_index++] = Position(pair);
                pos = close_bracket + 1;
            }
        } else if (str_1 == "ARRAY_FAKE_WALLS") {
            int pairs_count = countPairs(str_2);
            this->arr_fake_walls = new Position[pairs_count];
            this->num_fake_walls = pairs_count;
            if (pairs_count == 0) { continue; } // Early return when there are no pair in input

            size_t pos = 0;
            int pair_index = 0;
            while ((pos = str_2.find('(', pos)) != string::npos) {
                size_t close_bracket = str_2.find(')', pos);
                string pair = str_2.substr(pos, close_bracket - pos + 1);
                this->arr_fake_walls[pair_index++] = Position(pair);
                pos = close_bracket + 1;
            }
        } else if (str_1 == "SHERLOCK_MOVING_RULE") { this->sherlock_moving_rule = str_2; }
        else if (str_1 == "SHERLOCK_INIT_POS") { this->sherlock_init_pos = Position(str_2); }
        else if (str_1 == "SHERLOCK_INIT_HP") { this->sherlock_init_hp = stoi(str_2); }
        else if (str_1 == "SHERLOCK_INIT_EXP") { this->sherlock_init_exp = stoi(str_2); }
        else if (str_1 == "WATSON_MOVING_RULE") { this->watson_moving_rule = str_2; }
        else if (str_1 == "WATSON_INIT_POS") { this->watson_init_pos = Position(str_2); }
        else if (str_1 == "WATSON_INIT_HP") { this->watson_init_hp = stoi(str_2); }
        else if (str_1 == "WATSON_INIT_EXP") { this->watson_init_exp = stoi(str_2); }
        else if (str_1 == "CRIMINAL_INIT_POS") { this->criminal_init_pos = Position(str_2); }
        else if (str_1 == "NUM_STEPS") { this->num_steps = stoi(str_2); }
        else { continue; }
    }
    ifs.close();
}

Configuration::~Configuration() {
    delete[] arr_walls;
    delete[] arr_fake_walls;
}

string Configuration::str() const {
    string res;
    res.append("Configuration[");
    res.append("\n");
    // num_rows, num_cols, and max_num_moving_obj
    res.append("MAP_NUM_ROWS=" + to_string(this->map_num_rows) + "\n");
    res.append("MAP_NUM_COLS=" + to_string(this->map_num_cols) + "\n");
    res.append("MAX_NUM_MOVING_OBJECTS=" + to_string(this->max_num_moving_objects) + "\n");
    // Walls
    res.append("NUM_WALLS=" + to_string(this->num_walls) + "\n");
    res.append("ARRAY_WALLS=[");
    for (int i = 0; i < this->num_walls; i++) {
        res.append(this->arr_walls[i].str());
        if (i < this->num_walls - 1) { res.append(";"); }
        else { res.append("]"); }
    }
    res.append("\n");
    // FakeWalls
    res.append("NUM_FAKE_WALLS=" + to_string(this->num_fake_walls) + "\n");
    res.append("ARRAY_FAKE_WALLS=[");
    for (int i = 0; i < this->num_fake_walls; i++) {
        res.append(this->arr_fake_walls[i].str());
        if (i < this->num_fake_walls - 1) { res.append(";"); }
        else { res.append("]"); }
    }
    res.append("\n");
    // Sherlock
    res.append("SHERLOCK_MOVING_RULE=" + this->sherlock_moving_rule + "\n");
    res.append("SHERLOCK_INIT_POS=(" + to_string(this->sherlock_init_pos.getRow()) + "," +
               to_string(this->sherlock_init_pos.getCol()) + ")" + "\n");
    res.append("SHERLOCK_INIT_HP=" + to_string(this->sherlock_init_hp) + "\n");
    res.append("SHERLOCK_INIT_EXP=" + to_string(this->sherlock_init_exp) + "\n");
    // Watson
    res.append("WATSON_MOVING_RULE=" + this->watson_moving_rule + "\n");
    res.append("WATSON_INIT_POS=(" + to_string(this->watson_init_pos.getRow()) + "," +
               to_string(this->watson_init_pos.getCol()) + ")" + "\n");
    res.append("WATSON_INIT_HP=" + to_string(this->watson_init_hp) + "\n");
    res.append("WATSON_INIT_EXP=" + to_string(this->watson_init_exp) + "\n");
    // Criminal
    res.append("CRIMINAL_INIT_POS=(" + to_string(this->criminal_init_pos.getRow()) + "," +
               to_string(this->criminal_init_pos.getCol()) + ")" + "\n");
    // num steps
    res.append("NUM_STEPS=" + to_string(this->num_steps) + "\n");
    res.append("]");

    return res;
}

// Robot, BaseItem, BaseBag,...



////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////