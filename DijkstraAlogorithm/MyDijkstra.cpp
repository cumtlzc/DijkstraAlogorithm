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
	//=======ͨ���Ѿ�������������б�Ȩͼ�Ĵ���========
	int vexnum;
	int edge;
	edge=2*clo*row-clo-row;//ȷ����ɢ��ͼ�бߵ�����
	vexnum=clo*row;

    //Ϊ�ڽӾ��󿪱ٿռ�͸���ֵ
    arc = new int*[vexnum];
    dis = new Dist[vexnum];
    for (int i = 0; i < vexnum; i++){
        arc[i] = new int[vexnum];
        for (int k = 0; k < vexnum; k++){
                arc[i][k] = INT_MAX;//�ڽӾ����ʼ��Ϊ�����
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
	cout<<"����ͼ��ʾ��Ϊ8*8�ĵ�ͼģ�ͣ�\n"
	<<"��ĸ.������õ�,"
	<<"��ĸO�����ϰ��㣬\n"
	<<"��ĸS������ʼ��,"
	<<"��ĸE������ֹ�㡣\n"
	<<"ԭ��ͼ���£�\n";
	cout<<"=============��ͼģ��============\n\n";
	for (int i = 0; i < row; i++){
		for (int j = 0; j < clo; j ++){
			cout<<Map[i][j]<<"\t";
		}
	cout<<"\n\n\n";
	}
	cout<<endl;
}
void MyDijkstra::printmatchMap(){
	cout<<"=============���ģ��============\n\n";
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
				//cout<<"�ϰ���ı�ţ�"<<clo*i+j+1<<endl;
				ObstacleStruct.ObstacleArr[0]=i;
				ObstacleStruct.ObstacleArr[1]=j;
				startEndStruct.obstacle.push_back(ObstacleStruct);
			}
		}
	}
	return startEndStruct;
}
int MyDijkstra::matchMap(int x,int y){
	return clo*x+y;//����ÿһ��Ԫ�ض�Ӧ�ı��
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
    int start=0;//������ı�ţ�ÿ�������㶼��Ӧ4��3��2����ֹ�㣬ѡ���һ������������չ
    /*
	//int end;//��ֹ��ı�ţ��ñ���������ı���ж�Ӧ�Ĺ�ϵ
    //int count = 0;
	//=======ͨ���Ѿ�������������б�Ȩͼ�Ĵ���========
	//int edge;
	//edge=2*clo*row-clo-row;//ȷ����ɢ��ͼ�бߵ�����
	*/
	while (start != clo*row) {
        /*cin >> start >> end >> weight;//�����жϱߵ���Ϣ�Ƿ�Ϸ�
        while (check_edge_value(start, end, weight)) {
            cout << "����ıߵ���Ϣ���Ϸ�������������" << endl;
            cin >> start >> end >> weight;
        }

		if(){//�ϰ�����Χ	
			arc[start - 1][end - 1] = INFINITE;//���ڽӾ����Ӧ�ϵĵ㸳ֵ
			arc[end - 1][start - 1] = INFINITE;//����ͼ��������д���

		}else{
			arc[start - 1][end - 1] = WEIGHT;//���ڽӾ����Ӧ�ϵĵ㸳ֵ
			arc[end - 1][start - 1] = WEIGHT;//����ͼ��������д���	
		}*/
		//�����ڽӾ���arc
		if (start==0){//�����������ŷֱ�Ϊstart+1,start+clo
			if(isObstacle(start)){//�õ�Ϊ�ϰ���
				arc[start][start+1]=INFINITE;
				arc[start][start+clo]=INFINITE;
			}else{//�õ㲻���ϰ���
				if(isObstacle(start+1)){//�жϸõ���ҷ����Ƿ�Ϊ�ϰ���
					arc[start][start+1]=INFINITE;
				}else{
					arc[start][start+1]=WEIGHT;
				}
				if(isObstacle(start+clo)){//�жϸõ���·����Ƿ�Ϊ�ϰ���
					arc[start][start+clo]=INFINITE;
				}else{
					arc[start][start+clo]=WEIGHT;
				}
			}	
		}else if(start==(clo-1)){
			//�����������ŷֱ�Ϊstart-1,start+clo
			if(isObstacle(start)){//�õ�Ϊ�ϰ���
				arc[start][start-1]=INFINITE;
				arc[start][start+clo]=INFINITE;
			}else{//�õ㲻���ϰ���
				if(isObstacle(start-1)){//�жϸõ���󷽵��Ƿ�Ϊ�ϰ���
					arc[start][start-1]=INFINITE;
				}else{
					arc[start][start-1]=WEIGHT;
				}
				if(isObstacle(start+clo)){//�жϸõ���·����Ƿ�Ϊ�ϰ���
					arc[start][start+clo]=INFINITE;
				}else{
					arc[start][start+clo]=WEIGHT;
				}
			}
		}else if(start==(clo*row-1)){
			//�����������ŷֱ�Ϊstart-1,start-clo
			if(isObstacle(start)){//�õ�Ϊ�ϰ���
				arc[start][start-1]=INFINITE;
				arc[start][start-clo]=INFINITE;
			}else{//�õ㲻���ϰ���
				if(isObstacle(start-1)){//�жϸõ���󷽵��Ƿ�Ϊ�ϰ���
					arc[start][start-1]=INFINITE;
				}else{
					arc[start][start-1]=WEIGHT;
				}
				if(isObstacle(start-clo)){//�жϸõ���Ϸ����Ƿ�Ϊ�ϰ���
					arc[start][start-clo]=INFINITE;
				}else{
					arc[start][start-clo]=WEIGHT;
				}
			}	
		}else if(start==(clo*row-clo-1)){
			//�����������ŷֱ�Ϊstart+1,start-clo
			if(isObstacle(start)){//�õ�Ϊ�ϰ���
				arc[start][start+1]=INFINITE;
				arc[start][start-clo]=INFINITE;
			}else{//�õ㲻���ϰ���
				if(isObstacle(start+1)){//�жϸõ���ҷ����Ƿ�Ϊ�ϰ���
					arc[start][start+1]=INFINITE;
				}else{
					arc[start][start+1]=WEIGHT;
				}
				if(isObstacle(start-clo)){//�жϸõ���Ϸ����Ƿ�Ϊ�ϰ���
					arc[start][start-clo]=INFINITE;
				}else{
					arc[start][start-clo]=WEIGHT;
				}
			}
		}else if(start%clo==0){
			//�����������ŷֱ�Ϊstart-clo,start+1,start+clo
			if(isObstacle(start)){//�õ�Ϊ�ϰ���
				arc[start][start+1]=INFINITE;
				arc[start][start-clo]=INFINITE;
				arc[start][start+clo]=INFINITE;
			}else{//�õ㲻���ϰ���
				if(isObstacle(start+1)){//�жϸõ���ҷ����Ƿ�Ϊ�ϰ���
					arc[start][start+1]=INFINITE;
				}else{
					arc[start][start+1]=WEIGHT;
				}
				if(isObstacle(start-clo)){//�жϸõ���Ϸ����Ƿ�Ϊ�ϰ���
					arc[start][start-clo]=INFINITE;
				}else{
					arc[start][start-clo]=WEIGHT;
				}
				if(isObstacle(start+clo)){//�жϸõ���·����Ƿ�Ϊ�ϰ���
					arc[start][start+clo]=INFINITE;
				}else{
					arc[start][start+clo]=WEIGHT;
				}
			}
		}else if(start/clo==0){
			//�����������ŷֱ�Ϊstart-1,start+clo,start+1
			if(isObstacle(start)){//�õ�Ϊ�ϰ���
				arc[start][start+1]=INFINITE;
				arc[start][start-1]=INFINITE;
				arc[start][start+clo]=INFINITE;
			}else{//�õ㲻���ϰ���
				if(isObstacle(start+1)){//�жϸõ���ҷ����Ƿ�Ϊ�ϰ���
					arc[start][start+1]=INFINITE;
				}else{
					arc[start][start+1]=WEIGHT;
				}
				if(isObstacle(start-1)){//�жϸõ���󷽵��Ƿ�Ϊ�ϰ���
					arc[start][start-1]=INFINITE;
				}else{
					arc[start][start-1]=WEIGHT;
				}
				if(isObstacle(start+clo)){//�жϸõ���·����Ƿ�Ϊ�ϰ���
					arc[start][start+clo]=INFINITE;
				}else{
					arc[start][start+clo]=WEIGHT;
				}
			}
		}else if((start+1)%clo==0){
			//�����������ŷֱ�Ϊstart-clo,start-1,start+clo
			if(isObstacle(start)){//�õ�Ϊ�ϰ���
				arc[start][start-1]=INFINITE;
				arc[start][start-clo]=INFINITE;
				arc[start][start+clo]=INFINITE;
			}else{//�õ㲻���ϰ���
				if(isObstacle(start-1)){//�жϸõ���󷽵��Ƿ�Ϊ�ϰ���
					arc[start][start-1]=INFINITE;
				}else{
					arc[start][start-1]=WEIGHT;
				}
				if(isObstacle(start-clo)){//�жϸõ���Ϸ����Ƿ�Ϊ�ϰ���
					arc[start][start-clo]=INFINITE;
				}else{
					arc[start][start-clo]=WEIGHT;
				}
				if(isObstacle(start+clo)){//�жϸõ���·����Ƿ�Ϊ�ϰ���
					arc[start][start+clo]=INFINITE;
				}else{
					arc[start][start+clo]=WEIGHT;
				}
			}
		}else if((start-(row-1)*clo>0)&&(start-(row-1)*clo)/clo==0){
			//�����������ŷֱ�Ϊstart-1,start-clo,start+1
			if(isObstacle(start)){//�õ�Ϊ�ϰ���
				arc[start][start+1]=INFINITE;
				arc[start][start-clo]=INFINITE;
				arc[start][start-1]=INFINITE;
			}else{//�õ㲻���ϰ���
				if(isObstacle(start+1)){//�жϸõ���ҷ����Ƿ�Ϊ�ϰ���
					arc[start][start+1]=INFINITE;
				}else{
					arc[start][start+1]=WEIGHT;
				}
				if(isObstacle(start-clo)){//�жϸõ���Ϸ����Ƿ�Ϊ�ϰ���
					arc[start][start-clo]=INFINITE;
				}else{
					arc[start][start-clo]=WEIGHT;
				}
				if(isObstacle(start-1)){//�жϸõ���󷽵��Ƿ�Ϊ�ϰ���
					arc[start][start-1]=INFINITE;
				}else{
					arc[start][start-1]=WEIGHT;
				}
			}
		}else{
			//�����ĸ����ŷֱ�Ϊstart-1,start-clo,start+1��start+clo
			if(isObstacle(start)){//�õ�Ϊ�ϰ���
				arc[start][start+1]=INFINITE;
				arc[start][start-clo]=INFINITE;
				arc[start][start+clo]=INFINITE;
				arc[start][start-1]=INFINITE;
			}else{//�õ㲻���ϰ���
				if(isObstacle(start+1)){//�жϸõ���ҷ����Ƿ�Ϊ�ϰ���
					arc[start][start+1]=INFINITE;
				}else{
					arc[start][start+1]=WEIGHT;
				}
				if(isObstacle(start-1)){//�жϸõ���󷽵��Ƿ�Ϊ�ϰ���
					arc[start][start-1]=INFINITE;
				}else{
					arc[start][start-1]=WEIGHT;
				}
				if(isObstacle(start-clo)){//�жϸõ���Ϸ����Ƿ�Ϊ�ϰ���
					arc[start][start-clo]=INFINITE;
				}else{
					arc[start][start-clo]=WEIGHT;
				}
				if(isObstacle(start+clo)){//�жϸõ���·����Ƿ�Ϊ�ϰ���
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
	 cout << "\nͼ���ڽӾ���Ϊ��" << endl;
    int count_row = 0; //��ӡ�еı�ǩ
    int count_col = 0; //��ӡ�еı�ǩ
    //��ʼ��ӡ
	while (count_row != row*clo) {
        count_col = 0;
        while (count_col != row*clo) {
			if (arc[count_row][count_col] == INFINITE){
                cout << "��" << " ";
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
	//���ȳ�ʼ�����ǵ�dis����
	int vexnum=clo*row;
	
	int i;
    for (i = 0; i <vexnum; i++) {
        //���õ�ǰ��·��
        dis[i].path = "V" + to_string(begin) + "-->V" + to_string(i);
        dis[i].value = arc[begin][i];
    }
    //�������ĵ�����·��Ϊ0
    dis[begin].value = 0;
    dis[begin].visit = true;

    int count = 1;
    //����ʣ��Ķ�������·����ʣ��this->vexnum-1�����㣩
    while (count != vexnum) {
        //temp���ڱ��浱ǰdis��������С���Ǹ��±�
        //min��¼�ĵ�ǰ����Сֵ
        int temp=0;
        int min = INT_MAX;
        for (i = 0; i <vexnum; i++) {
            if (!dis[i].visit && dis[i].value<min) {
				min = dis[i].value;
                temp = i;
            }
        }
        //��temp��Ӧ�Ķ�����뵽�Ѿ��ҵ������·���ļ�����
        dis[temp].visit = true;
        ++count;
        for (i = 0; i < vexnum; i++) {
            //ע�����������arc[temp][i]!=INT_MAX����ӣ���Ȼ�����������Ӷ���ɳ����쳣
            if (!dis[i].visit && arc[temp][i]!=INT_MAX && (dis[temp].value + arc[temp][i]) < dis[i].value) {
                //����µõ��ı߿���Ӱ������Ϊ���ʵĶ��㣬�Ǿ;͸����������·���ͳ���
                dis[i].value = dis[temp].value + arc[temp][i];
                dis[i].path = dis[temp].path + "-->V" + to_string(i + 1);
				dis[i].pathInfo.push_back(temp);//��·�������ı����ӵ�������
            }
        }
    }
}
void MyDijkstra::printAllPath(int begin,int end) {
    string str;
    str = "V" + to_string(begin);
    cout << "��"<<str<<"Ϊ����ͼ�����·��Ϊ��" << endl;
    for (int i = 0; i <clo*row; i++) {
        if(dis[i].value!=INT_MAX){
			cout << dis[i].path << "=" << dis[i].value << endl;
		}else{
            cout << dis[i].path << "�����·��" << endl;
        }
    }
	//��㵽�յ��·��Ϊ
	cout<<"\n=============================\n��ʼ�㵽�յ��·��������ʾ��\n";
	if(dis[end].value!=INT_MAX){
		cout << dis[end].path << "=" << dis[end].value << endl;
	}else{
        cout << dis[end].path << "�����·��" << endl;
    }
	cout<<"\n==============���·���ı��===============\n";
	for (int i = 0; i < dis[end].pathInfo.size(); i++)
	{
		cout<<dis[end].pathInfo.at(i);
	}
	


}

