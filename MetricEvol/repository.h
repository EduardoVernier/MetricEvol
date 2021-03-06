/*
    Considering that the Qt wrapper for libgit2 could not build
    properly, all member of this class will be implemented in
    pure C form.
*/

#ifndef l
#define REPOSITORY_H

#include <stdio.h>
#include <vector>
#include <string.h>
#include <math.h>

#include "git2.h"
#include "trie.h"
#include "metricextractor.h"

using namespace std;

class Repository
{
public:
    Repository(char *repo_path, int _number_of_samples);

private:
    git_repository *repo;
    char *repo_dir_path;
    Trie *trie;
    unsigned int commit_order_index;
    vector <QString> Lr; // list of filtered filenames in repository
    vector <QString> Lf; // list of filtered filenames in the working folder
    MetricExtractor metric_extractor;
    int commit_count;
    int number_of_samples;

    void count_number_of_commits();
    void check_error(int error_code, const char *action);
    void lookup_commit_file_tree(git_oid oid);
    void walk_repository();
    void dfs_tree_walk(git_tree *tree);
    void write_blob(const git_oid *oid, QString filename);

public slots:

protected:

};

#endif // REPOSITORY_H
