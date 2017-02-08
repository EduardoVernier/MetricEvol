/*
    Considering that the Qt wrapper for libgit2 could not build
    properly, all member of this class will be implemented in
    pure C form.
*/


#include "repository.h"
// Creating the directories makes it Unix compatible only - fix it later
#include <sys/stat.h>
#include <sys/types.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>

Repository::Repository(char* repo_path, int _number_of_samples)
{
		repo_dir_path = repo_path;
    number_of_samples = _number_of_samples;
    // Time execution for reporting purposes

    git_libgit2_init();

		// Opening repository
		int error = git_repository_open(&repo, repo_path);
		check_error(error, "opening repository");

    // Getting the repo object database
    git_odb *odb;
    git_repository_odb(&odb, repo);

    walk_repository();

    // Cleanup
    git_odb_free(odb);
    git_repository_free(repo);
    delete trie;
}

// Report error on qDebug
void Repository::check_error(int error_code, const char *action)
{
    const git_error *error = giterr_last();
    if (!error_code)
        return;

    qDebug("Error %d %s - %s\n", error_code, action,
           (error && error->message) ? error->message : "???");
    exit(1);
}

// Count number of commits in the repository - doesn't count merges
void Repository::count_number_of_commits()
{
    // Create walker
    git_revwalk *walk;
    int error = git_revwalk_new(&walk, repo);
    check_error(error, "creating walker");

    // Configure walker
    git_revwalk_sorting(walk, GIT_SORT_TOPOLOGICAL | GIT_SORT_REVERSE );
    git_revwalk_push_head(walk); // Start at repo HEAD

    // Iterate through commits and lookup file trees
    unsigned int i = 0;
    git_oid oid;
    while (git_revwalk_next(&oid, walk) == 0)
    {
        i++;
    }
    git_revwalk_free(walk);
    commit_count = i;
}

// Walk between commits selecting which should be analysed (e.g. one every 20)
void Repository::walk_repository()
{
    count_number_of_commits();

    // Create SHA-1 trie to avoid rewriting files to disc or
    // walking trees that suffered no changes
    trie = new Trie;

    // Create walker
    git_revwalk *walk;
    int error = git_revwalk_new(&walk, repo);
    check_error(error, "creating walker");

    // Configure walker to come from past to future
    git_revwalk_sorting(walk, GIT_SORT_TOPOLOGICAL | GIT_SORT_REVERSE );
    git_revwalk_push_head(walk); // Start at repo HEAD

    // Iterate through commits and lookup file trees
    commit_order_index = 0;
    git_oid oid;
		int collection_interval = 8;
		for (int i = 0; git_revwalk_next(&oid, walk) == 0; i++)
    {
        if (i % collection_interval == 0)
        {
						// lookup_commit_file_tree(oid);
            commit_order_index++;
						string cmd = "cd ";
						cmd += repo_dir_path;
						cmd += "; ";
						cmd += "git reset --hard ";
						char oidstr[GIT_OID_HEXSZ+1] = {0};
						git_oid_tostr(oidstr, GIT_OID_HEXSZ+1, &oid);
						cmd += oidstr;
						cmd += "; ";
						cmd += "cloc . --by-file --csv --out='../calcuta/";
						char buffer [33];
						sprintf(buffer, "%d", i/collection_interval);
						cmd += buffer;
						cmd += ".csv'";
						system(cmd.c_str());
        }
    }
    git_revwalk_free(walk);
}

// Enter a commit tree and walk files
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

    // Delete files removed from Vn-1 to Vn
    sort(Lf.begin(), Lf.end());
    sort(Lr.begin(), Lr.end());
//    vector<QString> difference;
//    set_difference(Lf.begin(), Lf.end(), Lr.begin(), Lr.end(), std::back_inserter(difference));

//    for(vector<QString>::iterator it = difference.begin(); it != difference.end(); ++it)
//        remove(it->toUtf8());
    Lf = Lr;
    Lr.clear();

		// Run metrics extraction and log id and time on qDebug
		cout <<  oidstr << " - " << metric_extractor.run_metrics(oidstr);

    // Free git objects
    git_tree_free(tree);
    git_commit_free(c);
}

// Writes source files to a directory and manages trie to avoid unnecessary "downloads"
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

				// Add all source files from version to Lr
						Lr.push_back(obj_str);

        // If file is already not downloaded (from previous commits)
        if(trie->searchSHA1(oidstr) == false)
        {
            // An entry can be either a blob (file) or tree (folder)
            if (strcmp("tree", str_type)==0)
            {
                // Recursive call if node is a tree
                git_tree *subtree;
                git_object *obj;
                git_tree_entry_to_object(&obj, repo, entry);
                int error = git_tree_lookup(&subtree, repo, git_object_id(obj));
                check_error(error, "walking the subtree");
                dfs_tree_walk(subtree);
            }
            else if (strcmp("blob", str_type)==0)
            {
                // Add file oid to trie even if not source file - prevents from re-downloading it
                trie->addSHA1(oidstr);
								// Match only C++ and Java source files

										// Write file to a specific directory - later to be analysed
										write_blob(git_object_id(objt), obj_str);

            }
        }
        git_object_free(objt);
    }
}

// Write source file to ./source_files/ directory.
// Using the same filename for different versions of the same file saves us from having to manage/delete old versions
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
