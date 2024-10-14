bool isSorted(const int arr[],int size)
{
    if(size <= 2)
        return true;
    bool sorting = arr[size - 1] > arr[0];

    for(int i = 0;i<size-1;i++)
    {
        if(inc)
        {
            if(arr[i] > arr[i+ 1])
                return false;
        }
        else if(arr[i] < arr[i + 1])
            return false;
    }
    return true;
}