/*
    Considering that the Qt wrapper for libgit2 could not build
    properly, all member of this class will be implemented in
    pure C form.
*/

#ifndef l
#define REPOSITORY_H

#include <QObject>
#include <stdio.h>
#include "git2.h"



class Repository
{
public:
    Repository(char *repo_path);

private:
    git_repository *repo;

    void check_error(int error_code, const char *action);

signals:

public slots:
protected:
    void walk_repo();
};

#endif // REPOSITORY_H
