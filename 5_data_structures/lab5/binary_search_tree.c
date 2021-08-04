bool search (node *tree, int number)
{
    if (tree == NULL)
    {
        return false;
    }
    else if (number < tree->number)
    {
        return search(tree->left, number) // recursion
    }
    else if (number > tree->number)
    {
        return search(tree->right, number) // recursion
    }
    else // if (number == tree->number)
    {
        return true;
    }
}