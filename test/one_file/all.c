const int rodata_0[4] = {0,1,2,3};

int data_0[4] = {1,2,3,4};


int func_a()
{
    data_0[0] = 2;
    return 0;
}

const int rodata_1[4] = {0,1,2,3};
int data_1[4] = {1,2,3,4};

int func_b()
{
    data_1[1] = 3;
    return 0;
}
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
