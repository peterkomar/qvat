#ifndef PLAYER_H
#define PLAYER_H

#include <QList>
#include "itemanimation.h"

typedef QList<ItemAnimation *> Movie;
typedef QHash<QString, Movie*> MovieIndex;

class Player
{
public:
	enum RUN_MODE {FROM_CURRENT, FROM_START, NEW_ANIMATION_ONLY, ONLY_IF_VISIBLE};
	
    Player();
    ~Player();

    void playMovie(const QString &indexName, RUN_MODE runMode = FROM_START, LOCK_MODE lockMode = SKIP_LOCK);
    void insertMovie(const QString &indexName, Movie *movie);
    Movie *insertMovie(const QString &indexName);
    bool hasQueuedMovies(){ return this->playList.size() > 0; };

    MovieIndex index;

private:
    void prepare(Movie *movie, RUN_MODE runMode, LOCK_MODE lockMode);
    void play(Movie *movie, RUN_MODE runMode);
};

#endif // SCORE_H

