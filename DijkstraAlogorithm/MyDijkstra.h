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
	int vexnum;   //图的顶点个数
    int edge;     //图的边数
    int **arc;   //邻接矩阵
    Dist * dis;   //记录各个顶点最短路径的信息
public:

	MyDijkstra();
	~MyDijkstra();

    static const int WEIGHT = 10;//可用边的权值
	static const int INFINITE = INT_MAX;//不可用边的权值,设置为int的最大值
	void printMap();
	void printmatchMap();
	StartEndStruct getPosition();
	int matchMap(int x,int y);//返回点对应的标号
	void createGraph();//创建边权图
	bool isObstacle(int n);//检查标号为n的点是否为障碍点
	void MyDijkstraAlgo(int startPosition);
	void printARC();
	void printAllPath(int begin,int end);
};