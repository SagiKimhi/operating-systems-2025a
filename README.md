# Operating Systems Course 2025a

[![GLWTSPL](https://img.shields.io/badge/GLWTS-Public_License-red.svg)](LICENSE)

Operating systems course of open university 2025a. Created for knowledge
sharing, learning from other people's solutions, and encouraging collaborations.

## Socials

<img alt="Discord logo"
    href=""
    width="70px"
    height="70px" 
    src="https://discord.com/assets/cb48d2a8d4991281d7a6a95d2f58195e.svg" 
/>
<img alt="Whatsapp logo"
    href=""
    width="70px"
    height="70px" 
    src="https://upload.wikimedia.org/wikipedia/commons/6/6b/WhatsApp.svg" 
/>

## Development Process

1. Clone the repository (or a fork of this repo) and set up local configurations
   (see workflow example's configurations section).

2. Create a new issue for whatever it is you will be working on, or select an
   existing issue from the [issues page](issues/)

3. Assign the issue to yourself, and create a dedicated branch for working on
   that issue using one of the name patterns listed below:

    - doc/\<issue-id\>/\<author\> : Use for issues labled as 'documentation'.

    - fix/\<issue-id\>/\<author\> : Use for issues labled as 'bug'.

    - feat/\<issue-id\>/\<author\> : Use for issues labled as 'enhancement'.

    - maint/\<issue-id\>/\<author\> : Use for issues labled as 'maintnance'.

    - exercise/\<issue-id\>/\<author\> : Use for issues labled as 'exercise'.

    - assignment/maman11/\<author\> : Use for working on your solution to
      maman11 assignment.

    - assignment/maman12/\<author\> : Use for working on your solution to
      maman12 assignment.

    - assignment/maman13/\<author\> : Use for working on your solution to
      maman13 assignment.

    - assignment/\<issue-id\>/\<author\> : Use for working on your solution to
      an assignment not listed above from a different institution.

## Complete workflow example

The following is a workflow example to set up git and commit changes from a user
called MrDocker working on maman11 assignment.

### Cloning the repository:

```sh
# Cloning the original repository via ssh
git clone git@github.com:SagiKimhi/operating-systems-2025a.git

# Cloning the original repository via http
git clone https://github.com/SagiKimhi/operating-systems-2025a.git

# Cloning a fork of the repository forked by MrDocker via ssh
git clone git@github.com:MrDocker/operating-systems-2025a.git

# Cloning a fork of the repository forked by MrDocker via https
git clone https://github.com/MrDocker/operating-systems-2025a.git
```

### Setting up local configurations:

```sh
# If you havent done so already, cd into your local repository copy
cd operating-systems-2025a

# Configure username and email
git config --local user.name "MrDocker"
git config --local user.email "mr-docker123@gmail.com"

# Configure pull and push strategies
git config --local pull.rebase true
git config --local push.followTags true
```

### Setting up a new branch, staging, commiting, and pushing changes to remote

```sh
# Creates a new branch called "assignment/maman11/MrDocker" and set it up to
# track changes from upstream branch origin/main
#
git checkout origin/main -b assignment/maman11/MrDocker

# Staging changes to file1, file2, and file3
#
git add file1 file2 file3

# Alternatively, use the -p or --patch flag to inspect changes in each file and
# interactively choose whether to skip/stage/edit change per-file for all
# changed files
#
git add -p

# Inspect differences between staged changes and the HEAD branch
#
git diff --word-diff-regex=. --color-words --cached

# Commit the changes, use the branch type for the title of your commit message
# followed by a semicolon and a short title to describe the change (up to 50
# characters long) written in imperative mood, i.e. instead of 
# 'fix: added x to y' write 'fix: add x to y'.
#
# This is useful when reviewing commits as each commit provides a brief
# description of what is going to happen after applying its changes.
#
git commit --verbose -s -m "assignment: add maman11 solution by MrDocker"

# Pull with rebase to ensure local changes are up to date with newest changes to
# upstream branch
#
git pull --rebase

# Push the changes to remote repository
#
git push origin HEAD
```

## Additional Resources

### Guidlines for submitting patches and commiting changes

[git/git.git - Submitting Patches](assets/SubmittingPatches.html):
General guidelines for submitting patches and commiting changes from the
original git repository of git (git.git)

### Fix commit and squash

```sh
# make changes for commit 1
#
git add <files>
git commit -s -m "MSG"

# make changes for commit 2
#
git add <files>
git commit -s -m "MSG"

# more changes for commit 1 in a third commit
#
git add <files>

# this will create a special commit message that git autosquash will
# automatically understand
#
# <identify_commit_1> can be the sha of the commit, HEAD^, :/"some text in
# commit 1's commit message"
#
git commit --fixup=<identify_commit_1>  

# open editor with the commits already rearranged and commit 1 + commit 3 ready
# to be squashed together
#
git rebase -i --autosquash 
```

### Git Cheatsheet

<img alt="Git Cheatsheet"
    src="assets/git-cheatsheet.png"
/>
