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
    char *repo_dir_path;
    void check_error(int error_code, const char *action);
    void lookup_commit_file_tree(git_oid oid);
    void walk_repository();
    void dfs_tree_walk(git_tree *tree);
    void write_blob(const git_oid *oid);

signals:

public slots:

protected:

};

#endif // REPOSITORY_H
