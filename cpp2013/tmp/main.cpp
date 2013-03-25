class Container
{
public:
Container()
{this->value = new int[100];}
~Container()
{delete this->value;}

int* value;
};

Container getContainer()
{
Container res;
return res;
}

int main()
{
Container res;
res = getContainer();
res.value[0] = 90;
return 0;
}
