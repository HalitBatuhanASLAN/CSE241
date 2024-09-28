int PreIncInt(int *ip)
{
    *ip += 1;
    return *ip;
}

int PostIncInt(int *ip)
{
    int tmp = *ip;
    *ip += 1;
    return tmp;
}