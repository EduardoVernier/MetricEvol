#include "trie.h"
#include <stdio.h>
#include <string.h>

Node* Node::findChild(char c)
{
    for (unsigned int i = 0; i < mChildren.size(); i++)
    {
        Node* tmp = mChildren.at(i);
        if (tmp->mContent == c)
            return tmp;
    }
    return NULL;
}

Trie::Trie()
{
    root = new Node();
}

Trie::~Trie()
{
    // Free memory
}

bool Trie::addSHA1(char *s)
{
    Node* current = root;

    if(strlen(s) == 0)
    {
        current->setWordMarker();
        return 0;
    }

    for (unsigned int i = 0; i < strlen(s); i++)
    {
        Node* child = current->findChild(s[i]);

        if (child != NULL)
        {
            current = child;
        }
        else
        {
            Node *tmp = new Node;
            tmp->setContent(s[i]);
            current->appendChild(tmp);
            current = tmp;
        }
        if (i == strlen(s)-1)
            current->setWordMarker();

    }
    return 0;
}

bool Trie::searchSHA1(char *s)
{
    Node* current = root;

    while (current != NULL)
    {
        for (unsigned int i = 0; i < strlen(s); i++)
        {
            Node *tmp = current->findChild(s[i]);

            if(tmp == NULL)
                return false;
            current = tmp;
        }
        if ( current->wordMarker())
            return true;
        else
            return false;
    }
    return false;
}
