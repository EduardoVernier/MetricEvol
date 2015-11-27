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
    Repository();

private:
    git_repository *repo;
    char *repo_path = "/home/eduardo/Desktop/MetricEvol/test-repo/knob/.git";
    void check_error(int error_code, const char *action);

signals:

public slots:
};

#endif // REPOSITORY_H
