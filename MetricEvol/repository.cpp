/*
    Considering that the Qt wrapper for libgit2 could not build
    properly, all member of this class will be implemented in
    pure C form.
*/

#include "repository.h"
#include <stdio.h>
#include <string.h>
#include "QDebug"
#include "git2.h"


Repository::Repository(char* repo_path)
{
    git_libgit2_init();

    // Opening repository
    int error = git_repository_open(&repo, repo_path);
    check_error(error, "opening repository");

    // Getting the repo object database
    git_odb *odb;
    git_repository_odb(&odb, repo);


//    qDebug("\n*Commit Parsing*\n");

//    git_commit *commit;
//    git_oid oid;
//    git_oid_fromstr(&oid, "7f5ffd65d7557857d170d9ba679deca8292265c7");
//    char out[GIT_OID_HEXSZ+1];
//    out[GIT_OID_HEXSZ] = '\0';

//    error = git_commit_lookup(&commit, repo, &oid);
//    check_error(error, "looking up commit");

//    unsigned int parents, p;
//    parents  = git_commit_parentcount(commit);
//    for (p = 0;p < parents;p++) {
//        git_commit *parent;
//        git_commit_parent(&parent, commit, p);
//        git_oid_fmt(out, git_commit_id(parent));
//        qDebug("Parent: %s\n", out);
//        git_commit_free(parent);
//    }

//    qDebug("\n*Tree Parsing*\n");
//    const git_tree_entry *entry;
//    git_tree *tree;
//    git_object *objt;

//    git_commit_tree(&tree, commit);

//    size_t cnt = git_tree_entrycount(tree);
//    qDebug("tree entries: %d\n", (int)cnt);

//    entry = git_tree_entry_byindex(tree, 0);
//    qDebug("Entry name: %s\n", git_tree_entry_name(entry)); // "hello.c"

//    git_tree_entry_to_object(&objt, repo, entry); // blob

//    git_blob *blob;
//    size_t rawsize;
//    const char *rawdata;

//    git_blob_lookup(&blob, repo, git_tree_entry_id(entry));
//    git_blob_rawcontent(blob);
//    rawsize = git_blob_rawsize(blob);


//    git_blob_free(blob);
//    git_object_free(objt);

    walk_repo();
    git_repository_free(repo);

}



void Repository::check_error(int error_code, const char *action)
{
    const git_error *error = giterr_last();
    if (!error_code)
        return;

    printf("Error %d %s - %s\n", error_code, action,
           (error && error->message) ? error->message : "???");

    exit(1);
}

void Repository::walk_repo()
{
    // Create walker
    git_revwalk *walk;
    if (git_revwalk_new(&walk, repo) < 0)
    { /* ERROR */ }

    // Configure walker
    git_revwalk_sorting(walk, GIT_SORT_TOPOLOGICAL | GIT_SORT_TIME);
    git_revwalk_push_head(walk); // Start at repo HEAD
    git_revwalk_hide_glob(walk, "tags/*"); // Hide tags

    git_oid oid;
    while (git_revwalk_next(&oid, walk) == 0) {
      list_commit_file_tree(oid);
    }
}

void Repository::list_commit_file_tree(git_oid oid)
{
    git_commit *c;
    char oidstr[GIT_OID_HEXSZ+1] = {0};
    oidstr[GIT_OID_HEXSZ] = '\n';

    int error = git_commit_lookup(&c, repo, &oid);
    check_error(error, "looking up commit");
    git_oid_tostr(oidstr, GIT_OID_HEXSZ+1, &oid);

    // Parse Commit Tree
    git_tree *tree;
    git_commit_tree(&tree, c);

    qDebug("%s\n%s", oidstr,
           git_commit_message(c));

    dfs_tree_walk(tree, c);

    git_commit_free(c);
}

void Repository::dfs_tree_walk(git_tree *tree, git_commit *c)
{
    size_t cnt = git_tree_entrycount(tree);
    char oidstr[GIT_OID_HEXSZ+1] = {0};
    oidstr[GIT_OID_HEXSZ] = '\n';


    for (size_t i = 0; i < cnt; i++)
    {
        git_object *objt;
        const git_tree_entry *entry;
        entry = git_tree_entry_byindex(tree, i);
        git_tree_entry_to_object(&objt, repo, entry); // blob
        git_oid_tostr(oidstr, GIT_OID_HEXSZ+1, git_object_id(objt));
        qDebug("%s - %s", git_tree_entry_name(entry), oidstr);
    }

}
