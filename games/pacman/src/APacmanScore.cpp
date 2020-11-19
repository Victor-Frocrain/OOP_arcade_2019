/*
** EPITECH PROJECT, 2020
** arcade
** File description:
** arcade: APacmanScore.cpp
*/

#include "../include/APacman.hpp"
#include "../../../include/Entity.hpp"
#include "../../../include/ArcadeUtils.hpp"
#include <fstream>

void APacman::readBestScores()
{
    std::ifstream fs;
    std::string line = "";
    size_t nbLines = 0;
    bool equality = false;

    fs.open("games/pacman/.scores",  std::ios_base::in | std::ios_base::out);
    if (fs.fail()) {
        throw ArcadeException("Score file can not be opened.");
    }
    else {
        for (size_t i = 0; std::getline(fs, line) && i < 10; i++) {
            if (checkScores(line) == 2 && nbLines < 10) {
                _scorePosition = i;
                addNewScore();
                equality = false;
                nbLines = 10;
            }
            else if (checkScores(line) == 1 && nbLines < 10 && i < 9) {
                _scorePosition = i + 1;
                equality = true;
            }
            nbLines++;
        }
        if (equality && nbLines < 10) {
            addNewScore();
        }
        else if (nbLines < 10) {
            _scorePosition = nbLines;
            addNewScore();
        }
        fs.close();
    }
}

int APacman::checkScores(const std::string &line) const
{
    int score = takeScore(line);
    if (score == _score) {
        return 1;
    }
    if (score < _score) {
        return 2;
    }
    return 0;
}

int APacman::takeScore(const std::string &line) const
{
    std::string strScore = "";
    int score = 0;
    size_t i = 0;

    for (i = 0; i < line.length() && line[i] != ' ' && line[i] != '\t'; i++);
    for (; i < line.length() && (line[i] == ' ' || line[i] == '\t'); i++);
    for (; i < line.length(); i++) {
        strScore += line[i];
    }
    if (strScore.empty()) {
        return score;
    }
    for (i = 0; i < strScore.length(); i++) {
        if (strScore[i] < '0' || strScore[i] > '9') {
            return score;
        }
    }
    score = std::atoi(strScore.c_str());
    return score;
}

void APacman::addNewScore()
{
    _newScore = true;
    auto newScore = new Text(_left + _map[0].size() / 2, _top - 1, "NEW SCORE !");
    _entities.push_back(newScore);
    auto name = new Text(_left + _map[0].size() / 2, _top + 1, "Enter your name");
    _entities.push_back(name);
    for (size_t i = 0; i < 3; i++) {
        auto chara = new Text(_left + _map[0].size() / 2 + (i * 2 - 2), _top + 4, "_");
        _characters.push_back(chara);
        _entities.push_back(chara);
    }
}

void APacman::enterName()
{
    static size_t i = 0;
    char c = 'A';
    std::string text = "";
    int inc = 0;

    if (i < _characters.size()) {
        text = _characters[i]->getText();
        if (text.length() > 0) {
            c = text[0];
        }
        switch (_playerDirection)
        {
        case DOWN:
            inc++;
            break;
        case UP:
            inc--;
            break;
        case LEFT:
            if (i > 0) {
                i--;
            }
            break;
        case RIGHT:
            if (i < _characters.size() - 1) {
                i++;
            }
            else {
                _newName = "";
                for (size_t count = 0; count < _characters.size(); count++) {
                    std::string chara = _characters[count]->getText();
                    if (chara == "_") {
                        _newName += ' ';
                    }
                    else {
                        _newName += chara;
                        _newScore = false;
                    }
                }
                if (!_newScore) {
                    _entities.erase(_entities.begin(), _entities.end());
                    writeNewScore();
                }
            }
            break;
        default:
            break;
        }
        text = "";
        if (inc != 0) {
            if (c == '_' || c + inc > 'Z') {
                c = 'A';
            }
            else if (c + inc < 'A') {
                c = 'Z';
            }
            else {
                c += inc;
            }
            text += c;
            _characters[i]->setText(text);
        }
    }
}

void APacman::writeNewScore() const
{
    std::ifstream fs;
    std::ofstream of;
    std::string line;
    std::string text = "";
    std::vector<std::string> linesBefore;
    std::vector<std::string> linesAfter;

    fs.open("games/pacman/.scores",  std::ios_base::in | std::ios_base::out);
    if (fs.fail()) {
        throw ArcadeException("Score file can not be opened.");
    }
    for (size_t i = 0; std::getline(fs, line) && i < 9; i++) {
        if (i < _scorePosition) {
            linesBefore.push_back(line);
        }
        else {
            linesAfter.push_back(line);
        }
    }
    for (size_t i = 0; i < linesBefore.size(); i++) {
        text += linesBefore[i] + "\n";
    }
    text += _newName + "   " + std::to_string(_score) + "\n";
    for (size_t i = 0; i < linesAfter.size(); i++) {
        text += linesAfter[i] + "\n";
    }
    fs.close();
    of.open("games/pacman/.scores",  std::ios_base::in | std::ios_base::out);
    if (of.fail()) {
        throw ArcadeException("Can not write in score file.");
    }
    of << text;
    of.close();
}

void APacman::addScoresList()
{
    std::ifstream fs;
    std::string line = "";
    static bool isFirstTime = true;

    if (isFirstTime) {
        fs.open("games/pacman/.scores",  std::ios_base::in | std::ios_base::out);
        if (fs.fail()) {
            throw ArcadeException("Score file can not be opened.");
        }
        auto best = new Text(_left + _map[0].size() / 2, _top - 2, "BEST SCORES");
        _entities.push_back(best);
        for (size_t i = 0; std::getline(fs, line) && i < 10; i++) {
            line = std::to_string(i + 1) + ". " + line;
            auto text = new Text(_left + _map[0].size() / 2, _top + (i * 2), line);
            _entities.push_back(text);
        }
        fs.close();
        isFirstTime = false;
    }
}