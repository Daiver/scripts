class MyCls
{
public:
MyCls()
{this->value = new int[100];}
~MyCls()
{delete this->value;}

int* value;
};

MyCls getContainer()
{
MyCls res;
return res;
}

int main()
{
MyCls res;
res = getContainer();
res.value[0] = 90;
return 0;
}
