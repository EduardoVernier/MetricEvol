/*
    Considering that the Qt wrapper for libgit2 could not build
    properly, all member of this class will be implemented in
    pure C form.
*/

#include <stdio.h>
#include <string.h>
#include "repository.h"
#include "QDebug"
#include "QRegExp" // Pick one
#include "QRegularExpression"
#include "QString"
#include "QTime"
#include "git2.h"
// Creating the directories makes it Unix compatible only - fix it later
#include <sys/stat.h>
#include <sys/types.h>


Repository::Repository(char* repo_path, MainWindow *_w)
{
    // Time execution for reporting purposes
    w = _w;
    QTime t;
    t.start();

    git_libgit2_init();

    QRegularExpression re("\\w+.git$");
    QRegularExpressionMatch match = re.match(repo_path);
    if (match.hasMatch())
    {
        QString matched = match.captured(0);
        const char *path = "./repo/";
        int error = git_clone(&repo, repo_path, path, NULL);
        check_error(error, "cloning repository");
        qDebug("Time elapsed cloning: %fs\n", t.elapsed()/1000.0);
    }
    else
    {
        // Opening repository
        int error = git_repository_open(&repo, repo_path);
        check_error(error, "opening repository");
        qDebug("Time elapsed opening: %fs", t.elapsed()/1000.0);
    }

    t.start();

    // Getting the repo object database
    git_odb *odb;
    git_repository_odb(&odb, repo);

    walk_repository();

    git_odb_free(odb);
    git_repository_free(repo);
    delete trie;

    qDebug("Time elapsed walking and writing to disc: %f\n",(t.elapsed()/1000.0));

}


void Repository::check_error(int error_code, const char *action)
{
    const git_error *error = giterr_last();
    if (!error_code)
        return;

    qDebug("Error %d %s - %s\n", error_code, action,
           (error && error->message) ? error->message : "???");
    exit(1);
}


void Repository::walk_repository()
{
    // Create SHA-1 trie to avoid rewriting files to disc or
    // walking trees that suffered no changes
    trie = new Trie;

    // Create walker
    git_revwalk *walk;
    int error = git_revwalk_new(&walk, repo);
    check_error(error, "creating walker");

    // Configure walker
    git_revwalk_sorting(walk, GIT_SORT_TOPOLOGICAL | GIT_SORT_REVERSE );
    git_revwalk_push_head(walk); // Start at repo HEAD

    // Iterate through commits and lookup file trees
    commit_order_index = 0;
    unsigned int i = 0;
    git_oid oid;
    unsigned int collection_interval = 40; // e.g. collect one version every 200 commits
    while (git_revwalk_next(&oid, walk) == 0)
    {
        i++;
        if ( i == collection_interval)
        {
            lookup_commit_file_tree(oid);
            i = 0;
            commit_order_index++;
        }
    }
    git_revwalk_free(walk);
}


void Repository::lookup_commit_file_tree(git_oid oid)
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



    // Walk through all files in this specific commit (version)
    dfs_tree_walk(tree);

    // Delete files added from Vn-1 to Vn
    sort(Lf.begin(), Lf.end());
    sort(Lr.begin(), Lr.end());
    vector<QString> difference;
    set_difference(
        Lf.begin(), Lf.end(),
        Lr.begin(), Lr.end(),
        std::back_inserter(difference));

    for(vector<QString>::iterator it = difference.begin(); it != difference.end(); ++it)
        remove(it->toUtf8());

    Lf = Lr;
    Lr.clear();

    // Run metrics extraction
    qDebug() <<  oidstr << " - " << metric_extractor.run_metrics();


    // qDebug("Done.");
    git_tree_free(tree);
    git_commit_free(c);
}


void Repository::dfs_tree_walk(git_tree *tree)
{
    // Count number of children nodes
    size_t cnt = git_tree_entrycount(tree);
    char oidstr[GIT_OID_HEXSZ+1] = {0};
    oidstr[GIT_OID_HEXSZ] = '\n';

    for (size_t i = 0; i < cnt; i++)
    {
        git_object *objt;
        const git_tree_entry *entry;
        entry = git_tree_entry_byindex(tree, i);
        git_tree_entry_to_object(&objt, repo, entry);
        git_oid_tostr(oidstr, GIT_OID_HEXSZ+1, git_object_id(objt));
        const char *str_type = git_object_type2string(git_object_type(objt));
        QString obj_str (git_tree_entry_name(entry));

        QRegExp regex("^.+\\.(c|h|cpp|cc|java)$");
        if (regex.exactMatch(obj_str))
            Lr.push_back(obj_str); // Add to Lr


        if(trie->searchSHA1(oidstr) == false)
        {
            // An entry can be either a blob (file) or tree
            if (strcmp("tree", str_type)==0)
            {
                // Recursive call if node is a tree
                git_tree *subtree;
                git_object *obj;
                git_tree_entry_to_object(&obj, repo, entry);
                int error = git_tree_lookup(&subtree, repo, git_object_id(obj));
                check_error(error, "walking the subtree");
                // Add tree oid to trie
                //trie->addSHA1(oidstr); -> commented to solve false deleted files
                dfs_tree_walk(subtree);
            }
            else if (strcmp("blob", str_type)==0)
            {
                // Add file oid to trie
                trie->addSHA1(oidstr);
                // Match only C++ and Java source files
                if(regex.exactMatch(obj_str))
                {
                    // Write file to a specific directory
                    write_blob(git_object_id(objt), obj_str);
                }
            }
        }
        git_object_free(objt);
    }
}


void Repository::write_blob(const git_oid *oid, QString filename)
{
    git_blob *blob = NULL;
    char oidstr[GIT_OID_HEXSZ+1] = {0};
    oidstr[GIT_OID_HEXSZ] = '\n';

    // Set blob (source file) path as: ./source_files/commit_index-commit_id/filename-blob_id
    git_oid_tostr(oidstr, GIT_OID_HEXSZ+1, oid);
    QString dir_path =  "./source_files/";
    QString file_path = dir_path + filename;

    // Open blob
    int error = git_blob_lookup(&blob, repo, oid);
    check_error(error, "opening blob");

    // Create directory with the hierachy explained above
    error = mkdir(dir_path.toStdString().c_str(), 0777); // Only Unix compatible

    // Write blob on file
    FILE *pFile;
    pFile = fopen(file_path.toStdString().c_str(), "w");
    fwrite(git_blob_rawcontent(blob), (size_t)git_blob_rawsize(blob), 1, pFile);
    fclose (pFile);

    git_blob_free(blob);
}


