/*
    Considering that the Qt wrapper for libgit2 could not build
    properly, all member of this class will be implemented in
    pure C form.
*/

#include "repository.h"
#include <stdio.h>
#include "QDebug"
#include "git2.h"


Repository::Repository()
{
    git_libgit2_init();

    // Cloning a repository
    int error = git_repository_open(&repo, repo_path);
    check_error(error, "opening repository");

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


