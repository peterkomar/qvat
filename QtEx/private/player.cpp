#include "player.h"
#include "../item.h"

Player::Player()
{
}

Player::~Player()
{
    // NB! Deleting all movies.
    qDeleteAll(this->index);
}

void Player::prepare(Movie *movie, RUN_MODE runMode, LOCK_MODE lockMode)
{
    if (lockMode == LOCK_ITEMS){
        for (int i=0; i<movie->size(); ++i){
            if (runMode == ONLY_IF_VISIBLE && !movie->at(i)->demoItem()->isVisible())
                continue;
            movie->at(i)->lockItem(true);
            movie->at(i)->prepare();
        }
    }
    else if (lockMode == UNLOCK_ITEMS){
        for (int i=0; i<movie->size(); ++i){
            if (runMode == ONLY_IF_VISIBLE && !movie->at(i)->demoItem()->isVisible())
                continue;
            movie->at(i)->lockItem(false);
            movie->at(i)->prepare();
        }
    }
    else {
        for (int i=0; i<movie->size(); ++i){
            if (runMode == ONLY_IF_VISIBLE && !movie->at(i)->demoItem()->isVisible())
                continue;
            movie->at(i)->prepare();
        }
    }
}

void Player::play(Movie *movie, RUN_MODE runMode)
{
    if (runMode == NEW_ANIMATION_ONLY){
        for (int i=0; i<movie->size(); ++i)
            if (movie->at(i)->notOwnerOfItem())
                movie->at(i)->play(true);
    }
    else if (runMode == ONLY_IF_VISIBLE){
        for (int i=0; i<movie->size(); ++i)
            if (movie->at(i)->demoItem()->isVisible())
                movie->at(i)->play(runMode == FROM_START);
    }
    else {
        for (int i=0; i<movie->size(); ++i)
            movie->at(i)->play(runMode == FROM_START);
    }
}

void Player::playMovie(const QString &indexName, RUN_MODE runMode, LOCK_MODE lockMode)
{
    MovieIndex::iterator movieIterator = this->index.find(indexName);
    if (movieIterator == this->index.end())
        return;

    Movie *movie = *movieIterator;
    this->prepare(movie, runMode, lockMode);
    this->play(movie, runMode);
}

void Player::queueMovie(const QString &indexName, RUN_MODE runMode, LOCK_MODE lockMode)
{
    MovieIndex::iterator movieIterator = this->index.find(indexName);
    if (movieIterator == this->index.end()){
        if (Colors::verbose)
            qDebug() << "Queuing movie:" << indexName << "(does not exist)";
        return;
    }

    Movie *movie = *movieIterator;
    this->prepare(movie, runMode, lockMode);
    this->playList.append(PlayListMember(movie, int(runMode)));
    if (Colors::verbose)
        qDebug() << "Queuing movie:" << indexName;
}

void Player::playQue()
{
    int movieCount = this->playList.size();
    for (int i=0; i<movieCount; i++)
        this->play(this->playList.at(i).movie, RUN_MODE(this->playList.at(i).runMode));
    this->playList.clear();
    if (Colors::verbose)
        qDebug() << "********* Playing que *********";
}

void Player::insertMovie(const QString &indexName, Movie *movie)
{
    this->index.insert(indexName, movie);
}

Movie *Player::insertMovie(const QString &indexName)
{
    Movie *movie = new Movie();
    insertMovie(indexName, movie);
    return movie;
}

