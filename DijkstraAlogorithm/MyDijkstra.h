#include <vector>
using namespace std;
typedef struct ObstacleStruct
{
	int ObstacleArr[2];
};

typedef struct StartEndStruct
{
	int startArr[2];
	int endArr[2];
	vector<ObstacleStruct>obstacle;
};

typedef struct Dist {
    string path;
    int value;
    bool visit;
	vector<int>pathInfo;
    Dist() {
        visit = false;
        value = 0;
        path = "";
    }
};
class MyDijkstra {
	static const int row=8;
	static const int clo=8;
private:
	int vexnum;   //ͼ�Ķ������
    int edge;     //ͼ�ı���
    int **arc;   //�ڽӾ���
    Dist * dis;   //��¼�����������·������Ϣ
public:

	MyDijkstra();
	~MyDijkstra();

    static const int WEIGHT = 10;//���ñߵ�Ȩֵ
	static const int INFINITE = INT_MAX;//�����ñߵ�Ȩֵ,����Ϊint�����ֵ
	void printMap();
	void printmatchMap();
	StartEndStruct getPosition();
	int matchMap(int x,int y);//���ص��Ӧ�ı��
	void createGraph();//������Ȩͼ
	bool isObstacle(int n);//�����Ϊn�ĵ��Ƿ�Ϊ�ϰ���
	void MyDijkstraAlgo(int startPosition);
	void printARC();
	void printAllPath(int begin,int end);
};