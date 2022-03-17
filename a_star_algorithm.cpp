#include <bits/stdc++.h>
using namespace std;
int calShortestPath(int src , int dest , int adjMat[14][14] , int distMat[14][14], bool visited[14])
{
//Function for calculation of shortest path between two nodes . Used in calculating heuristic value of nodes .
   if(src == dest)
   {
       return 0;
   }
   visited[src]=1;
   int ans=INT_MAX;
   for(int i=0;i<14;i++)
   {
       if(i!=src)
       {
           if(adjMat[src][i]==1&&!visited[i])
           {
               int curr = calShortestPath(i,dest,adjMat,distMat,visited);
            if (curr < INT_MAX) 
            {
 
                // Taking the minimum cost path
                ans = min(ans, distMat[src][i] + curr);
            }        
           }
       }
   }
   visited[src]=0;
   return ans;
}
void a_star_algorithm(int src,int dest,int adjMat[14][14],int distMat[14][14],bool visited[14],int heuristic[14])
{
    //A* search algorithm implementation 
    bool reachDest = false;
    int start = src;
    int parent[14],level[14];
    level[src]=0;
    vector <int> final_queue;
    list <pair <int,int> > open;
    list <pair <int,int> > closed;
    pair < int , int > p1;
    p1 = make_pair(distMat[src][src]+heuristic[src],src);
    open.push_back(p1);
    int sum = 0 ;
    
    while(!reachDest && open.empty() == false)
    {
        //sort(open.begin(),open.end());
        open.sort([](auto const& a, auto const& b) {
           return a.first < b.first;
       });
        pair < int , int > p2;
        p2 = open.front();
        open.pop_front();
        start = p2.second;
            for(auto it=closed.begin();it!=closed.end();it++)
            {
                 if(level[it->second]>=level[start])
                 {
                     pair<int,int>p3;
                     p3 = make_pair(it->first,it->second);
                     open.push_back(p3);
                     it=closed.erase(it);
                     
                 }
            }
         closed.push_back(p2);
        
        sum=p2.first-heuristic[p2.second];
        visited[start] = true ;
        if (start == dest)
        {
            reachDest = true;
            break;
        }
        for(int i=0;i<14;i++)
        {

               if(distMat[start][i]>0)
               {
                   if(visited[i]==false){     //if the child node is encountered for the first time 
                   pair < int , int > p4;
                   p4 = make_pair((distMat[start][i]+sum+heuristic[i]),i);
                   parent[i]=start;
                   level[i]=level[parent[i]]+1;
                   open.push_back(p4);
                   
                   visited[i]=true;
                   }
                   else{
                       for(auto it=open.begin();it!=open.end();it++)    //if child node is already present in open list 
                       {
                           if(it->second == i)
                           {
                               if(it->first >= distMat[start][i]+sum+heuristic[i])
                               {
                                   it->first = distMat[start][i]+sum+heuristic[i];
                                   parent[i]=start;
                                   level[i]=level[parent[i]]+1;
                               }
                           }
                       }
                       bool foundOpen = 0;
                       for(auto it=closed.begin();it!=closed.end();it++)  //if child node is present in closed list 
                       {
                           if(it->second == i)
                           {
                               if(it->first >= distMat[start][i]+sum+heuristic[i])
                               {
                                   
                                   it->first = distMat[start][i]+sum+heuristic[i];
                                   pair<int,int>p3;
                                   p3 = make_pair(it->first,it->second);
                                   open.push_back(p3);
                                  
                                   it=closed.erase(it);
                                   foundOpen = 1;
                               }
                           }
                       }
                       if(foundOpen)             
                       {
                            for(auto it=closed.begin();it!=closed.end();it++)
                         {
                           if(level[it->second] > 0)
                           {
                               pair<int,int>p5;
                               p5 = make_pair(it->first,it->second);
                               open.push_back(p5);
                               it=closed.erase(it);
                           }
                        }
                         parent[i]=start;
                         level[i]=level[parent[i]]-1;
                        
                       }


                       
                   }

                }

            
        }
        
    
    }
    if(!reachDest)
    {
        cout << "No optimal path exists" << endl;
    }
    else
    { 
        // displaying the path with the cost at each node in the optimal path 
        
        for (auto currentPair : closed)
       {
    
         pair<int, int> currentpair = currentPair;
         cout << currentPair.first << ' ' <<
            currentPair.second;
    
         cout << '\n';
  }
    }
    cout << endl;
    
}
int main()
{
    int adjMat[14][14]
        = { { 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0 },
            { 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0 },
            { 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0 },
            { 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1 },
            { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1 },
            { 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1 }
             };
    // 0th node for src and 13th node for dest
    // rest other nodes are checkpoints

    int distMat[14][14]
        = { { 0, 120, -1, -1, -1, -1, -1, 77, -1, 142, -1, -1, -1, -1 },
            { 120, 0, 113, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
            { -1, 113, 0, 72, -1, -1, -1, -1, -1, -1, -1, -1, -1,  -1 },
            { -1, -1, 72, 0, 77, -1, -1, -1, -1, -1, -1, -1, -1, -1  },
            { 0, -1, -1, 77, 0, 122, -1, -1, -1, -1, -1, -1, -1, -1 },
            { -1, -1, -1, -1, 122, 0, 126, -1, -1, -1, -1, -1, -1, -1 },
            { -1, -1, -1, -1, -1, 126, 0, -1, -1, -1, -1, 140, 148, -1},
            { 77, -1, -1, -1, -1, -1, -1, 0, 71, -1, -1, -1, -1, -1   },
            { -1, -1, -1, -1, -1, -1, -1, 71, 0, 122, -1, -1, -1, -1  },
            { 142, -1, -1, -1, -1, -1, -1, -1, 122, 0, 111, -1, 82, -1},
            { -1, -1, -1, -1, -1, -1, -1, -1, -1, 111, 0, -1, -1, 213 },
            { -1, -1, -1, -1, -1, -1, 140, -1, -1, -1, -1, 0, 99, 105 },
            { -1, -1, -1, -1, -1, -1, 148, -1, -1, 82, -1, 99, 0, -1  },
            { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 213, 105, -1, 0 }
             };
    bool visited[14] = { false };
    int shortestPath[14][14];
    int src=0,dest=13;
    for(int i=0;i<13;i++)
    {
        for(int j=i;j<14;j++)
        {
            bool visited_shortest[14]={0};
            shortestPath[i][j]=calShortestPath(i,j,adjMat,distMat,visited_shortest);
            shortestPath[j][i]=shortestPath[i][j];
        }
    }
    int heuristic[14] ;  
    //Calculation of heurisitic function 
    
    for(int i=0;i<14;i++)
    {
        
        if(i!=dest){
            heuristic[i]=0;
            for(int j=0;j<14;j++)
            {
                heuristic[i]=max(abs(shortestPath[i][j]-shortestPath[j][dest]),heuristic[i]);
            }
            
            
        }
        

    }   
    heuristic[dest]=0;
    a_star_algorithm(src,dest,adjMat,distMat,visited,heuristic);
    return 0;
}         
    