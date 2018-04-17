#include <vector>
using namespace std;

struct MyVector
{
#ifdef _DEBUG
	struct MyVector** pSelf;
#endif
	int* pDataStart;
	int* pDataEnd;
	int* pBufEnd;
};

int main(int argc, char* argv[])
{

	// ��̬���飬���ݴ洢�ڶ��ڴ���
	// ��Ԫ�ط����ı�֮�󣬻ᶯ̬�����ڴ档
	vector<int> vecObj;
	vecObj.push_back(1);
	vecObj.push_back(2);
	vecObj.push_back(3);
	vecObj.pop_back();
	vecObj.push_back(4);

	// ����vector
	for (size_t i = 0; i < vecObj.size(); i++)
	{
		printf("vecObj[%d] = %d\n", i, vecObj[i]);
	}
	// ����vector
	vector<int>::iterator iter = vecObj.begin();
	while (iter != vecObj.end())
	{
		int n = *iter;
		printf("vecObj i = %d\n", n);
		iter++;
	}

	// ����ṹ������vector
	MyVector* pVector = (MyVector*)&vecObj;
	size_t size = pVector->pDataEnd - pVector->pDataStart;
	for (size_t i = 0; i < size; i++)
	{
		//pVector->pDataStart[i] = 3;
		int n = pVector->pDataStart[i];
		printf("Ԫ��=%d\n", n);
	}

	return 0;
}