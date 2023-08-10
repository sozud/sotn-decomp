const int rodata_3[4] = {0,1,2,3};

int data_3[4] = {1,2,3,4};

int _main()
{
    func_a();
    func_b();
    data_3[0] = 2;
    return 0;
}

int __start()
{
    _main();
}
