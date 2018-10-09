#include "stdafx.h" 
#include "MyDijkstra.h"
#include <iostream>
#include <string>
using namespace std;

char Map[8][8]={
	{'.','.','.','.','.','.','.','.'},//01,02,03,04,05,06,07,08
	{'.','.','.','.','.','.','.','.'},//09,10,11,12,13,14,15,16
	{'.','O','.','.','.','.','.','.'},//17,18,19,20,21,22,23,24
	{'.','O','.','.','S','.','.','.'},//25,26,27,28,29,30,31,32
	{'.','.','.','.','.','.','.','.'},//33,34,35,36,37,38,39,40
	{'.','.','.','.','.','.','.','.'},//41,42,43,44,45,46,47,48
	{'.','.','.','.','.','.','E','.'},//49,50,51,52,53,54,55,56
	{'.','.','.','.','.','.','.','.'}//57,58,59,60,61,62,63,64
};

MyDijkstra::MyDijkstra(){
	//=======通过已经创建的数组进行边权图的创建========
	int vexnum;
	int edge;
	edge=2*clo*row-clo-row;//确定离散地图中边的数量
	vexnum=clo*row;

    //为邻接矩阵开辟空间和赋初值
    arc = new int*[vexnum];
    dis = new Dist[vexnum];
    for (int i = 0; i < vexnum; i++){
        arc[i] = new int[vexnum];
        for (int k = 0; k < vexnum; k++){
                arc[i][k] = INT_MAX;//邻接矩阵初始化为无穷大
        }
    }
}
MyDijkstra::~MyDijkstra(){
	vexnum=clo*row;
	delete[] dis;
    for (int i = 0; i < vexnum; i++) {
        delete this->arc[i];
    }
    delete arc;
}
void MyDijkstra::printMap(){
	cout<<"如下图所示，为8*8的地图模型：\n"
	<<"字母.代表可用点,"
	<<"字母O代表障碍点，\n"
	<<"字母S代表起始点,"
	<<"字母E代表终止点。\n"
	<<"原地图如下：\n";
	cout<<"=============地图模型============\n\n";
	for (int i = 0; i < row; i++){
		for (int j = 0; j < clo; j ++){
			cout<<Map[i][j]<<"\t";
		}
	cout<<"\n\n\n";
	}
	cout<<endl;
}
void MyDijkstra::printmatchMap(){
	cout<<"=============标号模型============\n\n";
	for (int i = 0; i < row; i++){
		for (int j = 0; j < clo; j ++){
			cout<<clo*i+j<<"\t";
		}
	cout<<"\n\n\n";
	}
	cout<<endl;
}
StartEndStruct MyDijkstra::getPosition(){
	StartEndStruct startEndStruct;
	ObstacleStruct ObstacleStruct;
	for (int i = 0; i < row; i++){
		for (int j = 0; j < clo; j++){
			if (Map[i][j]=='S')	{	
				startEndStruct.startArr[0]=i;
				startEndStruct.startArr[1]=j;
			}
			if (Map[i][j]=='E'){		
				startEndStruct.endArr[0]=i;
				startEndStruct.endArr[1]=j;
			}
			if(Map[i][j]=='O'){		
				//cout<<"障碍点的标号："<<clo*i+j+1<<endl;
				ObstacleStruct.ObstacleArr[0]=i;
				ObstacleStruct.ObstacleArr[1]=j;
				startEndStruct.obstacle.push_back(ObstacleStruct);
			}
		}
	}
	return startEndStruct;
}
int MyDijkstra::matchMap(int x,int y){
	return clo*x+y;//返回每一个元素对应的标号
}
bool MyDijkstra::isObstacle(int n){
	StartEndStruct StartEndStruct;
	StartEndStruct=getPosition();
	for (int i = 0; i < StartEndStruct.obstacle.size(); i++){
		if(n==matchMap(StartEndStruct.obstacle.at(i).ObstacleArr[0],
			StartEndStruct.obstacle.at(i).ObstacleArr[1])){
				return true;
		}
	}
	return false;	
}
void MyDijkstra::createGraph(){
    int start=0;//出发点的标号，每个出发点都对应4、3、2个终止点，选择第一个进行依次延展
    /*
	//int end;//终止点的标号，该标号与出发点的标号有对应的关系
    //int count = 0;
	//=======通过已经创建的数组进行边权图的创建========
	//int edge;
	//edge=2*clo*row-clo-row;//确定离散地图中边的数量
	*/
	while (start != clo*row) {
        /*cin >> start >> end >> weight;//首先判断边的信息是否合法
        while (check_edge_value(start, end, weight)) {
            cout << "输入的边的信息不合法，请重新输入" << endl;
            cin >> start >> end >> weight;
        }

		if(){//障碍物周围	
			arc[start - 1][end - 1] = INFINITE;//对邻接矩阵对应上的点赋值
			arc[end - 1][start - 1] = INFINITE;//无向图添加上这行代码

		}else{
			arc[start - 1][end - 1] = WEIGHT;//对邻接矩阵对应上的点赋值
			arc[end - 1][start - 1] = WEIGHT;//无向图添加上这行代码	
		}*/
		//创建邻接矩阵arc
		if (start==0){//存在两个点标号分别为start+1,start+clo
			if(isObstacle(start)){//该点为障碍点
				arc[start][start+1]=INFINITE;
				arc[start][start+clo]=INFINITE;
			}else{//该点不是障碍点
				if(isObstacle(start+1)){//判断该点的右方点是否为障碍点
					arc[start][start+1]=INFINITE;
				}else{
					arc[start][start+1]=WEIGHT;
				}
				if(isObstacle(start+clo)){//判断该点的下方点是否为障碍点
					arc[start][start+clo]=INFINITE;
				}else{
					arc[start][start+clo]=WEIGHT;
				}
			}	
		}else if(start==(clo-1)){
			//存在两个点标号分别为start-1,start+clo
			if(isObstacle(start)){//该点为障碍点
				arc[start][start-1]=INFINITE;
				arc[start][start+clo]=INFINITE;
			}else{//该点不是障碍点
				if(isObstacle(start-1)){//判断该点的左方点是否为障碍点
					arc[start][start-1]=INFINITE;
				}else{
					arc[start][start-1]=WEIGHT;
				}
				if(isObstacle(start+clo)){//判断该点的下方点是否为障碍点
					arc[start][start+clo]=INFINITE;
				}else{
					arc[start][start+clo]=WEIGHT;
				}
			}
		}else if(start==(clo*row-1)){
			//存在两个点标号分别为start-1,start-clo
			if(isObstacle(start)){//该点为障碍点
				arc[start][start-1]=INFINITE;
				arc[start][start-clo]=INFINITE;
			}else{//该点不是障碍点
				if(isObstacle(start-1)){//判断该点的左方点是否为障碍点
					arc[start][start-1]=INFINITE;
				}else{
					arc[start][start-1]=WEIGHT;
				}
				if(isObstacle(start-clo)){//判断该点的上方点是否为障碍点
					arc[start][start-clo]=INFINITE;
				}else{
					arc[start][start-clo]=WEIGHT;
				}
			}	
		}else if(start==(clo*row-clo-1)){
			//存在两个点标号分别为start+1,start-clo
			if(isObstacle(start)){//该点为障碍点
				arc[start][start+1]=INFINITE;
				arc[start][start-clo]=INFINITE;
			}else{//该点不是障碍点
				if(isObstacle(start+1)){//判断该点的右方点是否为障碍点
					arc[start][start+1]=INFINITE;
				}else{
					arc[start][start+1]=WEIGHT;
				}
				if(isObstacle(start-clo)){//判断该点的上方点是否为障碍点
					arc[start][start-clo]=INFINITE;
				}else{
					arc[start][start-clo]=WEIGHT;
				}
			}
		}else if(start%clo==0){
			//存在三个点标号分别为start-clo,start+1,start+clo
			if(isObstacle(start)){//该点为障碍点
				arc[start][start+1]=INFINITE;
				arc[start][start-clo]=INFINITE;
				arc[start][start+clo]=INFINITE;
			}else{//该点不是障碍点
				if(isObstacle(start+1)){//判断该点的右方点是否为障碍点
					arc[start][start+1]=INFINITE;
				}else{
					arc[start][start+1]=WEIGHT;
				}
				if(isObstacle(start-clo)){//判断该点的上方点是否为障碍点
					arc[start][start-clo]=INFINITE;
				}else{
					arc[start][start-clo]=WEIGHT;
				}
				if(isObstacle(start+clo)){//判断该点的下方点是否为障碍点
					arc[start][start+clo]=INFINITE;
				}else{
					arc[start][start+clo]=WEIGHT;
				}
			}
		}else if(start/clo==0){
			//存在三个点标号分别为start-1,start+clo,start+1
			if(isObstacle(start)){//该点为障碍点
				arc[start][start+1]=INFINITE;
				arc[start][start-1]=INFINITE;
				arc[start][start+clo]=INFINITE;
			}else{//该点不是障碍点
				if(isObstacle(start+1)){//判断该点的右方点是否为障碍点
					arc[start][start+1]=INFINITE;
				}else{
					arc[start][start+1]=WEIGHT;
				}
				if(isObstacle(start-1)){//判断该点的左方点是否为障碍点
					arc[start][start-1]=INFINITE;
				}else{
					arc[start][start-1]=WEIGHT;
				}
				if(isObstacle(start+clo)){//判断该点的下方点是否为障碍点
					arc[start][start+clo]=INFINITE;
				}else{
					arc[start][start+clo]=WEIGHT;
				}
			}
		}else if((start+1)%clo==0){
			//存在三个点标号分别为start-clo,start-1,start+clo
			if(isObstacle(start)){//该点为障碍点
				arc[start][start-1]=INFINITE;
				arc[start][start-clo]=INFINITE;
				arc[start][start+clo]=INFINITE;
			}else{//该点不是障碍点
				if(isObstacle(start-1)){//判断该点的左方点是否为障碍点
					arc[start][start-1]=INFINITE;
				}else{
					arc[start][start-1]=WEIGHT;
				}
				if(isObstacle(start-clo)){//判断该点的上方点是否为障碍点
					arc[start][start-clo]=INFINITE;
				}else{
					arc[start][start-clo]=WEIGHT;
				}
				if(isObstacle(start+clo)){//判断该点的下方点是否为障碍点
					arc[start][start+clo]=INFINITE;
				}else{
					arc[start][start+clo]=WEIGHT;
				}
			}
		}else if((start-(row-1)*clo>0)&&(start-(row-1)*clo)/clo==0){
			//存在三个点标号分别为start-1,start-clo,start+1
			if(isObstacle(start)){//该点为障碍点
				arc[start][start+1]=INFINITE;
				arc[start][start-clo]=INFINITE;
				arc[start][start-1]=INFINITE;
			}else{//该点不是障碍点
				if(isObstacle(start+1)){//判断该点的右方点是否为障碍点
					arc[start][start+1]=INFINITE;
				}else{
					arc[start][start+1]=WEIGHT;
				}
				if(isObstacle(start-clo)){//判断该点的上方点是否为障碍点
					arc[start][start-clo]=INFINITE;
				}else{
					arc[start][start-clo]=WEIGHT;
				}
				if(isObstacle(start-1)){//判断该点的左方点是否为障碍点
					arc[start][start-1]=INFINITE;
				}else{
					arc[start][start-1]=WEIGHT;
				}
			}
		}else{
			//存在四个点标号分别为start-1,start-clo,start+1，start+clo
			if(isObstacle(start)){//该点为障碍点
				arc[start][start+1]=INFINITE;
				arc[start][start-clo]=INFINITE;
				arc[start][start+clo]=INFINITE;
				arc[start][start-1]=INFINITE;
			}else{//该点不是障碍点
				if(isObstacle(start+1)){//判断该点的右方点是否为障碍点
					arc[start][start+1]=INFINITE;
				}else{
					arc[start][start+1]=WEIGHT;
				}
				if(isObstacle(start-1)){//判断该点的左方点是否为障碍点
					arc[start][start-1]=INFINITE;
				}else{
					arc[start][start-1]=WEIGHT;
				}
				if(isObstacle(start-clo)){//判断该点的上方点是否为障碍点
					arc[start][start-clo]=INFINITE;
				}else{
					arc[start][start-clo]=WEIGHT;
				}
				if(isObstacle(start+clo)){//判断该点的下方点是否为障碍点
					arc[start][start+clo]=INFINITE;
				}else{
					arc[start][start+clo]=WEIGHT;
				}
			}
		}
        ++start;
    }
}
void MyDijkstra::printARC(){
	 cout << "\n图的邻接矩阵为：" << endl;
    int count_row = 0; //打印行的标签
    int count_col = 0; //打印列的标签
    //开始打印
	while (count_row != row*clo) {
        count_col = 0;
        while (count_col != row*clo) {
			if (arc[count_row][count_col] == INFINITE){
                cout << "∞" << " ";
			}else{
				cout << arc[count_row][count_col] << " ";
			}
            ++count_col;
        }
        cout << endl;
        ++count_row;
    }
}


void MyDijkstra::MyDijkstraAlgo(int begin){
	//首先初始化我们的dis数组
	int vexnum=clo*row;
	
	int i;
    for (i = 0; i <vexnum; i++) {
        //设置当前的路径
        dis[i].path = "V" + to_string(begin) + "-->V" + to_string(i);
        dis[i].value = arc[begin][i];
    }
    //设置起点的到起点的路径为0
    dis[begin].value = 0;
    dis[begin].visit = true;

    int count = 1;
    //计算剩余的顶点的最短路径（剩余this->vexnum-1个顶点）
    while (count != vexnum) {
        //temp用于保存当前dis数组中最小的那个下标
        //min记录的当前的最小值
        int temp=0;
        int min = INT_MAX;
        for (i = 0; i <vexnum; i++) {
            if (!dis[i].visit && dis[i].value<min) {
				min = dis[i].value;
                temp = i;
            }
        }
        //把temp对应的顶点加入到已经找到的最短路径的集合中
        dis[temp].visit = true;
        ++count;
        for (i = 0; i < vexnum; i++) {
            //注意这里的条件arc[temp][i]!=INT_MAX必须加，不然会出现溢出，从而造成程序异常
            if (!dis[i].visit && arc[temp][i]!=INT_MAX && (dis[temp].value + arc[temp][i]) < dis[i].value) {
                //如果新得到的边可以影响其他为访问的顶点，那就就更新它的最短路径和长度
                dis[i].value = dis[temp].value + arc[temp][i];
                dis[i].path = dis[temp].path + "-->V" + to_string(i + 1);
				dis[i].pathInfo.push_back(temp);//将路径经过的标号添加到容器中
            }
        }
    }
}
void MyDijkstra::printAllPath(int begin,int end) {
    string str;
    str = "V" + to_string(begin);
    cout << "以"<<str<<"为起点的图的最短路径为：" << endl;
    for (int i = 0; i <clo*row; i++) {
        if(dis[i].value!=INT_MAX){
			cout << dis[i].path << "=" << dis[i].value << endl;
		}else{
            cout << dis[i].path << "无最短路径" << endl;
        }
    }
	//起点到终点的路径为
	cout<<"\n=============================\n起始点到终点的路径如下所示：\n";
	if(dis[end].value!=INT_MAX){
		cout << dis[end].path << "=" << dis[end].value << endl;
	}else{
        cout << dis[end].path << "无最短路径" << endl;
    }
	cout<<"\n==============输出路径的标号===============\n";
	for (int i = 0; i < dis[end].pathInfo.size(); i++)
	{
		cout<<dis[end].pathInfo.at(i);
	}
	


}

