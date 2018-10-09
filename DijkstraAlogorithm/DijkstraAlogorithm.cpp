#include "stdafx.h"
#include "Dijkstra.h"
#include "MyDijkstra.h"

int _tmain(int argc, _TCHAR* argv[])
{
	system("COLOR 0E");

	MyDijkstra MyDijkstra;

	MyDijkstra.printMap();
	MyDijkstra.printmatchMap();
	StartEndStruct StartEndStruct;
	StartEndStruct=MyDijkstra.getPosition();
	int start_subscipt,end_subscipt,obstacle_subscript;
	start_subscipt=MyDijkstra.matchMap(StartEndStruct.startArr[0],StartEndStruct.startArr[1]);
	cout<<"\n��ʼ��ı�ţ�"<<start_subscipt<<endl;
	end_subscipt=MyDijkstra.matchMap(StartEndStruct.endArr[0],StartEndStruct.endArr[1]);
	cout<<"��ֹ��ı�ţ�"<<end_subscipt<<endl;
	for (int i = 0; i < StartEndStruct.obstacle.size(); i++)
	{
		obstacle_subscript=MyDijkstra.matchMap(StartEndStruct.obstacle.at(i).ObstacleArr[0],
			StartEndStruct.obstacle.at(i).ObstacleArr[1]);
		cout<<"�ϰ���ı�ţ�"<<obstacle_subscript<<endl;
	}
	
	MyDijkstra.createGraph();
	//MyDijkstra.printARC();



	MyDijkstra.MyDijkstraAlgo(start_subscipt);

	MyDijkstra.printAllPath(start_subscipt,end_subscipt);

	/*====================================//
	int vexnum,edge;
    cout << "����ͼ�Ķ�������ͱߵ�������" << endl;
    cin >> vexnum >> edge;

    while (!check(vexnum, edge)) {
        cout << "�������ֵ���Ϸ�������������" << endl;
        cin >> vexnum >> edge;
    }
    Graph_DG graph(vexnum, edge);
    graph.createGraph();
    graph.print();
    graph.Dijkstra(1);
    graph.print_path(1);*/
	

	
	getchar();
	getchar();
	return 0;
}

