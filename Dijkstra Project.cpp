#include <iostream>
#include <string>
#include <limits.h>
#include<fstream>
using namespace std;

#define Vertex 100

int getMinIndex(int distance[], bool lockedSet[], int nodes)  	//returns the minimum index to be locked
{
   int min = INT_MAX;
   int min_index;
    
   for (int v = 0; v < nodes; v++)
   {
		if (lockedSet[v] == false && distance[v] <= min)	
		{
			//lockedSet[v] == false => If node is not locked then move further
			//distance[v] <= min => finds the node having minimum distance so that it can be locked
			min = distance[v], min_index = v;
		}
   }
    
   return min_index;
}

int printResult(int distance[], int nodes)
{
	char ch;
	int n;
	cout<<"Vertex   Distance from Source\n";
	for (int i = 0; i < nodes; i++)
	{
		cout<<i<<" \t\t "<<distance[i]<<"\n";
	}
	cout<<"\nDo you want distance from source to any particular node (y/n) :  ";
	cin>>ch;
	if(ch == 'y' || ch == 'Y')
	{
		cout<<"\nEnter the destination node : ";
		cin>>n;
		cout<<"Shortest distance from source to node "<<n<<" is "<<distance[n];
	}
}

void dijkstra(int nodes, int graph[Vertex][Vertex], int source)
{
	int distance[nodes];  // keeps the data of distance from source to all nodes in respective index 
	bool lockedSet[nodes];  //becomes true when node is finalized or locked
	
	for (int i = 0; i < nodes; i++)
	{
		distance[i] = INT_MAX;		//Every index contain infinity distance initially because of INT_MAX
		lockedSet[i] = false;		//Initially all nodes are unlocked
	}
	
	distance[source] = 0;			
	
	for (int count = 0; count < nodes-1; count++) 		//nodes-1 shows last iteration contains only one unlocked node therefore no need of extra loop
	{
		int u = getMinIndex(distance, lockedSet, nodes);		//returns the minimum index to be locked
		
		lockedSet[u] = true;		//Index number "u" contain minimum distance therefore locked it by initialize true
		
		for (int v = 0; v < nodes; v++)
		{
			if (lockedSet[v]!=true && graph[u][v] !=0 && distance[u] != INT_MAX && distance[u]+graph[u][v] < distance[v])  
			{
				//lockedSet[v] shows if node is not locked then check the further condition
				//if graph[u][v] is not equal to zero means path exist (Not infinity) then check further condition
				//distance[u]+graph[u][v] < distance[v] => if current path is less than previous then move further 
				distance[v] = distance[u] + graph[u][v];
			}
		}
	}
	 
	printResult(distance, nodes);
}

int main()
{
	int nodes;
	int choice1;
	char choice,choice2;
	int source;
	int s,e,w,edges ;
	int mat, ed1,ed2,ed3, totalEdges;	// variables for filing
	cout<<"Enter the total nodes : ";
	cin>>nodes;
	int graph[Vertex][Vertex];
	for(int i=0; i<nodes; i++)
	{
		for(int j=0; j<nodes; j++)
		{
			graph[i][j];
		}
	}
	up:
	cout<<"\nEnter your choice for input : \n1- Console \n2- Filing\n";
	cin>>choice1;
	
	switch(choice1)
	{
		case 1:
			{
				start:
				cout<<"\nHow do you want to enter your graph ?\n";
				cout<<"\na- Using matrix \nb- Using edges \nEnter your choice : ";
				cin>>choice;
				switch(choice)
				{
					case 'a':
						cout<<"Enter the matrix : \n";
						for(int i=0; i<nodes; i++)
						{
							for(int j=0; j<nodes; j++)
							{
								cin>>graph[i][j];
							}
						}
						break;
					case 'b':
						cout<<"Enter the total number of edges : ";
						cin>>edges;
						for(int k=0; k<edges; k++)
						{
							cout<<"\nEnter the starting node , ending node and weight between them respectively : ";
							cin>>s>>e>>w ;
							graph[s][e] = w ;
							graph[e][s] = w ;
						}
						break;
					default:
						cout<<"Not correct choice !!!!! Enter again";
						goto start;
						break;
				}// end of switch 2 in console asking for matrix or edges
				break;
			}
		case 2:
			{
				start1:
				cout<<"\nHow do you want to enter your graph ?\n";
				cout<<"\na- Using matrix \nb- Using edges \nEnter your choice : ";
				cin>>choice2;
				switch(choice2)
				{
					case 'a':
						{
							ifstream myMatrix("matrix.txt");
							for(int i=0; i<nodes; i++)
							{
								for(int j=0; j<nodes; j++)
								{
									myMatrix>>mat;
									graph[i][j] = mat;
								}
							}
							myMatrix.close();
							break;
						}
					case 'b':
						{
							ifstream myedges("edges.txt");
							myedges>>totalEdges;
							for(int i=0; i<totalEdges; i++)
							{
								myedges >>ed1 >>ed2>> ed3;
								graph[ed1][ed2] = ed3;
								graph[ed2][ed1] = ed3;		
							}
							myedges.close();
							break;
						}
					default:
						cout<<"Not correct choice !!!!! Enter again";
						goto start1;
						break;
				}// end of switch 3 in filing asking for matrix or edges
				break;
			}
		default:
			cout<<"Not correct choice !!!!! Enter again";
			goto up;		//goto up => if choice is other except for filing or console
			break;
		
	} //end of switch 1 for filing or console
	
	
	
	cout<<"\nEnter the source node : ";
	cin>>source;
	dijkstra(nodes ,graph, source);
}
/*
	project made by 
	* Rahul kothari , Marium Jahan :-)
}*/
